// FeatureView.cpp : implementation file 

#include "stdafx.h"
#include "GISViewer.h"
#include "DockablePaneEditWindow.h"
#include "resource.h"
#include "GISViewerView.h"

#include "..\\S100EditingResource\\EditingContent.h"
#include "..\\FeatureCatalog\\FeatureCatalogue.h"
#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"

#include "GISLibrary\\S101Layer.h"
#include "GISLibrary\\ENC_S101_Factory.h"
#include "GISLibrary\\ATTF.h"
#include "GISLibrary\\ATTV.h"
#include "GISLibrary\\VRPT.h"
#include "GISLibrary\\NATF.h"
#include "GISLibrary\\FSPT.h"
#include "GISLibrary\\F_CUCO.h"
#include "GISLibrary\\F_PTAS.h"
#include "GISLibrary\\F_SPAS.h"
#include "GISLibrary\\F_C3IL.h"
#include "GISLibrary\\F_C2IL.h"
#include "GISLibrary\\F_C2IT.h"
#include "GISLibrary\\F_ATTR.h"
#include "GISLibrary\\F_RIAS.h"
#include "GISLibrary\\R_InformationRecord.h"
#include "GISLibrary\\R_MultiPointRecord.h"
#include "GISLibrary\\R_CurveRecord.h"
#include "GISLibrary\\R_CompositeRecord.h"
#include "GISLibrary\\R_SurfaceRecord.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\R_PointRecord.h"
#include "GISLibrary\\ATTR.h"
#include "GISLibrary\C3IL.h"
#include "GISLibrary\\IC2D.h"
#include "GISLibrary\\CodeWithNumericCode.h"
#include "GISLibrary\\CUCO.h"
#include "GISLibrary\\SPAS.h"
#include "GISLibrary\\PTAS.h"
#include "GISLibrary\\RIAS.h"

#include "PLLibrary\\Attribute.h"
#include "PLLibrary\\AttributeListValue.h"

#include <vector>
#include <sstream>
#include <string>     

const UINT WM_FILTER_LIST = ::RegisterWindowMessage(_T("WM_FILTER_LIST"));   

CPropertyGridAttributeModify	CDockablePaneEditWindow::m_wndListAttribute; 


IMPLEMENT_DYNAMIC(CDockablePaneEditWindow, CDockablePane)

CDockablePaneEditWindow::CDockablePaneEditWindow()
{
	m_pView = NULL;
	m_pObject = NULL;
	m_pFeature = NULL;
}

CDockablePaneEditWindow::~CDockablePaneEditWindow()
{
	DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CDockablePaneEditWindow, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP() 
BOOL CDockablePaneEditWindow::MoveVectorToPoint(int x, int y)
{
	S101Cell* cell = (S101Cell*)m_cell;

	CString msg;
	double dx = x / (double)cell->m_dsgir.m_dssi.m_cmfx;
	double dy = y / (double)cell->m_dsgir.m_dssi.m_cmfy;

	msg.Format(L"%.07f, %07f", dx, dy);
	m_wndListVector.pSelectedProperty->SetValue(msg);

	return TRUE;
} 
LRESULT CDockablePaneEditWindow::OnPropertyChanged(WPARAM wparam, LPARAM lparam)
{ 
	if (m_cell->m_FileType == FILE_S_57)
	{
		ENCCell* cell = (ENCCell*)m_cell;

		UINT nID = (UINT)wparam;
		CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)lparam;
		if (!pProp)
			return 0;

		if (nID == IDC_PROPERTY_GRID_VECTOR)
		{
			std::wstring name = pProp->GetName();
			CString value = pProp->GetValue().bstrVal;

			AfxMessageBox(L"" + value);

			CString xValue, yValue;

			AfxExtractSubString(xValue, value, 0, ',');
			AfxExtractSubString(yValue, value, 1, ',');

			MultiData* md = (MultiData*)pProp->GetData();
			if (name.compare(L"SG2D") == 0)
			{
				SG2D* sg2d = (SG2D*)md->data[2];
				sg2d->XCOO = _wtoi(xValue);
				sg2d->YCOO = _wtoi(yValue);
			}

			cell->MakeFullSpatialData();
		}
		else if (nID == IDC_PROPERTY_GRID_ATTRIBUTE)
		{ 
			MultiData* md = (MultiData*)pProp->GetData();
			INT_PTR type = md->type;

			NATF* natf = NULL;
			ATTF* attf = NULL;
			CAttribute* pAttr = NULL;

			if (type == 1)
			{
				attf = (ATTF*)md->data[1];
				pAttr = ENCGeometry::pAttribute->GetAttributeFromCode(attf->ATTL);
				if (pAttr->Attribute_type == CAttributeMap::ENUMERATED ||
					pAttr->Attribute_type == CAttributeMap::LIST)
				{
					CString tstr = pProp->GetValue().bstrVal;
					attf->ATVL = L"";

					int curPos = 0;
					CString resToken = tstr.Tokenize(_T(",/"), curPos);
					while (resToken != _T(""))
					{
						resToken;

						for (auto itor = pAttr->valueList.begin(); itor != pAttr->valueList.end(); itor++)
						{
							AttributeListValue* av = *itor;

							if (resToken.Find(av->name.c_str()) == 0)
							{
								if (attf->ATVL.size() > 0)
								{
									attf->ATVL.append(L",");
								}
								attf->ATVL.append(to_wstring(av->index - 1));
							}
						}
						resToken = tstr.Tokenize(_T(",/"), curPos);
					}
				}
				else
				{
					attf->ATVL = pProp->GetValue().bstrVal;
				}
			}
			else if (type == 2)
			{
				natf = (NATF*)md->data[1];
				natf->ATVL = pProp->GetValue().bstrVal;
			}
			cell->GetFeatureDisplayOption(m_pObject);
			cell->GetEffectiveFeatures();
			cell->GetDisplayFeatures();

			if (m_pView)
			{
				m_pView->MapRefresh();
			}

		}
	}
	else if (
		m_cell->m_FileType == FILE_S_100_VECTOR            
		)
	{
		S101Cell* cell = (S101Cell*)m_cell;

		UINT nID = (UINT)wparam;
		CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)lparam;

		if (!pProp)
			return 0;

		if (nID == IDC_PROPERTY_GRID_VECTOR)
		{
			std::wstring name = pProp->GetName();
			CString value = pProp->GetValue().bstrVal;

			CString xValue, yValue;

			AfxExtractSubString(xValue, value, 0, ',');
			AfxExtractSubString(yValue, value, 1, ',');

			int x = (int)(_wtof(xValue) * cell->m_dsgir.m_dssi.m_cmfx);
			int y = (int)(_wtof(yValue) * cell->m_dsgir.m_dssi.m_cmfy);                   

			if (m_pEdtContent)
			{
				m_pEdtContent->LButtonUp(x, y);
				m_pView->Invalidate();
			}  
		}
		else if (nID == IDC_PROPERTY_GRID_ATTRIBUTE)
		{ 
			MultiData* md = (MultiData*)pProp->GetData();
			ATTR* attr = (ATTR*)md->data[2];

			if (!attr)
			{
				AfxMessageBox(L"ERROR");
				return 0;
			}

			Catalog* catalog = ((S101Layer*)cell->m_pLayer)->GetFC();
			auto aitor = cell->m_dsgir.m_atcs->m_arr.find(attr->m_natc);

			SimpleAttribute* sa = catalog->m_pCatalogueList.begin()->second->GetSimpleAttribute(aitor->second->m_code.GetBuffer());

			if (sa)
			{
				if (sa->valueType.GetValueString().compare(L"enumeration") == 0)
				{
					std::wstring propValue = pProp->GetValue().bstrVal;

					int numindex = (propValue.find('.')) + 1;
					if (numindex > 0)
					{
						propValue.erase(propValue.begin(), propValue.begin() + numindex);
					}
					for (auto	itor = (*sa->listedValues.begin()).listedValue.begin();
						itor != (*sa->listedValues.begin()).listedValue.end();
						itor++)
					{
						ListedValue* lv = &itor->second;

						if (propValue.compare(lv->label.c_str()) == 0)
						{
							char buf[10];
							_itoa_s(lv->code.GetvalueInteger(), buf, 10);
							attr->m_atvl = buf;
						}
					}
				}
				else
				{
					attr->m_atvl = pProp->GetValue().bstrVal;//값을 추가합니다.
				}
			}

			m_pView->m_pGisLib->BuildS101Portrayal(cell->m_pLayer);
			m_pView->MapRefresh();
		}
	}
	return 0;
}
int CDockablePaneEditWindow::OnCreate(LPCREATESTRUCT lp)
{
	if (CDockablePane::OnCreate(lp) == -1)
	{
		return -1;
	}    

	CRect rect;
	GetClientRect(&rect);

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1; 
	}
	m_wndTabs.HideSingleTab(TRUE); 
	if (!m_wndListAttribute.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL
		| LVS_REPORT, rect, &m_wndTabs, IDC_PROPERTY_GRID_ATTRIBUTE)
		)
	{
		TRACE0("Failed to create Nodes List\n");
		return -1;
	}
	m_wndListAttribute.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_wndListAttribute.EnableHeaderCtrl(FALSE);
	m_wndListAttribute.EnableDescriptionArea();
	m_wndListAttribute.SetVSDotNetLook();
	m_wndListAttribute.MarkModifiedProperties();

	m_wndTabs.AddTab(&m_wndListAttribute, L"Attribute Information", (UINT)0, 0);

	::ShowScrollBar(m_wndListAttribute.GetSafeHwnd(), SB_VERT, FALSE);

