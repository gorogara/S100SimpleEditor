#pragma once
#include<string>

class AttributeListValue
{
public:
	AttributeListValue();
	virtual ~AttributeListValue();
public:
	int index;
	std::wstring name;
};