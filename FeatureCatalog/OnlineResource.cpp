#include "stdafx.h"
#include "OnlineResource.h"

#include "..\\DLL_MessageProcess\DLL_MessageProcess.h"
OnlineResource::OnlineResource()
{
}


OnlineResource::~OnlineResource()
{
}


void OnlineResource::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr pChildNode = pNodeList->Getitem(i);
		if (pChildNode == NULL)
			continue;
		if (!pChildNode->baseName)
			continue;

		std::string baseName = std::string(W2A(pChildNode->baseName));

		if (baseName.compare("url") == 0)
		{
			url = pChildNode->Gettext();
		}
		else if (baseName.compare("protocol") == 0)
		{
			protocol = pChildNode->Gettext();
		}
		else if (baseName.compare("applicationProfile") == 0)
		{
			applicationProfile = pChildNode->Gettext();
		}
		else if (baseName.compare("name") == 0)
		{
			name = pChildNode->Gettext();
		}
		else if (baseName.compare("description") == 0)
		{
			description = pChildNode->Gettext();
		}
		else if (baseName.compare("function") == 0)
		{
			function.GetContents(pChildNode);
		}
	}
}

void OnlineResource::GetContents(pugi::xml_node& node)
{ 
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();

		if (!strcmp(instructionName, "S100CI:url"))
		{
			url = pugi::as_wide(instruction.child_value()); 
		}
		else if (!strcmp(instructionName, "S100CI:protocol"))
		{
			protocol = pugi::as_wide(instruction.child_value()); 
		}
		else if (!strcmp(instructionName, "S100CI:applicationProfile"))
		{
			applicationProfile = pugi::as_wide(instruction.child_value()); 
		}
		else if (!strcmp(instructionName, "S100CI:name"))
		{
			name = pugi::as_wide(instruction.child_value()); 
		}
		else if (!strcmp(instructionName, "S100CI:description"))
		{
			description = pugi::as_wide(instruction.child_value()); 
		}
		else if (!strcmp(instructionName, "S100CI:function"))
		{
			function.GetContents(instruction); 
		}
		else if (!strcmp(instructionName, "S100CI:linkage"))
		{
			linkage = instruction.child_value();
		}
		else
		{
			std::wstring content = pugi::as_wide(instructionName);
			content.append(L" is another data");
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, content.c_str(),KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
	}
}

