// PropertyModify.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "PropertyGridAttributeModify.h"
#include "resource.h"
#include "DockablePaneAttributeList.h"
#include "DockablePaneEditWindow.h"
#include "GISViewer.h"

#include"GISViewerView.h"


#include "..\\FeatureCatalog\\FeatureCatalogue.h"

#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\F_ATTR.h"
#include "GISLibrary\\S101Cell.h"
#include "GISLibrary\\S100Layer.h"
#include "GISLibrary\\R_InformationRecord.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\ATTR.h"
#include "GISLibrary\\CodeWithNumericCode.h"

#include "..\\FeatureCatalog\\AttributeBinding.h"
#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"

#include <string.h>  

IMPLEMENT_DYNAMIC(CPropertyGridAttributeModify, CMFCPropertyGridCtrl)

CPropertyGridAttributeModify::CPropertyGridAttributeModify()
{
	pSelectedProperty = NULL;
}

CPropertyGridAttributeModify::~CPropertyGridAttributeModify()
{
}


BEGIN_MESSAGE_MAP(CPropertyGridAttributeModify, CMFCPropertyGridCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_ATTRIBUTE_DEL, &CPropertyGridAttributeModify::OnDeleteAttribute)
	ON_COMMAND(ID_ATTRIBUTEEDIT_OPEN, &CPropertyGridAttributeModify::OnAttributeeditOpen)
	ON_COMMAND(ID_ATTTRIBUTEEDIT_DELETE, &CPropertyGridAttributeModify::OnAtttributeeditDelete)
END_MESSAGE_MAP()


S101Cell* CPropertyGridAttributeModify::GetS101Cell()
{
	return (S101Cell*)spatialObject;
} 
void CPropertyGridAttributeModify::OnLButtonDown(UINT nFlags, CPoint point)
{  
	CMFCPropertyGridProperty::ClickArea clickArea;
	CMFCPropertyGridProperty *pProp = HitTest(point, &clickArea);

	if (theApp.IsViewerMode())
	{
		return;
	}

	if (!spatialObject)
	{
		return;
	}

	auto layer = (S100Layer*)spatialObject->m_pLayer;
	auto fc = layer->GetFC();

	if (pProp != nullptr)
	{
		auto complexAttribute = fc->m_pCatalogueList.begin()->second->GetComplexAttributeFromName(pProp->GetName());
		MultiData *multiData = (MultiData *)pProp->GetData();
		ATTR *attr = (ATTR *)multiData->data[2];
		int type = multiData->data[3];



		int attributeIndex;
		if (type == 0)
		{
			auto feature = (R_FeatureRecord*)multiData->data[1];
			attributeIndex = feature->GetAttributeIndex(attr);
		}
		else
		{
			auto info = (R_InformationRecord*)multiData->data[1];
			attributeIndex = info->GetAttributeIndex(attr);
		}

		if (complexAttribute != nullptr) 
		{ 
			int Nodenumber = attributeIndex;
			theApp.GetDockFeatureInformationList().m_treeCtrl.DeleteAllItems();
			AttributeBinding *ab = nullptr;
			for (auto itor = complexAttribute->subAttributeBinding.begin(); itor != complexAttribute->subAttributeBinding.end(); itor++)
			{
				ab = &(*itor);
				theApp.m_DockablePaneAttributeList.ComplexSetShowTree(fc, ab); 
				theApp.GetDockFeatureInformationList().SetParentProperty(pProp); 
				theApp.GetDockFeatureInformationList().SetindexNum(Nodenumber); 
			}
		}
		else 
		{ 
			theApp.m_DockablePaneAttributeList.BaseSetShowThee();
			theApp.GetDockFeatureInformationList().SetParentProperty(nullptr);//추가될값을 초기화해줍니다.
			theApp.GetDockFeatureInformationList().SetindexNum(0);
		}
	}
	else
	{ 
		theApp.m_DockablePaneAttributeList.BaseSetShowThee();
		theApp.GetDockFeatureInformationList().SetParentProperty(nullptr);//추가될값을 초기화해줍니다.
		theApp.GetDockFeatureInformationList().SetindexNum(0);
	}
	CMFCPropertyGridCtrl::OnLButtonDown(nFlags, point);
}

