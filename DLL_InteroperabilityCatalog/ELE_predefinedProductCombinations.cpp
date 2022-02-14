#include "stdafx.h"
#include "ELE_predefinedProductCombinations.h"


ELE_predefinedProductCombinations::ELE_predefinedProductCombinations()
{
}


ELE_predefinedProductCombinations::~ELE_predefinedProductCombinations()
{
}

void ELE_predefinedProductCombinations::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		std::wstring baseName = std::wstring(pChildNode->baseName);

		if (baseName.compare(L"S100_IC_PredefinedCombination") == 0)
		{
			S100_IC_PredefinedCombination pc;
			pc.GetContents(pChildNode);
			S100_IC_PredefinedCombinations.push_back(pc);
		}
		else
		{

		}   
	}
}

void ELE_predefinedProductCombinations::GetContents(pugi::xml_node node)
{
	for (auto instruction= node.first_child(); instruction; instruction=instruction.next_sibling())
	{
		auto instructionName = instruction.name();
		if (!strcmp(instructionName,"S100_IC_PredefinedCombination")) 
		{
			S100_IC_PredefinedCombination pc;
			pc.GetContents(instruction);
			S100_IC_PredefinedCombinations.push_back(pc);
		}
	}
}