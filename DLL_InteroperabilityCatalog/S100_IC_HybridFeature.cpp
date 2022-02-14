#include "stdafx.h"
#include "S100_IC_HybridFeature.h"


S100_IC_HybridFeature::S100_IC_HybridFeature()
{
}


S100_IC_HybridFeature::~S100_IC_HybridFeature()
{
}

void S100_IC_HybridFeature::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	((S100_IC_FeatureDerivation*)this)->GetContents(pNode);

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr pChildNode = pNodeList->Getitem(i);
		if (pChildNode == NULL)
			continue;

		if (!pChildNode->baseName)
			continue;

		std::wstring baseName = std::wstring(pChildNode->baseName);

		if (baseName.compare(L"creationRule") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				creationRule = std::wstring(variant.bstrVal).c_str();
		}
		else
		{

		}
	}
}

void S100_IC_HybridFeature::GetContents(pugi::xml_node node) 
{
	for (auto instruction=node.first_child(); instruction; instruction.next_sibling())
	{
		auto instructionName = instruction.name();
		if (!strcmp(instructionName,"creationRule"))
		{
			std::wstring value =pugi::as_wide(instruction.child_value());
		}
	}
}
