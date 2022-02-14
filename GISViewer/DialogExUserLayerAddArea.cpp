#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExUserLayerAddArea.h"
#include "afxdialogex.h"

#include "GISViewerView.h"

IMPLEMENT_DYNAMIC(CDialogExUserLayerAddArea, CDialogEx)

CDialogExUserLayerAddArea::CDialogExUserLayerAddArea(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogExUserLayerAddArea::IDD, pParent)
	, m_strName(_T(""))
	, m_strDescription(_T(""))
{

}

CDialogExUserLayerAddArea::~CDialogExUserLayerAddArea()
{
	points.clear();
}

void CDialogExUserLayerAddArea::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_LBString(pDX, IDC_LIST_DESCRIPTION, m_strDescription);
	DDX_Control(pDX, IDC_LIST_VIEW_COORDINATES, m_ListCtrlCoordinates);
}


BEGIN_MESSAGE_MAP(CDialogExUserLayerAddArea, CDialogEx)
END_MESSAGE_MAP()


// CDialogExUserLayerAddArea 메시지 처리기입니다.
