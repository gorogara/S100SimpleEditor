#include "stdafx.h"
#include "Telephone.h"

#include "..\\DLL_MessageProcess\DLL_MessageProcess.h"

Telephone::Telephone()
{
}


Telephone::~Telephone()
{
}

void Telephone::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare("voice") == 0)
		{
			voice.push_back(std::wstring(pChildNode->Gettext()));
		}
		else if (baseName.compare("facsimile") == 0)
		{
			facsimile = pChildNode->Gettext();
		}
	}
}
void Telephone::GetContents(pugi::xml_node& node)
{ 
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100CI:voice"))
		{
			voice.push_back(pugi::as_wide(instruction.child_value())); 
		}
		else if (!strcmp(instructionName, "S100CI:facsimile"))
		{
			facsimile = pugi::as_wide(instruction.child_value()); 
		}
		else 
		{
			std::wstring content = pugi::as_wide(instructionName);
			content.append(L"is another data");
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, content.c_str(),KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
	}
}