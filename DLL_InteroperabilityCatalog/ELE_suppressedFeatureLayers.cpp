#include "stdafx.h"
#include "ELE_suppressedFeatureLayers.h"


ELE_suppressedFeatureLayers::ELE_suppressedFeatureLayers()
{
}


ELE_suppressedFeatureLayers::~ELE_suppressedFeatureLayers()
{
}

void ELE_suppressedFeatureLayers::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare(L"S100_IC_SuppressedFeatureLayer") == 0)
		{
			S100_IC_SuppressedFeatureLayer sf;
			sf.GetContents(pChildNode);
			S100_IC_SuppressedFeatureLayers.push_back(sf);
		}
		else
		{

		}   
	}
}

void ELE_suppressedFeatureLayers::GetContents(pugi::xml_node node)
{
	for (auto instruction=node.first_child(); instruction; instruction=instruction.next_sibling())
	{
		auto instructionName = instruction.name();
		if (!strcmp(instructionName,"S100_IC_SuppressedFeatureLayer"))
		{
			S100_IC_SuppressedFeatureLayer sf;
			sf.GetContents(instruction);
			S100_IC_SuppressedFeatureLayers.push_back(sf);
		}
	}

}