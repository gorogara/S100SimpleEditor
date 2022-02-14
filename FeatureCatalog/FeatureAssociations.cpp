#include "StdAfx.h"
#include "FeatureAssociations.h"

FeatureAssociations::FeatureAssociations(void)
{ 
}


FeatureAssociations::~FeatureAssociations(void)
{
}

void FeatureAssociations::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		std::string baseName = std::string(W2A(pChildNode->baseName));

		if (baseName.compare("S100_FC_FeatureAssociation") == 0)
		{
			FeatureAssociation fa;
			fa.GetContents(pChildNode);
			featureAssociation.insert(
				std::unordered_map<std::wstring, FeatureAssociation>::value_type(fa.code.GetValueString(), fa)
			);
		}
	}
}
void FeatureAssociations::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FC:S100_FC_FeatureAssociation"))
		{
			FeatureAssociation sa;
			sa.GetContents(instruction);
			featureAssociation[sa.code.GetValueString()] = sa;

			if (instruction.attribute("isAbstract"))
			{
				XML_Attribute value;
				value.Setname("isAbstract");
				value.Setvalue((char*)instruction.attribute("isAbstract").value());
			}
		}
	}
}