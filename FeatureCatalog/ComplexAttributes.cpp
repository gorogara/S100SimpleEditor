#include "StdAfx.h"
#include "ComplexAttributes.h"

ComplexAttributes::ComplexAttributes(void)
{ 
}


ComplexAttributes::~ComplexAttributes(void)
{
}

void ComplexAttributes::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare("S100_FC_ComplexAttribute") == 0)
		{
			ComplexAttribute attr;
			attr.GetContents(pChildNode);
			std::wstring key = attr.code.GetValueString();

			complexAttribute.insert({ key ,attr }); 
		}
	}
}

void ComplexAttributes::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FC:S100_FC_ComplexAttribute"))
		{
			ComplexAttribute complex;
			complex.GetContents(instruction);
			complexAttribute[complex.code.GetValueString()] = complex;
		}
	}
}