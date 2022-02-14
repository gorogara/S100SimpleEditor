// DialogDockLayerManager.cpp : implementation file 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogDockLogger.h"
#include "GISViewerView.h"
#include "afxdialogex.h"

#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"


using namespace std;  


IMPLEMENT_DYNAMIC(CDialogDockLogger, CDialog)
CComboBox CDialogDockLogger::m_ComboLogType;
CListCtrl CDialogDockLogger::m_ListLogger;


CDialogDockLogger::CDialogDockLogger(CWnd* pParent )
	: CDialog(CDialogDockLogger::IDD, pParent)
{
	nSelectedItem = -1;
}

CDialogDockLogger::~CDialogDockLogger()
{
}

void CDialogDockLogger::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOGGER, m_ListLogger);
	DDX_Control(pDX, IDC_COMBO_LOG_TYPE, m_ComboLogType);
	DDX_Control(pDX, IDC_BUTTON_LISTCLEAR, b_ListClearButton);
}


BEGIN_MESSAGE_MAP(CDialogDockLogger, CDialog)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &CDialogDockLogger::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogDockLogger::OnBnClickedCancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_LOGGER, &CDialogDockLogger::OnLvnItemchangedList)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_NOTIFY(NM_CLICK, IDC_LIST_LOGGER, &CDialogDockLogger::OnNMClickListLm)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_LOGGER, &CDialogDockLogger::OnNMDblclkListLm)
	ON_BN_CLICKED(IDC_BUTTON_LISTCLEAR, &CDialogDockLogger::OnBnClickedButtonListclear) 
	ON_CBN_SELCHANGE(IDC_COMBO_LOG_TYPE, &CDialogDockLogger::OnCbnSelchangeComboLogType)
END_MESSAGE_MAP() 
int CDialogDockLogger::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;


	CRect rectDummy;
	rectDummy.SetRectEmpty(); 


	return 0;
}

void CDialogDockLogger::OnBnClickedOk()
{ 
	return;
}


void CDialogDockLogger::OnBnClickedCancel()
{ 
	return;
}


void CDialogDockLogger::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR); 

	*pResult = 0;
}


void CDialogDockLogger::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CDialogDockLogger::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialog::OnSizing(fwSide, pRect);
} 
BOOL CDialogDockLogger::OnInitDialog()
{
	CDialog::OnInitDialog(); 
	m_ListLogger.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CRect listRect;
	m_ListLogger.GetWindowRect(listRect);
	m_ListLogger.InsertColumn(0, _T("Date Time"), LVCFMT_CENTER, (int)(listRect.Width()*0.3));
	m_ListLogger.InsertColumn(1, _T("Log Text"), LVCFMT_LEFT, (int)(listRect.Width()*0.7));

	CRect rectDummy;
	rectDummy.SetRectEmpty();  
	m_ComboLogType.SetFont(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT))); 
	m_ComboLogType.AddString(_T("INFO"));
	m_ComboLogType.AddString(_T("WARNING"));
	m_ComboLogType.AddString(_T("ERROR"));
	m_ComboLogType.AddString(_T("ALL"));
	m_ComboLogType.SetCurSel(0); 




	AdjustLayout();
	UpdateListTest();


	return TRUE; 

}

void CDialogDockLogger::UpdateList()
{
	m_ListLogger.DeleteAllItems();
}

void CDialogDockLogger::OnNMClickListLm(NMHDR *pNMHDR, LRESULT *pResult)
{
}

void CDialogDockLogger::OnNMDblclkListLm(NMHDR *pNMHDR, LRESULT *pResult)
{
}


void CDialogDockLogger::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient, rectCombo;
	GetClientRect(rectClient);

	CRect      rectENCs;
	int comboBoxHeight = 30; 
	int buttonWidth = 70;

	if (m_ComboLogType.GetSafeHwnd())
	{
		m_ComboLogType.SetWindowPos(&wndTop,
			rectClient.left, rectClient.top, rectClient.Width() - buttonWidth, comboBoxHeight - 10,
			SWP_SHOWWINDOW);
	}
	if (m_ListLogger.GetSafeHwnd())
	{
		rectENCs = CRect(rectClient.left, rectClient.top + comboBoxHeight, rectClient.Size().cx, rectClient.Size().cy);
		m_ListLogger.MoveWindow(rectENCs);
		m_ListLogger.SetColumnWidth(0, (int)(rectENCs.Width()*0.2)); 
		m_ListLogger.SetColumnWidth(1, (int)(rectENCs.Width()*0.8)); 
	}
	if (b_ListClearButton.GetSafeHwnd())
	{
		b_ListClearButton.SetWindowPos(&wndTop,
			rectClient.Width() - buttonWidth + 10, rectClient.top, buttonWidth - 10, comboBoxHeight - 10,
			SWP_SHOWWINDOW);
	}
}


void CDialogDockLogger::UpdateListTest()
{
	m_ListLogger.DeleteAllItems();
	LVITEM firstItem = { 0 };
	m_ListLogger.InsertItem(&firstItem); 
	theApp.m_DockablePaneLogger.AppendList(_T("[Logger] Logger start!!"));

	UpdateData(false);
}

void CDialogDockLogger::AppendList(CString str)
{
	LVITEM firstItem = { 0 };
	m_ListLogger.InsertItem(&firstItem); 

	time_t now = 0;
	time(&now); 

	char buf[256] = { 0, };
	struct tm tmbuf;

	localtime_s(&tmbuf, &now);

	strftime(buf, 256, "%H:%M:%S", &tmbuf);   
	m_ListLogger.SetItemText(0, 0, CString(buf));
	m_ListLogger.SetItemText(0, 1, str);

	UpdateData(false);
}

void CDialogDockLogger::OnBnClickedButtonListclear() 
{
	m_ListLogger.DeleteAllItems();
	CGISViewerView::LogList.clear(); 

}

void CDialogDockLogger::OnCbnSelchangeComboLogType()
{

	if (CGISViewerView::LogList.size() != 0)
	{
		m_ListLogger.ShowWindow(FALSE);
		m_ListLogger.DeleteAllItems();  
		CString comboBox;
		int nIndex;

		nIndex = CDialogDockLogger::m_ComboLogType.GetCurSel();
		CDialogDockLogger::m_ComboLogType.GetLBText(nIndex, comboBox); 


		for (unsigned i = 0; i < CGISViewerView::LogList.size(); i++)
		{
			ENCCommon::UserMode Mode = CGISViewerView::LogList[i].userMode;

			if (Mode == ENCCommon::m_UserMode || Mode == ENCCommon::User_Developer_Mode) 
			{
				if (comboBox == "ALL")
				{
					theApp.m_DockablePaneLogger.AppendList(CGISViewerView::LogList[i].LogContent); 
				}
				else if (comboBox == "INFO"&&CGISViewerView::LogList[i].LogType == KRS_MSG_INFO)
				{
					theApp.m_DockablePaneLogger.AppendList(CGISViewerView::LogList[i].LogContent); 
				}
				else if (comboBox == "ERROR"&&CGISViewerView::LogList[i].LogType == KRS_MSG_ERROR)
				{
					theApp.m_DockablePaneLogger.AppendList(CGISViewerView::LogList[i].LogContent); 
				}
				else if (comboBox == "WARNING"&&CGISViewerView::LogList[i].LogType == KRS_MSG_WARNING)
				{
					theApp.m_DockablePaneLogger.AppendList(CGISViewerView::LogList[i].LogContent); 
				}
			}
			else
			{

			}
		}

		m_ListLogger.ShowWindow(TRUE);
	}
	else
	{
		return;
	}
}        
