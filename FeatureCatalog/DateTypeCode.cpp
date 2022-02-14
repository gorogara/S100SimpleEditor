#include "stdafx.h"
#include "DateTypeCode.h"


DateTypeCode::DateTypeCode()
{
	InsertValue(L"creation");
	InsertValue(L"publication");
	InsertValue(L"revision");
}

DateTypeCode::~DateTypeCode()
{
}

void DateTypeCode::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	SetValueString(std::wstring(pNode->Gettext())); 
}

void DateTypeCode::GetContents(pugi::xml_node& node)
{
	SetValueString(pugi::as_wide(node.child_value())); 
}