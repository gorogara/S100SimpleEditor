#include "stdafx.h"
#include "ELE_features.h"


ELE_features::ELE_features()
{
}


ELE_features::~ELE_features()
{
}

void ELE_features::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare(L"S100_IC_Feature") == 0)
		{
			S100_IC_Feature f;
			f.GetContents(pChildNode);
			S100_IC_Features.push_back(f);
		}
		else
		{

		}   
	}
}

void ELE_features::GetContents(pugi::xml_node node) 
{
	USES_CONVERSION;

	for (auto instruction= node.first_child(); instruction; instruction=instruction.next_sibling()) 
	{
		auto instructionName = instruction.name();

		if (!strcmp(instructionName,"S100_IC_Feature")) 
		{
			S100_IC_Feature f;
			f.GetContents(instruction);
			S100_IC_Features.push_back(f);
		}
	}
}