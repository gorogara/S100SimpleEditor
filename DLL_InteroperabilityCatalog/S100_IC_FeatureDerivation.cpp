#include "stdafx.h"
#include "S100_IC_FeatureDerivation.h"


S100_IC_FeatureDerivation::S100_IC_FeatureDerivation()
{
}


S100_IC_FeatureDerivation::~S100_IC_FeatureDerivation()
{
}

void S100_IC_FeatureDerivation::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare(L"primaryProduct") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				primaryProduct = StringToEnum_DataProduct(std::wstring(variant.bstrVal).c_str());
		}
		else if (baseName.compare(L"primaryFeatureCode") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				primaryFeatureCode = std::wstring(variant.bstrVal).c_str();
		}
		else if (baseName.compare(L"primarySelector") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				primarySelector = std::wstring(variant.bstrVal).c_str();
		}
		else if (baseName.compare(L"secondaryProduct") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				secondaryProduct = StringToEnum_DataProduct(std::wstring(variant.bstrVal).c_str());
		}
		else if (baseName.compare(L"secondaryFeatureCode") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				secondaryFeatureCode = std::wstring(variant.bstrVal).c_str();
		}
		else if (baseName.compare(L"secondarySelector") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				secondarySelector = std::wstring(variant.bstrVal).c_str();
		}
		else if (baseName.compare(L"outputProduct") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				outputProduct = StringToEnum_DataProduct(std::wstring(variant.bstrVal).c_str());
		}
		else if (baseName.compare(L"outputFeatureCode") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				outputFeatureCode = std::wstring(variant.bstrVal).c_str();
		}
		else if (baseName.compare(L"featureRef") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				featureRef = std::wstring(variant.bstrVal).c_str();
		}
		else
		{

		}
	}
}

void S100_IC_FeatureDerivation::GetContents(pugi::xml_node node)
{
	for (auto instruction=node.first_child(); instruction; instruction=instruction.next_sibling()) 
	{
		auto instructionName = instruction.name();
		if (!strcmp(instructionName,"primaryProduct"))
		{
			std::wstring value =pugi::as_wide(instruction.name());
			primaryProduct = StringToEnum_DataProduct(value.c_str());
		}
		else if (!strcmp(instructionName, "primaryFeatureCode"))
		{
			std::wstring value = pugi::as_wide(instruction.name());
			primaryFeatureCode = value;
		}
		else if (!strcmp(instructionName, "primarySelector"))
		{
			std::wstring value = pugi::as_wide(instruction.name());
			primarySelector = value;
		}
		else if (!strcmp(instructionName, "secondaryProduct"))
		{
			std::wstring value = pugi::as_wide(instruction.name());
			secondaryProduct = StringToEnum_DataProduct(value);

		}
		else if (!strcmp(instructionName, "secondaryFeatureCode"))
		{
			std::wstring value = pugi::as_wide(instruction.name());
			secondaryFeatureCode = value;
		}
		else if (!strcmp(instructionName, "secondarySelector"))
		{
			std::wstring value = pugi::as_wide(instruction.name());
			secondarySelector = value;
		}
		else if (!strcmp(instructionName, "outputProduct"))
		{
			std::wstring value = pugi::as_wide(instruction.name());
			outputProduct = StringToEnum_DataProduct(value);
		}
		else if (!strcmp(instructionName, "outputFeatureCode"))
		{
			std::wstring value = pugi::as_wide(instruction.name());
			outputFeatureCode = value;
		}
		else if (!strcmp(instructionName, "featureRef"))
		{
			std::wstring value = pugi::as_wide(instruction.name());
			featureRef = value;
		}
	}
}