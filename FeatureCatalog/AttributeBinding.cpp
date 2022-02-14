#include "stdafx.h"
#include "AttributeBinding.h"

AttributeBinding::AttributeBinding()
{
}

AttributeBinding::~AttributeBinding()
{
}

void AttributeBinding::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;
	MSXML2::IXMLDOMNamedNodeMapPtr pAttr = pNode->Getattributes();
	MSXML2::IXMLDOMNodePtr pAttrNP;
	pAttrNP = pAttr->getNamedItem(L"sequential");
	VARIANT value;
	if (pAttrNP)
	{
		pAttrNP->get_nodeValue(&value);
		
		XML_Attribute attr;
		attr.Setname("sequential");
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
		else if (baseName.compare("permittedValues") == 0)
		{
			permittedValues.GetContents(pChildNode);
		}
		else if (baseName.compare("attribute") == 0)
		{
			attribute.GetContents(pChildNode);
		}
	}
}
void AttributeBinding::GetContents(pugi::xml_node& node)
{
	if (node.attribute("sequential")) 
	{
		XML_Attribute value;
		value.Setname("sequential");
		value.Setvalue((char*)node.attribute("sequential").value());
		SetAttributes(value);
	}

	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();

		if (!strcmp(instructionName, "S100FC:multiplicity"))
		{
			multiplicity.GetContents(instruction);
		}
		else if (!strcmp(instructionName, "S100FC:permittedValues"))
		{
			permittedValues.GetContents(instruction);
		}
		else if (!strcmp(instructionName, "S100FC:attribute"))
		{
			attribute.GetContents(instruction);
		}
	}
}