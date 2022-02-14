// DLL_MessageProcess.cpp : 해당 DLL의 초기화 루틴을 정의합니다. 

#include "stdafx.h"
#include "DLL_MessageProcess.h"

#include <thread>

using std::thread;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif                         

BEGIN_MESSAGE_MAP(CDLL_MessageProcessApp, CWinApp)
END_MESSAGE_MAP() 

CDLL_MessageProcessApp::CDLL_MessageProcessApp()
{  
} 
CDLL_MessageProcessApp theApp; 
BOOL CDLL_MessageProcessApp::InitInstance()
{
	CWinApp::InitInstance();

	listCtrl = NULL;
	viewCtrl = NULL;
	return TRUE;
}

namespace KRS_MSG_PROCESS
{
	void SetTargetWindowHandle(CListCtrl* listCtrl)
	{
		theApp.listCtrl = listCtrl;// ->GetSafeHwnd();
	}

	void SetTargetMainViewClass(CView* listCtrl)
	{
		theApp.viewCtrl = listCtrl;// ->GetSafeHwnd();
	}

	void SendMessageToTargetWindow(int msgType, CString msg, CString mode, CString data) 
	{
		if (theApp.listCtrl == NULL && msg.Compare(L"") == 0)
		{
			return;
		}

		CString * message = new CString(msg);
		message->Append(L"$" + mode);
		message->Append(L"$" + data);
		PostMessage(theApp.viewCtrl->GetSafeHwnd(), KRS_CODE_MESSAGE, (WPARAM)msgType, (LPARAM)message);
	}

	void SendMessageToTargetWindow(int msgType, CString msg, UserMode mode, ReportingData data)
	{
		CString userMode = EnumToString(mode);
		CString reportingData = EnumToString(data);

		if (userMode.IsEmpty())
		{
			int i = 0;
		}
		if (reportingData=="")
		{
			int i = 0;
		}


		SendMessageToTargetWindow(msgType, msg, userMode, reportingData);
	}

	void SendMessageToTargetMainView(LPARAM newLayer)
	{

		if (theApp.viewCtrl == NULL)
			return;
		PostMessage(theApp.viewCtrl->GetSafeHwnd(), KRS_CODE_MESSAGE, (WPARAM)KRS_MSG_NEW_LAYER, newLayer);
	}

	CString AddLayerMessage(CString filePath)
	{
		CString msg;
		msg.Append(L"ADD LAYER : ");
		msg.Append(filePath);

		return msg;
	}

	UserMode GetUserMode()
	{
		return theApp.m_UserMode;
	}

	void SetUserMode(UserMode value)
	{
		theApp.m_UserMode = value;
	}

	ReportingData GetReportingData() 
	{
		return theApp.m_ReportingData;
	}

	void SetReportingData(ReportingData value) 
	{
		theApp.m_ReportingData = value;
	}


	CString EnumToString(UserMode mode)
	{
		if (mode == UserMode::User_Mode)
		{
			return _T("User_Mode");
		}
		else if (mode == UserMode::User_Developer_Mode)
		{
			return _T("User_Developer_Mode");
		}
		else// if (mode == UserMode::Developer_Mode)
		{
			return _T("Developer_Mode");
		}
	}

	CString EnumToString(ReportingData data)
	{
		if (data == ReportingData::DataSet)
		{
			return _T("DataSet");
		}
		else if (data == ReportingData::FC)
		{
			return _T("FC");
		}
		else if (data == PC)
		{
			return _T("PC");
		}
		else
		{
			return _T("None");
		}

	}

}