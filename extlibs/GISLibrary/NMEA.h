#pragma once

#define CMD_OTHERS 0
#define CMD_GPS    1

class NMEA
{
public:
	NMEA();
	virtual ~NMEA();

protected:
	CString m_DATA;
	CString m_END_OF_SENTENCE;
	HWND		m_hwnd; 
public:
	bool	m_validGPS;
	double	m_Lon;
	double	m_Lat;

public:
	void AddString(CString str);
	bool Processing();
protected:
	void SetHwnd(HWND hwnd);
	int GetCommand(CString sentence);
	int GetGPG(CString sentence);
	bool ProcCommand(int icmd, CString sentence);
};

