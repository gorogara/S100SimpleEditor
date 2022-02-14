#include "stdafx.h"
#include "InformationBinding.h"


InformationBinding::InformationBinding()
{
}


InformationBinding::~InformationBinding()
{
}

void InformationBinding::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	MSXML2::IXMLDOMNamedNodeMapPtr pAttr = pNode->Getattributes();
	MSXML2::IXMLDOMNodePtr pAttrNP;
	pAttrNP = pAttr->getNamedItem(L"roleType");
	VARIANT value;
	if (pAttrNP)
	{
		pAttrNP->get_nodeValue(&value);

		XML_Attribute attr;
		attr.Setname("roleType");
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

		if (baseName.compare("multiplicity") == 0)
		{
			multiplicity.GetContents(pChildNode);
		}
		else if (baseName.compare("association") == 0)
		{
			association.GetContents(pChildNode);
		}
		else if (baseName.compare("role") == 0)
		{
			role.GetContents(pChildNode);
		}
		else if (baseName.compare("informationType") == 0)
		{
			informationType.GetContents(pChildNode);
		}
	}
}
void InformationBinding::GetContents(pugi::xml_node& node)
{
	auto attribute = node.attribute("roleType");
	if (attribute)
	{
		XML_Attribute value;
		value.Setname("roleType");
		value.Setvalue((char*)attribute.value());

		SetAttributes(value); 
	}
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FC:multiplicity"))
		{
			multiplicity.GetContents(instruction);
		}
		else if (!strcmp(instructionName, "S100FC:association"))
		{
			association.GetContents(instruction);
		}
		else if (!strcmp(instructionName, "S100FC:role"))
		{
			role.GetContents(instruction);
		}
		else if (!strcmp(instructionName, "S100FC:informationType"))
		{
			informationType.GetContents(instruction);
		}
	}                    
}