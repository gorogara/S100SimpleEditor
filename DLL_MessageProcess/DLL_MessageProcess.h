// DLL_MessageProcess.h : DLL_MessageProcess DLL의 기본 헤더 파일입니다. 

#pragma once

#include "Enum.h"


#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#define KRS_CODE_MESSAGE (WM_USER+7)

#define KRS_MSG_INFO	0xFF002001
#define KRS_MSG_ERROR	0xFF002002
#define KRS_MSG_WARNING	0xFF002003

#define KRS_MSG_NEW_LAYER	0xFF002004

#ifdef MSG_PROCESS_DLL_EXPORTS
#define MSG_PROCESS_DLL_API __declspec(dllexport) 
#else
#define MSG_PROCESS_DLL_API __declspec(dllimport) 
#endif   

class CListCtrl;
class CView;

namespace KRS_MSG_PROCESS
{
	MSG_PROCESS_DLL_API void SetTargetWindowHandle(CListCtrl* listCtrl);
	MSG_PROCESS_DLL_API void SetTargetMainViewClass(CView* listCtrl);        

	MSG_PROCESS_DLL_API void SendMessageToTargetWindow(int msgType, CString msg, CString mode, CString data);
	MSG_PROCESS_DLL_API void SendMessageToTargetWindow(int msgType, CString msg, UserMode mode, ReportingData data);
	MSG_PROCESS_DLL_API void SendMessageToTargetMainView(LPARAM newLayer);

	MSG_PROCESS_DLL_API CString AddLayerMessage(CString filePath);
	
	MSG_PROCESS_DLL_API UserMode GetUserMode();
	MSG_PROCESS_DLL_API void SetUserMode(UserMode value);
	
	MSG_PROCESS_DLL_API ReportingData GetReportingData();
	MSG_PROCESS_DLL_API void SetReportingData(ReportingData value);


	MSG_PROCESS_DLL_API CString EnumToString(UserMode mode);
	MSG_PROCESS_DLL_API CString EnumToString(ReportingData data);
}


class MSG_PROCESS_DLL_API CDLL_MessageProcessApp : public CWinApp
{
public:

	CDLL_MessageProcessApp();
	CListCtrl *listCtrl;
	CView *viewCtrl;
	KRS_MSG_PROCESS::UserMode m_UserMode; 
	KRS_MSG_PROCESS::ReportingData m_ReportingData; 

public: 
public:
	
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};
