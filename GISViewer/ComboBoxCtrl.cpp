// ComboBoxCtrl.cpp : ���� �����Դϴ�. 

#include "stdafx.h"
#include "GISViewer.h"
#include "ComboBoxCtrl.h" 

IMPLEMENT_DYNAMIC(CComboBoxCtrl, CComboBox)

CComboBoxCtrl::CComboBoxCtrl()
{

}

CComboBoxCtrl::~CComboBoxCtrl()
{
}


BEGIN_MESSAGE_MAP(CComboBoxCtrl, CComboBox)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &CComboBoxCtrl::OnCbnSelchange)
END_MESSAGE_MAP() 




void CComboBoxCtrl::OnCbnSelchange()
{                                                   
}
