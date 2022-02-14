#include "stdafx.h"
#include "AttributeConstraints.h"

AttributeConstraints::AttributeConstraints()
{
}


AttributeConstraints::~AttributeConstraints()
{
}

void AttributeConstraints::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare("stringLength") == 0)
		{
			stringLength = _wtoi(pChildNode->Gettext());
		}
		else if (baseName.compare("textPattern") == 0)
		{
			textPattern = pChildNode->Gettext();
		}
		else if (baseName.compare("range") == 0)
		{
			range.GetContents(pChildNode);
		}
		else if (baseName.compare("precision") == 0)
		{
			precision = _wtoi(pChildNode->Gettext());
		}
	}
}
void AttributeConstraints::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FD:stringLength"))
		{
			stringLength = std::stoi(instruction.child_value());
		}
		else if (!strcmp(instructionName, "S100FD:textPattern"))
		{
			textPattern = pugi::as_wide(instruction.child_value());
		}
		else if (!strcmp(instructionName, "S100FD:range"))
		{
			range.GetContents(instruction);
		}
		else if (!strcmp(instructionName, "S100FD:precision"))
		{
			precision = std::stoi(instruction.child_value());
		}
	}
}