#pragma once
#include <list>
#include <string>
#include "XML_Attribute.h"

class XML_Item
{
public: 
	XML_Item();
	virtual ~XML_Item();
	
public: 
	std::list<XML_Attribute> attributes;
	std::wstring value;

public: 
	virtual void GetContents() {};
	void SetAttributes(std::list<XML_Attribute>& value);
	void SetAttributes(XML_Attribute& value);
	std::list<XML_Attribute> Getattributes();
	std::list<XML_Attribute>* GetattributesPointer();
	void Setvalue(std::wstring& value);
	std::wstring Getvalue();
	std::wstring* GetvaluePointer();
	std::wstring GetReference();
	void SetReference(std::wstring _value);
};