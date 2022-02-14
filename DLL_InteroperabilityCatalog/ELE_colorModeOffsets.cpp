#include "stdafx.h"
#include "ELE_colorModeOffsets.h"


ELE_colorModeOffsets::ELE_colorModeOffsets()
{
}


ELE_colorModeOffsets::~ELE_colorModeOffsets()
{
}
void ELE_colorModeOffsets::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare(L"S100_IC_SaturationOffset") == 0)
		{
			S100_IC_SaturationOffset so;
			so.GetContents(pChildNode);
			S100_IC_SaturationOffsets.push_back(so);
		}
		else
		{

		}   
	}
}

void ELE_colorModeOffsets::GetContents(pugi::xml_node node)
{
	USES_CONVERSION;
	for (auto instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		auto instructionName = instruction.name();
		if (!strcmp(instructionName,"S100_IC_SaturationOffset"))
		{
			S100_IC_SaturationOffset so;
			so.GetContents(instruction);
			S100_IC_SaturationOffsets.push_back(so);
		}
	}
}
