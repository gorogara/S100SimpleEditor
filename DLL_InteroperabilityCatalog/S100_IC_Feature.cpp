#include "stdafx.h"
#include "S100_IC_Feature.h"


S100_IC_Feature::S100_IC_Feature()
{
	geometry = NO_GEOMETRY;
}


S100_IC_Feature::~S100_IC_Feature()
{
}

void S100_IC_Feature::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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
		else if (baseName.compare(L"geometry") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				geometry = StringToEnum_Geometry(std::wstring(variant.bstrVal).c_str());
		}
		else if (baseName.compare(L"drawOrder") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				drawOrder = _wtoi(std::wstring(variant.bstrVal).c_str());
		}
		else if (baseName.compare(L"viewingGroup") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				viewingGroup = _wtoi(std::wstring(variant.bstrVal).c_str());
		}
		else if (baseName.compare(L"attributeCombination") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				attributeCombination.push_back(std::wstring(variant.bstrVal).c_str());
		}
		else if (baseName.compare(L"significant") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
			{
				std::wstring t = std::wstring(variant.bstrVal).c_str();
				significant = t.compare(L"true") == 0 ? true : false;
			}
		}
		else
		{

		}
	}
}

void S100_IC_Feature::GetContents(pugi::xml_node node)
{
	for (auto instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		auto instructionName = instruction.name();
		if (!strcmp(instructionName,"featureCode"))
		{
			std::wstring value =pugi::as_wide(instruction.child_value());
			featureCode = value;
		}
		else if (!strcmp(instructionName, "product"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			product = StringToEnum_DataProduct( value);
		}
		else if (!strcmp(instructionName, "geometry"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			geometry = StringToEnum_Geometry(value);
		}
		else if (!strcmp(instructionName, "drawOrder"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			drawOrder = _wtoi(value.c_str());
		}
		else if (!strcmp(instructionName, "viewingGroup"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			viewingGroup = _wtoi(value.c_str());
		}
		else if (!strcmp(instructionName, "attributeCombination"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			attributeCombination.push_back(value);
		}
		else if (!strcmp(instructionName, "significant"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			significant = value.compare(L"true") == 0 ? true : false;
		}
	}
}