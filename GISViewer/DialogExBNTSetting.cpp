
// DialogExBNTSetting.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExBNTSetting.h"
#include "afxdialogex.h"
#include "GISViewerView.h"

// CDialogExBNTSetting ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDialogExBNTSetting, CDialogEx)

CDialogExBNTSetting::CDialogExBNTSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogExBNTSetting::IDD, pParent),
      m_pView(nullptr)
{

}

CDialogExBNTSetting::~CDialogExBNTSetting()
{
}

void CDialogExBNTSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START_DATE, m_DataTimeCtrlStartDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START_TIME, m_DateTimeCtrlStartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END_DATE, m_DateTimeCtrlEndDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END_TIME, m_DateTimeCtrlEndTime);
	DDX_Control(pDX, IDC_COMBO_INTERVAL, m_ComboBoxInterval);
}


BEGIN_MESSAGE_MAP(CDialogExBNTSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogExBNTSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogExBNTSetting::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDialogExBNTSetting �޽��� ó�����Դϴ�.

void CDialogExBNTSetting::PostNcDestroy()
{
	CDialogEx::PostNcDestroy();
	m_pView->m_pDlgBNTSetting = nullptr;
	delete this;
}


void CDialogExBNTSetting::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pView->m_pMainFrame->GetRibbonBar();
	CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_RIBBON_SLIDER_BNT_SLIDER);
	slider->SetZoomIncrement(1);

#ifdef BNT_MODULE

	theApp.m_Times.clear();
#endif
#ifdef BNT_MODULE
	SYSTEMTIME sDate, sTime, eDate, eTime;
	m_DataTimeCtrlStartDate.GetTime(&sDate);
	m_DateTimeCtrlStartTime.GetTime(&sTime);
	m_DateTimeCtrlEndDate.GetTime(&eDate);
	m_DateTimeCtrlEndTime.GetTime(&eTime);

	CTime limitTime1(2014, 1, 1, 02, 26, 0);
	CTime limitTime2(2014, 12, 31, 23, 20, 0);

	CTime sCTime(sDate.wYear, sDate.wMonth, sDate.wDay, sTime.wHour, sTime.wMinute, sTime.wSecond);
	CTime eCTime(eDate.wYear, eDate.wMonth, eDate.wDay, eTime.wHour, eTime.wMinute, eTime.wSecond);
	CTime tCTime;

	if (sCTime > eCTime) {
		AfxMessageBox(_T("���� ���� �ð��� ���� ���� �ð����� ����� �մϴ�."));
		return;
	}

	if (sCTime < limitTime1) {
		AfxMessageBox(_T("���� �ð��� 2014�� 1�� 1�� ���� 2�� 26�к��� 2014�� 12�� 31�� ���� 11�� 20�б��� �Դϴ�."));
		return;
	}
	
	SYSTEMTIME tTime;
	sCTime.GetAsSystemTime(tTime);
	theApp.m_Times.push_back(tTime);

	while (true)
	{
		if (m_ComboBoxInterval.GetCurSel() == 0) // 10
		{
			tCTime = sCTime + CTimeSpan(0, 0, 10, 0);
		}
		else if (m_ComboBoxInterval.GetCurSel() == 1) // 30
		{
			tCTime = sCTime + CTimeSpan(0, 0, 30, 0);
		}
		else if (m_ComboBoxInterval.GetCurSel() == 2) // 60
		{
			tCTime = sCTime + CTimeSpan(0, 1, 0, 0);
		}
		else
		{
			OutputDebugString(_T("GISViewer : Can't find selected interval"));
			return;
		}

		if (tCTime > eCTime)
		{
			break;
		}
		else
		{
			tCTime.GetAsSystemTime(tTime);
			theApp.m_Times.push_back(tTime);
			sCTime = tCTime;
		}
	}

	CTime lastTime(theApp.m_Times.back());

	if (lastTime != eCTime)
	{
		eCTime.GetAsSystemTime(tTime);
		theApp.m_Times.push_back(tTime);
	}


	slider->SetRange(0, theApp.m_Times.size() - 1);
	slider->SetPos(0);

	try {
		m_pView->m_pMainFrame->DisplayBNTTime(theApp.m_Times.at(0));
	}
	catch (std::out_of_range)
	{
		OutputDebugString(_T("GISViewer : exception error in DialogExBNTSetting.cpp (117)"));
		return;
	}
	
	theApp.Reset_Frame(theApp.m_Times.at(0));
	m_pView->Invalidate();

	DestroyWindow();
#endif
}


void CDialogExBNTSetting::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DestroyWindow();
}


BOOL CDialogExBNTSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SYSTEMTIME sTime, eTime;
	GetLocalTime(&sTime);
	CTime afterOneMonth(sTime);
	afterOneMonth += CTimeSpan(7, 0, 0, 0);
	afterOneMonth.GetAsSystemTime(eTime);
	m_DateTimeCtrlEndDate.SetTime(&eTime);

	m_ComboBoxInterval.AddString(_T("10"));
	m_ComboBoxInterval.AddString(_T("30"));
	m_ComboBoxInterval.AddString(_T("60"));
	m_ComboBoxInterval.SetCurSel(2);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