#ifndef _S101_VIEWER
	if (!m_wndListVector.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL
		| LVS_REPORT, rect, &m_wndTabs, IDC_PROPERTY_GRID_VECTOR)
		) 
	{
		TRACE0("Failed to create Nodes List\n");
		return -1;
	}
	m_wndListVector.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	m_wndListVector.EnableHeaderCtrl(FALSE);
	m_wndListVector.EnableDescriptionArea();
	m_wndListVector.SetVSDotNetLook();
	m_wndListVector.MarkModifiedProperties();

	m_wndTabs.AddTab(&m_wndListVector, L"Vector Information", (UINT)0, 0);

	::ShowScrollBar(m_wndListVector.GetSafeHwnd(), SB_VERT, FALSE);

#else
	if (!m_wndListVector.Create(WS_CHILD | PGF_INVISIBLE | WS_CLIPSIBLINGS | WS_VSCROLL
		| LVS_REPORT, rect, &m_wndTabs, IDC_PROPERTY_GRID_VECTOR)
		)
	{
		TRACE0("Failed to create Nodes List\n");
		return -1;
	}
#endif

	return 0;
}

bool CDockablePaneEditWindow::ChcekAttribteUpperValue(AttributeBinding* ab)
{
	XML_Attribute *attr = NULL;
	for (auto itor = ab->attribute.Getattributes().begin(); itor != ab->attribute.Getattributes().end(); itor++)
	{
		attr = &(*itor);

		if (attr->Getname().compare(L"ref") == 0)
		{
			break;
		}
	}

	std::wstring attrName;
	if (!attr)
	{
		return false;
	}

	else
	{
		Catalog* catalog = ((S101Layer*)m_cell->m_pLayer)->GetFC();
		SimpleAttribute* sa = catalog->m_pCatalogueList.begin()->second->GetSimpleAttribute(attr->Getvalue());
		if (sa)
		{
			attrName = sa->name;
		}

		ComplexAttribute* ca = catalog->m_pCatalogueList.begin()->second->GetComplexAttribute(attr->Getvalue());
		if (ca)
		{
			attrName = ca->name;
		}
	}

	XML_Attribute *upperAttr = NULL;
	for (auto itor = ab->multiplicity.upper.Getattributes().begin(); itor != ab->multiplicity.upper.Getattributes().end(); itor++)
	{
		upperAttr = &(*itor);

		if (upperAttr->Getname().compare(L"infinite") == 0)
		{
			break;
		}
	}

	int upperCount = 0;
	if (upperAttr)
	{
		if (upperAttr->Getvalue().compare(L"true") == 0)
		{
			return true;
		}
		else
		{
			upperCount = _wtoi(ab->multiplicity.upper.Getvalue().c_str());
		}
	}

	int attrCount = 0;
	int count = m_wndListAttribute.GetPropertyCount();
	for (int i = 0; i < count; i++)
	{
		CMFCPropertyGridProperty *pProperty = m_wndListAttribute.GetProperty(i);

		wstring name = pProperty->GetName();
		if (name.compare(attrName) == 0)
		{
			attrCount++;
			if (attrCount >= upperCount)
			{
				return false;
			}
		}
	}

	return true;
}

void CDockablePaneEditWindow::AddAttribute(CAttribute* pAttr)
{
	CMFCPropertyGridProperty *pAttribute = NULL;
	if (pAttr->Indication == CAttributeMap::NATIONAL)
	{ 

		int code = ENCGeometry::pAttribute->GetCodeFromAcronym(pAttr->Acronym);
		for (auto itor = m_pObject->m_natfList.begin(); itor != m_pObject->m_natfList.end(); itor++)
		{
			NATF* natfCheck = *itor;
			if (natfCheck->ATTL == code)
			{
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"You can't input this attribute", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
				return;
			}
		}

		pAttribute = new CMFCPropertyGridProperty(pAttr->Attribute_name, L"");
		NATF* natf = new NATF();
		natf->ATTL = code;
		m_pObject->m_natfList.push_back(natf);

		CString decription;
		decription.Format(L"Arcronym : %s", pAttr->Acronym);

		pAttribute->SetDescription(decription);

		MultiData *multiData = InsertPropertyMultiData(12, pAttribute, (DWORD_PTR)(NATF*)natf);
		pAttribute->SetData((DWORD_PTR)multiData);
	}
	else
	{ 
		int code = ENCGeometry::pAttribute->GetCodeFromAcronym(pAttr->Acronym);
		for (auto itor = m_pObject->m_attfList.begin(); itor != m_pObject->m_attfList.end(); itor++)
		{
			ATTF* attfCheck = *itor;
			if (attfCheck->ATTL == code)
			{
				AfxMessageBox(L"You can't input this attribute");
				return;
			}
		}

		pAttribute = new CMFCPropertyGridProperty(pAttr->Attribute_name, L"");
		ATTF* attf = new ATTF();
		attf->ATTL = code;

		m_pObject->m_attfList.push_back(attf);

		CString decription;
		decription.Format(L"Arcronym : %s", pAttr->Acronym);

		pAttribute->SetDescription(decription);

		MultiData *multiData = InsertPropertyMultiData(11, pAttribute, (DWORD_PTR)(ATTF*)attf);
		pAttribute->SetData((DWORD_PTR)multiData);

		if (pAttr->Attribute_type == CAttributeMap::ENUMERATED ||
			pAttr->Attribute_type == CAttributeMap::LIST
			)
		{ 
			for (auto itor = pAttr->valueList.begin(); itor != pAttr->valueList.end(); itor++)
			{
				AttributeListValue* av = (*itor);

				if (av->name.size() <= 0)
					continue;

				CString tstr;
				tstr.Format(L"%s(%d)", av->name.c_str(), av->index);
				pAttribute->AddOption(tstr);
			} 
		}
	}
	m_wndListAttribute.AddProperty(pAttribute);

	return;
}

void CDockablePaneEditWindow::AddAttribute(AttributeBinding* ab, CMFCPropertyGridProperty *pSuperProperty, unsigned newParentIndex)
{
	XML_Attribute *attr = nullptr;
	auto attribute = ab->attribute.Getattributes();
	for (auto itor = attribute.begin(); itor != attribute.end(); itor++)
	{
		attr = &(*itor);
		if (attr->Getname().compare(L"ref") == 0)
		{
			break;
		}
	}

	if (!attr)
	{
		return;
	}        

	Catalog* catalog = ((S101Layer*)m_cell->m_pLayer)->GetFC();
	if (!CheckingAttriData(ab, attr->Getvalue().c_str(), pSuperProperty))
	{

		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_ERROR, L"This attribute cannot be added anymore.", KRS_MSG_PROCESS::User_Mode, KRS_MSG_PROCESS::DataSet);
		return;
	}

	SimpleAttribute* sa = catalog->m_pCatalogueList.begin()->second->GetSimpleAttribute(attr->Getvalue());
	if (sa) 
	{
		AddSimpleAttribute(sa, pSuperProperty, newParentIndex);
	}
	ComplexAttribute* ca = catalog->m_pCatalogueList.begin()->second->GetComplexAttribute(attr->Getvalue());
	if (ca)
	{
		AddComplexAttribute(ca, pSuperProperty, newParentIndex);
	}
	return;
}

