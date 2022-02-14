#include "stdafx.h"
#include "LOG.h"

LOG::LOG() {

}

LOG::~LOG() {

}


void LOG::Set_Log(CString logContent, ENCCommon::UserMode mode, int logtype, ENCCommon::ReportingData reporting)
{
	LogContent = logContent;
	userMode = mode;
	LogType = logtype;
	reportingData = reporting;
}