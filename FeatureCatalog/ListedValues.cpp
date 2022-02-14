#include "stdafx.h"
#include "ListedValues.h"


ListedValues::ListedValues()
{
}


ListedValues::~ListedValues()
{
}


void ListedValues::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr pChildNode = pNodeList->Getitem(i);
		if (pChildNode == NULL)
			continue;
		bstr_t bstr = pChildNode->baseName;
		if (!!bstr)
		{
			std::string baseName = std::string(W2A(bstr));

			if (baseName.compare("listedValue") == 0)
			{
				ListedValue lv;
				lv.GetContents(pChildNode); 
				listedValue.insert(
					std::unordered_map<int, ListedValue>::value_type(lv.code.GetvalueInteger(), lv)
					);
			}
		}
	}
}

void ListedValues::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FC:listedValue"))
		{
			ListedValue sa;
			sa.GetContents(instruction); 
			listedValue.insert({ sa.code.GetvalueInteger() ,sa });
			int i = 0;
		}
	}

}