void CDockablePaneEditWindow::AddSimpleAttribute(SimpleAttribute* sa, CMFCPropertyGridProperty *pSuperProperty, unsigned parentIndex)
{
	if (m_cell->m_FileType == FILE_S_100_VECTOR)
	{
		S101Cell* cell = (S101Cell*)m_cell;

		int atix = 1;
		CMFCPropertyGridProperty *pProperty = new CMFCPropertyGridProperty(sa->name.c_str(), L"");
		pProperty->SetDescription(sa->definition.c_str());

		if (sa->valueType.GetValueString().compare(L"enumeration") == 0) 
		{
			SettingEnumType(sa->listedValues, pProperty);
		}

		ATTR* attr = new ATTR();
		F_ATTR* attrParent = nullptr; 


		if (m_pFeature != nullptr)
		{
			if (m_pFeature->m_attr.begin() != m_pFeature->m_attr.end())
			{
				attrParent = *m_pFeature->m_attr.begin();
			}
			else
			{
				attrParent = new F_ATTR();
				m_pFeature->m_attr.push_back(attrParent);
			}

			auto itor = cell->m_dsgir.m_atcs->m_arrFindForCode.find(sa->code.GetValueString()); 
			if (itor == cell->m_dsgir.m_atcs->m_arrFindForCode.end())
			{ 
				attr->m_natc = GetATCS(sa->code.GetValueString());
			}
			else
			{
				attr->m_natc = itor->second->m_nmcd;
			}

			attr->m_paix = parentIndex; 
			attr->m_atin = 1; 
			attr->m_atix = GetATIX(attr->m_natc, parentIndex);
			attrParent->m_arr.push_back(attr);

			MultiData *multiData = InsertPropertyMultiData(111, pProperty, (DWORD_PTR)m_pFeature, (DWORD_PTR)attr, 0);
			pProperty->SetData((DWORD_PTR)multiData);

		}

		if (m_pInformation != nullptr)
		{
			if (m_pInformation->m_attr.begin() != m_pInformation->m_attr.end())
			{
				attrParent = *m_pInformation->m_attr.begin();
			}
			else
			{
				attrParent = new F_ATTR();
				m_pInformation->m_attr.push_back(attrParent);
			}

			auto itor = cell->m_dsgir.m_atcs->m_arrFindForCode.find(sa->code.GetValueString()); 
			if (itor == cell->m_dsgir.m_atcs->m_arrFindForCode.end())
			{ 
				attr->m_natc = GetATCS(sa->code.GetValueString());
			}
			else
			{
				attr->m_natc = itor->second->m_nmcd;
			}

			attr->m_paix = parentIndex; 
			attr->m_atin = 1; 
			attr->m_atix = GetATIX(attr->m_natc, parentIndex);
			attrParent->m_arr.push_back(attr);

			MultiData *multiData = InsertPropertyMultiData(111, pProperty, (DWORD_PTR)m_pInformation, (DWORD_PTR)attr, 1);
			pProperty->SetData((DWORD_PTR)multiData);
		}

		if (pSuperProperty) 
		{
			pSuperProperty->AddSubItem(pProperty);
		}
		else
		{
			m_wndListAttribute.AddProperty(pProperty);
		}
		m_wndListAttribute.ExpandAll();
	}

	return;
}

void CDockablePaneEditWindow::AddComplexAttribute(ComplexAttribute* ca, CMFCPropertyGridProperty *pSuperProperty, unsigned parentIndex)
{
	if (m_cell->m_FileType == FILE_S_100_VECTOR)
	{
		S101Cell* cell = GetS101Cell(); 
		CMFCPropertyGridProperty *pProperty = new CMFCPropertyGridProperty(ca->name.c_str());
		pProperty->SetDescription(ca->definition.c_str());
		pProperty->AllowEdit(FALSE);
		if (!pSuperProperty)
		{
			pProperty->Expand(FALSE);
		}

		if (pSuperProperty)
		{
			pSuperProperty->AddSubItem(pProperty);
		}
		else
		{
			m_wndListAttribute.AddProperty(pProperty);
		}

		ATTR* attr = new ATTR();
		F_ATTR* attrParent = nullptr;
		int attributeIndex = 0; 
		if (m_pFeature != nullptr)
		{  
			if (m_pFeature->m_attr.size() > 0)
			{
				attrParent = *m_pFeature->m_attr.begin();
			} 
			else
			{
				attrParent = new F_ATTR();
				m_pFeature->m_attr.push_back(attrParent);
			} 
			auto itor = cell->m_dsgir.m_atcs->m_arrFindForCode.find(ca->code.GetValueString());
			if (itor == cell->m_dsgir.m_atcs->m_arrFindForCode.end())
			{
				attr->m_natc = GetATCS(ca->code.GetValueString());
			}
			else
			{
				attr->m_natc = itor->second->m_nmcd;
			}


			attr->m_atix = GetATIX(attr->m_natc, parentIndex);
			attr->m_paix = parentIndex;
			attr->m_atin = 1;
			attrParent->m_arr.push_back(attr);

			attributeIndex = m_pFeature->GetAttributeIndex(attr);

			MultiData *multiData = InsertPropertyMultiData(111, pProperty, (DWORD_PTR)m_pFeature, (DWORD_PTR)attr, 0);
			pProperty->SetData((DWORD_PTR)multiData);
		} 
		else if (m_pInformation != nullptr)
		{
			if (m_pInformation->m_attr.begin() != m_pInformation->m_attr.end())
			{
				attrParent = *m_pInformation->m_attr.begin();
			}
			else
			{
				attrParent = new F_ATTR();
				m_pInformation->m_attr.push_back(attrParent);
			}


			attr->m_paix = parentIndex;
			auto itor = cell->m_dsgir.m_atcs->m_arrFindForCode.find(ca->code.GetValueString());
			if (itor == cell->m_dsgir.m_atcs->m_arrFindForCode.end())
			{
				attr->m_natc = GetATCS(ca->code.GetValueString());
			}
			else
			{
				attr->m_natc = itor->second->m_nmcd;
			}


			attr->m_atix = GetATIX(attr->m_natc, parentIndex);
			attr->m_paix = parentIndex;
			attr->m_atin = 1;
			attrParent->m_arr.push_back(attr);
			attributeIndex = m_pInformation->GetAttributeIndex(attr);

			MultiData *multiData = InsertPropertyMultiData(111, pProperty, (DWORD_PTR)m_pInformation, (DWORD_PTR)attr, 1);
			pProperty->SetData((DWORD_PTR)multiData);
		} 
		for (auto itor = ca->subAttributeBinding.begin(); itor != ca->subAttributeBinding.end(); itor++) 
		{
			auto ab = &(*itor);
			if (ab->multiplicity.lower == 1) 
			{  

				if (attributeIndex > 0)
				{
					AddAttribute(ab, pProperty, attributeIndex);
				}
				else
				{
					OutputDebugString(_T("Complex Attribute의 Sub Attribute의 부모 인덱스 오류\n"));
				}
			}
		}
	}
	return;
}

bool CDockablePaneEditWindow::CheckingAttriData(AttributeBinding* ab, CString inputName, CMFCPropertyGridProperty *pSuperProperty)
{     
	if (m_wndListAttribute.GetPropertyCount() == 0)
	{
		return true;
	}

	int thisAttriCount = 0;
	if (pSuperProperty == nullptr) 
	{
		XML_Attribute *attr = NULL;
		auto attribute = ab->attribute.Getattributes();
		for (auto itor = attribute.begin(); itor != attribute.end(); itor++)
		{
			attr = &(*itor);

			if (attr->Getname().compare(L"ref") == 0)
			{
				break;
			}
		}

		std::wstring attrName;
		if (!attr)
		{
			return false;
		}

		else
		{
			Catalog* catalog = ((S101Layer*)m_cell->m_pLayer)->GetFC();
			SimpleAttribute* sa = catalog->m_pCatalogueList.begin()->second->GetSimpleAttribute(attr->Getvalue());
			if (sa)
			{
				attrName = sa->name;
			}
			ComplexAttribute* ca = catalog->m_pCatalogueList.begin()->second->GetComplexAttribute(attr->Getvalue());
			if (ca)
			{
				attrName = ca->name;
			}
		}

		XML_Attribute *upperAttr = NULL;
		attribute = ab->multiplicity.upper.Getattributes();
		for (auto itor = attribute.begin(); itor != attribute.end(); itor++)
		{
			upperAttr = &(*itor);

			if (upperAttr->Getname().compare(L"infinite") == 0)
			{
				break;
			}
		}

		int upperCount = 0;
		if (upperAttr)
		{
			if (upperAttr->Getvalue().compare(L"true") == 0)
			{
				return true;
			}
			else
			{
				upperCount = _wtoi(ab->multiplicity.upper.Getvalue().c_str());
			}
		}

		int attrCount = 0;
		int count = m_wndListAttribute.GetPropertyCount();
		for (int i = 0; i < count; i++)
		{
			CMFCPropertyGridProperty *pProperty = m_wndListAttribute.GetProperty(i);

			wstring name = pProperty->GetName();
			if (name.compare(attrName) == 0)
			{
				attrCount++;
				if (attrCount >= upperCount)
				{
					return false;
				}
			}
		}
	}
	else 
	{
		int allCount = pSuperProperty->GetSubItemsCount();
		if (allCount == 0)
		{
			return true;
		}
		for (int i = 0; i < allCount; i++)
		{
			MultiData* data = (MultiData*)pSuperProperty->GetSubItem(i)->GetData();
			ATTR *attribute = (ATTR*)data->data[2];

			auto s101Cell = GetS101Cell();
			auto DGIR = s101Cell->GetDatasetGeneralInformationRecord();
			auto attributeCode = DGIR->GetAttributeCode(attribute->m_natc);

			if (attributeCode.CompareNoCase(inputName) == 0)
			{
				thisAttriCount++;
			}
		}

	}

	int upperCount = 0;
	bool isUpper = false; 

	auto attri = ab->multiplicity.upper.Getattributes();
	for (auto i = attri.begin(); i != attri.end(); i++)
	{
		std::wstring infi = i->Getname();
		if (infi.compare(L"infinite") == 0)
		{
			if (i->Getvalue().compare(L"true") == 0)
			{
				isUpper = true;
			}
			else 
			{
				upperCount = std::stoi(ab->multiplicity.upper.Getvalue());
			}
		}
	}

	if (thisAttriCount == 0 || isUpper == true || thisAttriCount < upperCount)
	{
		return true;
	}
	else if (thisAttriCount == upperCount || thisAttriCount > upperCount)
	{
		return false;
	}

	return true;
}

