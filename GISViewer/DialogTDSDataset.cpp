// DialogTDSDataset.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogTDSDataset.h"
#include "afxdialogex.h"
#include "GISViewerView.h"

#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\F_SPAS.h"
#include "GISLibrary\\ENC_S101_Factory.h"
#include "GISLibrary\\F_COCC.h"
#include "GISLibrary\\F_C3IL.h"
#include "GISLibrary\\F_C2IL.h"
#include "GISLibrary\\F_ATTR.h"
#include "GISLibrary\\F_RIAS.h"
#include "GISLibrary\\R_CurveRecord.h"
#include "GISLibrary\\R_SurfaceRecord.h"
#include "GISLibrary\\R_MultiPointRecord.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\NewFeatureManager.h"
#include "GISLibrary\\ATTR.h"
#include "GISLibrary\\C3IL.h"
#include "GISLibrary\IC2D.h"
#include "GISLibrary\\CodeWithNumericCode.h"
#include "GISLibrary\\SPAS.h"
#include "GISLibrary\\RIAS.h"

#include "S100Geometry\\SPoint.h" 

IMPLEMENT_DYNAMIC(CDialogTDSDataset, CDialogEx)

CDialogTDSDataset::CDialogTDSDataset(PortrayalCatalogue* portrayalCatalogue, CWnd* pParent )
	: CDialogEx(CDialogTDSDataset::IDD, pParent)
{
	pc = portrayalCatalogue;
	cautionaryAreaKeyValue = 0;
}

CDialogTDSDataset::~CDialogTDSDataset()
{
}

void CDialogTDSDataset::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogTDSDataset, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_TDS_1, &CDialogTDSDataset::OnBnClickedBtnTds1)
	ON_BN_CLICKED(IDC_BTN_TDS_2, &CDialogTDSDataset::OnBnClickedBtnTds2)
	ON_BN_CLICKED(IDC_BTN_TDS_3, &CDialogTDSDataset::OnBnClickedBtnTds3)
	ON_BN_CLICKED(IDC_BTN_TDS_4, &CDialogTDSDataset::OnBnClickedBtnTds4)
	ON_BN_CLICKED(IDC_BTN_TDS_5, &CDialogTDSDataset::OnBnClickedBtnTds5)
	ON_BN_CLICKED(IDC_BTN_TDS_6, &CDialogTDSDataset::OnBnClickedBtnTds6)
	ON_BN_CLICKED(IDC_BTN_TDS_7, &CDialogTDSDataset::OnBnClickedBtnTds7)
	ON_BN_CLICKED(IDC_BTN_TDS_8, &CDialogTDSDataset::OnBnClickedBtnTds8)
	ON_BN_CLICKED(IDC_BTN_TDS_9, &CDialogTDSDataset::OnBnClickedBtnTds9)
	ON_BN_CLICKED(IDC_BTN_TDS_10, &CDialogTDSDataset::OnBnClickedBtnTds10)
	ON_BN_CLICKED(IDC_BTN_TDS_11, &CDialogTDSDataset::OnBnClickedBtnTds11)
	ON_BN_CLICKED(IDC_BTN_TDS_12, &CDialogTDSDataset::OnBnClickedBtnTds12)
	ON_BN_CLICKED(IDC_BTN_TDS_13, &CDialogTDSDataset::OnBnClickedBtnTds13)
	ON_BN_CLICKED(IDC_BTN_TDS_14, &CDialogTDSDataset::OnBnClickedBtnTds14)
	ON_BN_CLICKED(IDC_BTN_TDS_15, &CDialogTDSDataset::OnBnClickedBtnTds15)
	ON_BN_CLICKED(IDC_BTN_TDS_16, &CDialogTDSDataset::OnBnClickedBtnTds16)
	ON_BN_CLICKED(IDC_BTN_TDS_17, &CDialogTDSDataset::OnBnClickedBtnTds17)
	ON_BN_CLICKED(IDC_BTN_TDS_18, &CDialogTDSDataset::OnBnClickedBtnTds18)
	ON_BN_CLICKED(IDC_BTN_TDS_19, &CDialogTDSDataset::OnBnClickedBtnTds19)
	ON_BN_CLICKED(IDC_BTN_TDS_20, &CDialogTDSDataset::OnBnClickedBtnTds20)
	ON_BN_CLICKED(IDC_BTN_TDS_21, &CDialogTDSDataset::OnBnClickedBtnTds21)
	ON_BN_CLICKED(IDC_BTN_TDS_22, &CDialogTDSDataset::OnBnClickedBtnTds22)
	ON_BN_CLICKED(IDC_BTN_TDS_23, &CDialogTDSDataset::OnBnClickedBtnTds23)
	ON_BN_CLICKED(IDC_BTN_TDS_24, &CDialogTDSDataset::OnBnClickedBtnTds24)
	ON_BN_CLICKED(IDC_BTN_TDS_25, &CDialogTDSDataset::OnBnClickedBtnTds25)
	ON_BN_CLICKED(IDC_BTN_TDS_26, &CDialogTDSDataset::OnBnClickedBtnTds26)
	ON_BN_CLICKED(IDC_BTN_TDS_27, &CDialogTDSDataset::OnBnClickedBtnTds27)
	ON_BN_CLICKED(IDC_BTN_TDS_28, &CDialogTDSDataset::OnBnClickedBtnTds28)
	ON_BN_CLICKED(IDC_BTN_TDS_29, &CDialogTDSDataset::OnBnClickedBtnTds29)
	ON_BN_CLICKED(IDC_BTN_TDS_30, &CDialogTDSDataset::OnBnClickedBtnTds30)
	ON_BN_CLICKED(IDC_BTN_TDS_31, &CDialogTDSDataset::OnBnClickedBtnTds31)
	ON_BN_CLICKED(IDC_BTN_TDS_32, &CDialogTDSDataset::OnBnClickedBtnTds32)
	ON_BN_CLICKED(IDC_BTN_TDS_33, &CDialogTDSDataset::OnBnClickedBtnTds33)
	ON_BN_CLICKED(IDC_BTN_TDS_34, &CDialogTDSDataset::OnBnClickedBtnTds34)
	ON_BN_CLICKED(IDC_BTN_TDS_35, &CDialogTDSDataset::OnBnClickedBtnTds35)
	ON_BN_CLICKED(IDC_BTN_TDS_36, &CDialogTDSDataset::OnBnClickedBtnTds36)
	ON_BN_CLICKED(IDC_BTN_TDS_37, &CDialogTDSDataset::OnBnClickedBtnTds37)
	ON_BN_CLICKED(IDC_BTN_TDS_38, &CDialogTDSDataset::OnBnClickedBtnTds38)
	ON_BN_CLICKED(IDC_BTN_TDS_39, &CDialogTDSDataset::OnBnClickedBtnTds39)
	ON_BN_CLICKED(IDC_BTN_TDS_40, &CDialogTDSDataset::OnBnClickedBtnTds40)
	ON_BN_CLICKED(IDC_CHANGE_DSNM, &CDialogTDSDataset::OnBnClickedChangeDsnm)