void CPropertyGridAttributeModify::OnRButtonDown(UINT nFlags, CPoint point)//마우스 오른쪽클릭
{ 
	CMFCPropertyGridProperty::ClickArea clickArea;
	CMFCPropertyGridProperty* pHit = HitTest(point, &clickArea);

	if (theApp.IsViewerMode())
	{
		return;
	}

	if (clickArea == CMFCPropertyGridProperty::ClickName ||
		clickArea == CMFCPropertyGridProperty::ClickValue)
	{
		ATTR* attr = (ATTR*)pHit->GetData(); 

		CPoint point;
		::GetCursorPos(&point);
		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU_EDIT_PANE));

		CString  value = pHit->GetValue();
		if (value != "")
		{
			CMenu* popup = menu.GetSubMenu(0);
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		}
		else
		{
			CMenu* popup = menu.GetSubMenu(4);
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		}

		pSelectedProperty = pHit;
	}
	return;
}
void CPropertyGridAttributeModify::OnDeleteAttribute()
{
	CWnd* pParent = GetParent(); 
	if (pSelectedProperty) 
	{ 
		MultiData *multiData = (MultiData *)pSelectedProperty->GetData();
		if (multiData == nullptr)
		{
			return;
		}
		ATTR *attr = (ATTR *)multiData->data[2];

		CString name = pSelectedProperty->GetName(); 
		auto s101Cell = GetS101Cell();
		auto DGIR = s101Cell->GetDatasetGeneralInformationRecord();
		auto attributeCode = DGIR->GetAttributeCode(attr->m_natc);

		if (CheckingAttriData(attributeCode))
		{
			pParent->PostMessage(WM_TRANSLATION_MESSAGE_TO_PARENT_DELETE_ATTRIBUTE, (WPARAM)this->m_hWnd, (LPARAM)pSelectedProperty);//pMsg->wParam, pMsg->lParam);
		}
		else
		{
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"You can't delete this data anymore.", KRS_MSG_PROCESS::User_Mode, KRS_MSG_PROCESS::DataSet);
		}

		theApp.m_DockablePaneAttributeList.BaseSetShowThee();
		theApp.GetDockFeatureInformationList().SetParentProperty(nullptr);//추가될값을 초기화해줍니다.
		theApp.GetDockFeatureInformationList().SetindexNum(0);
	}
}
void CPropertyGridAttributeModify::SetSpatialObject(SpatialObject *spatialObject)
{
	this->spatialObject = spatialObject;
}
void CPropertyGridAttributeModify::ComplexAttriIndexnumSet(int num)
{
	this->ComplexAttriIndexnum = num;
}
int CPropertyGridAttributeModify::ComplexAttriIndexnumGet()
{
	return ComplexAttriIndexnum;
}
void CPropertyGridAttributeModify::OnAttributeeditOpen()
{
	if (pSelectedProperty != nullptr) 
	{
		CString Value = pSelectedProperty->GetValue(); 
		{
			ShellExecute(NULL, _T("open"), _T("iexplore"), NULL, NULL, SW_SHOW); 
		}
	}
}
void CPropertyGridAttributeModify::OnAtttributeeditDelete() 
{
	OnDeleteAttribute();  
}

