// CDialogExCreateLayersub.cpp: 구현 파일 
#include "stdafx.h" 
#include "CDialogExCreateLayersub.h"
#include "afxdialogex.h"

#include "GISLibrary\\S101Cell.h"
#include "GISLibrary\\Layer.h"
#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\R_InformationRecord.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\F_ATTR.h"
#include "GISLibrary\\ATTR.h"
#include "GISLibrary\\CodeWithNumericCode.h"


#include "..\\FeatureCatalog\\Catalog.h"

#include "..\\FeatureCatalog\\FeatureCatalogue.h"
#include "..\\FeatureCatalog\\InformationType.h" 

IMPLEMENT_DYNAMIC(CDialogExCreateLayersub, CDialogEx)

CDialogExCreateLayersub::CDialogExCreateLayersub(CWnd* pParent )
	: CDialogEx(IDD_DIALOG_LAYERSUB, pParent)
{

}

CDialogExCreateLayersub::~CDialogExCreateLayersub()
{
}

void CDialogExCreateLayersub::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_LAYERFEATURE, LayerFeatureTree);
}


BEGIN_MESSAGE_MAP(CDialogExCreateLayersub, CDialogEx)
END_MESSAGE_MAP() 
void CDialogExCreateLayersub::SetLayerFeatureData(S101Cell* cell)
{
	Catalog *catalog = ((S101Layer*)cell->m_pLayer)->GetFC();
	FeatureCatalogue* fc = catalog->m_pCatalogueList.begin()->second;

	POSITION pos = cell->m_infMap.GetStartPosition();
	while (pos != nullptr)
	{
		__int64 key = 0;
		R_InformationRecord* ir = nullptr;
		cell->m_infMap.GetNextAssoc(pos, key, ir);

		int code = ir->m_irid.m_nitc;
		auto itor = cell->m_dsgir.m_itcs->m_arr.find(code);
		CodeWithNumericCode* nc = itor->second;

		std::wstring codeStr = nc->m_code;
		InformationType *objIT = &catalog->m_pCatalogueList.begin()->second->informationTypes.informationType.find(codeStr)->second; 
		CInformationCodeStringAddPath cs;
		cs._name = objIT->code.GetValueString();
		cs._id = ir->m_irid.m_name.RCID;
		cs._ir = ir;
		cs.featureCatalog = fc;
		cs.filepath = cell->GetFileName();
	
		cs.dsgir = cell->GetDatasetGeneralInformationRecord();
		infolist.push_back(cs);
	}

	pos = cell->m_feaMap.GetStartPosition();
	while (pos != nullptr)
	{
		__int64 key = 0;
		R_FeatureRecord* fr = nullptr;
		cell->m_feaMap.GetNextAssoc(pos, key, fr);

		int code = fr->m_frid.m_nftc;

		auto itor = cell->m_dsgir.m_ftcs->m_arr.find(code);
		CodeWithNumericCode* nc = itor->second;

		std::wstring codeStr = nc->m_code;
		FeatureType *objFT = &catalog->m_pCatalogueList.begin()->second->featureTypes.featureType.find(codeStr)->second;

		CFeatureCodeStringAutoAddPath cs;
		cs._name = objFT->code.GetValueString();
		cs._id = fr->m_frid.m_name.RCID;
		cs._fr = fr;
		cs.filepath = cell->GetFileName();
		cs.featureCatalog = fc;
		cs.dsgir = cell->GetDatasetGeneralInformationRecord();
		featurelist.push_back(cs);
	}
}
BOOL CDialogExCreateLayersub::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HTREEITEM root, featureTyperoot, InformationTyperoot;

	root = LayerFeatureTree.InsertItem(TEXT("Dataset"), 0, 0, TVI_ROOT, TVI_LAST);
	featureTyperoot = LayerFeatureTree.InsertItem(TEXT("FeatureType"), 0, 0, root, TVI_LAST);

	for (size_t i = 0; i < featurelist.size(); i++)
	{
		CFeatureCodeStringAutoAddPath cs;
		cs = featurelist[i];

		std::wstring value = cs._name;
		std::wstring fileName = cs.filepath;

		HTREEITEM featureType = LayerFeatureTree.InsertItem(value.c_str(), 0, 0, featureTyperoot, TVI_LAST);

		HTREEITEM featureName = LayerFeatureTree.InsertItem(fileName.c_str(), 0, 0, featureType, TVI_LAST);

		HTREEITEM AttributeType = LayerFeatureTree.InsertItem(_TEXT("Attribute"), 0, 0, featureType, TVI_LAST);

		R_DSGIR* DGIR = cs.dsgir;
		R_FeatureRecord* fefo = cs._fr;
		FeatureCatalogue* fc = cs.featureCatalog; 

		for (auto fattr = fefo->m_attr.begin(); fattr != fefo->m_attr.end(); fattr++)
		{
			F_ATTR* f_attr = *fattr;
			unordered_map<int, HTREEITEM> attrilist;
			int num = 0;
			for (auto attr = f_attr->m_arr.begin(); attr != f_attr->m_arr.end(); attr++)
			{
				ATTR* _attr = *attr;
				int parentindex = _attr->m_paix;
				CString Name = DGIR->GetAttributeCode(_attr->m_natc);
				wstring Result = wstring(Name) + L" : " + wstring(_attr->m_atvl);

				ComplexAttribute* complex= fc->GetComplexAttribute(std::wstring(Name));
				if (complex!=nullptr) 
				{
					Result = wstring(Name);
				}
				
		
				if (parentindex == 0)
				{
					
					HTREEITEM AttributeChildType = LayerFeatureTree.InsertItem(Result.c_str(), 0, 0, AttributeType, TVI_LAST);
					LayerFeatureTree.Expand(AttributeChildType, TVE_EXPAND); 
					attrilist.insert({ num,AttributeChildType });
				}
				else
				{
					HTREEITEM parent = attrilist[parentindex - 1];
					if (parent != nullptr)
					{
						HTREEITEM AttributeChildType = LayerFeatureTree.InsertItem(Result.c_str(), 0, 0, parent, TVI_LAST);
						LayerFeatureTree.Expand(AttributeChildType, TVE_EXPAND); 
						attrilist.insert({ num,AttributeChildType });
					}
					LayerFeatureTree.Expand(parent, TVE_EXPAND); 
				}
				num++;
			}
		}

		LayerFeatureTree.Expand(AttributeType, TVE_EXPAND); 
		LayerFeatureTree.Expand(featureName, TVE_EXPAND); 
		LayerFeatureTree.Expand(featureType, TVE_EXPAND); 
	}
	LayerFeatureTree.Expand(featureTyperoot, TVE_EXPAND); 


	InformationTyperoot = LayerFeatureTree.InsertItem(TEXT("InformationType"), 0, 0, root, TVI_LAST);
	for (size_t i = 0; i < infolist.size(); i++)
	{
		CInformationCodeStringAddPath cs;
		cs = infolist[i];
		std::wstring value = cs._name;
		std::wstring fileName = L"Chart : " + cs.filepath;
		HTREEITEM informationType = LayerFeatureTree.InsertItem(value.c_str(), 0, 0, InformationTyperoot, TVI_LAST);

		HTREEITEM informationName = LayerFeatureTree.InsertItem(fileName.c_str(), 0, 0, informationType, TVI_LAST);

		HTREEITEM AttributeType = LayerFeatureTree.InsertItem(TEXT("Attribute"), 0, 0, informationType, TVI_LAST);


		R_DSGIR* DGIR = cs.dsgir;
		R_InformationRecord* info = cs._ir;
		FeatureCatalogue* fc = cs.featureCatalog;

		for (auto fattr = info->m_attr.begin(); fattr != info->m_attr.end(); fattr++)
		{
			F_ATTR* f_attr = *fattr;
			unordered_map<int, HTREEITEM> attrilist;
			int num = 0;
			for (auto attr = f_attr->m_arr.begin(); attr != f_attr->m_arr.end(); attr++)
			{
				ATTR* _attr = *attr;
				int parentindex = _attr->m_paix;
				CString Name = DGIR->GetAttributeCode(_attr->m_natc);
				wstring Result = wstring(Name) + L" : " + wstring(_attr->m_atvl);

				ComplexAttribute* complex = fc->GetComplexAttribute(std::wstring(Name));
				if (complex != nullptr) 
				{
					Result = wstring(Name);
				}


				if (parentindex == 0)
				{

					HTREEITEM AttributeChildType = LayerFeatureTree.InsertItem(Result.c_str(), 0, 0, AttributeType, TVI_LAST);
					LayerFeatureTree.Expand(AttributeChildType, TVE_EXPAND); 
					attrilist.insert({ num,AttributeChildType });
				}
				else
				{
					HTREEITEM parent = attrilist[parentindex - 1];
					if (parent != nullptr)
					{
						HTREEITEM AttributeChildType = LayerFeatureTree.InsertItem(Result.c_str(), 0, 0, parent, TVI_LAST);
						LayerFeatureTree.Expand(AttributeChildType, TVE_EXPAND); 
						attrilist.insert({ num,AttributeChildType });
					}
					LayerFeatureTree.Expand(parent, TVE_EXPAND); 
				}
				num++;
			}
		}            


		
		LayerFeatureTree.Expand(AttributeType, TVE_EXPAND); 
		LayerFeatureTree.Expand(informationName, TVE_EXPAND); 
		LayerFeatureTree.Expand(informationType, TVE_EXPAND); 
	}
	LayerFeatureTree.Expand(InformationTyperoot, TVE_EXPAND); 

	LayerFeatureTree.Expand(root, TVE_EXPAND);
	return false;
}