void CDockablePaneEditWindow::SettingEnumType(std::list<ListedValues> list, CMFCPropertyGridProperty* pSuperProperty)
{
	std::list<int>num;
	for (auto i = list.begin(); i != list.end(); i++)
	{
		ListedValues* lvs = &(*i);

		for (auto lvitor = lvs->listedValue.begin(); lvitor != lvs->listedValue.end(); lvitor++)
		{
			num.push_back(lvitor->first);
		}

		num.sort();

		for each (auto i in num)
		{
			ListedValue* lv = &(lvs->listedValue[i]);
			CString label(lv->label.c_str());
			CString namestr;
			namestr.Format(_T("%d.%s"), i, label);
			LPCTSTR name = namestr;
			pSuperProperty->AddOption(name);
		}
	}


}

unsigned CDockablePaneEditWindow::GetATCS(wstring code)
{
	unsigned nmcd = 1;
	if (m_cell->m_FileType == FILE_S_100_VECTOR)
	{
		S101Cell* cell = (S101Cell*)m_cell;

		auto itor = cell->m_dsgir.m_atcs->m_arrFindForCode.find(code);

		if (itor == cell->m_dsgir.m_atcs->m_arrFindForCode.end())
		{
			for (unsigned i = 1; i < 65535; i++)
			{
				nmcd = i;

				auto itor = cell->m_dsgir.m_atcs->m_arr.find(nmcd);

				if (itor == cell->m_dsgir.m_atcs->m_arr.end())
				{
					break;
				}
			}

			CodeWithNumericCode *cnc = new CodeWithNumericCode();
			cnc->m_nmcd = nmcd;
			cnc->m_code = code.c_str();

			cell->m_dsgir.m_atcs->m_arr.insert(std::unordered_map<int, CodeWithNumericCode*>::value_type(cnc->m_nmcd, cnc));
			cell->m_dsgir.m_atcs->m_arrFindForCode.insert(std::unordered_map<std::wstring, CodeWithNumericCode*>::value_type(cnc->m_code.GetBuffer(), cnc));
		}
	}
	return nmcd;
}

unsigned CDockablePaneEditWindow::GetATIX(unsigned natc, unsigned parentIndex)
{
	unsigned index = 1; 

	if (m_pFeature != nullptr)
	{
		for (auto iATTR = m_pFeature->m_attr.begin(); iATTR != m_pFeature->m_attr.end(); iATTR++)
		{
			F_ATTR* fATTR = *iATTR; 

			for (auto i = fATTR->m_arr.begin(); i != fATTR->m_arr.end(); i++)
			{
				ATTR* attr = *i; 
				if (attr->m_paix == parentIndex && attr->m_natc == natc)
				{ 
					index++;
				}
			}           
		}

	}

	if (m_pInformation != nullptr)
	{
		for (auto iATTR = m_pInformation->m_attr.begin(); iATTR != m_pInformation->m_attr.end(); iATTR++)
		{
			F_ATTR* fATTR = *iATTR; 

			for (auto i = fATTR->m_arr.begin(); i != fATTR->m_arr.end(); i++)
			{
				ATTR* attr = *i; 
				if (attr->m_paix == parentIndex && attr->m_natc == natc)
				{ 
					index++;
				}
			}           
		}
	}

	return index;
}

void CDockablePaneEditWindow::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndListVector.SetFont(&m_fntPropList);
	m_wndListAttribute.SetFont(&m_fntPropList);
}

void CDockablePaneEditWindow::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(&rect);


	m_wndTabs.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
} 
BOOL CDockablePaneEditWindow::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	::FillRect(pDC->m_hDC, &rect, GetSysColorBrush(COLOR_3DFACE));
	return TRUE;
}

void CDockablePaneEditWindow::SetFeatureRecord(ENC_Feature* pObject)
{
	m_pObject = pObject;

	m_selectedObjectType = L"Feature";
	SetAttributes();
	SetVectors();
}

void CDockablePaneEditWindow::SetFeatureRecord(R_FeatureRecord* pFeature)//점클릭이후 넘어옴
{
	m_pFeature = pFeature;
	m_pInformation = nullptr;
	m_selectedObjectType = L"Feature";
	SetAttributes();
	SetVectors();
}

void CDockablePaneEditWindow::SetFeatureRecord(R_InformationRecord* pInformation)
{
	m_pInformation = pInformation;
	m_pFeature = nullptr;

	m_selectedObjectType = L"Information";
	SetAttributes();
}

void CDockablePaneEditWindow::SetEditingContent(EditingContent *ec)
{
	m_pEdtContent = ec;

	m_wndListVector.GetPropertyCount();

	for (int i = 0; i < m_wndListVector.GetPropertyCount(); i++)
	{
		CMFCPropertyGridProperty* pgp = m_wndListVector.GetProperty(i);
	} 
}

