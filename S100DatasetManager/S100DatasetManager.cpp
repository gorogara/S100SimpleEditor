// S100DatasetManager.cpp : 해당 DLL의 초기화 루틴을 정의합니다.
#include "stdafx.h"
#include "S100DatasetManager.h"

#include "GISLibrary\\ENC_S101_Factory.h"
#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\LayerManager.h"
#include "GISLibrary\\F_CodeWithNumericCode.h"
#include "GISLibrary\\F_ATTR.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\NewFeatureManager.h"
#include "GISLibrary\\NewInformationManager.h"
#include "GISLibrary\\R_InformationRecord.h"
#include "GISLibrary\\ATTR.h"
#include "GISLibrary\\F_FASC.h"
#include "GISLibrary\\F_INAS.h"
#include "GISLibrary\\CodeWithNumericCode.h"


#include "..\\FeatureCatalog\\FeatureCatalogue.h"

#include "..\\S100DatasetGML\\S100GML_Dataset.h"
#include "..\\S100DatasetGML\\S100GML_InformationType.h"
#include "..\\S100DatasetGML\\S100GML_FeatureType.h"
#include "..\\S100DatasetGML\\S100GML_Geometry.h"

#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"




#include <list>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif                         

BEGIN_MESSAGE_MAP(CS100DatasetManagerApp, CWinApp)
END_MESSAGE_MAP() 
CS100DatasetManagerApp::CS100DatasetManagerApp()
{  
}   

BOOL CS100DatasetManagerApp::InitInstance()
{
	CWinApp::InitInstance();

	return true;
}

void SetNewFeatureGeometryFromGMLFeature(int pointAdjustment_X, int pointAdjustment_Y, int pointAdjustment_Z, S100DatasetGML::S100GML_FeatureType* gml_feature, NewFeatureManager &nfm)
{
	if (!gml_feature->geometry)
	{
		nfm.m_geometryType = 255;
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"GMLfile Dataset S100GML_FeatureType is null", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::DataSet);
		return;
	}

	int cmfx = (int)((S101Cell*)nfm.m_cell)->m_dsgir.m_dssi.m_cmfx;
	int cmfy = (int)((S101Cell*)nfm.m_cell)->m_dsgir.m_dssi.m_cmfy;

	nfm.m_geometryType = gml_feature->geometry->GetType();
	switch (gml_feature->geometry->GetType())
	{
	case 1:
	{
		nfm.m_geometryType = 1;
		S100DatasetGML::S100GML_Geometry* geo = gml_feature->geometry;
		std::list<S100DatasetGML::GMLPoint> list = geo->GetCoordinates();

		nfm.m_addFeaturePoint.x = list.begin()->x / cmfx * pointAdjustment_X;
		nfm.m_addFeaturePoint.y = list.begin()->y / cmfy * pointAdjustment_Y;

		break;
	}
	case 2:
	{
		nfm.m_geometryType = 2;
		S100DatasetGML::S100GML_Geometry* geo = gml_feature->geometry;
		std::list<S100DatasetGML::GMLPoint> list = geo->GetCoordinates();

		for (auto itor = list.begin(); itor != list.end(); itor++)
		{
			PointD p;
			p.x = itor->x / cmfx * pointAdjustment_X;
			p.y = itor->y / cmfy * pointAdjustment_Y;
			nfm.m_addFeaturePoints.push_back(p);
		}
		break;
	}
	case 3:
	{
		nfm.m_geometryType = 3;
		S100DatasetGML::S100GML_Geometry* geo = gml_feature->geometry;
		std::list<std::list<S100DatasetGML::GMLPoint>> listOfPointList = geo->GetCoordinatesInSurface();

		PointD p;
		for (auto itor = listOfPointList.begin(); itor != listOfPointList.end(); itor++)
		{
			std::list<S100DatasetGML::GMLPoint> *list = &(*itor);
			if (itor == listOfPointList.begin())
			{
				for (auto itor2 = list->begin(); itor2 != list->end(); itor2++)
				{
					S100DatasetGML::GMLPoint *gp = &(*itor2);
					p.x = gp->x / cmfx * pointAdjustment_X;
					p.y = gp->y / cmfy * pointAdjustment_Y;
					nfm.m_addFeaturePoints.push_back(p);
				}

			}
			else
			{
				std::vector<PointD> vp;
				for (auto itor2 = list->begin(); itor2 != list->end(); itor2++)
				{
					S100DatasetGML::GMLPoint *gp = &(*itor2);
					p.x = gp->x / cmfx * pointAdjustment_X;
					p.y = gp->y / cmfy * pointAdjustment_Y;
					vp.push_back(p);
				}
				nfm.m_addFeatureInnerCirclePointsList.push_back(vp);
			}
		}
		break;
	}
	}
}

