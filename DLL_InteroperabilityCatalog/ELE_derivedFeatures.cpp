#include "stdafx.h"
#include "ELE_derivedFeatures.h"


ELE_derivedFeatures::ELE_derivedFeatures()
{
}


ELE_derivedFeatures::~ELE_derivedFeatures()
{
}

void ELE_derivedFeatures::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare(L"S100_IC_SuppressedFeatureInstance") == 0)
		{
			S100_IC_SuppressedFeatureInstance sfi;
			sfi.GetContents(pChildNode);
			S100_IC_SuppressedFeatureInstances.push_back(sfi);
		}
		else if (baseName.compare(L"S100_IC_HybridFeatures") == 0)
		{
			S100_IC_HybridFeature hf;
			hf.GetContents(pChildNode);
			S100_IC_HybridFeatures.push_back(hf);
		}
		else
		{

		}   
	}
}

void ELE_derivedFeatures::GetContents(pugi::xml_node node)
{
	USES_CONVERSION;

	for (auto instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		auto instructionName = instruction.name();
		if (!strcmp(instructionName,"S100_IC_SuppressedFeatureInstance"))
		{
			S100_IC_SuppressedFeatureInstance sfi;
			sfi.GetContents(instruction);
			S100_IC_SuppressedFeatureInstances.push_back(sfi);
		}
		else if (!strcmp(instructionName, "S100_IC_HybridFeatures"))
		{
			S100_IC_HybridFeature hf;
			hf.GetContents(instruction);
			S100_IC_HybridFeatures.push_back(hf);
		}

	}

}