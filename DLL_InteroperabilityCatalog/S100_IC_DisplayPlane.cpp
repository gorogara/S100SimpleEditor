#include "stdafx.h"
#include "S100_IC_DisplayPlane.h"


S100_IC_DisplayPlane::S100_IC_DisplayPlane()
{
}


S100_IC_DisplayPlane::~S100_IC_DisplayPlane()
{
}

void S100_IC_DisplayPlane::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare(L"identifier") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				identifier = std::wstring(variant.bstrVal).c_str();
		}
		else if (baseName.compare(L"name") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				name = std::wstring(variant.bstrVal).c_str();;
		}
		else if (baseName.compare(L"displayPriority") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				displayPriority = _wtoi(std::wstring(variant.bstrVal).c_str());
		}
		else if (baseName.compare(L"description") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				description = std::wstring(variant.bstrVal).c_str();;
		}
		else if (baseName.compare(L"S100_IC_SaturationOffset") == 0)
		{
			S100_IC_SaturationOffset.GetContents(pChildNode);
		}
		else if (baseName.compare(L"features") == 0)
		{
			features.GetContents(pChildNode);
		}
		else
		{

		}
	}
}

void S100_IC_DisplayPlane::GetContents(pugi::xml_node node)
{
	for (auto instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		auto instructionName = instruction.name();
		if (!strcmp(instructionName, "identifier"))
		{
			std::wstring value =pugi::as_wide(instruction.child_value());
			identifier = value;
		}
		else if (!strcmp(instructionName, "name"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			name = value;
		}
		else if (!strcmp(instructionName, "displayPriority"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			displayPriority = _wtoi(value.c_str());
		}
		else if (!strcmp(instructionName, "description"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			description = value;
		}
		else if (!strcmp(instructionName, "S100_IC_SaturationOffset"))
		{
			S100_IC_SaturationOffset.GetContents(instruction);
		}
		else if (!strcmp(instructionName, "features"))
		{
			features.GetContents(instruction);
		}
	}
}