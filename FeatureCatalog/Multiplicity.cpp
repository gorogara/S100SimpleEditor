#include "stdafx.h"
#include "Multiplicity.h"

#include "..\\LibMFCUtil\\LibMFCUtil.h" 
#include "..\\DLL_MessageProcess\DLL_MessageProcess.h"

#include <string>

Multiplicity::Multiplicity()
{
}

Multiplicity::~Multiplicity()
{
}

void Multiplicity::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare("lower") == 0)
		{
			lower = _wtoi(pChildNode->Gettext());
		}
		else if (baseName.compare("upper") == 0)
		{ 
			upper.GetContents(pChildNode);
		}
	}
}
void Multiplicity::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100Base:lower"))
		{
			lower = std::stoi(instruction.child_value()); 
		}
		else if (!strcmp(instructionName, "S100Base:upper"))
		{
			upper.GetContents(instruction); 
		}
	}
}
void Multiplicity::SetLower(int value)
{
	lower = value;
}

int Multiplicity::GetLower() 
{
	return lower;
}

void Multiplicity::SetUpper(UnlimitedInteger& value) 
{
	upper = value;
}

UnlimitedInteger& Multiplicity::GetUpper() 
{
	return upper;
}