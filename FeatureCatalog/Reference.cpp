#include "stdafx.h"
#include "Reference.h"


Reference::Reference()
{
}


Reference::~Reference()
{
}

void Reference::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	MSXML2::IXMLDOMNamedNodeMapPtr pAttr = pNode->Getattributes();
	MSXML2::IXMLDOMNodePtr pAttrNP;
	pAttrNP = pAttr->getNamedItem(L"ref");
	VARIANT value;
	if (pAttrNP)
	{
		pAttrNP->get_nodeValue(&value);

		XML_Attribute attr;
		attr.Setname("ref");
		attr.Setvalue((char*)value.bstrVal);
		SetAttributes(attr); 
	}              
}
void Reference::GetContents(pugi::xml_node& node)
{
	for (auto attri =node.first_attribute(); attri; attri =attri.next_attribute())
	{
		auto attriName = attri.name();
		if (!strcmp(attriName,"ref"))
		{
			XML_Attribute attr;
			attr.Setname("ref");
			attr.Setvalue((char*)node.attribute("ref").value());
			SetAttributes(attr);   
		}
	}
}