void SetNewAttributeFromGMLAttribute(S101Cell* cell, S100DatasetGML::S100GML_Attribute* gml_attr, F_ATTR *f_attr, int parentATTR = 0)
{
	auto fi = cell->m_dsgir.m_atcs->m_arrFindForCode.find(gml_attr->camelCase);
	if (fi == cell->m_dsgir.m_atcs->m_arrFindForCode.end())
	{
		return;
	}

	ATTR *attr = new ATTR();
	f_attr->m_arr.push_back(attr);

	attr->m_natc = fi->second->m_nmcd;//ENC_S101_Factory::GetATCS(this, L"speed");
	attr->m_atix = 1;
	attr->m_paix = parentATTR;
	attr->m_atin = 1;

	int parentIndex = f_attr->m_arr.size();
	for (auto aitor = gml_attr->childAttr.begin(); aitor != gml_attr->childAttr.end(); aitor++)
	{
		S100DatasetGML::S100GML_Attribute *gattr = &(*aitor);

		SetNewAttributeFromGMLAttribute(cell, gattr, f_attr, parentIndex);
	}
	
	auto catalog =  cell->GetS100Layer()->GetFC(); 
	SimpleAttribute* sa = catalog->m_pCatalogueList.begin()->second->GetSimpleAttribute(std::wstring(fi->second->m_code));

	if (sa)
	{
		wstring value;
											
		if (sa->valueType.valueString.compare(L"enumeration") == 0)
		{ 
			std::unordered_map<int, ListedValue>* lvs = &(*sa->listedValues.begin()).listedValue;
			for (auto itor = lvs->begin(); itor != lvs->end(); itor++)
			{
				ListedValue* lv = &itor->second;  
				if (lv->label.compare(gml_attr->value) == 0)
				{
					value = to_wstring(lv->code.GetvalueInteger());
					break;
				}
			}
		}
		else
		{
			value = gml_attr->value.c_str();
		}
		attr->m_atvl = value.c_str();
	}
	else
	{
		attr->m_atvl = gml_attr->value.c_str();
	}
}  
void SetFeatureToFeatureAssociation(S101Cell* cell, R_FeatureRecord* orgFr, R_FeatureRecord* objFr)
{
	if (!cell || !orgFr || !objFr)
	{
		return;
	}

	S101Layer* layer = (S101Layer*)cell->m_pLayer;
	FeatureCatalogue* fc = layer->GetFC()->m_pCatalogueList.begin()->second;

	auto objFtItor = cell->m_dsgir.m_ftcs->m_arr.find(objFr->m_frid.m_nftc);
	if (objFtItor == cell->m_dsgir.m_ftcs->m_arr.end())
	{
		return;
	}
	wstring objFeatureName = objFtItor->second->m_code;

	auto orgFtItor = cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
	if (orgFtItor == cell->m_dsgir.m_ftcs->m_arr.end())
	{
		return;
	}
	wstring orgFeatureName = orgFtItor->second->m_code;

	FeatureType* objFT = &(fc->featureTypes.featureType.find(objFeatureName)->second);
	auto objFBItor = objFT->featureBinding.find(orgFeatureName);
	if (objFBItor == objFT->featureBinding.end())
	{
		return;
	}
	FeatureBinding* objFB = &objFBItor->second;

	FeatureType* orgFT = &(fc->featureTypes.featureType.find(orgFeatureName)->second);
	auto orgFBItor = orgFT->featureBinding.find(objFeatureName);
	if (orgFBItor == orgFT->featureBinding.end())
	{
		return;
	}
	FeatureBinding* orgFB = &orgFBItor->second; 
	wstring objAssociationName = objFB->association.Getvalue();
	if (objAssociationName.compare(L"") == 0)
	{
		for (auto itor = objFB->association.GetattributesPointer()->begin();
			itor != objFB->association.GetattributesPointer()->end();
			itor++)
		{
			XML_Attribute* attr = &(*itor);
			if (attr->Getname().compare(L"ref") == 0)
			{
				objAssociationName = attr->Getvalue();
			}
		}
	}

	wstring objRoleName = objFB->role.Getvalue();
	if (objRoleName.compare(L"") == 0)
	{
		for (auto itor = objFB->role.GetattributesPointer()->begin();
			itor != objFB->role.GetattributesPointer()->end();
			itor++)
		{
			XML_Attribute* attr = &(*itor);
			if (attr->Getname().compare(L"ref") == 0)
			{
				objRoleName = attr->Getvalue();
			}
		}
	}

	if (!cell->m_dsgir.m_facs)
	{
		cell->m_dsgir.m_facs = new F_CodeWithNumericCode();
	}
	if (!cell->m_dsgir.m_arcs)
	{
		cell->m_dsgir.m_arcs = new F_CodeWithNumericCode();
	}

	F_FASC* objF_AFSC = new F_FASC();
	objF_AFSC->m_name.RCID = orgFr->m_frid.m_name.RCID;
	objF_AFSC->m_name.RCNM = orgFr->m_frid.m_name.RCNM;
	objF_AFSC->m_nfac = ENC_S101_Factory::GetFACS(cell, objAssociationName);
	objF_AFSC->m_narc = ENC_S101_Factory::GetARCS(cell, objRoleName);
	objF_AFSC->m_faui = 1;

	objFr->m_fasc.push_back(objF_AFSC);

	wstring orgAssociationName = orgFB->association.Getvalue();
	if (orgAssociationName.compare(L"") == 0)
	{
		for (auto itor = orgFB->association.GetattributesPointer()->begin();
			itor != orgFB->association.GetattributesPointer()->end();
			itor++)
		{
			XML_Attribute* attr = &(*itor);
			if (attr->Getname().compare(L"ref") == 0)
			{
				orgAssociationName = attr->Getvalue();
			}
		}
	}

	wstring orgRoleName = orgFB->role.Getvalue();
	if (orgRoleName.compare(L"") == 0)
	{
		for (auto itor = orgFB->role.GetattributesPointer()->begin();
			itor != orgFB->role.GetattributesPointer()->end();
			itor++)
		{
			XML_Attribute* attr = &(*itor);
			if (attr->Getname().compare(L"ref") == 0)
			{
				orgRoleName = attr->Getvalue();
			}
		}
	}

	F_FASC* orgF_AFSC = new F_FASC();
	orgF_AFSC->m_name.RCID = objFr->m_frid.m_name.RCID;
	orgF_AFSC->m_name.RCNM = objFr->m_frid.m_name.RCNM;
	orgF_AFSC->m_nfac = ENC_S101_Factory::GetFACS(cell, orgAssociationName);
	orgF_AFSC->m_narc = ENC_S101_Factory::GetARCS(cell, orgRoleName);
	orgF_AFSC->m_faui = 1;

	orgFr->m_fasc.push_back(orgF_AFSC);
}


