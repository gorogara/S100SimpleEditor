#pragma once
#include "GeoMetryLibrary\\ENCCommon.h" 

 class LOG
{
public:
	CString				LogContent=L""; 
	ENCCommon::UserMode userMode; 
	int LogType = 0; 
	ENCCommon::ReportingData reportingData;


public:
	void Set_Log(CString LogContent, ENCCommon::UserMode mode,int logtype, ENCCommon::ReportingData reporting);
	
	LOG();
	virtual ~LOG();
};




