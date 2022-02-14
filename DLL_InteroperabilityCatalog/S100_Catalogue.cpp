#include "stdafx.h"
#include "S100_Catalogue.h"


S100_Catalogue::S100_Catalogue()
{
}


S100_Catalogue::~S100_Catalogue()
{
}
void S100_Catalogue::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare(L"name") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				name = std::wstring(variant.bstrVal).c_str();;
		}
		else if (baseName.compare(L"scope") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				scope = std::wstring(variant.bstrVal).c_str();;
		}
		else if (baseName.compare(L"fieldOfApplication") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				fieldOfApplication = std::wstring(variant.bstrVal).c_str();;
		}

		else if (baseName.compare(L"versionNumber") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				versionNumber = std::wstring(variant.bstrVal).c_str();;
		}
		else if (baseName.compare(L"versionDate") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				versionDate = std::wstring(variant.bstrVal).c_str();;
		}
		else if (baseName.compare(L"language") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				language = std::wstring(variant.bstrVal).c_str();;
		}
		else if (baseName.compare(L"locale") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				locale = std::wstring(variant.bstrVal).c_str();;
		}
		else if (baseName.compare(L"characterSet ") == 0)
		{
			variant_t variant = pChildNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				characterSet = std::wstring(variant.bstrVal).c_str();;
		}
		else
		{

		}
	}
}

void S100_Catalogue::GetContents(pugi::xml_node node) 
{
	USES_CONVERSION;

	for (auto instruction= node.first_child(); instruction; instruction=instruction.next_sibling()) 
	{
		auto instructionName = instruction.name();

		if (!strcmp(instructionName,"name")) 
		{
			std::wstring value =pugi::as_wide(instruction.child_value());
			name = value;
		}
		else if (!strcmp(instructionName, "scope"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			scope = value;
		}
		else if (!strcmp(instructionName, "fieldOfApplication"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			fieldOfApplication = value;
		}
		else if (!strcmp(instructionName, "versionNumber"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			versionNumber = value;
		}
		else if (!strcmp(instructionName, "versionDate"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			versionDate = value;
		}
		else if (!strcmp(instructionName, "language"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			language = value;
		}
		else if (!strcmp(instructionName, "locale"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			locale = value;
		}
		else if (!strcmp(instructionName, "characterSet"))
		{
			std::wstring value = pugi::as_wide(instruction.child_value());
			characterSet = value;
		}
	}
}