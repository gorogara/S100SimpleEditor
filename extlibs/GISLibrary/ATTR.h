#pragma once

struct ATTR
{
public: 
	unsigned m_natc; 
	unsigned m_atix; 
	unsigned m_paix; 
	unsigned m_atin; 
	CString m_atvl = L"";

private:      

public:
	static const int OffsetToATVL = 7;
};