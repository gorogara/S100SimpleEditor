#include "stdafx.h"
#include "MFCTabCtrlMsgToParent.h"


CMFCTabCtrlMsgToParent::CMFCTabCtrlMsgToParent()
{
}


CMFCTabCtrlMsgToParent::~CMFCTabCtrlMsgToParent()
{
}

BEGIN_MESSAGE_MAP(CMFCTabCtrlMsgToParent, CMFCTabCtrl)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()

LRESULT CMFCTabCtrlMsgToParent::OnPropertyChanged(WPARAM wparam, LPARAM lparam)
{
	CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)lparam;
	if (!pProp)
		return 0;

	GetParent()->SendMessage(AFX_WM_PROPERTY_CHANGED, wparam, lparam); 

	return 0;
}

BOOL CMFCTabCtrlMsgToParent::PreTranslateMessage(MSG* pMsg)
{ 

	switch (pMsg->message)
	{
	case WM_TRANSLATION_MESSAGE_TO_PARENT_DELETE_ATTRIBUTE:
	case WM_TRANSLATION_MESSAGE_TO_PARENT_ADD_VECTOR:
	case WM_TRANSLATION_MESSAGE_TO_PARENT_DELETE_VECTOR:
		GetParent()->SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
		break;
	}

	return CMFCTabCtrl::PreTranslateMessage(pMsg);
}
