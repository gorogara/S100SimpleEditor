#include "stdafx.h"
#include "ResponsibleParty.h"

#include "..\\DLL_MessageProcess\DLL_MessageProcess.h"

ResponsibleParty::ResponsibleParty()
{
}


ResponsibleParty::~ResponsibleParty()
{
}




void ResponsibleParty::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare("individualName") == 0)
		{
			individualName = pChildNode->Gettext();
		}
		else if (baseName.compare("organisationName") == 0)
		{
			organisationName = pChildNode->Gettext();
		}
		else if (baseName.compare("positionName") == 0)
		{
			positionName = pChildNode->Gettext();
		}
		else if (baseName.compare("contactInfo") == 0)
		{
			contactInfo.GetContents(pChildNode);
		}
		else if (baseName.compare("role") == 0)
		{
			role.GetContents(pChildNode);
		}
		else if (baseName.compare("party") == 0)
		{ 
		}
	}
}
void ResponsibleParty::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();

		if (!strcmp(instructionName, "S100CI:individualName"))
		{
			individualName = pugi::as_wide(instruction.child_value());
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:individualName setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:organisationName"))
		{
			organisationName = pugi::as_wide(instruction.child_value());
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:organisationName setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:positionName"))
		{
			positionName = pugi::as_wide(instruction.child_value());
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:positionName setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:contactInfo"))
		{
			contactInfo.GetContents(instruction);
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:contactInfo setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:role"))
		{
			role.GetContents(instruction);
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:role setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if(!strcmp(instructionName,"S100CI:party"))
		{
			party.GetContents(instruction);

		}
		else 
		{
			std::wstring content = pugi::as_wide(instruction.child_value());
			content.append(L" is another data");
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, content.c_str(),KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
	}
}

