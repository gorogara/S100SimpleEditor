// DTreeO.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "resource.h"
#include "GISViewer.h"
#include "DialogTreeAttributeList.h"
#include "DialogDockCurrentSelection.h"
#include "GISViewerView.h"

#include "PLLibrary\\GeoObject.h"
#include "PLLibrary\\Attribute.h"
#include "GeoMetryLibrary\\ENCGeometry.h"
#include "..\\FeatureCatalog\\FeatureCatalogue.h"
#include "GISLibrary\\NewFeatureManager.h"


IMPLEMENT_DYNAMIC(CDialogTreeAttributeList, CTree)

CDialogTreeAttributeList::CDialogTreeAttributeList()
{
}


CDialogTreeAttributeList::~CDialogTreeAttributeList()
{
}

BEGIN_MESSAGE_MAP(CDialogTreeAttributeList, CTree)
	ON_NOTIFY_REFLECT(NM_CLICK, &CDialogTreeAttributeList::OnNMClick)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CDialogTreeAttributeList::OnNMDblclk)
END_MESSAGE_MAP() 
void CDialogTreeAttributeList::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{ 
	CPoint p;
	GetCursorPos(&p);
	::ScreenToClient(m_hWnd, &p);
	UINT nFlags = 0;
	HTREEITEM hltem = NULL;
	hltem = HitTest(p, &nFlags);
	HTREEITEM start = GetRootItem();

	while (GetItemText(start).Compare(_T("")) != 0)
	{
		SetItemColor(start, RGB(0, 0, 0));

		start = GetNextSiblingItem(start);
	}

	HTREEITEM start1 = GetRootItem();

	while (GetItemText(start1).Compare(_T("")) != 0)
	{
		SetItemColor(start1, RGB(0, 0, 0));

		start1 = GetNextSiblingItem(start1);
	}

	if (hltem)
	{
		SelectItem(hltem);
		SetFocus();

		while (GetItemText(start).Compare(_T("")) != 0)
		{
			SetCheck(start, FALSE);
			start = GetNextSiblingItem(start);
		}

		SetCheck(hltem, TRUE); 

		selectIndex = GetItemData(hltem); 
	}

	*pResult = 0;
}

int CDialogTreeAttributeList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1; 
	CBitmap Bmp1;
	Bmp1.LoadBitmap(IDB_BITMAP3);
	ImgList.Create(16, 16, ILC_COLOR24, 3, 0);
	ImgList.Add(&Bmp1, RGB(0, 233, 233));

	SetImageList(&ImgList, TVSIL_NORMAL);
	return 0;
}

void CDialogTreeAttributeList::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{ 

	HTREEITEM item = GetSelectedItem();
	InsertAttribute(item);

	*pResult = 0;
}

void CDialogTreeAttributeList::SetShowTree(CGeoObject* ot)
{
	m_type = 1;

	DeleteAllItems();

	if (ot == NULL)
	{
		return;
	}

	for (int i = 2; i >= 0; i--)
	{
		for (int j = 0; j < ot->Attribute[i].GetSize(); j++)
		{
			CGeoObject::_Attribute* attribute = &ot->Attribute[i].GetAt(j);

			std::wstring acronym = attribute->Attribute_name;
			if (acronym.size() < 6)
			{
				continue;
			}

			CAttribute* pAttr = ENCGeometry::pAttribute->GetAttributeFromAcronym(acronym.c_str());
			std::wstring name = pAttr->Attribute_name;

			TVINSERTSTRUCT tvi;
			tvi.hParent = TVI_ROOT;
			tvi.hInsertAfter = TVI_LAST;
			tvi.item.mask = TVIF_TEXT;
			tvi.item.pszText = LPWSTR(name.c_str());

			HTREEITEM insertedItem = InsertItem(&tvi);
			SetItemData(insertedItem, (DWORD_PTR)pAttr);
		}
	}
}

