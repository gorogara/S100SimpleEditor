#include "stdafx.h"
#include "DefinitionSources.h"

#include "..\\DLL_MessageProcess\DLL_MessageProcess.h"
DefinitionSources::DefinitionSources()
{
}


DefinitionSources::~DefinitionSources()
{
}

void DefinitionSources::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		std::wstring value;

		if (baseName.compare("sourceIdentifier") == 0)
		{
			sourceIdentifier = pChildNode->Gettext();
		}
		else if (baseName.compare("definitionSource") == 0)
		{
			DefinitionSource ds;
			ds.GetContents(pChildNode);
		}
	}
}
void DefinitionSources::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FC:S100_FC_sourceIdentifier"))
		{
			sourceIdentifier = pugi::as_wide(instruction.child_value());
		}
		else if (!strcmp(instructionName, "S100FC:S100_FC_definitionSource"))
		{
			DefinitionSource definition;
			definition.GetContents(instruction);
			definitionSource[definition.Getvalue()] = definition;
		}
		else
		{
			std::wstring content = pugi::as_wide(instruction.child_value());
			content.append(L"is another data");
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, content.c_str(),KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
	}

}