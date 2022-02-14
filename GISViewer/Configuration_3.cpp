// Configuration_3.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "GISViewer.h"
#include "Configuration_3.h"
#include "afxdialogex.h"

#include "GISLibrary/GISLibrary.h" 

IMPLEMENT_DYNAMIC(CConfiguration_3, CDialogEx)

CConfiguration_3::CConfiguration_3(CWnd* pParent )
	: CDialogEx(CConfiguration_3::IDD, pParent)
{

}

CConfiguration_3::~CConfiguration_3()
{
}

void CConfiguration_3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_UNIT_DISTANCE, m_ComboBoxUnitDistance);
}


BEGIN_MESSAGE_MAP(CConfiguration_3, CDialogEx)
	ON_BN_CLICKED(IDOK, &CConfiguration_3::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CConfiguration_3::OnBnClickedCancel)
END_MESSAGE_MAP() 


void CConfiguration_3::OnBnClickedOk()
{
}


void CConfiguration_3::OnBnClickedCancel()
{
}


BOOL CConfiguration_3::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 
	InitComboBoxUnitDistance();

	return TRUE;  
}

void CConfiguration_3::InitComboBoxUnitDistance()
{
	AddString_ComboBox_UnitDistance();
	SetCurSel_ComboBox_UnitDistance();
}

void CConfiguration_3::AddString_ComboBox_UnitDistance()
{
	m_ComboBoxUnitDistance.AddString(_T("km"));
	m_ComboBoxUnitDistance.AddString(_T("해리"));
}

void CConfiguration_3::SetCurSel_ComboBox_UnitDistance()
{
	m_ComboBoxUnitDistance.SetCurSel(ENCCommon::UNIT_DISTANCE);
}