void CDialogTreeAttributeList::SetShowTree(Catalog* _catalog, FeatureType* ft)//
{
	m_type = 2;
	DeleteAllItems(); 
	int attributeCount = CDockablePaneEditWindow::m_wndListAttribute.GetPropertyCount(); 

	if (ft == nullptr)
	{
		return;
	}


	int i = 0;
	if (attributeCount == 0)
	{
		AttributeBinding* ab = NULL;
		for (auto itor = ft->attributeBinding.begin(); itor != ft->attributeBinding.end(); itor++)
		{
			ab = &(*itor);
			std::wstring name;
			auto attribute = ab->attribute.Getattributes();
			for (auto i = attribute.begin(); i != attribute.end(); i++)
			{
				if (i->Getname().compare(L"ref") == 0)
				{
					name = i->Getvalue();
				}
			}

			if (ab->multiplicity.lower == 1) 
			{
				theApp.m_DockablePaneEditWindow.AddAttribute(ab);
			}

			FeatureCatalogue* fc = _catalog->m_pCatalogueList.begin()->second;
			auto fc_simpleAttribute = fc->GetSimpleAttribute(name);
			auto fc_complexAttribute = fc->GetComplexAttribute(name);

			TVINSERTSTRUCT tvi;
			tvi.hParent = TVI_ROOT;
			tvi.hInsertAfter = TVI_LAST;
			tvi.item.mask = TVIF_TEXT;

			if (fc_simpleAttribute)
			{
				tvi.item.pszText = LPWSTR(fc_simpleAttribute->name.c_str());
				tvi.item.lParam = (LPARAM)fc_simpleAttribute;
			}
			else if (fc_complexAttribute)
			{
				tvi.item.pszText = LPWSTR(fc_complexAttribute->name.c_str());
				tvi.item.lParam = (LPARAM)fc_complexAttribute;
			}
			else
			{
				tvi.item.pszText = LPWSTR(name.c_str());
			}
			HTREEITEM insertedItem = InsertItem(&tvi);
			SetItemData(insertedItem, (DWORD_PTR)ab);
		}
	}
	else 
	{
		AttributeBinding* ab = NULL;
		for (auto itor = ft->attributeBinding.begin(); itor != ft->attributeBinding.end(); itor++)
		{
			ab = &(*itor);
			std::wstring name;
			std::list<XML_Attribute> atttri = ab->attribute.Getattributes();
			
			for (auto i = atttri.begin(); i != atttri.end(); i++)
			{
				if (i->Getname().compare(L"ref") == 0)
				{
					name = i->Getvalue();
				}
			}

			if (_catalog==nullptr)
			{
				return;    
			}
		
			auto dfsf = _catalog->m_pCatalogueList;
			FeatureCatalogue* fc = _catalog->m_pCatalogueList.begin()->second;
			auto fc_simpleAttribute = fc->GetSimpleAttribute(name);
			auto fc_complexAttribute = fc->GetComplexAttribute(name);

			TVINSERTSTRUCT tvi;
			tvi.hParent = TVI_ROOT;
			tvi.hInsertAfter = TVI_LAST;
			tvi.item.mask = TVIF_TEXT;

			if (fc_simpleAttribute)
			{
				tvi.item.pszText = LPWSTR(fc_simpleAttribute->name.c_str());
				tvi.item.lParam = (LPARAM)fc_simpleAttribute;
			}
			else if (fc_complexAttribute)
			{
				tvi.item.pszText = LPWSTR(fc_complexAttribute->name.c_str());
				tvi.item.lParam = (LPARAM)fc_complexAttribute;
			}
			else
			{
				tvi.item.pszText = LPWSTR(name.c_str());
			}

			HTREEITEM insertedItem = InsertItem(&tvi);
			SetItemData(insertedItem, (DWORD_PTR)ab);
		}
	}

}

