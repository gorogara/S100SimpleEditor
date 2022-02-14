#include "stdafx.h"
#include "NamedType.h"


NamedType::NamedType()
{
}


NamedType::~NamedType()
{
}


void NamedType::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	this->Item::GetContents(pNode);

	MSXML2::IXMLDOMNamedNodeMapPtr pAttr = pNode->Getattributes();
	MSXML2::IXMLDOMNodePtr pAttrNP;
	pAttrNP = pAttr->getNamedItem(L"isAbstract");
	VARIANT value;
	if (pAttrNP)
	{
		pAttrNP->get_nodeValue(&value);

		XML_Attribute attr;
		attr.Setname("isAbstract");
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

		if (baseName.compare("attributeBinding") == 0)
		{
			AttributeBinding ab;
			ab.GetContents(pChildNode);
			attributeBinding.push_back(ab);
		}
	}
}

void NamedType::GetContents(pugi::xml_node& node)
{
	this->Item::GetContents(node);

	if (node.attribute("isAbstract"))
	{
		XML_Attribute attr;
		attr.Setname("isAbstract");
		attr.Setvalue((char*)node.attribute("isAbstract").value());

		SetAttributes(attr);
	}

	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FC:attributeBinding"))
		{
			attributeBinding.push_back(AttributeBinding());
			attributeBinding.back().GetContents(instruction);
		}
	}
}