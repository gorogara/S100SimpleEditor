#include "stdafx.h"
#include "DateExt.h"


DateExt::DateExt()
{
}


DateExt::~DateExt()
{
}
void DateExt::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare("date") == 0)
		{
			date = pChildNode->Gettext();
		}
		else if (baseName.compare("yearMonth") == 0)
		{
			date = pChildNode->Gettext();
		}
		else if (baseName.compare("year") == 0)
		{
			date = pChildNode->Gettext();
		}
	}
}
void DateExt::GetContents(pugi::xml_node& node)
{                
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100CI:date")) 
		{
			SetDate((char*)instruction.child_value()); 
		}
		else if (!strcmp(instructionName, "S100CI:yearMonth"))
		{
			SetDate((char*)instruction.child_value()); 
		}
		else if (!strcmp(instructionName, "S100CI:year"))
		{
			SetDate((char*)instruction.child_value()); 
		}
	}
}

void DateExt::SetDate(char* value) 
{
	date = pugi::as_wide(value);
}
std::wstring DateExt::GetDate() 
{
	return date;
}