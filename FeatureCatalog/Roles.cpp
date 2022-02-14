#include "StdAfx.h"
#include "Roles.h"

#include "../LibMFCUtil/LibMFCUtil.h"
Roles::Roles(void)
{ 
}


Roles::~Roles(void)
{

}



void Roles::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare("S100_FC_Role") == 0)
		{
			Role r;
			r.GetContents(pChildNode);
			role.insert(std::make_pair(r.code.GetValueString(), r));
		}
	}
}
void Roles::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FC:S100_FC_Role"))
		{
			Role r;
			r.GetContents(instruction);
			role.insert(std::make_pair(r.code.GetValueString(), r));
		}
	}
}
