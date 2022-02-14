#pragma once
#include "XML_Item.h"
#include <string>
#include <unordered_map>

class Restriction_Item : public XML_Item
{
public:
	Restriction_Item();
	virtual ~Restriction_Item();

public:
	std::unordered_map<std::wstring, std::wstring> permittedValues;
	std::wstring pattern;
	std::wstring maxExclusive;
	std::wstring valueString;
	int valueInteger;

public:
	void SetPermittedValues(std::unordered_map<std::wstring, std::wstring>& value);
	std::unordered_map<std::wstring, std::wstring>& GetPermittedValues();

	void SetPattern(std::wstring& value);
	std::wstring& GetPattern();

	void SetMaxExclusive(std::wstring& value);
	std::wstring& GetMaxExclusive();

	void SetValueString(std::wstring& value); 
	std::wstring& GetValueString();


	void SetValueInteger(int value);
	int GetvalueInteger();

	void InsertValue(std::wstring value);
};