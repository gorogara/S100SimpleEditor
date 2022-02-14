#include "stdafx.h"
#include "DefinitionSource.h"

#include "..\\DLL_MessageProcess\DLL_MessageProcess.h"

DefinitionSource::DefinitionSource()
{
}


DefinitionSource::~DefinitionSource()
{
}


void DefinitionSource::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{

	USES_CONVERSION;

	MSXML2::IXMLDOMNamedNodeMapPtr pAttr = pNode->Getattributes();
	MSXML2::IXMLDOMNodePtr pAttrNP;
	pAttrNP = pAttr->getNamedItem(L"id");
	VARIANT value;
	if (pAttrNP)
	{
		pAttrNP->get_nodeValue(&value);

		XML_Attribute attr;
		attr.Setname("id");
		attr.Setvalue((char*)value.bstrVal);
		SetAttributes(attr); 
	}

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr pChildNode = pNodeList->Getitem(i);
		if (pChildNode == NULL)
			continue;
		if (!pChildNode->baseName)
			continue;

		std::string baseName = std::string(W2A(pChildNode->baseName));

		if (baseName.compare("source") == 0)
		{
			source.GetContents(pChildNode);
		}
	}
}
void DefinitionSource::GetContents(pugi::xml_node& node)
{
	auto attribute = node.attribute("id");
	if (attribute) 
	{
		XML_Attribute value;
		value.Setname("id");
		value.Setvalue((char*)attribute.value());

		SetAttributes(value); 
	}
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FC:source"))
		{
		   source.GetContents(instruction);
		}
		else 
		{
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC another data value",KRS_MSG_PROCESS::User_Developer_Mode,KRS_MSG_PROCESS::FC);
		}
	}

}