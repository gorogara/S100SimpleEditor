#include "stdafx.h"
#include "NumericRange.h"

#include "..\\DLL_MessageProcess\DLL_MessageProcess.h"

NumericRange::NumericRange()
{
}


NumericRange::~NumericRange()
{
}

void NumericRange::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare("sourceIdentifier") == 0)
		{
			lowerBound = _wtof(pChildNode->Gettext());
		}
		else if (baseName.compare("routeName") == 0)
		{
			upperBound = _wtof(pChildNode->Gettext());
		}
		else if (baseName.compare("routeName") == 0)
		{
			intervalType.GetContents(pChildNode);
		}
	}
}
void NumericRange::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();

		if (!strcmp(instructionName, "S100Base:lowerBound"))
		{
			lowerBound = std::stod(instruction.child_value()); 
		}

		else if (!strcmp(instructionName, "S100Base:upperBound"))
		{
			upperBound = std::stod(instruction.child_value()); 
		}

		else if (!strcmp(instructionName, "S100Base:intervalType"))
		{
			intervalType.GetContents(instruction); 
		}
	}
}

void NumericRange::SetLowerBound(double value)
{
	lowerBound = value;
}

double NumericRange::GetLowerBound() 
{
	return lowerBound;
}

void NumericRange::SetUpperBound(double value)
{
	upperBound = value;
}

double NumericRange::GetUpperBound() 
{
	return upperBound;
}

void NumericRange::SetIntervalType(IntervalType value)
{
	intervalType = value;
}

IntervalType NumericRange::GetIntervalType() 
{
	return intervalType;
}