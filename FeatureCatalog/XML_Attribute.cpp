#include "stdafx.h"
#include"XML_Attribute.h"
#include <pugixml.hpp>


XML_Attribute::XML_Attribute()
{
}

XML_Attribute::~XML_Attribute()
{
}

void XML_Attribute::Setname(std::wstring& values)
{
	name = value;
}

void XML_Attribute::Setname(char* value)
{
	name = pugi::as_wide(value);
}

std::wstring& XML_Attribute::Getname()
{
	return name;
}

void XML_Attribute::Setvalue(std::wstring& values)
{
	value = values;
}

void XML_Attribute::Setvalue(char* _value)
{
	value = pugi::as_wide(_value);
	int i = 0;
}

std::wstring& XML_Attribute::Getvalue()
{
	return value;
}

char* XML_Attribute::GetvalueString()
{
	std::string resultstring= std::string(value.begin(), value.end());
	char*  result = new char[resultstring.size()+1];
	strcpy(result, resultstring.c_str());
	return result;
}