END_MESSAGE_MAP() 


void CDialogTDSDataset::OnBnClickedBtnTds1()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds2()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds3()
{

}


void CDialogTDSDataset::OnBnClickedBtnTds4()
{

}


void CDialogTDSDataset::OnBnClickedBtnTds5()
{

}


void CDialogTDSDataset::OnBnClickedBtnTds6()
{

}


void CDialogTDSDataset::OnBnClickedBtnTds7()
{

}


void CDialogTDSDataset::OnBnClickedBtnTds8()
{
	NewFeatureManager newFeatureManager;
	R_FeatureRecord* fr = NULL; 
	S101Layer *layer = new S101Layer();
	layer->Open(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\2.1.1 Power Up\\ENC_ROOT\\AAS101X1SW.000");
	S101Cell* cell = (S101Cell*)layer->m_spatialObject; 
	S101Cell* updateCell = ENC_S101_Factory::CreateUpdateFile(cell);
	cell->updateInformation = updateCell;
	newFeatureManager.m_featureType = ENC_S101_Factory::GetFTCS(cell, L"Wreck");
	newFeatureManager.m_addFeaturePoint.x = -32.315;
	newFeatureManager.m_addFeaturePoint.y = 60.955; 
	newFeatureManager.m_cell = cell;
	newFeatureManager.m_geometryType = 1;

	fr = ENC_S101_Factory::CreateFeature(&newFeatureManager, theApp.pView->m_pGisLib->GetScaler());
	cell->m_feaMap.SetAt(fr->m_frid.m_name.GetName(), fr);

	ATTR* attr = new ATTR();
	F_ATTR* attrParent = new F_ATTR();
	attrParent->m_arr.push_back(attr);
	fr->m_attr.push_back(attrParent);
	attr->m_natc = ENC_S101_Factory::GetATCS(cell, L"categoryOfWreck");

	attr->m_atix = 1;
	attr->m_paix = 0;
	attr->m_atin = 1;
	attr->m_atvl = L"2";


	newFeatureManager.m_featureType = ENC_S101_Factory::GetFTCS(cell, L"BuoyCardinal");
	newFeatureManager.m_addFeaturePoint.x = -32.525;
	newFeatureManager.m_addFeaturePoint.y = 60.957667; 
	newFeatureManager.m_cell = cell;
	newFeatureManager.m_geometryType = 1;

	fr = ENC_S101_Factory::CreateFeature(&newFeatureManager, theApp.pView->m_pGisLib->GetScaler());
	cell->m_feaMap.SetAt(fr->m_frid.m_name.GetName(), fr);

	attr = new ATTR();
	attrParent->m_arr.push_back(attr);
	attr->m_natc = ENC_S101_Factory::GetATCS(cell, L"categoryOfCardinalMark");

	attr->m_atix = 1;
	attr->m_paix = 0;
	attr->m_atin = 1;
	attr->m_atvl = L"2";

	newFeatureManager.m_featureType = ENC_S101_Factory::GetFTCS(cell, L"BuoyCardinal");
	newFeatureManager.m_addFeaturePoint.x = -32.525;
	newFeatureManager.m_addFeaturePoint.y = 60.952667; 
	newFeatureManager.m_cell = cell;
	newFeatureManager.m_geometryType = 1;

	fr = ENC_S101_Factory::CreateFeature(&newFeatureManager, theApp.pView->m_pGisLib->GetScaler());
	cell->m_feaMap.SetAt(fr->m_frid.m_name.GetName(), fr);

	attr = new ATTR();
	attrParent->m_arr.push_back(attr);
	attr->m_natc = ENC_S101_Factory::GetATCS(cell, L"categoryOfCardinalMark");

	attr->m_atix = 1;
	attr->m_paix = 0;
	attr->m_atin = 1;
	attr->m_atvl = L"3";

	updateCell->Save(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\2.1.1 Power Up\\ENC_ROOT\\AAS101X1SW.001", L"000");  
	delete layer;
}

void CDialogTDSDataset::OnBnClickedBtnTds9()
{
	NewFeatureManager newFeatureManager;
	R_FeatureRecord* fr = NULL; 
	S101Layer *layer = new S101Layer();
	layer->Open(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\2.1.1 Power Up\\ENC_ROOT\\AAS101X1SW.000");
	S101Cell* cell = (S101Cell*)layer->m_spatialObject; 
	S101Cell* updateCell = ENC_S101_Factory::CreateUpdateFile(cell, 2);
	cell->updateInformation = updateCell;
	updateCell->m_dsgir.m_dsid.m_dsrd = L"20050101";

	newFeatureManager.m_featureType = ENC_S101_Factory::GetFTCS(cell, L"Wreck");
	newFeatureManager.m_addFeaturePoints.clear();

	PointD p;
	p.x = -32.542121;
	p.y = 60.935314;
	newFeatureManager.m_addFeaturePoints.push_back(p);
	p.x = -32.549752;
	p.y = 60.935314;
	newFeatureManager.m_addFeaturePoints.push_back(p);
	p.x = -32.549752;
	p.y = 60.939752;
	newFeatureManager.m_addFeaturePoints.push_back(p);
	p.x = -32.542121;
	p.y = 60.939752;
	newFeatureManager.m_addFeaturePoints.push_back(p);

	newFeatureManager.m_cell = cell;
	newFeatureManager.m_geometryType = 3;
	fr = ENC_S101_Factory::CreateFeature(&newFeatureManager, theApp.pView->m_pGisLib->GetScaler());
	cell->m_feaMap.SetAt(fr->m_frid.m_name.GetName(), fr);
	R_FeatureRecord* fr2 = ENC_S101_Factory::CreateFeatureSameGeometry(fr, &newFeatureManager, L"CautionaryArea");
	cell->m_feaMap.SetAt(fr2->m_frid.m_name.GetName(), fr2);
	updateCell->Save(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\2.1.1 Power Up\\ENC_ROOT\\AAS101X1SW.002", L"000");

	ATTR* attr = new ATTR();
	F_ATTR* attrParent = new F_ATTR();
	attrParent->m_arr.push_back(attr);
	fr->m_attr.push_back(attrParent);

	attr->m_natc = ENC_S101_Factory::GetATCS(cell, L"categoryOfRestrictedArea");

	attr->m_atix = 1;
	attr->m_paix = 0;
	attr->m_atin = 1;
	attr->m_atvl = L"7";

	prohibitedAreaKeyValue = fr->m_frid.m_name.GetName();
	cautionaryAreaKeyValue = fr2->m_frid.m_name.GetName();

	prohibitedAreaID = fr->m_frid.m_name.RCID;
	cautionaryAreaID = fr2->m_frid.m_name.RCID;

	{
		R_FeatureRecord* orgFr = fr;

		for (auto itorParent = fr->m_spas.begin(); itorParent != fr->m_spas.end(); itorParent++)
		{
			F_SPAS *spasParent = *itorParent;

			for (auto itor = spasParent->m_arr.begin(); itor != spasParent->m_arr.end(); itor++)
			{
				SPAS* spas = *itor;

				__int64 key = ((__int64)spas->m_name.RCNM) << 32 | ((__int64)spas->m_name.RCID);

				if (spas->m_name.RCNM == 130)
				{
					R_SurfaceRecord* vr1 = (R_SurfaceRecord*)cell->m_vecMap.find(key)->second;
					for (auto itorParent = vr1->m_rias.begin(); itorParent != vr1->m_rias.end(); itorParent++)
					{
						F_RIAS* riasParent = *itorParent;

						for (auto itor = riasParent->m_arr.begin(); itor != riasParent->m_arr.end(); itor++)
						{
							RIAS* rias = *itor;
							__int64 key2 = ((__int64)rias->m_name.RCNM) << 32 | ((__int64)rias->m_name.RCNM);

							R_CurveRecord* vr2 = (R_CurveRecord*)cell->m_vecMap.find(key2)->second;

							if (rias->m_name.RCNM == 120)
							{
								__int64 key3 = ((__int64)rias->m_name.RCNM) << 32 | ((__int64)rias->m_name.RCNM);

								prohibitedAreaSpatialID = ((R_CurveRecord*)cell->m_vecMap.find(key3)->second)->m_crid.m_name.RCID;
							}
						}
					}
				}
			}
		}
	}

	delete layer;
}

void CDialogTDSDataset::OnBnClickedBtnTds10()
{ 
	S101Layer *layer = new S101Layer();
	layer->Open(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\2.1.1 Power Up\\ENC_ROOT\\AAS101X1SW.000");
	S101Cell* cell = (S101Cell*)layer->m_spatialObject;

	S101Cell* updateCell = ENC_S101_Factory::CreateUpdateFile(cell, 3);
	updateCell->m_dsgir.m_dsid.m_dsed = L"3";
	updateCell->m_dsgir.m_dsid.m_dsrd = L"20050908";
	R_FeatureRecord* fr = ENC_S101_Factory::CreateDeleteFeature(cell, cautionaryAreaID);
	cell->m_feaMap.SetAt(fr->m_frid.m_name.GetName(), fr);


	R_CurveRecord* ucr = new R_CurveRecord();

	ucr->m_crid.m_name.RCID = prohibitedAreaSpatialID;
	ucr->m_crid.m_name.RCNM = 120;
	ucr->m_cocc = new F_COCC();
	ucr->m_cocc->m_coui = 3;
	ucr->m_cocc->m_coix = 1;
	ucr->m_cocc->m_ncor = 2;

	F_C2IL *c2il = new F_C2IL();
	ucr->m_c2il.push_back(c2il);

	IC2D* ic2d = new IC2D();
	ic2d->m_xcoo = -32551000;
	ic2d->m_ycoo = -60935314;
	c2il->m_arr.push_back(ic2d);

	ic2d = new IC2D();
	ic2d->m_xcoo = -32551000;
	ic2d->m_ycoo = -60939752;
	c2il->m_arr.push_back(ic2d);


	updateCell->m_vecMap.insert(
		std::unordered_map<__int64, R_VectorRecord*>::value_type(ucr->m_crid.m_name.GetName(), ucr)
	);

	updateCell->Save(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\2.1.1 Power Up\\ENC_ROOT\\AAS101X1SW.003", L"000");

	delete layer;
}

void CDialogTDSDataset::OnBnClickedBtnTds11()
{ 
	S101Layer *layer = new S101Layer();
	layer->Open(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\2.1.1 Power Up\\ENC_ROOT\\AAS101X1SW.000");
	S101Cell* cell = (S101Cell*)layer->m_spatialObject;

	S101Cell* updateCell = ENC_S101_Factory::CreateUpdateFile(cell, 3);
	updateCell->m_dsgir.m_dsid.m_dsed = L"4";
	updateCell->m_dsgir.m_dsid.m_dsrd = L"20050922";

	R_FeatureRecord* fr = ENC_S101_Factory::CreateDeleteFeature(cell, prohibitedAreaID);
	cell->m_feaMap.SetAt(fr->m_frid.m_name.GetName(), fr);

	updateCell->Save(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\2.1.1 Power Up\\ENC_ROOT\\AAS101X1SW.004", L"000");
	delete layer;
}


void CDialogTDSDataset::OnBnClickedBtnTds12()
{ 
	S101Layer *layer = new S101Layer();
	layer->Open(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\2.1.1 Power Up\\ENC_ROOT\\AAS101X1SW.000");
	S101Cell* cell = (S101Cell*)layer->m_spatialObject;

	S101Cell* updateCell = ENC_S101_Factory::CreateUpdateFile(cell, 3);
	updateCell->m_dsgir.m_dsid.m_dsed = L"5";

	POSITION pos = cell->m_feaMap.GetStartPosition();

	while (pos != NULL) 
	{
		__int64 key = 0;
		R_FeatureRecord* fr = NULL;
		cell->m_feaMap.GetNextAssoc(pos, key, fr);

		CodeWithNumericCode *nc = cell->m_dsgir.m_ftcs->m_arr.find(fr->m_frid.m_nftc)->second;

		if (nc->m_code.Compare(L"Sounding") == 0)
		{
			for (auto itorParent = fr->m_spas.begin(); itorParent != fr->m_spas.end(); itorParent++)
			{
				F_SPAS *spasParent = *itorParent;

				for (auto itor = spasParent->m_arr.begin(); itor != spasParent->m_arr.end(); itor++)
				{
					SPAS* spas = *itor;

					key = ((__int64)spas->m_name.RCNM) << 32 | ((__int64)spas->m_name.RCID);
					auto mrk = cell->m_vecMap.find(key);
					R_MultiPointRecord* mr = (R_MultiPointRecord*)mrk->second;

					R_MultiPointRecord* umr = new R_MultiPointRecord(); 
					umr->m_mrid.m_name.RCID = mr->m_mrid.m_name.RCID;
					umr->m_mrid.m_name.RCNM = mr->m_mrid.m_name.RCNM;
					umr->m_cocc = new F_COCC();
					umr->m_cocc->m_coui = 1;
					umr->m_cocc->m_coix = 0;
					umr->m_cocc->m_ncor = 1;

					F_C3IL *c3il = new F_C3IL();

					C3IL* unitC3IL = new C3IL();
					unitC3IL->m_xcoo = -32551000;
					unitC3IL->m_ycoo = -60935314;
					unitC3IL->m_zcoo = 15;
					c3il->m_arr.push_back(unitC3IL);
					umr->m_c3il.push_back(c3il);

					updateCell->m_vecMap.insert(
						std::unordered_map<__int64, R_VectorRecord*>::value_type(umr->m_mrid.m_name.GetName(), umr)
					);
				}
			}
		}
	}
	updateCell->Save(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\2.1.1 Power Up\\ENC_ROOT\\AAS101X1SW.005", L"000");
	delete layer;
}


void CDialogTDSDataset::OnBnClickedBtnTds13()
{
}

void CDialogTDSDataset::OnBnClickedBtnTds14()
{
}

void CDialogTDSDataset::OnBnClickedBtnTds15()
{
}

void CDialogTDSDataset::OnBnClickedBtnTds16()
{
}

void CDialogTDSDataset::OnBnClickedBtnTds17()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds18()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds19()
{ 
	S101Layer *layer = new S101Layer();
	layer->Open(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\2.1.1 Power Up\\ENC_ROOT\\AAS101X000.000");
	S101Cell* cell = (S101Cell*)layer->m_spatialObject;

	S101Cell* updateCell = ENC_S101_Factory::CreateUpdateFile(cell, 3);
	updateCell->m_dsgir.m_dsid.m_dsrd = L"20060104";

	updateCell->Save(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\2.2.7 Cancellation\\ENC_ROOT\\AAS101X000.001", L"000");
}


void CDialogTDSDataset::OnBnClickedBtnTds20()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds21()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds22()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds23()
{          
}


void CDialogTDSDataset::OnBnClickedBtnTds24()
{
	R_FeatureRecord *fr = NULL;
	__int64 iKey;

	CopyFile(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\2.1.1 Power Up\\ENC_ROOT\\AAS101X1NE.000",
		L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\3.2 Invalid Object\\Invalid Base\\ENC_ROOT\\AAS101X1NE.000",
		FALSE); 
	S101Layer *layer = new S101Layer();
	layer->Open(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\3.2 Invalid Object\\Invalid Base\\ENC_ROOT\\AAS101X1NE.000");
	S101Cell* cell = (S101Cell*)layer->m_spatialObject;

	POSITION pos = cell->m_feaMap.GetStartPosition();
	while (pos != NULL)
	{
		cell->m_feaMap.GetNextAssoc(pos, iKey, fr);

		auto itor = cell->m_dsgir.m_ftcs->m_arr.find(fr->m_frid.m_nftc);
		if (itor != cell->m_dsgir.m_ftcs->m_arr.end())
		{
			CodeWithNumericCode* nc = itor->second;

			if (nc->m_code.Compare(L"CoastguardStation") == 0)
			{
				if (fr->m_geometry->type == 1)
				{
					fr->m_frid.m_nftc = 999;
				}
			}
			else if (nc->m_code.Compare(L"BuoySpecialPurposeGeneral") == 0)
			{   
				if (fr->m_geometry->type == 1)
				{
					double tlat = -(32 + 30.924 / 60);
					double tlon = 60 + 58.719 / 60;
					m_pView->m_pGisLib->Projection(&tlon, &tlat);

					SPoint *p = (SPoint*)(fr->m_geometry);

					double dx = fabs(p->m_point.x - tlon);
					double dy = fabs(p->m_point.y - tlat);
					if (dx < 0.0001 && dy < 0.0002)

					{
						for (auto afitor = fr->m_attr.begin(); afitor != fr->m_attr.end(); afitor++)
						{
							F_ATTR* attrField = *afitor;

							for (auto aitor = attrField->m_arr.begin(); aitor != attrField->m_arr.end(); aitor++)
							{
								ATTR* attr = *aitor;
								auto atitor = cell->m_dsgir.m_atcs->m_arr.find(attr->m_natc);

								if (atitor->second->m_code.Compare(L"buoyShape") == 0)
								{

									{
										attr->m_natc = 777;
									}

								}
							}
						}
					}
				}
			}
			else if (nc->m_code.Compare(L"BuoyLateral") == 0)
			{   

				if (fr->m_geometry->type == 1)
				{
					double tlat = -(32 + 31.665 / 60);
					double tlon = 60 + 58.243 / 60;
					m_pView->m_pGisLib->Projection(&tlon, &tlat);

					SPoint *p = (SPoint*)(fr->m_geometry);

					double dx = fabs(p->m_point.x - tlon);
					double dy = fabs(p->m_point.y - tlat);

					if (dx < 0.0001 && dy < 0.0001)
					{

						for (auto afitor = fr->m_attr.begin(); afitor != fr->m_attr.end(); afitor++)
						{
							F_ATTR* attrField = *afitor;

							bool hasBouyShape = false;
							auto atitor2 = cell->m_dsgir.m_atcs->m_arrFindForCode.find(L"buoyShape");
							for (auto aitor = attrField->m_arr.begin(); aitor != attrField->m_arr.end(); aitor++)
							{
								ATTR* attr = *aitor;
								auto atitor = cell->m_dsgir.m_atcs->m_arr.find(attr->m_natc);

								if (atitor->second->m_code.Compare(L"buoyShape") == 0)
								{
									attr->m_atvl = L"555";
									hasBouyShape = true;
								}
							}

							if (!hasBouyShape)
							{
								ATTR* attr = new ATTR();
								attr->m_atin = 1;
								attr->m_atix = 1;
								attr->m_paix = 0;
								attr->m_natc = atitor2->second->m_nmcd;
								attr->m_atvl = L"555";

								attrField->m_arr.push_back(attr);
							}
						}
					}
				}
			}
		}
	}

	cell->Save(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\3.2 Invalid Object\\Invalid Base\\ENC_ROOT\\AAS101X1NE.000", L"000");
	delete layer;
}


void CDialogTDSDataset::OnBnClickedBtnTds25()
{
	R_FeatureRecord *fr = NULL;
	__int64 iKey; 
	S101Layer *layer = new S101Layer();
	layer->Open(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\3.9 Polar ENC Data\\ENC_ROOT\\AAS101NPL2.000");
	S101Cell* cell = (S101Cell*)layer->m_spatialObject;

	POSITION pos = cell->m_feaMap.GetStartPosition();
	while (pos != NULL)
	{
		cell->m_feaMap.GetNextAssoc(pos, iKey, fr);
		auto itor = fr->m_spas.begin();

		if ((*(*itor)->m_arr.begin())->m_smin == -1)
			(*(*itor)->m_arr.begin())->m_smin = 1;
		if ((*(*itor)->m_arr.begin())->m_smax == 0)
			(*(*itor)->m_arr.begin())->m_smax = 15;
	}
	cell->Save(L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\3.9 Polar ENC Data\\ENC_ROOT\\AAS101NPL2.000", L"000");

	delete layer;
}



void CDialogTDSDataset::OnBnClickedBtnTds26()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds27()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds28()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds29()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds30()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds31()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds32()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds33()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds34()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds35()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds36()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds37()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds38()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds39()
{
}


void CDialogTDSDataset::OnBnClickedBtnTds40()
{
}


void CDialogTDSDataset::OnBnClickedChangeDsnm() 
{
	CString orgPath = L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\@ConvertedOnly\\";
	CString outPath = L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\";

	CFile file;
	CString saveFileName = L"C:\\ENC_테스트\\S-64_e3.0.0_ENC_Unencrypted_TDS_Jan_2015\\Boundary.txt";
	file.Open(saveFileName, CFile::modeCreate | CFile::modeWrite); 
	S101Layer *layer = new S101Layer();
	layer->Open(orgPath + L"2.1.1 Power Up\\ENC_ROOT\\GB4X0000__.000");
	S101Cell* cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101X000.000";
	cell->Save(outPath + L"2.1.1 Power Up\\ENC_ROOT\\AAS101X000.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer;

	layer = new S101Layer();
	layer->Open(orgPath + L"2.1.1 Power Up\\ENC_ROOT\\GB5X01NE__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101X1NE.000";
	cell->Save(outPath + L"2.1.1 Power Up\\ENC_ROOT\\AAS101X1NE.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer;

	layer = new S101Layer();
	layer->Open(orgPath + L"2.1.1 Power Up\\ENC_ROOT\\GB5X01NW__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101X1NW.000";
	cell->Save(outPath + L"2.1.1 Power Up\\ENC_ROOT\\AAS101X1NW.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer;

	layer = new S101Layer();
	layer->Open(orgPath + L"2.1.1 Power Up\\ENC_ROOT\\GB5X01SE__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101X1SE.000";
	cell->Save(outPath + L"2.1.1 Power Up\\ENC_ROOT\\AAS101X1SE.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer;

	layer = new S101Layer();
	layer->Open(orgPath + L"2.1.1 Power Up\\ENC_ROOT\\GB5X01SW__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101X1SW.000";
	cell->Save(outPath + L"2.1.1 Power Up\\ENC_ROOT\\AAS101X1SW.000", L"000");
	WriteCellBoundary(&file, cell);

	layer = new S101Layer();
	layer->Open(orgPath + L"2.1.1 Power Up\\ENC_ROOT\\GB5X02SE__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101X2SE.000";
	cell->Save(outPath + L"2.1.1 Power Up\\ENC_ROOT\\AAS101X2SE.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"2.1.5 Loading Corrupt Data\\ENC_ROOT\\GB5X01NE__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101X1NE.000";
	cell->Save(outPath + L"2.1.5 Loading Corrupt Data\\ENC_ROOT\\AAS101X1NE.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"2.2.5 Good Base Cells\\ENC_ROOT\\GB5X01SW__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101X1SW.000";
	cell->Save(outPath + L"2.2.5 Good Base Cells\\ENC_ROOT\\AAS101X1SW.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"2.2.6 Re-issue\\GB5X01SW_RE-ISSUE\\ENC_ROOT\\GB5X01SW__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101X1SW.000";
	cell->Save(outPath + L"2.2.6 Re-issue\\GB5X01SW_RE-ISSUE\\ENC_ROOT\\AAS101X1SW.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer;  
	layer = new S101Layer();
	layer->Open(orgPath + L"3.1 ENC Display\\Base\\ENC_ROOT\\AA5DBASE__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101DBAS.000";
	cell->Save(outPath + L"3.1 ENC Display\\Base\\ENC_ROOT\\AAS101DBAS.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"3.1 ENC Display\\Other\\ENC_ROOT\\AA5OTHER__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101OTHE.000";
	cell->Save(outPath + L"3.1 ENC Display\\Other\\ENC_ROOT\\AAS101OTHE.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"3.1 ENC Display\\Standard\\ENC_ROOT\\AA5STNDR__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101STND.000";
	cell->Save(outPath + L"3.1 ENC Display\\Standard\\ENC_ROOT\\AAS101STND.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"3.2 Invalid Object\\ENC_ROOT\\AA3INVOB__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101INVO.000";
	cell->Save(outPath + L"3.2 Invalid Object\\ENC_ROOT\\AAS101INVO.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer;         
	layer = new S101Layer();
	layer->Open(orgPath + L"3.3 Settings\\ENC_ROOT\\GB4X0001__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101X001.000";
	cell->Save(outPath + L"3.3 Settings\\ENC_ROOT\\AAS101X001.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"3.4 Non-Official Data\\ENC_ROOT\\1B5X01NE__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"1BS101X1NE.000";
	cell->Save(outPath + L"3.4 Non-Official Data\\ENC_ROOT\\1BS101X1NE.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer;                 
	layer = new S101Layer();
	layer->Open(orgPath + L"3.6 Display Priorities\\ENC_ROOT\\2J4X0001__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101XDP1.000";
	cell->Save(outPath + L"3.6 Display Priorities\\ENC_ROOT\\AAS101XDP1.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"3.6 Display Priorities\\ENC_ROOT\\2J5X0001__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101XDP2.000";
	cell->Save(outPath + L"3.6 Display Priorities\\ENC_ROOT\\AAS101XDP2.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"3.6 Display Priorities\\ENC_ROOT\\2J5X0002__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101XDP3.000";
	cell->Save(outPath + L"3.6 Display Priorities\\ENC_ROOT\\AAS101XDP3.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"3.7 Overlap\\ENC_ROOT\\GB3OVRLP__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101OVLP.000";
	cell->Save(outPath + L"3.7 Overlap\\ENC_ROOT\\AAS101OVLP.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"3.7.7 Scale minimum\\ENC_ROOT\\AA3SCAMN__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101SCMN.000";
	cell->Save(outPath + L"3.7.7 Scale minimum\\ENC_ROOT\\AAS101SCMN.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer;                                 
	layer = new S101Layer();
	layer->Open(orgPath + L"3.9 Polar ENC Data\\ENC_ROOT\\AA1NPOL3__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101NPL1.000";
	cell->Save(outPath + L"3.9 Polar ENC Data\\ENC_ROOT\\AAS101NPL1.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"3.9 Polar ENC Data\\ENC_ROOT\\AA1NPOLA__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101NPL2.000";
	cell->Save(outPath + L"3.9 Polar ENC Data\\ENC_ROOT\\AAS101NPL2.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"3.9 Polar ENC Data\\ENC_ROOT\\AA1NPOLB__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101NPL3.000";
	cell->Save(outPath + L"3.9 Polar ENC Data\\ENC_ROOT\\AAS101NPL3.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"5.0 Navigational Hazards\\ENC_ROOT\\AA3NAVHZ__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101NHZ1.000";
	cell->Save(outPath + L"5.0 Navigational Hazards\\ENC_ROOT\\AAS101NHZ1.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"5.0 Navigational Hazards\\Overview\\ENC_ROOT\\AA2OVRVU__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101OVRVU.000";
	cell->Save(outPath + L"5.0 Navigational Hazards\\Overview\\ENC_ROOT\\AAS101OVRVU.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer;         
	layer = new S101Layer();
	layer->Open(orgPath + L"6.0 Special Conditions\\ENC_ROOT\\AA3ARSPC__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101SPCN.000";
	cell->Save(outPath + L"6.0 Special Conditions\\ENC_ROOT\\AAS101SPCN.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer; 
	layer = new S101Layer();
	layer->Open(orgPath + L"7.0 Safety Contour\\ENC_ROOT\\AA3SAFCO__.000");
	cell = (S101Cell*)layer->m_spatialObject;
	cell->m_dsgir.m_dsid.m_dsnm = L"AAS101SFCO.000";
	cell->Save(outPath + L"7.0 Safety Contour\\ENC_ROOT\\AAS101SFCO.000", L"000");
	WriteCellBoundary(&file, cell);
	delete layer;

	file.Close();
}

void CDialogTDSDataset::WriteCellBoundary(CFile *file, S101Cell* cell)
{
	if (!file)
		return;

	CString seperateLine = L"-";
	CString nextLine = L"\r\n";

	CString str;
	CString s1;
	R_FeatureRecord *fr;
	__int64 iKey;
	POSITION pos = cell->m_feaMap.GetStartPosition();

	str.Format(L"%s", cell->m_dsgir.m_dsid.m_dsnm);
	str.Append(nextLine);

	str.Append(L"Full Coverage : ");

	auto mbr = cell->GetMBR();

	double xmin = mbr.xmin;
	double xmax = mbr.xmax;
	double ymin = mbr.ymin;
	double ymax = mbr.ymax;

	m_pView->m_pGisLib->InverseProjection(&xmin, &ymin);
	m_pView->m_pGisLib->InverseProjection(&xmax, &ymax);

	s1.Format(L"%.06f %.06f %.06f %.06f"
		, xmin
		, ymin
		, xmax
		, ymax);
	str.Append(s1);
	str.Append(nextLine);

	while (pos != NULL)
	{
		cell->m_feaMap.GetNextAssoc(pos, iKey, fr);

		auto itor = cell->m_dsgir.m_ftcs->m_arr.find(fr->m_frid.m_nftc);
		if (itor != cell->m_dsgir.m_ftcs->m_arr.end())
		{
			CodeWithNumericCode* nc = itor->second;

			if (nc->m_code.Compare(L"DataCoverage") == 0)
			{ 
				xmin = fr->m_geometry->m_mbr.xmin;
				xmax = fr->m_geometry->m_mbr.xmax;
				ymin = fr->m_geometry->m_mbr.ymin;
				ymax = fr->m_geometry->m_mbr.ymax;

				m_pView->m_pGisLib->InverseProjection(&xmin, &ymin);
				m_pView->m_pGisLib->InverseProjection(&xmax, &ymax);

				s1.Format(L"%.06f %.06f %.06f %.06f"
					, xmin
					, ymin
					, xmax
					, ymax);
				str.Append(s1);
				str.Append(nextLine);
			}
		}
	} 
	str.Append(_T("Encoding specification : "));
	str.Append(cell->m_dsgir.m_dsid.m_ensp);
	str.Append(nextLine);

	str.Append(_T("Encoding specification edition : "));
	str.Append(cell->m_dsgir.m_dsid.m_ened);
	str.Append(nextLine);

	str.Append(_T("Product identifier : "));
	str.Append(cell->m_dsgir.m_dsid.m_prsp);
	str.Append(nextLine);

	str.Append(_T("Product edition : "));
	str.Append(cell->m_dsgir.m_dsid.m_pred);
	str.Append(nextLine);

	str.Append(_T("Application profile : "));
	str.Append(cell->m_dsgir.m_dsid.m_prof);
	str.Append(nextLine);

	str.Append(_T("Dataset file identifier : "));
	str.Append(cell->m_dsgir.m_dsid.m_dsnm);
	str.Append(nextLine);

	str.Append(_T("Dataset title : "));
	str.Append(cell->m_dsgir.m_dsid.m_dstl);
	str.Append(nextLine);

	str.Append(_T("Dataset reference date : "));
	str.Append(cell->m_dsgir.m_dsid.m_dsrd);
	str.Append(nextLine);

	str.Append(_T("Dataset language : "));
	str.Append(cell->m_dsgir.m_dsid.m_dslg);
	str.Append(nextLine);

	str.Append(_T("Dataset abstract : "));
	str.Append(cell->m_dsgir.m_dsid.m_dsab);
	str.Append(nextLine);

	str.Append(_T("Dataset edition : "));
	str.Append(cell->m_dsgir.m_dsid.m_dsed);
	str.Append(nextLine);

	for (int i = 0; i < cell->m_dsgir.m_dsid.m_dstc.GetSize(); i++)
	{
		int valueInt = cell->m_dsgir.m_dsid.m_dstc.GetAt(i);

		s1.Format(L"%d", valueInt);
		str.Append(_T("A set of topic categories : "));
		str.Append(s1);
		str.Append(nextLine);
	}

	file->Write(str, str.GetLength() * 2);
}