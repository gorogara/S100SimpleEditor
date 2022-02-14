#include "StdAfx.h"
#include "SimpleAttributes.h"


SimpleAttributes::SimpleAttributes(void)
{ 

}

SimpleAttributes::~SimpleAttributes(void)
{

}


void SimpleAttributes::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr pChildNode = pNodeList->Getitem(i);
		if (pChildNode == NULL)
			continue;

		bstr_t bstr = pChildNode->baseName;
		if (!!bstr)
		{
			std::string baseName = std::string(bstr);

			if (baseName.compare("S100_FC_SimpleAttribute") == 0)
			{
				SimpleAttribute attr;
				attr.GetContents(pChildNode);
				simpleAttribute.insert(
					std::unordered_map<std::wstring, SimpleAttribute>::value_type(attr.code.GetValueString(), attr)
				);
			}
		}
	}
}
void SimpleAttributes::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FC:S100_FC_SimpleAttribute"))
		{
			SimpleAttribute sa;
			sa.GetContents(instruction);
			simpleAttribute[sa.code.GetValueString()] = sa;
		}
	}        
}