void CDialogTreeAttributeList::SetShowTree(Catalog* _catalog, InformationType* ift)
{
	m_type = 2;

	DeleteAllItems();

	if (ift == nullptr)
	{
		return;
	}

	for (auto itor = ift->attributeBinding.begin(); itor != ift->attributeBinding.end(); itor++)
	{
		AttributeBinding* ab = &(*itor);

		std::wstring name;

		auto attri= ab->attribute.Getattributes(); 
		for (auto i = attri.begin(); i != attri.end(); i++)
		{
			if (i->Getname().compare(L"ref") == 0)
			{
				name = i->Getvalue();
			}
		}

		FeatureCatalogue* fc = _catalog->m_pCatalogueList.begin()->second;
		auto fc_simpleAttribute = fc->GetSimpleAttribute(name);
		auto fc_complexAttribute = fc->GetComplexAttribute(name);

		TVINSERTSTRUCT tvi;
		tvi.hParent = TVI_ROOT;
		tvi.hInsertAfter = TVI_LAST;
		tvi.item.mask = TVIF_TEXT;

		if (fc_simpleAttribute)
		{
			tvi.item.pszText = LPWSTR(fc_simpleAttribute->name.c_str());
			tvi.item.lParam = (LPARAM)fc_simpleAttribute;
		}
		else if (fc_complexAttribute)
		{
			tvi.item.pszText = LPWSTR(fc_complexAttribute->name.c_str());
			tvi.item.lParam = (LPARAM)fc_complexAttribute;
		}
		else
		{
			tvi.item.pszText = LPWSTR(name.c_str());
		}

		HTREEITEM insertedItem = InsertItem(&tvi);
		SetItemData(insertedItem, (DWORD_PTR)ab);
	}
}

void CDialogTreeAttributeList::InsertAttribute(HTREEITEM &item)
{
	if (item)
	{
		if (m_type == 1)
		{
			CAttribute* pAttr = (CAttribute*)GetItemData(item);
			theApp.m_DockablePaneEditWindow.AddAttribute(pAttr);
		}
		else if (m_type == 2)
		{
			AttributeBinding* ab = (AttributeBinding*)GetItemData(item);
			theApp.m_DockablePaneEditWindow.AddAttribute(ab, pParentAttribute, selectIndexNum);
		}
	}
}

void CDialogTreeAttributeList::ComplexSetShowTree(Catalog* _catalog, AttributeBinding* ab)
{
	std::wstring name;
	auto attribute = ab->attribute.Getattributes();
	for (auto i = attribute.begin(); i != attribute.end(); i++)
	{
		if (i->Getname().compare(L"ref") == 0)
		{
			name = i->Getvalue();
		}
	}
	FeatureCatalogue* fc = _catalog->m_pCatalogueList.begin()->second;
	auto fc_simpleAttribute = fc->GetSimpleAttribute(name);
	auto fc_complexAttribute = fc->GetSimpleAttribute(name);

	TVINSERTSTRUCT tvi;
	tvi.hParent = TVI_ROOT;
	tvi.hInsertAfter = TVI_LAST;
	tvi.item.mask = TVIF_TEXT;

	if (fc_simpleAttribute)
	{
		tvi.item.pszText = LPWSTR(fc_simpleAttribute->name.c_str());
		tvi.item.lParam = (LPARAM)fc_simpleAttribute;
	}
	else if (fc_complexAttribute)
	{
		tvi.item.pszText = LPWSTR(fc_complexAttribute->name.c_str());
		tvi.item.lParam = (LPARAM)fc_complexAttribute;
	}
	else
	{
		tvi.item.pszText = LPWSTR(name.c_str());
	}
	HTREEITEM insertedItem = InsertItem(&tvi);
	SetItemData(insertedItem, (DWORD_PTR)ab);

}

void CDialogTreeAttributeList::BaseSetShowThee() 
{
	auto featureType = theApp.pView->m_pNewFeatureManager->GetFeatureType();
	if (featureType!=nullptr)
	{ 
		SetShowTree(theApp.pView->m_pNewFeatureManager->GetCatalog(), featureType);
	} 
	auto informationType=theApp.m_DockablePaneCurrentSelection.pDlg->m_selectedInformationType;
	if (informationType!=nullptr)
	{
		SetShowTree(theApp.pView->m_pNewFeatureManager->GetCatalog(), informationType);
	}
}