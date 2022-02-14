#include "stdafx.h"
#include "OnlineFunctionCode.h"

#include "..\\DLL_MessageProcess\DLL_MessageProcess.h"

OnlineFunctionCode::OnlineFunctionCode()
{
	InsertValue(L"download");
	InsertValue(L"information");
	InsertValue(L"offlineAccess");
	InsertValue(L"order");
	InsertValue(L"search");
}


OnlineFunctionCode::~OnlineFunctionCode()
{
}



void OnlineFunctionCode::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	SetValueString(std::wstring(pNode->Gettext())); 
}
void OnlineFunctionCode::GetContents(pugi::xml_node& node)
{
	SetValueString(pugi::as_wide(node.child_value())); 
}