void CDockablePaneEditWindow::SetAttributes() 
{
	DeleteAttributeItems();
	std::vector<CMFCPropertyGridProperty*> pAttrItemList; 
	if (m_cell->m_FileType == FILE_S_57)
	{
		ENCCell* cell = (ENCCell*)m_cell;

		if (!m_pObject)
		{
			return;
		}


		for (auto iter = m_pObject->m_attfList.begin();
			iter != m_pObject->m_attfList.end();
			iter++)
		{
			ATTF* attf = *iter;
			CString attrValue = attf->ATVL.c_str();
			CString outputString;;
			CAttribute* pAttr = ENCGeometry::pAttribute->GetAttributeFromCode(attf->ATTL); 
			if (pAttr->Attribute_type == CAttributeMap::ENUMERATED ||
				pAttr->Attribute_type == CAttributeMap::LIST
				)
			{

				int curPos = 0; 
				CString resToken = attrValue.Tokenize(_T(",/"), curPos);
				vector<int> vectorAttributeValue;

				while (resToken != _T(""))
				{
					vectorAttributeValue.push_back(_ttoi(resToken));
					resToken = attrValue.Tokenize(_T(",/"), curPos);

				} 
				for (unsigned int i = 0; i < vectorAttributeValue.size(); i++)
				{
					if (i > 0)
					{
						outputString.Append(_T(","));
					}
					CString tstr;
					tstr.Format(L"%s(%d)", pAttr->valueList[vectorAttributeValue[i]]->name.c_str(), pAttr->valueList[vectorAttributeValue[i]]->index);
					outputString.Append(tstr);
				}
			}
			else
			{
				outputString = ((ATTF*)(*iter))->ATVL.c_str();
			}

			CMFCPropertyGridProperty *pAttribute = new CMFCPropertyGridProperty(pAttr->Attribute_name, outputString);
			CString decription;
			decription.Format(L"Arcronym : %s", pAttr->Acronym);

			pAttribute->SetDescription(decription);

			MultiData *multiData = InsertPropertyMultiData(11, pAttribute, (DWORD_PTR)(ATTF*)(*iter));
			pAttribute->SetData((DWORD_PTR)multiData);

			if (pAttr->Attribute_type == CAttributeMap::ENUMERATED ||
				pAttr->Attribute_type == CAttributeMap::LIST
				)
			{
				for (auto itor = pAttr->valueList.begin(); itor != pAttr->valueList.end(); itor++)
				{
					AttributeListValue* av = (*itor);

					if (av->name.size() <= 0)
						continue;

					CString tstr;
					tstr.Format(L"%s(%d)", av->name.c_str(), av->index);
					pAttribute->AddOption(tstr);
				}
			}

			m_wndListAttribute.AddProperty(pAttribute);
		}

		for (auto iter = m_pObject->m_natfList.begin();
			iter != m_pObject->m_natfList.end();
			iter++)
		{ 
			CString value = L"";
			CAttribute* pAttr = ENCGeometry::pAttribute->GetAttributeFromCode(((NATF*)(*iter))->ATTL);

			value = ((NATF*)(*iter))->ATVL.c_str();

			CMFCPropertyGridProperty *pAttribute = new CMFCPropertyGridProperty(pAttr->Attribute_name, value);
			CString decription;
			decription.Format(L"Arcronym : %s", pAttr->Acronym);
			pAttribute->SetDescription(decription);

			MultiData *multiData = InsertPropertyMultiData(12, pAttribute, (DWORD_PTR)(NATF*)(*iter));
			pAttribute->SetData((DWORD_PTR)multiData);

			m_wndListAttribute.AddProperty(pAttribute);
		}

	} 

	else if (m_cell->m_FileType == FILE_S_100_VECTOR)            
	{
		S101Cell* cell = (S101Cell*)m_cell; 

		if (m_selectedObjectType == L"Feature")
		{ 
			if (m_pFeature->m_attr.size() == 0)
			{
				return;
			}
			for (auto itorParent = m_pFeature->m_attr.begin(); itorParent != m_pFeature->m_attr.end(); itorParent++)
			{
				F_ATTR* attrParent = *itorParent;
				for (auto itor = attrParent->m_arr.begin(); itor != attrParent->m_arr.end(); itor++)
				{
					ATTR* attr = *itor;      
					auto aitor = cell->m_dsgir.m_atcs->m_arr.find(attr->m_natc);
					Catalog* catalog = ((S101Layer*)cell->m_pLayer)->GetFC();
					SimpleAttribute* sa = catalog->m_pCatalogueList.begin()->second->GetSimpleAttribute(aitor->second->m_code.GetBuffer());

					if (sa)
					{
						wstring value;
						if (sa->valueType.GetValueString().compare(L"enumeration") == 0)
						{
							auto dfsf = _wtoi(attr->m_atvl);
							unordered_map<int,ListedValue> attributelist = (*sa->listedValues.begin()).listedValue; 
							auto itor = attributelist.find(_wtoi(attr->m_atvl));

							if (itor != attributelist.end())
							{
								ListedValue* plv = &itor->second;

								auto result = attr->m_atvl;
								result.Append(L".");
								result.Append(plv->label.c_str());
								value = result;
							}              
						}
						else
						{
							value = attr->m_atvl;
						}

						CMFCPropertyGridProperty *pAttribute = new CMFCPropertyGridProperty(sa->name.c_str(), value.c_str());
						pAttrItemList.push_back(pAttribute);
						pAttribute->SetDescription(sa->definition.c_str()); 
						MultiData *multiData = InsertPropertyMultiData(111, pAttribute, (DWORD_PTR)m_pFeature, (DWORD_PTR)attr, 0);
						pAttribute->SetData((DWORD_PTR)multiData);

						if (attr->m_paix != 0)
						{
							if (pAttrItemList.size() < 1) 
							{
								CString msg;
								msg.Format(L"[%s] parent[index : %d] attribute not found - EDIT WINDOW", sa->name.c_str(), attr->m_paix);
								KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_ERROR, msg, KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
								continue;
							}
							else
							{

								pAttrItemList[attr->m_paix - 1]->AddSubItem(pAttribute);
							}
						}
						else
						{
							m_wndListAttribute.AddProperty(pAttribute); 
						}

						if (sa->valueType.GetValueString().compare(L"enumeration") == 0)
						{
							SettingEnumType(sa->listedValues, pAttribute); 
						}
					}
					else 
					{
						Catalog* catalog = ((S101Layer*)cell->m_pLayer)->GetFC();
						ComplexAttribute* ca = catalog->m_pCatalogueList.begin()->second->GetComplexAttribute(aitor->second->m_code.GetBuffer());
						if (ca)
						{
							CMFCPropertyGridProperty *pAttribute = new CMFCPropertyGridProperty(ca->name.c_str());

							pAttrItemList.push_back(pAttribute);
							pAttribute->SetDescription(ca->definition.c_str()); 
							MultiData *multiData = InsertPropertyMultiData(111, pAttribute, (DWORD_PTR)m_pFeature, (DWORD_PTR)attr, 0);
							pAttribute->SetData((DWORD_PTR)multiData);

							if (attr->m_paix != 0)
							{
								if (pAttrItemList[attr->m_paix - 1]->IsGroup()) 
								{
									pAttrItemList[attr->m_paix - 1]->AddSubItem(pAttribute);
								}
								else
								{
									pAttrItemList[attr->m_paix]->AddSubItem(pAttribute);
								}
							}
							else
							{ 
								m_wndListAttribute.AddProperty(pAttribute);
							}
						}
						else
						{
							CString msg;
							msg.Format(L"[%s] attribute not exist in feature catalog - EDIT WINDOW", aitor->second->m_code);
							KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_ERROR, msg, KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::FC);

							CMFCPropertyGridProperty *pAttribute = new CMFCPropertyGridProperty(aitor->second->m_code);
							pAttrItemList.push_back(pAttribute); 

							MultiData *multiData = InsertPropertyMultiData(111, pAttribute, (DWORD_PTR)m_pFeature, (DWORD_PTR)attr, 0);
							pAttribute->SetData((DWORD_PTR)multiData);

							if (attr->m_paix != 0)
							{ 
								pAttrItemList[attr->m_paix]->AddSubItem(pAttribute);
							}
							else
							{
								m_wndListAttribute.AddProperty(pAttribute);
							}
						}
					}
				}
			}

		}
		else if (m_selectedObjectType = L"Information")
		{ 
			if (m_pInformation->m_attr.size() == 0)
			{
				return;
			}

			for (auto itorParent = m_pInformation->m_attr.begin(); itorParent != m_pInformation->m_attr.end(); itorParent++)
			{
				F_ATTR* attrParent = *itorParent;


				for (auto itor = attrParent->m_arr.begin(); itor != attrParent->m_arr.end(); itor++)
				{
					ATTR* attr = *itor;

					CString value = L"";
					{
						value = attr->m_atvl;
					}

					auto aitor = cell->m_dsgir.m_atcs->m_arr.find(attr->m_natc);

					Catalog* catalog = ((S101Layer*)cell->m_pLayer)->GetFC();
					SimpleAttribute* sa = catalog->m_pCatalogueList.begin()->second->GetSimpleAttribute(aitor->second->m_code.GetBuffer());

					if (sa) 
					{
						wstring value;
						if (sa->valueType.GetValueString().compare(L"enumeration") == 0)
						{
							auto itor = (*sa->listedValues.begin()).listedValue.find(_wtoi(attr->m_atvl));
							if (itor == (*sa->listedValues.begin()).listedValue.end())
							{
							}
							else
							{
								ListedValue* plv = &itor->second;
								value = plv->label.c_str();
							}
						}
						else
						{
							value = attr->m_atvl;
						}

						CMFCPropertyGridProperty *pAttribute = new CMFCPropertyGridProperty(sa->name.c_str(), value.c_str());

						pAttrItemList.push_back(pAttribute);
						pAttribute->SetDescription(sa->definition.c_str());

						MultiData *multiData = InsertPropertyMultiData(111, pAttribute, (DWORD_PTR)m_pInformation, (DWORD_PTR)attr, 1);
						pAttribute->SetData((DWORD_PTR)multiData);

						if (attr->m_paix != 0)
						{ 
							pAttrItemList[attr->m_paix - 1]->AddSubItem(pAttribute);
						}
						else
						{
							m_wndListAttribute.AddProperty(pAttribute);
						}

						if (sa->valueType.GetValueString().compare(L"enumeration") == 0)
						{
							for (auto itor = sa->listedValues.begin(); itor != sa->listedValues.end(); itor++)
							{
								ListedValues* lvs = &(*itor);

								for (auto lvitor = lvs->listedValue.begin(); lvitor != lvs->listedValue.end(); lvitor++)
								{
									ListedValue* lv = &(lvitor->second);
									pAttribute->AddOption(lv->label.c_str());
								}
							}
						}
					}
					else
					{
						Catalog* catalog = ((S101Layer*)cell->m_pLayer)->GetFC();
						ComplexAttribute* ca = catalog->m_pCatalogueList.begin()->second->GetComplexAttribute(std::wstring(aitor->second->m_code)); 
						if (ca)
						{
							CMFCPropertyGridProperty *pAttribute = new CMFCPropertyGridProperty(ca->name.c_str());

							pAttrItemList.push_back(pAttribute);
							pAttribute->SetDescription(ca->definition.c_str());
							MultiData *multiData = InsertPropertyMultiData(111, pAttribute, (DWORD_PTR)m_pInformation, (DWORD_PTR)attr, 1);
							pAttribute->SetData((DWORD_PTR)multiData);

							if (attr->m_paix != 0)
							{
								pAttrItemList[attr->m_paix]->AddSubItem(pAttribute);
							}
							else
							{
								m_wndListAttribute.AddProperty(pAttribute);
							}
						}
					}
				}
			}

		} 
	}
	m_wndListAttribute.ExpandAll();
	theApp.GetDockFeatureInformationList().SetindexNum(0);
	theApp.GetDockFeatureInformationList().SetParentProperty(nullptr);
}

