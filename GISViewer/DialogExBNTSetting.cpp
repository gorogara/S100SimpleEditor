
// DialogExBNTSetting.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExBNTSetting.h"
#include "afxdialogex.h"
#include "GISViewerView.h"

// CDialogExBNTSetting 대화 상자입니다.

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


// CDialogExBNTSetting 메시지 처리기입니다.

void CDialogExBNTSetting::PostNcDestroy()
{
	CDialogEx::PostNcDestroy();
	m_pView->m_pDlgBNTSetting = nullptr;
	delete this;
}


void CDialogExBNTSetting::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		AfxMessageBox(_T("예측 시작 시간이 종료 예측 시간보다 빨라야 합니다."));
		return;
	}

	if (sCTime < limitTime1) {
		AfxMessageBox(_T("예측 시간은 2014년 1월 1일 오전 2시 26분부터 2014년 12월 31일 오후 11시 20분까지 입니다."));
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DestroyWindow();
}


BOOL CDialogExBNTSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
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
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
