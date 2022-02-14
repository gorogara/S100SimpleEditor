#include "stdafx.h"
#include "ValueList.h" 

ValueList::ValueList()
{
}


ValueList::~ValueList()
{
}

void ValueList::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare("value") == 0)
		{
			value.push_back(_wtoi(pChildNode->Gettext()));
		}
	}
}
void ValueList::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FC:value"))
		{
			int Value = std::stoi(instruction.child_value());
			value.push_back(Value);
		}
	}
}