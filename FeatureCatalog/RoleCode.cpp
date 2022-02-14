#include "stdafx.h"
#include "RoleCode.h"



RoleCode::RoleCode()
{
	InsertValue(L"resourceProvider");
	InsertValue(L"custodian");
	InsertValue(L"owner");
	InsertValue(L"user");
	InsertValue(L"distributer");
	InsertValue(L"originator");
	InsertValue(L"pointOfContact");
	InsertValue(L"principalInvestigator");
	InsertValue(L"processor");
	InsertValue(L"publisher");
}


RoleCode::~RoleCode()
{
}

void RoleCode::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	SetValueString(std::wstring(pNode->Gettext()));
}

void RoleCode::GetContents(pugi::xml_node& node)
{
	SetValueString(pugi::as_wide(node.child_value()));
}