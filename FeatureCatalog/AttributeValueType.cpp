#include "stdafx.h"
#include "AttributeValueType.h"


AttributeValueType::AttributeValueType()
{
	InsertValue(L"boolean");
	InsertValue(L"enumeration");
	InsertValue(L"integer");
	InsertValue(L"real");
	InsertValue(L"text");
	InsertValue(L"date");
	InsertValue(L"time");
	InsertValue(L"dateTime");
	InsertValue(L"URI");
	InsertValue(L"URL");
	InsertValue(L"URN");
	InsertValue(L"S100_CodeList");
	InsertValue(L"S100_TruncatedDate");
}

AttributeValueType::~AttributeValueType()
{
}

void AttributeValueType::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	SetValueString(std::wstring(pNode->Gettext()));
}
void AttributeValueType::GetContents(pugi::xml_node& node)
{
	SetValueString(pugi::as_wide(node.child_value())); 
}