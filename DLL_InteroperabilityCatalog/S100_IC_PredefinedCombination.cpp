#include "stdafx.h"
#include "S100_IC_PredefinedCombination.h"


S100_IC_PredefinedCombination::S100_IC_PredefinedCombination()
{
}


S100_IC_PredefinedCombination::~S100_IC_PredefinedCombination()
{
}

void S100_IC_PredefinedCombination::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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
				name = std::wstring(variant.bstrVal).c_str();
		}
		else if (baseName.compare(L"description") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				description = std::wstring(variant.bstrVal).c_str();
		}
		else if (baseName.compare(L"useConditions") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				useConditions = std::wstring(variant.bstrVal).c_str();
		}
		else if (baseName.compare(L"interoperabilityLevel") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				interoperabilityLevel = _wtoi(std::wstring(variant.bstrVal).c_str());
		}
		else if (baseName.compare(L"includedProduct") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
			{
				S100_dataProduct t = StringToEnum_DataProduct(std::wstring(variant.bstrVal).c_str());
				includedProduct.push_back(t);
			}
		}
		else if (baseName.compare(L"suppressedFeatureLayers") == 0)
		{
			suppressedFeatureLayers.GetContents(pChildNode);
		}
		else if (baseName.compare(L"derivedFeatures") == 0)
		{
			derivedFeatures.GetContents(pChildNode);
		}
		else if (baseName.compare(L"colorModeOffsets") == 0)
		{
			colorModeOffsets.GetContents(pChildNode);
		}
		else
		{

		}
	}
}

void S100_IC_PredefinedCombination::GetContents(pugi::xml_node node)
{
	for (auto instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{

		auto instructionName = instruction.name();
		if (!strcmp(instructionName, "identifier"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			identifier = value;
		}
		else if (!strcmp(instructionName, "name"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			name = value;
		}
		else if (!strcmp(instructionName, "description"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			description = value;
		}
		else if (!strcmp(instructionName, "useConditions"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			useConditions = value;
		}
		else if (!strcmp(instructionName, "interoperabilityLevel"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			interoperabilityLevel = _wtoi(value.c_str());
		}
		else if (!strcmp(instructionName, "includedProduct"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			S100_dataProduct t = StringToEnum_DataProduct(value);
			includedProduct.push_back(t);
		}
		else if (!strcmp(instructionName, "suppressedFeatureLayers"))
		{
			suppressedFeatureLayers.GetContents(instruction);
		}
		else if (!strcmp(instructionName, "derivedFeatures"))
		{
			derivedFeatures.GetContents(instruction);
		}
		else if (!strcmp(instructionName, "colorModeOffsets"))
		{
			colorModeOffsets.GetContents(instruction);
		}
	}
}