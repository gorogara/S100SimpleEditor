#include "stdafx.h"
#include "SimpleAttribute.h"

#include "../LibMFCUtil/LibMFCUtil.h" 

SimpleAttribute::SimpleAttribute()
{
}


SimpleAttribute::~SimpleAttribute()
{
}


void SimpleAttribute::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	((Attribute*)this)->Attribute::GetContents(pNode);

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

			if (baseName.compare("valueType") == 0)
			{
				valueType.GetContents(pChildNode);
			}
			else if (baseName.compare("uom") == 0)
			{
				uom.GetContents(pChildNode);
			}
			else if (baseName.compare("quantitySpecification") == 0)
			{
				quantitySpecification.GetContents(pChildNode);
			}
			else if (baseName.compare("constraints") == 0)
			{
				constraints.GetContents(pChildNode);
			}
			else if (baseName.compare("listedValues") == 0)
			{
				ListedValues lvs;
				lvs.GetContents(pChildNode);
				listedValues.push_back(lvs);
			}
		}
	}
	OutputDebugString(L"");
}
void SimpleAttribute::GetContents(pugi::xml_node& node)
{
	((Attribute*)this)->Attribute::GetContents(node);
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();

		if (!strcmp(instructionName, "S100FC:valueType"))
		{
			valueType.GetContents(instruction);
		}
		else if (!strcmp(instructionName, "S100FC:uom"))
		{
			uom.GetContents(instruction);
		}
		else if (!strcmp(instructionName, "S100FC:quantitySpecification"))
		{
			quantitySpecification.GetContents(instruction);
		}
		else if (!strcmp(instructionName, "S100FC:constraints"))
		{
			constraints.GetContents(instruction);
		}
		else if (!strcmp(instructionName, "S100FC:listedValues"))
		{
			listedValues.push_back(ListedValues());
			listedValues.back().GetContents(instruction);
		}
	}
}