void CDockablePaneEditWindow::SetVectors()
{
	DeleteVectorItems();

	wstring str;
	R_PointRecord* pr = NULL;
	R_MultiPointRecord* mpr = NULL;
	R_CurveRecord* cr = NULL;
	R_CompositeRecord* ccr = NULL;
	R_SurfaceRecord* sr = NULL;  
	if (m_cell->m_FileType == FILE_S_57)
	{
		ENCCell* cell = (ENCCell*)m_cell;

		for (auto itor = m_pObject->m_fsptList.begin();
			itor != m_pObject->m_fsptList.end();
			itor++)
		{
			FSPT* fspt = *itor;
			__int64 iKey = ((__int64)fspt->RCNM) << 32 | fspt->RCID;
			auto searchItor = cell->m_veMap.find(iKey);

			ENC_Vector* v = searchItor->second;

			SetVector(v);
		}
	}
	else if (m_cell->m_FileType == FILE_S_100_VECTOR)            
	{
		S101Cell* cell = (S101Cell*)m_cell;

		for (auto itorParent = m_pFeature->m_spas.begin(); itorParent != m_pFeature->m_spas.end(); itorParent++)
		{
			F_SPAS *spasParent = *itorParent;

			for (auto itor = spasParent->m_arr.begin(); itor != spasParent->m_arr.end(); itor++)
			{
				SPAS* spas = *itor;

				switch (spas->m_name.RCNM)
				{
				case 110:
					pr = cell->m_ptMap.PLookup(spas->m_name.GetName())->value;
					SetVector(pr);
					break;
				case 115:
					mpr = cell->m_mpMap.PLookup(spas->m_name.GetName())->value;
					SetVector(mpr);
					break;
				case 120:
					cr = cell->m_curMap.PLookup(spas->m_name.GetName())->value;
					SetVector(cr);
					break;
				case 125:
					ccr = cell->m_comMap.PLookup(spas->m_name.GetName())->value;
					SetVector(ccr);
					break;
				case 130:
					sr = cell->m_surMap.PLookup(spas->m_name.GetName())->value;
					SetVector(sr);
					break;
				}
			}
		}
	}

	m_wndListVector.ExpandAll();
}

void CDockablePaneEditWindow::SetVector(ENC_Vector* v, CMFCPropertyGridProperty *pSuperProperty)
{
	if (v->m_vrid.RCNM == 110 || v->m_vrid.RCNM == 120)
	{
		if (v->m_sg2dList.size() > 0)
		{
			CMFCPropertyGridProperty *pProperty = new CMFCPropertyGridProperty(L"Point");
			for (auto itor = v->m_sg2dList.begin();
				itor != v->m_sg2dList.end();
				itor++)
			{
				SG2D* sg2d = *itor;
				if (pSuperProperty)
				{
					pSuperProperty->AddSubItem(pProperty);
				}
				else
				{
					m_wndListVector.AddProperty(pProperty);
				}
				std::wstringstream wss; 
				wss << sg2d->YCOO << L"," << sg2d->XCOO;
				CMFCPropertyGridProperty *pChildProperty = new CMFCPropertyGridProperty(L"Position", wss.str().c_str());
				pProperty->AddSubItem(pChildProperty);

				pChildProperty->SetName(L"SG2D"); 
				MultiData *multiData = InsertPropertyMultiData(1, pChildProperty, (DWORD_PTR)v, (DWORD_PTR)sg2d);
				pChildProperty->SetData((DWORD_PTR)multiData);

			}
		}
	}
	else if (v->m_vrid.RCNM == 130 || v->m_vrid.RCNM == 140)
	{
		ENCCell* cell = (ENCCell*)m_cell;
		if (v->m_sg2dList.size() > 0)
		{
			CMFCPropertyGridProperty *pProperty = new CMFCPropertyGridProperty(L"Curve");
			if (pSuperProperty)
			{
				pSuperProperty->AddSubItem(pProperty);
			}
			else
			{
				m_wndListVector.AddProperty(pProperty);
			}

			__int64 iKey;
			ENC_Vector *spv = NULL, *epv = NULL;
			for (auto itor = v->m_vrptList.begin(); itor != v->m_vrptList.end(); itor++)
			{
				VRPT* vrpt = *itor;

				iKey = ((__int64)vrpt->RCNM) << 32 | vrpt->RCID;
				if (vrpt->TOPI == 1 
					)
				{
					auto spvItor = cell->m_veMap.find(iKey);
					spv = spvItor->second;
				}
				else if (vrpt->TOPI == 2 
					)
				{
					auto epvItor = cell->m_veMap.find(iKey);
					epv = epvItor->second;
				}
			}
			SetVector(spv, pProperty);

			for (auto itor = v->m_sg2dList.begin(); itor != v->m_sg2dList.end(); itor++)
			{
				SG2D* ic = *itor;
				std::wstringstream wss; 
				wss << ic->YCOO << L"," << ic->XCOO;

				CMFCPropertyGridProperty *pChildProperty = new CMFCPropertyGridProperty(L"Position", wss.str().c_str());
				pProperty->AddSubItem(pChildProperty);
				pChildProperty->SetName(L"SG2D"); 
				MultiData *multiData = InsertPropertyMultiData(1, pChildProperty, (DWORD_PTR)v, (DWORD_PTR)ic);
				pChildProperty->SetData((DWORD_PTR)multiData);
			}
			SetVector(epv, pProperty);
		}
	}
}

void CDockablePaneEditWindow::SetVector(int RCNM, R_VectorRecord* r, CMFCPropertyGridProperty *pSuperProperty)
{
	switch (RCNM)
	{
	case 110:
		SetVector((R_PointRecord*)r, pSuperProperty);
		break;
	case 115:
		SetVector((R_MultiPointRecord*)r, pSuperProperty);
		break;
	case 120:
		SetVector((R_CurveRecord*)r, pSuperProperty);
		break;
	case 125:
		SetVector((R_CompositeRecord*)r, pSuperProperty);
		break;
	case 130:
		SetVector((R_SurfaceRecord*)r, pSuperProperty);
		break;
	}
}

void CDockablePaneEditWindow::SetVector(R_PointRecord* r, CMFCPropertyGridProperty *pSuperProperty)
{
	CMFCPropertyGridProperty *pProperty = new CMFCPropertyGridProperty(L"Point");
	if (pSuperProperty)
	{
		pSuperProperty->AddSubItem(pProperty);
	}
	else
	{
		m_wndListVector.AddProperty(pProperty);
	}

	S101Cell* cell = (S101Cell*)m_cell;
	int precision_x = 0;
	int cmf = cell->m_dsgir.m_dssi.m_cmfx;
	while (cmf >= 10)
	{
		cmf /= 10;
		precision_x++;
	}

	int precision_y = 0;
	cmf = cell->m_dsgir.m_dssi.m_cmfy;
	while (cmf >= 10)
	{
		cmf /= 10;
		precision_y++;
	}

	if (r->m_c2it)
	{        

		std::wstringstream wss;
		wss.setf(ios::fixed, ios::floatfield);
		double x = r->m_c2it->m_xcoo / (double)cell->m_dsgir.m_dssi.m_cmfx;
		wss.precision(precision_x);
		double y = r->m_c2it->m_ycoo / (double)cell->m_dsgir.m_dssi.m_cmfy;
		wss.precision(precision_y);

		wss << y << L"," << x;



		CMFCPropertyGridProperty *pChildProperty = new CMFCPropertyGridProperty(L"Position", wss.str().c_str());
		pProperty->AddSubItem(pChildProperty);

		pChildProperty->SetName(L"C2IT"); 
		MultiData *multiData = InsertPropertyMultiData(101, pChildProperty, (DWORD_PTR)r, (DWORD_PTR)r->m_c2it);
		pChildProperty->SetData((DWORD_PTR)multiData);
	}
}

void CDockablePaneEditWindow::SetVector(R_MultiPointRecord* r, CMFCPropertyGridProperty *pSuperProperty)
{
	CMFCPropertyGridProperty *pProperty = new CMFCPropertyGridProperty(L"MultiPoint");
	if (pSuperProperty)
	{
		pSuperProperty->AddSubItem(pProperty);
	}
	else
	{
		m_wndListVector.AddProperty(pProperty);
	}

	S101Cell* cell = (S101Cell*)m_cell;
	int precision_x = 0;
	int cmf = cell->m_dsgir.m_dssi.m_cmfx;
	while (cmf >= 10)
	{
		cmf /= 10;
		precision_x++;
	}

	int precision_y = 0;
	cmf = cell->m_dsgir.m_dssi.m_cmfy;
	while (cmf >= 10)
	{
		cmf /= 10;
		precision_y++;
	}

	int precision_z = 0;
	cmf = cell->m_dsgir.m_dssi.m_cmfz;
	while (cmf >= 10)
	{
		cmf /= 10;
		precision_z++;
	}

	for (auto itor = r->m_c3il.begin(); itor != r->m_c3il.end(); itor++)
	{
		for (auto itor2 = (*itor)->m_arr.begin(); itor2 != (*itor)->m_arr.end(); itor2++)
		{
			C3IL* c3 = *itor2;
			std::wstringstream wss;
			wss.setf(ios::fixed, ios::floatfield);
			double x = c3->m_xcoo / (double)cell->m_dsgir.m_dssi.m_cmfx;
			wss.precision(precision_x);
			wss << x << L",";
			double y = c3->m_ycoo / (double)cell->m_dsgir.m_dssi.m_cmfy;
			wss.precision(precision_y);
			wss << y << L",";
			double z = c3->m_zcoo / (double)cell->m_dsgir.m_dssi.m_cmfz;
			wss.precision(precision_z);
			wss << z;

			CMFCPropertyGridProperty *pChildProperty = new CMFCPropertyGridProperty(L"Position", wss.str().c_str());
			pProperty->AddSubItem(pChildProperty);

			pChildProperty->SetName(L"C3IL"); 
			MultiData *multiData = InsertPropertyMultiData(102, pChildProperty, (DWORD_PTR)r, (DWORD_PTR)c3, (DWORD_PTR)*itor, m_vIndex++);
			pChildProperty->SetData((DWORD_PTR)multiData);

		}
	}
}

