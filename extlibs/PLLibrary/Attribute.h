#pragma once
#include <vector> 

class AttributeListValue;
class CAttribute
{
public:
	CAttribute();
	virtual ~CAttribute();

public:
	CString Acronym;
	int Code;
	int Indication;
	CString Project;
	CString Attribute_name;
	CString Value;
	CString References_INT_1;
	CString References_M_4;
	CString References_File_name;
	CString Page_number;
	CString Version_number;
	int Attribute_type;
	CString Format;
	CString Minimum_Value;
	CString Maximum_Value;
	std::vector<AttributeListValue*> valueList;
};