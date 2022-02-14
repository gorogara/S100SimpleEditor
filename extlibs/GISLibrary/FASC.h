#pragma once
#include <atlstr.h>

struct FASC { 
	unsigned m_natc; 
	unsigned m_atix; 
	unsigned m_paix; 
	unsigned m_atin; 
	CString m_atvl;
	static const int size = 7;
};