void CDockablePaneEditWindow::SetVector(R_CurveRecord* r, CMFCPropertyGridProperty *pSuperProperty)
{
	S101Cell* cell = (S101Cell*)m_cell;

	CMFCPropertyGridProperty *pProperty = new CMFCPropertyGridProperty(L"Curve");
	if (pSuperProperty)
	{
		pSuperProperty->AddSubItem(pProperty);
	}
	else
	{
		m_wndListVector.AddProperty(pProperty);
	}
	POSITION ptasPos = NULL;
	PTAS *ptas = NULL;
	R_PointRecord *spr, *epr;
	__int64 iKey;
	ptasPos = r->m_ptas->m_arr.GetHeadPosition();

	while (ptasPos)
	{
		ptas = r->m_ptas->m_arr.GetNext(ptasPos);

		iKey = ((__int64)ptas->m_name.RCNM) << 32 | ptas->m_name.RCID;
		if (ptas->m_topi == 1 
			)
		{
			cell->m_ptMap.Lookup(iKey, spr);
		}
		else if (ptas->m_topi == 2 
			)
		{
			cell->m_ptMap.Lookup(iKey, epr);
		}
		else if (ptas->m_topi == 3)
		{
			cell->m_ptMap.Lookup(iKey, spr);
			epr = spr;
		}
	}
	SetVector(spr, pProperty);

	int precision_x = 0;
	int cmf = cell->m_dsgir.m_dssi.m_cmfx;
	while (cmf >= 10)
	{
		cmf /= 10;
		precision_x++;
	}

	int precision_y = 0;
	cmf = cell->m_dsgir.m_dssi.m_cmfy;
	while (cmf >= 10)
	{
		cmf /= 10;
		precision_y++;
	}

	for (auto itorParent = r->m_c2il.begin(); itorParent != r->m_c2il.end(); itorParent++)
	{
		int index = 0;
		for (auto itor = (*itorParent)->m_arr.begin(); itor != (*itorParent)->m_arr.end(); itor++)
		{
			IC2D* ic = *itor;  
			EdtVector* ev = NULL;
			bool isDeleted = false;
			for (auto itor = m_pEdtContent->vectorList.begin(); itor != m_pEdtContent->vectorList.end(); itor++)
			{
				ev = &*itor;

				if (ev->type != 1)
					continue;

				IC2D* ic2d = (IC2D*)ev->data[2];
				if (ic2d == ic)
				{
					isDeleted = ev->deleted;

					break;
				}
			}
			if (isDeleted)
			{
				m_vIndex++;
				continue;
			} 
			std::wstringstream wss;
			wss.setf(ios::fixed, ios::floatfield);      

			double x = ic->m_xcoo / (double)cell->m_dsgir.m_dssi.m_cmfx;
			wss.precision(precision_x);

			double y = ic->m_ycoo / (double)cell->m_dsgir.m_dssi.m_cmfy;
			wss.precision(precision_y);

			wss << y << L"," << x;


			CMFCPropertyGridProperty *pChildProperty = new CMFCPropertyGridProperty(L"Position", wss.str().c_str());
			pProperty->AddSubItem(pChildProperty);
			pChildProperty->SetName(L"C2IL"); 
			MultiData *multiData = InsertPropertyMultiData(100, pChildProperty, (DWORD_PTR)r, (DWORD_PTR)ic, (DWORD_PTR)*itorParent, m_vIndex++);
			pChildProperty->SetData((DWORD_PTR)multiData);
		}
	}
	SetVector(epr, pProperty);
}

void CDockablePaneEditWindow::SetVector(R_CompositeRecord* r, CMFCPropertyGridProperty *pSuperProperty)
{
	S101Cell* cell = (S101Cell*)m_cell;
	CMFCPropertyGridProperty *pProperty = new CMFCPropertyGridProperty(L"Composite Curve");
	if (pSuperProperty)
	{
		pSuperProperty->AddSubItem(pProperty);
	}
	else
	{
		m_wndListVector.AddProperty(pProperty);
	}

	for (auto itorParent = r->m_cuco.begin(); itorParent != r->m_cuco.end(); itorParent++)
	{
		F_CUCO* cucoParent = *itorParent;

		for (auto itor = cucoParent->m_arr.begin(); itor != cucoParent->m_arr.end(); itor++)
		{
			CUCO* cuco = *itor;

			auto itorFind = cell->m_vecMap.find(cuco->m_name.GetName());
			if (itorFind != cell->m_vecMap.end())
			{
				SetVector(cuco->m_name.RCNM, itorFind->second, pProperty);
			}
		}
	}
}

void CDockablePaneEditWindow::SetVector(R_SurfaceRecord* r, CMFCPropertyGridProperty *pSuperProperty)
{
	S101Cell* cell = (S101Cell*)m_cell;
	CMFCPropertyGridProperty *pProperty = new CMFCPropertyGridProperty(L"Surface");
	if (pSuperProperty)
	{
		pSuperProperty->AddSubItem(pProperty);
	}
	else
	{
		m_wndListVector.AddProperty(pProperty);
	}


	for (auto itorParent = r->m_rias.begin(); itorParent != r->m_rias.end(); itorParent++)
	{
		F_RIAS* riasParent = *itorParent;

		for (auto itor = riasParent->m_arr.begin(); itor != riasParent->m_arr.end(); itor++)
		{
			RIAS* rias = *itor;

			auto itorFind = cell->m_vecMap.find(rias->m_name.GetName());
			if (itorFind != cell->m_vecMap.end())
			{
				SetVector(rias->m_name.RCNM, itorFind->second, pProperty);
			}
		}
	}
}

void CDockablePaneEditWindow::SetFeatureList()
{
	DeleteAllItems();

	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;                                                                            
}

void CDockablePaneEditWindow::DeleteAllItems()
{
	DeleteAttributeItems();
	DeleteVectorItems();
}

void CDockablePaneEditWindow::DeleteAttributeItems()
{
	while (m_wndListAttribute.GetPropertyCount() > 0)
	{
		CMFCPropertyGridProperty* prop = m_wndListAttribute.GetProperty(0);
		m_wndListAttribute.DeleteProperty(prop);
	} 

	for (auto itor = m_propertyAttributeMultiData.begin();
		itor != m_propertyAttributeMultiData.end();
		itor++)
	{
		delete itor->second;
	}
	m_propertyAttributeMultiData.clear();
}
void CDockablePaneEditWindow::DeleteVectorItems()
{

	while (m_wndListVector.GetPropertyCount() > 0)
	{
		CMFCPropertyGridProperty* prop = m_wndListVector.GetProperty(0);
		m_wndListVector.DeleteProperty(prop);
	}

	if (m_wndListVector)
		m_wndListVector.RemoveAll();

	for (auto itor = m_propertyVectorMultiData.begin();
		itor != m_propertyVectorMultiData.end();
		itor++)
	{
		delete itor->second;
	}
	m_propertyVectorMultiData.clear();
}

