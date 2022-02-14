#pragma once
#include<atlstr.h>


class GMLValue
{
public:
	GMLValue(); 
	GMLValue(CString camelCase, CString value); 
	virtual ~GMLValue() ;
private:
	bool m_hasValue;

public:
	CString m_value;
	CString m_camelCase;

	GMLValue& operator = (const CString &str);
	bool HasValue();
};