void SetFeatureToInformationAssociation(S101Cell* cell, R_FeatureRecord* orgFr, R_InformationRecord* objIr)
{
	S101Layer* layer = (S101Layer*)cell->m_pLayer;
	FeatureCatalogue* fc = layer->GetFC()->m_pCatalogueList.begin()->second;

	auto objItItor = cell->m_dsgir.m_itcs->m_arr.find(objIr->m_irid.m_nitc);
	if (objItItor == cell->m_dsgir.m_itcs->m_arr.end())  return;
	wstring objInformationName = objItItor->second->m_code;

	auto orgFtItor = cell->m_dsgir.m_ftcs->m_arr.find(orgFr->m_frid.m_nftc);
	if (orgFtItor == cell->m_dsgir.m_ftcs->m_arr.end())  return;
	wstring orgFeatureName = orgFtItor->second->m_code;

	FeatureType* orgFT = &(fc->featureTypes.featureType.find(orgFeatureName)->second);

	auto orgFBItor = orgFT->informationBinding.find(objInformationName);
	if (orgFBItor == orgFT->informationBinding.end())		return;
	InformationBinding* orgFB = &orgFBItor->second; 
	wstring orgAssociationName = orgFB->association.Getvalue();
	if (orgAssociationName.compare(L"") == 0)
	{
		for (auto itor = orgFB->association.GetattributesPointer()->begin();
			itor != orgFB->association.GetattributesPointer()->end();
			itor++)
		{
			XML_Attribute* attr = &(*itor);
			if (attr->Getname().compare(L"ref") == 0)
			{
				orgAssociationName = attr->Getvalue();
			}
		}
	}

	wstring orgRoleName = orgFB->role.Getvalue();
	if (orgRoleName.compare(L"") == 0)
	{
		for (auto itor = orgFB->role.GetattributesPointer()->begin();
			itor != orgFB->role.GetattributesPointer()->end();
			itor++)
		{
			XML_Attribute* attr = &(*itor);
			if (attr->Getname().compare(L"ref") == 0)
			{
				orgRoleName = attr->Getvalue();
			}
		}
	}

	F_INAS* orgF_INAS = new F_INAS();
	orgF_INAS->m_name.RCID = objIr->m_irid.m_name.RCID;
	orgF_INAS->m_name.RCNM = objIr->m_irid.m_name.RCNM;
	orgF_INAS->m_niac = ENC_S101_Factory::GetIACS(cell, orgAssociationName);
	orgF_INAS->m_narc = ENC_S101_Factory::GetARCS(cell, orgRoleName);
	orgF_INAS->m_iuin = 1;

	orgFr->m_inas.push_back(orgF_INAS);
}