BOOL CDockablePaneEditWindow::PreTranslateMessage(MSG* pMsg)
{ 
	HWND thisHandle = this->m_hWnd;
	HWND attributeHandle = m_wndListAttribute.m_hWnd;

	HWND hwnd;
	int index = 0;
	R_VectorRecord* vr = NULL;
	IC2D* ic = NULL;
	F_C2IL* fic = NULL;
	F_C2IT* it = NULL;

	CMFCPropertyGridProperty *pProp;
	switch (pMsg->message)
	{
	case WM_TRANSLATION_MESSAGE_TO_PARENT_DELETE_ATTRIBUTE:
		hwnd = (HWND)pMsg->wParam;
		pProp = (CMFCPropertyGridProperty*)pMsg->lParam;
		if (!pProp)
		{
			return 0;
		} 
		if (m_wndListAttribute.m_hWnd == hwnd)
		{
			std::unordered_map<unsigned, unsigned> attrToProperty;
			if (m_pFeature != nullptr) 
			{
				for (auto itorParent = m_pFeature->m_attr.begin(); itorParent != m_pFeature->m_attr.end(); itorParent++)
				{
					F_ATTR* attrParent = *itorParent;

					for (unsigned i = 0; i < attrParent->m_arr.size(); i++)
					{
						ATTR* attr = attrParent->m_arr[i];

						if (attr->m_paix == 0) 
						{
							unsigned ui = (unsigned)attrToProperty.size();
							attrToProperty.insert(std::unordered_map<unsigned, unsigned>::value_type(i, ui));
						}

					}
				}

				MultiData* md = (MultiData*)m_wndListAttribute.pSelectedProperty->GetData();
				ATTR* attr = (ATTR*)md->data[2];
				ATTR* deletedAttr = NULL; 
				if (attr->m_paix == 0)
				{
					m_wndListAttribute.DeleteProperty(m_wndListAttribute.pSelectedProperty);
					deletedAttr = attr;
				} 
				else 
				{   
					CMFCPropertyGridProperty* pProp = m_wndListAttribute.pSelectedProperty;
					MultiData* md = (MultiData*)pProp->GetData();
					deletedAttr = (ATTR*)md->data[2];

					m_propertyAttributeMultiData.erase(pProp);
					delete md;

					m_wndListAttribute.DeleteProperty(pProp);
				}
				ENC_S101_Factory::DeleteAttribute(m_pFeature, deletedAttr);
				m_wndListAttribute.pSelectedProperty = nullptr;
			}

			if (m_pInformation != nullptr)
			{
				for (auto itorParent = m_pInformation->m_attr.begin(); itorParent != m_pInformation->m_attr.end(); itorParent++)
				{
					F_ATTR* attrParent = *itorParent;

					for (unsigned i = 0; i < attrParent->m_arr.size(); i++)
					{
						ATTR* attr = attrParent->m_arr[i];

						if (attr->m_paix == 0) 
						{
							unsigned ui = (unsigned)attrToProperty.size();
							attrToProperty.insert(std::unordered_map<unsigned, unsigned>::value_type(i, ui));
						}
					}
				}
				MultiData* md = (MultiData*)m_wndListAttribute.pSelectedProperty->GetData();
				ATTR* attr = (ATTR*)md->data[2];
				ATTR* deletedAttr = NULL;

				if (attr->m_paix == 0)
				{
					m_wndListAttribute.DeleteProperty(m_wndListAttribute.pSelectedProperty);
					deletedAttr = attr;
				}
				else
				{   
					CMFCPropertyGridProperty* pProp = m_wndListAttribute.pSelectedProperty;
					MultiData* md = (MultiData*)pProp->GetData();
					deletedAttr = (ATTR*)md->data[2];

					m_propertyAttributeMultiData.erase(pProp);
					delete md;

					m_wndListAttribute.DeleteProperty(pProp);

				}

				ENC_S101_Factory::DeleteAttribute(m_pInformation, deletedAttr);
				m_wndListAttribute.pSelectedProperty = nullptr;
			}


		}

		break;
	case WM_TRANSLATION_MESSAGE_TO_PARENT_ADD_VECTOR:
		hwnd = (HWND)pMsg->wParam;
		pProp = (CMFCPropertyGridProperty*)pMsg->lParam;
		if (!pProp)
			return 0;

		if (m_wndListVector.m_hWnd == hwnd)
		{
			MultiData* md = (MultiData*)m_wndListVector.pSelectedProperty->GetData(); 

			R_VectorRecord* r = (R_VectorRecord*)md->data[1];
			IC2D* ic = (IC2D*)md->data[2];
			F_C2IL* fic = (F_C2IL*)md->data[3];
			int index = (int)md->data[4];
			S101Cell* cell = (S101Cell*)m_cell;               
		}
		else if (m_wndListAttribute.m_hWnd == hwnd)
		{
			m_wndListAttribute.pSelectedProperty = NULL;
		}
		break;
	case WM_TRANSLATION_MESSAGE_TO_PARENT_DELETE_VECTOR:
		hwnd = (HWND)pMsg->wParam;
		pProp = (CMFCPropertyGridProperty*)pMsg->lParam;
		if (!pProp)
			return 0;

		if (m_wndListVector.m_hWnd == hwnd)
		{
			MultiData* md = (MultiData*)m_wndListVector.pSelectedProperty->GetData(); 

			if (m_pEdtContent)
			{
				EdtVector ev;
				if (md->type == 100)
				{
					ev.type = EdtDateType::E_F_C2IL;
					ev.data.push_back(md->data[1]);
					ev.data.push_back(md->data[3]);
					ev.data.push_back(md->data[2]);
				}       
				m_pEdtContent->SelectWorkPoint(&ev);
				m_pEdtContent->DeleteCurrentVector();
			}

			SetVectors();
			m_pView->Invalidate(); 
		}
		else if (m_wndListAttribute.m_hWnd == hwnd)
		{
			m_wndListAttribute.pSelectedProperty = NULL;
		}
		break;
	case WM_TRANSLATION_MESSAGE_TO_PARENT_SELECTED_VECTOR:
		hwnd = (HWND)pMsg->wParam;
		pProp = (CMFCPropertyGridProperty*)pMsg->lParam;
		if (m_wndListVector.m_hWnd == hwnd)
		{
			MultiData* md = (MultiData*)m_wndListVector.pSelectedProperty->GetData();
			m_selectedMultiData = md;

			if (m_pEdtContent && m_selectedMultiData)
			{
				EdtVector ev;
				if (md->type == 100)
				{
					ev.type = EdtDateType::E_F_C2IL;
					ev.data.push_back(md->data[1]);
					ev.data.push_back(md->data[3]);
					ev.data.push_back(md->data[2]);
				}
				else if (md->type == 101)
				{
					ev.type = EdtDateType::E_F_C2IT;
					ev.data.push_back(md->data[1]);
					ev.data.push_back(md->data[2]);
				}
				m_pEdtContent->SelectWorkPoint(&ev);
			}                
			m_pView->Invalidate();
		}
		break;
	}

	return CDockablePane::PreTranslateMessage(pMsg);
}

MultiData* CDockablePaneEditWindow::InsertPropertyMultiData(
	int multidataType,
	CMFCPropertyGridProperty* pGP,
	DWORD_PTR pointer_1,
	DWORD_PTR pointer_2,
	DWORD_PTR pointer_3,
	DWORD_PTR pointer_4)
{
	MultiData* multiData = new MultiData();

	if (multidataType % 100 > 10)
	{
		m_propertyAttributeMultiData.insert
		(
			std::unordered_map<CMFCPropertyGridProperty*, MultiData*>::value_type(pGP, multiData)
		);
	}
	else
	{
		m_propertyVectorMultiData.insert
		(
			std::unordered_map<CMFCPropertyGridProperty*, MultiData*>::value_type(pGP, multiData)
		);
	}

	multiData->type = multidataType;
	multiData->data.push_back((DWORD_PTR)m_cell);
	multiData->data.push_back((DWORD_PTR)pointer_1);
	multiData->data.push_back((DWORD_PTR)pointer_2);
	multiData->data.push_back((DWORD_PTR)pointer_3);
	multiData->data.push_back((DWORD_PTR)pointer_4);

	return multiData;
}

void CDockablePaneEditWindow::DrawVectorData(CDC* pDC, CGISLibraryApp *pGisLib, const int _offX, const int _offY)
{                                                            
}  
bool CDockablePaneEditWindow::SelectMultiData(EdtVector* ev)
{
	m_selectedMultiData = NULL;
	for (auto itor = m_propertyVectorMultiData.begin(); itor != m_propertyVectorMultiData.end(); itor++)
	{

		MultiData* md = itor->second;  
		if (md->type == 100 && ev->type == 1)
		{
			IC2D* ic1 = (IC2D*)md->data[2];
			IC2D* ic2 = (IC2D*)ev->data[2];
			if (ic1 == ic2)
			{
				m_selectedMultiData = md;
			}
		}
		else if (md->type == 101 && ev->type == 2)
		{
			F_C2IT* c2it1 = (F_C2IT*)md->data[2];
			F_C2IT* c2it2 = (F_C2IT*)ev->data[1];
			if (c2it1 == c2it2)
			{
				m_selectedMultiData = md;
			}
		}

		if (m_selectedMultiData)
		{
			CMFCPropertyGridProperty* selectedProperty = (CMFCPropertyGridProperty*)itor->first;
			m_wndListVector.pSelectedProperty = selectedProperty;
			m_wndListVector.SetCurSel(selectedProperty);
			break;
		}
	}
	return false;
}                                     
void CDockablePaneEditWindow::SetSpatialObject(SpatialObject *object)
{
	m_cell = object;
	m_wndListAttribute.SetSpatialObject(m_cell);
}

SpatialObject *CDockablePaneEditWindow::GetSpatialObject()
{
	return m_cell;
}

S101Cell* CDockablePaneEditWindow::GetS101Cell()
{
	return (S101Cell*)m_cell;
}