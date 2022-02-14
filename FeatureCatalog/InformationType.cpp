#include "stdafx.h"
#include "InformationType.h"


InformationType::InformationType()
{
}


InformationType::~InformationType()
{
}

void InformationType::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	this->S100ObjectType::GetContents(pNode);

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	int roleCnt = 0;

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr pChildNode = pNodeList->Getitem(i);
		if (pChildNode == NULL)
			continue;

		if (!pChildNode->baseName)
			continue;

		std::string baseName = std::string(W2A(pChildNode->baseName));

		if (baseName.compare("superType") == 0)
		{
			superType = pChildNode->Gettext();
		}
		else if (baseName.compare("subType") == 0)
		{
			subType.push_back(std::wstring(pChildNode->Gettext()));
		}
	}

}
void InformationType::GetContents(pugi::xml_node& node)
{
	this->S100ObjectType::GetContents(node);
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FC:superType"))
		{
			superType = pugi::as_wide(instruction.child_value());
		}
		else if (!strcmp(instructionName, "S100FC:subType"))
		{
			subType.push_back(pugi::as_wide(instruction.child_value()));
		}
	}
}