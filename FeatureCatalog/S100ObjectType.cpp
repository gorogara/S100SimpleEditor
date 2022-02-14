#include "stdafx.h"
#include "S100ObjectType.h"

#include "..\\DLL_MessageProcess\DLL_MessageProcess.h"
S100ObjectType::S100ObjectType()
{
}


S100ObjectType::~S100ObjectType()
{
}


void S100ObjectType::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	this->NamedType::GetContents(pNode);

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr pChildNode = pNodeList->Getitem(i);
		if (pChildNode == NULL)
			continue;

		if (!pChildNode->baseName)
			continue;

		std::string baseName = std::string(W2A(pChildNode->baseName));


		if (baseName.compare("informationBinding") == 0)
		{
			InformationBinding ib;
			ib.GetContents(pChildNode);

			std::wstring associatename = ib.informationType.Getvalue();
			if (associatename.compare(L"") == 0)
			{
				for (auto itor = ib.informationType.Getattributes().begin();
					itor != ib.informationType.Getattributes().end();
					itor++)
				{
					XML_Attribute* attr = &(*itor);
					if (attr->Getname().compare(L"ref") == 0)
					{
						associatename = attr->Getvalue();
					}
				}
			}
			informationBinding.insert(
				std::unordered_map<std::wstring, InformationBinding>::value_type(
					associatename,
					ib));
		}
	}
}
void S100ObjectType::GetContents(pugi::xml_node& node)
{
	this->NamedType::GetContents(node);

	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FC:informationBinding"))
		{
			InformationBinding ib;
			ib.GetContents(instruction);

			std::wstring associatename = ib.informationType.Getvalue();
			if (associatename.compare(L"") == 0)
			{
				std::list<XML_Attribute> *attributeList = ib.informationType.GetattributesPointer();

				for (auto itor = attributeList->begin();
					itor != attributeList->end();
					itor++)
				{
					XML_Attribute* attr = &(*itor);
					if (attr->Getname().compare(L"ref") == 0)
					{
						associatename = attr->Getvalue();
					}
				}
			}

			informationBinding[associatename] = ib;
		}
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:informationBinding Setting clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
	}
}
