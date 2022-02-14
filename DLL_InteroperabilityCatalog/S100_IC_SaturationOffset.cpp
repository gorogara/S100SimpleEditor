#include "stdafx.h"
#include "S100_IC_SaturationOffset.h"


S100_IC_SaturationOffset::S100_IC_SaturationOffset()
{
}


S100_IC_SaturationOffset::~S100_IC_SaturationOffset()
{
}

void S100_IC_SaturationOffset::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare(L"product") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				product = StringToEnum_DataProduct(std::wstring(variant.bstrVal).c_str());
		}
		else	if (baseName.compare(L"offsetDusk") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				offsetDusk = (float)_wtof(std::wstring(variant.bstrVal).c_str());
		}
		else	if (baseName.compare(L"offsetNight") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				offsetNight = (float)_wtof(std::wstring(variant.bstrVal).c_str());
		}
	}
}

void S100_IC_SaturationOffset::GetContents(pugi::xml_node node)
{
	USES_CONVERSION;

	for (auto instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		auto instructionName = instruction.name();
		if (!strcmp(instructionName, "product"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			product = StringToEnum_DataProduct(value);
		}
		else if (!strcmp(instructionName, "product"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			offsetDusk = (float)_wtof(value.c_str());
		}
		else if (!strcmp(instructionName, "offsetNight"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			offsetNight = (float)_wtof(value.c_str());
		}
	}


}