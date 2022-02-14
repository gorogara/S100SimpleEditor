#include "stdafx.h"
#include "UnitOfMeasure.h"

#include "..\\DLL_MessageProcess\DLL_MessageProcess.h"

UnitOfMeasure::UnitOfMeasure()
{
}


UnitOfMeasure::~UnitOfMeasure()
{
}

void UnitOfMeasure::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare("name") == 0)
		{
			name = pChildNode->Gettext();
		}
		else if (baseName.compare("definition") == 0)
		{
			definition = pChildNode->Gettext();
		}
		else if (baseName.compare("symbol") == 0)
		{
			symbol = pChildNode->Gettext();
		}
	}
}
void UnitOfMeasure::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100Base:name"))
		{
			name = pugi::as_wide(instruction.child_value()); 
		}
		else if (!strcmp(instructionName, "S100Base:definition"))
		{
			definition = pugi::as_wide(instruction.child_value()); 
		}
		else if (!strcmp(instructionName, "S100Base:symbol"))
		{
			symbol = pugi::as_wide(instruction.child_value()); 
		}
	}
}

void UnitOfMeasure::SetName(std::wstring value)
{
	name = value;
}

std::wstring UnitOfMeasure::GetName() 
{
	return name;
}

void UnitOfMeasure::SetDefinition(std::wstring value)
{
	definition = value;
}

std::wstring UnitOfMeasure::GetDefinition()
{
	return definition;
}

void UnitOfMeasure::SetSymbol(std::wstring value) 
{
	symbol = value;
}

std::wstring UnitOfMeasure::GetSymbol() 
{
	return symbol;
}