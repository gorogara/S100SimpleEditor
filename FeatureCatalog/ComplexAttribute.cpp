#include "stdafx.h"
#include "ComplexAttribute.h"


ComplexAttribute::ComplexAttribute()
{
}


ComplexAttribute::~ComplexAttribute()
{
}

void ComplexAttribute::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	((Item*)this)->Item::GetContents(pNode);

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr pChildNode = pNodeList->Getitem(i);
		if (pChildNode == NULL)
			continue;

		if (!pChildNode->baseName)
			continue;

		std::string baseName = std::string(W2A(pChildNode->baseName));

		if (baseName.compare("subAttributeBinding") == 0)
		{
			AttributeBinding ab;
			ab.GetContents(pChildNode);
			subAttributeBinding.push_back(ab);
		}
	}
}
void ComplexAttribute::GetContents(pugi::xml_node& node)
{
	((Item*)this)->Item::GetContents(node);
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FC:subAttributeBinding"))
		{
			subAttributeBinding.push_back(AttributeBinding());
			subAttributeBinding.back().GetContents(instruction);
		}
	}
}