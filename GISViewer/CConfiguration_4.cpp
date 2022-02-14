// CConfiguration_4.cpp: 구현 파일
//

#include "stdafx.h"
#include "GISViewer.h"
#include "Configuration_4.h"
#include "afxdialogex.h"
#include "../GISLibrary/GISLibrary.h"

// CConfiguration_4 대화 상자

IMPLEMENT_DYNAMIC(CConfiguration_4, CDialogEx)

CConfiguration_4::CConfiguration_4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONFIG_4, pParent)
{

}

CConfiguration_4::~CConfiguration_4()
{
}

void CConfiguration_4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfiguration_4, CDialogEx)
END_MESSAGE_MAP()


// CConfiguration_4 메시지 처리기