void SetInformationToInformationAssociation(S101Cell* cell, R_InformationRecord* orgIr, R_InformationRecord* objIr)
{
	S101Layer* layer = (S101Layer*)cell->m_pLayer;
	FeatureCatalogue* fc = layer->GetFC()->m_pCatalogueList.begin()->second;

	auto objItItor = cell->m_dsgir.m_itcs->m_arr.find(objIr->m_irid.m_nitc);
	if (objItItor == cell->m_dsgir.m_itcs->m_arr.end())  return;
	wstring objInforamtionName = objItItor->second->m_code;

	auto orgItItor = cell->m_dsgir.m_itcs->m_arr.find(orgIr->m_irid.m_nitc);
	if (orgItItor == cell->m_dsgir.m_itcs->m_arr.end())  return;
	wstring orgInformationName = orgItItor->second->m_code;

	InformationType* objIT = fc->GetInformationType(objInforamtionName);
	auto objIBItor = objIT->informationBinding.find(orgInformationName);
	if (objIBItor == objIT->informationBinding.end())		return;
	InformationBinding* objIB = &objIBItor->second;

	InformationType* orgIT = fc->GetInformationType(orgInformationName);
	auto orgIBItor = orgIT->informationBinding.find(objInforamtionName);
	if (orgIBItor == orgIT->informationBinding.end())		return;
	InformationBinding* orgIB = &orgIBItor->second; 

	wstring objAssociationName = objIB->association.Getvalue();
	if (objAssociationName.compare(L"") == 0)
	{
		for (auto itor = objIB->association.GetattributesPointer()->begin();
			itor != objIB->association.GetattributesPointer()->end();
			itor++)
		{
			XML_Attribute* attr = &(*itor);
			if (attr->Getname().compare(L"ref") == 0)
			{
				objAssociationName = attr->Getvalue();
			}
		}
	}

	wstring objRoleName = objIB->role.Getvalue();
	if (objRoleName.compare(L"") == 0)
	{
		for (auto itor = objIB->role.GetattributesPointer()->begin();
			itor != objIB->role.GetattributesPointer()->end();
			itor++)
		{
			XML_Attribute* attr = &(*itor);
			if (attr->Getname().compare(L"ref") == 0)
			{
				objRoleName = attr->Getvalue();
			}
		}
	}

	F_INAS* objF_INAS = new F_INAS();
	objF_INAS->m_name.RCID = orgIr->m_irid.m_name.RCID;
	objF_INAS->m_name.RCNM = orgIr->m_irid.m_name.RCNM;
	objF_INAS->m_niac = ENC_S101_Factory::GetIACS(cell, objAssociationName);
	objF_INAS->m_narc = ENC_S101_Factory::GetARCS(cell, objRoleName);
	objF_INAS->m_iuin = 1;

	objIr->m_inas.push_back(objF_INAS);


	wstring orgAssociationName = orgIB->association.Getvalue();
	if (orgAssociationName.compare(L"") == 0)
	{
		for (auto itor = orgIB->association.GetattributesPointer()->begin();
			itor != orgIB->association.GetattributesPointer()->end();
			itor++)
		{
			XML_Attribute* attr = &(*itor);
			if (attr->Getname().compare(L"ref") == 0)
			{
				orgAssociationName = attr->Getvalue();
			}
		}
	}


	wstring orgRoleName = orgIB->role.Getvalue();
	if (orgRoleName.compare(L"") == 0)
	{
		for (auto itor = orgIB->role.GetattributesPointer()->begin();
			itor != orgIB->role.GetattributesPointer()->end();
			itor++)
		{
			XML_Attribute* attr = &(*itor);
			if (attr->Getname().compare(L"ref") == 0)
			{
				orgRoleName = attr->Getvalue();
			}
		}
	}

	F_INAS* orgF_INAS = new F_INAS();
	orgF_INAS->m_name.RCID = objIr->m_irid.m_name.RCID;
	orgF_INAS->m_name.RCNM = objIr->m_irid.m_name.RCNM;
	orgF_INAS->m_niac = ENC_S101_Factory::GetIACS(cell, orgAssociationName);
	orgF_INAS->m_narc = ENC_S101_Factory::GetARCS(cell, orgRoleName);
	orgF_INAS->m_iuin = 1;

	orgIr->m_inas.push_back(orgF_INAS);
} 
void SetNewFeatureAssociationFromGMLAssociation(Catalog* catalog, S101Cell* cell, R_FeatureRecord* fr, S100DatasetGML::S100GML_Dataset* gml_dataset,  S100DatasetGML::S100GML_Association* gml_as)
{ 
	auto fi = cell->m_dsgir.m_arcs->m_arrFindForCode.find(gml_as->tag);

	if (fi != cell->m_dsgir.m_arcs->m_arrFindForCode.end())
	{
		auto fc = catalog->m_pCatalogueList.begin()->second;
		auto id = gml_as->href.substr(1, gml_as->href.size() - 1);
		auto associatedFeatureIter = gml_dataset->features.find(id);
		
		auto associatedInformationIter = gml_dataset->informations.find(id);

		if (associatedFeatureIter != gml_dataset->features.end())
		{
			auto associatedFeature = associatedFeatureIter->second;
			SetFeatureToFeatureAssociation(cell, fr, associatedFeature->fr);
		}

		if (associatedInformationIter != gml_dataset->informations.end())
		{
			auto associatedInformation = associatedInformationIter->second;
			SetFeatureToInformationAssociation(cell, fr, associatedInformation->ir);
		}
	}
}

