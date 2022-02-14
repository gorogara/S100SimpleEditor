#include "stdafx.h"
#include "S100_IC_SuppressedFeatureLayer.h"


S100_IC_SuppressedFeatureLayer::S100_IC_SuppressedFeatureLayer()
{
}


S100_IC_SuppressedFeatureLayer::~S100_IC_SuppressedFeatureLayer()
{
}

void S100_IC_SuppressedFeatureLayer::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	MSXML2::IXMLDOMNamedNodeMapPtr pAttr = pNode->Getattributes();
	MSXML2::IXMLDOMNodePtr pAttrNP;
	VARIANT value;

	pAttrNP = pAttr->getNamedItem(L"id");
	if (pAttrNP)
	{
		pAttrNP->get_nodeValue(&value);
		id = std::wstring(value.bstrVal).c_str();
	}

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr pChildNode = pNodeList->Getitem(i);
		if (pChildNode == NULL)
			continue;

		if (!pChildNode->baseName)
			continue;

		std::wstring baseName = std::wstring(pChildNode->baseName);

		if (baseName.compare(L"featureCode") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				featureCode = std::wstring(variant.bstrVal).c_str();
		}
		else if (baseName.compare(L"product") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				product = StringToEnum_DataProduct(std::wstring(variant.bstrVal).c_str());
		}
		else if (baseName.compare(L"featureRef") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
			{
				std::wstring ref = std::wstring(variant.bstrVal).c_str();
				featureRef.push_back(ref);
			}
		}
		else
		{

		}
	}
}

void S100_IC_SuppressedFeatureLayer::GetContents(pugi::xml_node node)
{
	for (auto attri = node.first_attribute(); attri; attri = attri.next_attribute())
	{
		auto attriName = attri.name();
		if (!strcmp(attriName, "id"))
		{
			std::wstring value = pugi::as_wide(attri.value());
			id = value;
		}
	}


	for (auto instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		auto instructionName = instruction.name();
		if (!strcmp(instructionName, "featureCode"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			featureCode = value;
		}
		else if (!strcmp(instructionName, "product"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			product = StringToEnum_DataProduct(value);
		}
		else if (!strcmp(instructionName, "featureRef"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			featureRef.push_back(value);
		}
	}
}