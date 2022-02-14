#include "stdafx.h"
#include "Date.h"

#include "..\\DLL_MessageProcess\DLL_MessageProcess.h"
Date::Date()
{
}


Date::~Date()
{
}



void Date::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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
			date.GetContents(pChildNode);
		}
		else if (baseName.compare("dateType") == 0)
		{
			dateType.GetContents(pChildNode);
		}
	}
}
void Date::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100CI:date"))
		{
			DateExt* dateData = new DateExt();
			dateData->GetContents(instruction);
			SetDate(*dateData); 
		}
		else if (!strcmp(instructionName, "S100CI:dateType"))
		{
			DateTypeCode* DatetypeCode = new DateTypeCode();
			DatetypeCode->GetContents(instruction);
			SetDateType(*DatetypeCode); 
		}
		else 
		{
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC another data value",KRS_MSG_PROCESS::User_Developer_Mode,KRS_MSG_PROCESS::FC);
		}
	}
}

void Date::SetDate(DateExt& value) 
{
	date = value;
}

DateExt& Date::GetDate() 
{
	return date;
}

void Date::SetDateType(DateTypeCode& value) 
{
	dateType = value;
}

DateTypeCode& Date::GetDateType() 
{
	return dateType;
}