void SetNewInformationAssociationFromGMLAssociation(Catalog* catalog, S101Cell* cell, R_InformationRecord* ir, S100DatasetGML::S100GML_Dataset* gml_dataset, S100DatasetGML::S100GML_Association* gml_as)
{ 
	auto fi = cell->m_dsgir.m_arcs->m_arrFindForCode.find(gml_as->tag);
	if (fi != cell->m_dsgir.m_arcs->m_arrFindForCode.end())
	{
		auto fc = catalog->m_pCatalogueList.begin()->second;
		auto id = gml_as->href.substr(1, gml_as->href.size() - 1);
		auto associatedInformationIter = gml_dataset->informations.find(id);

		if (associatedInformationIter != gml_dataset->informations.end())
		{
			auto associatedInformation = associatedInformationIter->second;  
			SetInformationToInformationAssociation(cell, ir, associatedInformation->ir);
		}
	}
} 
S101Layer* S100DatasetMgr::CreateSENCFromGML(Catalog* catalog, PortrayalCatalogue* portrayalCatalog, S100DatasetGML::S100GML_Dataset* dataset)
{
	S101Layer* layer = new S101Layer(catalog, portrayalCatalog);

	S100DatasetGML::S100GML_Attribute* gmlAttr;

	auto fitor = dataset->attribute.find(L"DatasetIdentificationInformation");
	wstring attrValue = L"S100 Dataset";
	if (fitor == dataset->attribute.end())
	{
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"GMLfile DatasetIdentificationInformation is null", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::DataSet);
	}
	else
	{
		gmlAttr = &(fitor->second);
		for (auto itor = gmlAttr->childAttr.begin(); itor != gmlAttr->childAttr.end(); itor++)
		{
			S100DatasetGML::S100GML_Attribute* attr = &(*itor);
			if (attr->camelCase.compare(L"S100:datasetFileIdentifier") == 0)
			{
				attrValue = attr->value;
			}
		}
	}

	layer->m_spatialObject = ENC_S101_Factory::CreateEmptyFileByCatalog(catalog, attrValue);
	layer->m_spatialObject->m_pLayer = layer;

	S101Cell* newCell = (S101Cell*)layer->m_spatialObject;
	newCell->m_dsgir.m_dsid.m_dstc.RemoveAll();  
	if (dataset->gml_namespace.size() > 0)
	{
		newCell->gml_namespace = new std::unordered_map<std::wstring, std::wstring>();
		for each (auto value in dataset->gml_namespace)
		{
			newCell->gml_namespace->insert({ value.first ,value.second });
		}
	}

	if (dataset->attribute.find(L"DatasetIdentificationInformation") ==
		dataset->attribute.end())
	{
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"GMLfile DatasetIdentificationInformation is null", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::DataSet);

		newCell->m_dsgir.m_dsid.m_ensp = L"S-100 Part 10a";
		newCell->m_dsgir.m_dsid.m_ened = L"1.1";
		newCell->m_dsgir.m_dsid.m_prsp = L"INT.IHO.S-101.1.0";
		newCell->m_dsgir.m_dsid.m_pred = L"1.0";
		newCell->m_dsgir.m_dsid.m_prof = L"1";
		newCell->m_dsgir.m_dsid.m_dsnm = L"";
		newCell->m_dsgir.m_dsid.m_dstl = L"Default";
		newCell->m_dsgir.m_dsid.m_dsrd = L"2000-00-00";
		newCell->m_dsgir.m_dsid.m_dslg = L"EN";
	}
	else
	{
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"DatasetIdentificationInformation child value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);

		gmlAttr = &(dataset->attribute.find(L"DatasetIdentificationInformation")->second);

		for (auto itor = gmlAttr->childAttr.begin(); itor != gmlAttr->childAttr.end(); itor++)
		{
			S100DatasetGML::S100GML_Attribute* attr = &(*itor);

			if (attr->camelCase.compare(L"S100:encodingSpecification") == 0)
			{
				newCell->m_dsgir.m_dsid.m_ensp = attr->value.c_str();
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:encodingSpecification value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:encodingSpecificationEdition") == 0)
			{
				newCell->m_dsgir.m_dsid.m_ened = attr->value.c_str();
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:encodingSpecificationEdition value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:productIdentifier") == 0)
			{
				newCell->m_dsgir.m_dsid.m_prsp = attr->value.c_str();
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:productIdentifier value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:productEdition") == 0)
			{
				newCell->m_dsgir.m_dsid.m_pred = attr->value.c_str();
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:productEdition value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:applicationProfile") == 0)
			{
				newCell->m_dsgir.m_dsid.m_prof = attr->value.c_str();
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:applicationProfile value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:datasetFileIdentifier") == 0)
			{
				newCell->m_dsgir.m_dsid.m_dsnm = attr->value.c_str();
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:datasetFileIdentifier value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:datasetTitle") == 0)
			{
				newCell->m_dsgir.m_dsid.m_dstl = attr->value.c_str();
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:datasetTitle value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:datasetReferenceDate") == 0)
			{
				newCell->m_dsgir.m_dsid.m_dsrd = attr->value.c_str();
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:datasetReferenceDate value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:datasetLanguage") == 0)
			{
				newCell->m_dsgir.m_dsid.m_dslg = attr->value.c_str();
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:datasetLanguage value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:datasetAbstract") == 0)
			{
				newCell->m_dsgir.m_dsid.m_dsab = attr->value.c_str();
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:datasetLanguage value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:datasetEdition") == 0)
			{
				newCell->m_dsgir.m_dsid.m_dsed = attr->value.c_str();
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:datasetLanguage value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:datasetTopicCategory") == 0)
			{
				newCell->m_dsgir.m_dsid.m_dstc.Add(ENC_S101_Factory::GetofTopicCategoriesFromAcronym(attr->value));
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:datasetTopicCategory value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
		}
	}

	if (dataset->attribute.find(L"DatasetStructureInformation") == dataset->attribute.end())
	{
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"GMLfile DatasetStructureInformation is null", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::DataSet);

		newCell->m_dsgir.m_dssi.m_dcox = 0.0;
		newCell->m_dsgir.m_dssi.m_dcoy = 0.0;
		newCell->m_dsgir.m_dssi.m_dcoz = 0.0;
		newCell->m_dsgir.m_dssi.m_cmfx = 1;
		newCell->m_dsgir.m_dssi.m_cmfy = 1;
		newCell->m_dsgir.m_dssi.m_cmfz = 1;
	}
	else
	{
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:DatasetStructureInformation childvalue Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
		gmlAttr = &(dataset->attribute.find(L"DatasetStructureInformation")->second);

		for (auto itor = gmlAttr->childAttr.begin(); itor != gmlAttr->childAttr.end(); itor++)
		{
			S100DatasetGML::S100GML_Attribute* attr = &(*itor);

			if (attr->camelCase.compare(L"S100:datasetCoordOriginX") == 0)
			{
				newCell->m_dsgir.m_dssi.m_dcox = _wtof(attr->value.c_str());
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:datasetCoordOriginX value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:datasetCoordOriginY") == 0)
			{
				newCell->m_dsgir.m_dssi.m_dcoy = _wtof(attr->value.c_str());
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:datasetCoordOriginY value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:datasetCoordOriginZ") == 0)
			{
				newCell->m_dsgir.m_dssi.m_dcoz = _wtof(attr->value.c_str());
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:datasetCoordOriginZ value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:coordMultFactorX") == 0)
			{
				newCell->m_dsgir.m_dssi.m_cmfx = _wtoi(attr->value.c_str());
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:coordMultFactorX value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:coordMultFactorY") == 0)
			{
				newCell->m_dsgir.m_dssi.m_cmfy = _wtoi(attr->value.c_str());
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:coordMultFactorY value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
			else if (attr->camelCase.compare(L"S100:coordMultFactorZ") == 0)
			{
				newCell->m_dsgir.m_dssi.m_cmfz = _wtoi(attr->value.c_str());
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100:coordMultFactorZ value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
			}
		}
	}  
	int pointAdjustment_X = 1;
	int pointAdjustment_Y = 1;
	int pointAdjustment_Z = 1;

	if (newCell->m_dsgir.m_dssi.m_cmfx < 10000000)
	{
		pointAdjustment_X = 10000000 / newCell->m_dsgir.m_dssi.m_cmfx;
		newCell->m_dsgir.m_dssi.m_cmfx = 10000000;
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"Xposition value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
	}

	if (newCell->m_dsgir.m_dssi.m_cmfy < 10000000)
	{
		pointAdjustment_Y = 10000000 / newCell->m_dsgir.m_dssi.m_cmfy;
		newCell->m_dsgir.m_dssi.m_cmfy = 10000000;
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"Yposition value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
	}

	if (newCell->m_dsgir.m_dssi.m_cmfz < 100)
	{
		pointAdjustment_Z = 100 / newCell->m_dsgir.m_dssi.m_cmfz;
		newCell->m_dsgir.m_dssi.m_cmfz = 100;
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"Zposition value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
	}

	for (auto itor = dataset->features.begin(); itor != dataset->features.end(); itor++)
	{
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"Zposition value Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
		S100DatasetGML::S100GML_FeatureType* gf = itor->second;

		auto colonItor = gf->camelCase.find_last_of(L":");

		wstring camelcase = gf->camelCase.substr(++colonItor);

		NewFeatureManager nfm;
		nfm.m_cell = newCell;

		auto fi = newCell->m_dsgir.m_ftcs->m_arrFindForCode.find(camelcase);
		if (fi == newCell->m_dsgir.m_ftcs->m_arrFindForCode.end())
		{
			continue;
		}

		CodeWithNumericCode* code = fi->second;
		nfm.m_featureType = code->m_nmcd;
		SetNewFeatureGeometryFromGMLFeature(pointAdjustment_X, pointAdjustment_Y, pointAdjustment_Z, gf, nfm);

		R_FeatureRecord* fr = ENC_S101_Factory::CreateFeature(&nfm);
		if (fr == nullptr)
		{
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_WARNING, L"failed to create feature", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::DataSet); 
			continue; 
		}

		newCell->m_feaMap.SetAt(fr->m_frid.m_name.GetName(), fr);

		F_ATTR* attrField = new F_ATTR();
		fr->m_attr.push_back(attrField);

		for (auto aitor = gf->attribute.begin(); aitor != gf->attribute.end(); aitor++)
		{
			S100DatasetGML::S100GML_Attribute *gattr = &(*aitor);
			SetNewAttributeFromGMLAttribute(newCell, gattr, attrField);
		}

		gf->fr = fr;          
	}

	for (auto itor = dataset->informations.begin(); itor != dataset->informations.end(); itor++)
	{
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"informationType record Set ", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::DataSet);
		S100DatasetGML::S100GML_InformationType* infor = itor->second;

		auto colonItor = infor->camelCase.find_last_of(L":");
		wstring camelcase = infor->camelCase.substr(++colonItor);
		
		infor->id;

		NewInformationManager ifm;
		ifm.m_cell = newCell;

		auto fi = newCell->m_dsgir.m_itcs->m_arrFindForCode.find(camelcase);
		if (fi == newCell->m_dsgir.m_itcs->m_arrFindForCode.end())
		{
			continue;
		}

		CodeWithNumericCode* code = fi->second;
		ifm.m_informationType = code->m_nmcd;
		
		R_InformationRecord* r = ENC_S101_Factory::CreateInformation(&ifm);
		if (r == nullptr)
		{
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_WARNING, L"informationRecord Setting Failed", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::DataSet);
			continue; 
		}
		newCell->m_infMap.SetAt(r->m_irid.m_name.GetName(), r);

		F_ATTR* attrField = new F_ATTR();
		r->m_attr.push_back(attrField);

		for (auto attr = infor->attribute.begin(); attr != infor->attribute.end(); attr++)
		{
			S100DatasetGML::S100GML_Attribute *gattr = &(*attr);
			SetNewAttributeFromGMLAttribute(newCell, gattr, attrField);
		}


		infor->ir = r;     
	}

	for (auto itor = dataset->features.begin(); itor != dataset->features.end(); itor++)
	{
		S100DatasetGML::S100GML_FeatureType* gf = itor->second;        
		for (auto asitor = gf->association.begin(); asitor != gf->association.end(); asitor++)
		{
			S100DatasetGML::S100GML_Association* gas = &(*asitor);
			SetNewFeatureAssociationFromGMLAssociation(catalog, newCell, gf->fr, dataset, gas);
		}
	}

	for (auto itor = dataset->informations.begin(); itor != dataset->informations.end(); itor++)
	{
		S100DatasetGML::S100GML_InformationType* infoType = itor->second;
		auto colonItor = infoType->camelCase.find_last_of(L":");
		wstring camelcase = infoType->camelCase.substr(++colonItor);         
		for (auto asitor = infoType->association.begin(); asitor != infoType->association.end(); asitor++)
		{
			S100DatasetGML::S100GML_Association* gas = &(*asitor);
			SetNewInformationAssociationFromGMLAssociation(catalog, newCell, infoType->ir, dataset, gas);
		}
	}

	newCell->MakeFullSpatialData();
	newCell->CalcMBR(); 

	KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"GML DATASET CLEAR", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::DataSet);
	return layer;

}