bool CPropertyGridAttributeModify::CheckingAttriData(CString inputName)
{
	auto mainParent = this; 
	int attriCount = 0;
	auto propertyParent = pSelectedProperty->GetParent();
	if (propertyParent == nullptr)
	{
		int itemCount = mainParent->GetPropertyCount(); 
		for (int i = 0; i < itemCount; i++)
		{
			MultiData* data = (MultiData*)mainParent->GetProperty(i)->GetData();
			ATTR *attribute = (ATTR*)data->data[2];

			auto s101Cell = GetS101Cell();
			auto DGIR = s101Cell->GetDatasetGeneralInformationRecord();
			auto attributeCode = DGIR->GetAttributeCode(attribute->m_natc);  
			if (attributeCode.Compare(inputName) == 0)
			{
				attriCount++; 
			}
		}

	}
	else
	{
		auto itemCount = propertyParent->GetSubItemsCount(); 
		for (int i = 0; i < itemCount; i++)
		{
			MultiData* data = (MultiData*)propertyParent->GetSubItem(i)->GetData();
			ATTR *attribute = (ATTR*)data->data[2];

			auto s101Cell = GetS101Cell();
			auto DGIR = s101Cell->GetDatasetGeneralInformationRecord();
			auto attributeCode = DGIR->GetAttributeCode(attribute->m_natc);

			if (attributeCode.Compare(inputName) == 0)
			{
				attriCount++; 
			}
		}
	} 

	int lower = 0;
	auto layer = (S100Layer*)spatialObject->m_pLayer;
	Catalog* fc = layer->GetFC();

	if (theApp.pView->SelectedFeatureType != nullptr || theApp.m_DockablePaneEditWindow.m_pFeature != nullptr)
	{
		std::wstring featureTypename = theApp.pView->SelectedFeatureType->code.GetValueString();
		FeatureType* FeatureType = fc->m_pCatalogueList.begin()->second->GetFeatureType(featureTypename);
		std::list<AttributeBinding> attributeBinding = FeatureType->attributeBinding;

		if (propertyParent != nullptr) 
		{
			MultiData* data = (MultiData*)propertyParent->GetData();
			ATTR *attribute = (ATTR*)data->data[2];

			auto s101Cell = GetS101Cell();
			auto DGIR = s101Cell->GetDatasetGeneralInformationRecord();
			CString parentName = DGIR->GetAttributeCode(attribute->m_natc);

			for each (AttributeBinding attribind in attributeBinding)
			{ 
				CString attriname = attribind.attribute.Getattributes().begin()->Getvalue().c_str();
				if (attriname.Compare(parentName) == 0)
				{
					ComplexAttribute* ca = fc->m_pCatalogueList.begin()->second->GetComplexAttribute(wstring(parentName));
					if (ca)
					{
						for each (AttributeBinding subAttr in ca->subAttributeBinding)
						{
							CString name = subAttr.attribute.Getattributes().begin()->Getvalue().c_str();
							if (name.Compare(inputName) == 0)
							{
								lower = subAttr.multiplicity.lower;
								break;
							}

						}
					}
				}
			}
		}
		else 
		{
			for each (AttributeBinding attribind in attributeBinding)
			{
				auto test = attribind.multiplicity.upper.Getattributes();
				std::wstring attriname = attribind.attribute.Getattributes().begin()->Getvalue();

				if (attriname.compare(inputName) == 0)
				{
					lower = attribind.multiplicity.lower;

					ComplexAttribute* ca = fc->m_pCatalogueList.begin()->second->GetComplexAttribute(wstring(inputName));
					if (ca != nullptr)
					{
						theApp.m_DockablePaneAttributeList.BaseSetShowThee();
						theApp.GetDockFeatureInformationList().SetParentProperty(nullptr);//추가될값을 초기화해줍니다.
						theApp.GetDockFeatureInformationList().SetindexNum(0);
					}
					break;
				}
			}
		}


	}

	if (theApp.m_DockablePaneEditWindow.m_pInformation != nullptr)
	{
		auto informationTypesdf = theApp.m_DockablePaneEditWindow.m_pInformation;
		auto cell = (S101Cell*)spatialObject;
		auto itor = cell->m_dsgir.m_itcs->m_arr.find(informationTypesdf->m_irid.m_nitc);


		auto informationType = fc->m_pCatalogueList.begin()->second->GetInformationType(std::wstring(itor->second->m_code));

		std::list<AttributeBinding> attributeBinding = informationType->attributeBinding;
		int i = 0;

		if (propertyParent != nullptr) 
		{
			MultiData* data = (MultiData*)propertyParent->GetData();
			ATTR *attribute = (ATTR*)data->data[2];

			auto s101Cell = GetS101Cell();
			auto DGIR = s101Cell->GetDatasetGeneralInformationRecord();
			CString parentName = DGIR->GetAttributeCode(attribute->m_natc);

			for each (AttributeBinding attribind in attributeBinding)
			{ 
				CString attriname = attribind.attribute.Getattributes().begin()->Getvalue().c_str();
				if (attriname.Compare(parentName) == 0)
				{
					ComplexAttribute* ca = fc->m_pCatalogueList.begin()->second->GetComplexAttribute(wstring(parentName));
					if (ca)
					{
						for each (AttributeBinding subAttr in ca->subAttributeBinding)
						{
							CString name = subAttr.attribute.Getattributes().begin()->Getvalue().c_str();
							if (name.Compare(inputName) == 0)
							{
								lower = subAttr.multiplicity.lower;
								break;
							}

						}
					}
				}
			}
		}
		else 
		{
			for each (AttributeBinding attribind in attributeBinding)
			{
				auto test = attribind.multiplicity.upper.Getattributes();
				std::wstring attriname = attribind.attribute.Getattributes().begin()->Getvalue();

				if (attriname.compare(inputName) == 0)
				{
					lower = attribind.multiplicity.lower;

					ComplexAttribute* ca = fc->m_pCatalogueList.begin()->second->GetComplexAttribute(wstring(inputName));
					if (ca != nullptr)
					{
						theApp.m_DockablePaneAttributeList.BaseSetShowThee();
						theApp.GetDockFeatureInformationList().SetParentProperty(nullptr);//추가될값을 초기화해줍니다.
						theApp.GetDockFeatureInformationList().SetindexNum(0);
					}
					break;
				}
			}
		}
	}


	if ((attriCount - 1) < lower)
	{
		return false;
	}

	else
	{
		return true;
	}
}
