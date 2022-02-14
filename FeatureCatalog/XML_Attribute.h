#pragma once

#include <string>

class XML_Attribute
{
public:
	XML_Attribute();
	virtual ~XML_Attribute();

private:
	std::wstring name;
	std::wstring value;

public:
	void Setname(std::wstring& values);
	void Setname(char* value);
	std::wstring& Getname();

	void Setvalue(std::wstring& value);
	void Setvalue(char* attribute);
	std::wstring& Getvalue();
	char* GetvalueString();
};