// PropertyModify.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "PropertyGridVectorModify.h"
#include "resource.h"

#include "GISLibrary/F_ATTR.h" 

IMPLEMENT_DYNAMIC(CPropertyGridVectorModify, CMFCPropertyGridCtrl)

CPropertyGridVectorModify::CPropertyGridVectorModify()
{
	pSelectedProperty = NULL;
}

CPropertyGridVectorModify::~CPropertyGridVectorModify()
{
}


BEGIN_MESSAGE_MAP(CPropertyGridVectorModify, CMFCPropertyGridCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_VECTOR_EDIT_ADD, &CPropertyGridVectorModify::OnAddVector)
	ON_COMMAND(ID_VECTOR_EDIT_DEL, &CPropertyGridVectorModify::OnDeleteVector)
END_MESSAGE_MAP() 
void CPropertyGridVectorModify::OnLButtonDown(UINT nFlags, CPoint point)
{ 
	CMFCPropertyGridProperty::ClickArea clickArea;
	CMFCPropertyGridProperty *pProp;
	pProp = HitTest(point, &clickArea);
	if (pProp != NULL)
	{
		pSelectedProperty = pProp;

		CWnd* pParent = GetParent();
		pParent->PostMessage(WM_TRANSLATION_MESSAGE_TO_PARENT_SELECTED_VECTOR, (WPARAM)this->m_hWnd, (LPARAM)pSelectedProperty);
	}

	CMFCPropertyGridCtrl::OnLButtonDown(nFlags, point);
}


void CPropertyGridVectorModify::OnRButtonDown(UINT nFlags, CPoint point)
{ 
	CMFCPropertyGridProperty::ClickArea clickArea;
	CMFCPropertyGridProperty* pHit = HitTest(point, &clickArea);

	if (clickArea == CMFCPropertyGridProperty::ClickName ||
		clickArea == CMFCPropertyGridProperty::ClickValue){

		ATTR* attr = (ATTR*)pHit->GetData(); 
		{  
			CPoint point;
			::GetCursorPos(&point);
			CMenu menu;
			VERIFY(menu.LoadMenu(IDR_MENU_EDIT_PANE)); 
			CMenu* popup = menu.GetSubMenu(1);
			popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this); 
			pSelectedProperty = pHit;
		}
	}

	return; 
}

void CPropertyGridVectorModify::OnAddVector()
{
	CWnd* pParent = GetParent();

	if (pSelectedProperty)
	{
		pParent->PostMessage(WM_TRANSLATION_MESSAGE_TO_PARENT_ADD_VECTOR, (WPARAM)this->m_hWnd, (LPARAM)pSelectedProperty);//pMsg->wParam, pMsg->lParam);
	}
}

void CPropertyGridVectorModify::OnDeleteVector()
{
	CWnd* pParent = GetParent();

	if (pSelectedProperty)
	{
		pParent->PostMessage(WM_TRANSLATION_MESSAGE_TO_PARENT_DELETE_VECTOR, (WPARAM)this->m_hWnd, (LPARAM)pSelectedProperty);//pMsg->wParam, pMsg->lParam);
	}
}
