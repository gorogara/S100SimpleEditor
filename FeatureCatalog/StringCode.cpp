#include "stdafx.h"
#include "StringCode.h"


StringCode::StringCode()
{
}


StringCode::~StringCode()
{
}

void StringCode::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	SetValueString(std::wstring(pNode->Gettext()));
}

void StringCode::GetContents(pugi::xml_node& node)
{
	SetValueString(pugi::as_wide(node.child_value()));
}