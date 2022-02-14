#include "stdafx.h"
#include "FeatureType.h"

#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"

FeatureType::FeatureType()
{
}


FeatureType::~FeatureType()
{
}


void FeatureType::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	((S100ObjectType*)this)->S100ObjectType::GetContents(pNode);

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	int roleCnt = 0;

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr pChildNode = pNodeList->Getitem(i);
		if (pChildNode == NULL)
			continue;

		if (!pChildNode->baseName)
			continue;

		std::string baseName = std::string(W2A(pChildNode->baseName));

		if (baseName.compare("superType") == 0)
		{
			superType = pChildNode->Gettext();
		}
		else if (baseName.compare("subType") == 0)
		{
			subType.push_back(std::wstring(pChildNode->Gettext()));
		}
		else if (baseName.compare("featureUseType") == 0)
		{
			featureUseType.GetContents(pChildNode);
		}
		else if (baseName.compare("featureBinding") == 0)
		{
			FeatureBinding fb;
			fb.GetContents(pChildNode);

			std::wstring associatename = fb.featureType.Getvalue();
			if (associatename.compare(L"") == 0)
			{ 
				for (auto itor = fb.featureType.Getattributes().begin();
					itor != fb.featureType.Getattributes().end();
					itor++)
				{
					XML_Attribute* attr = &(*itor);
					if (attr->Getname().compare(L"ref") == 0)
					{
						associatename = attr->Getvalue();
					}
				}
			}
			featureBinding.insert(
				std::unordered_map<std::wstring, FeatureBinding>::value_type(
					associatename,
					fb));
		}
		else if (baseName.compare("permittedPrimitives") == 0)
		{
			SpatialPrimitiveType spt;
			spt.GetContents(pChildNode);
			permittedPrimitives.push_back(spt);
		}
	}
}
void FeatureType::GetContents(pugi::xml_node& node)
{
	((S100ObjectType*)this)->S100ObjectType::GetContents(node);

	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FC:featureUseType"))
		{
			featureUseType.GetContents(instruction);
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:featureUseType Setting clear", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100FC:featureBinding"))
		{
			FeatureBinding feature;
			feature.GetContents(instruction);

			std::wstring associatename = feature.featureType.Getvalue();
			if (associatename.compare(L"") == 0)
			{

				for (auto itor = feature.featureType.attributes.begin();
					itor != feature.featureType.attributes.end();
					itor++)
				{
					auto attri = &(*itor);
					if (attri->Getname().compare(L"ref") == 0)
					{
						associatename = attri->Getvalue();
					}
				}
			}
			featureBinding[associatename] = feature;
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:featureBinding Setting clear", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100FC:permittedPrimitives"))
		{
			permittedPrimitives.push_back(SpatialPrimitiveType());
			permittedPrimitives.back().GetContents(instruction);
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:permittedPrimitives Setting clear", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100FC:superType"))
		{
			superType = pugi::as_wide(instruction.child_value());
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:superType Setting clear", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100FC:subType"))
		{
			subType.push_back(pugi::as_wide(instruction.child_value()));
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:subType Setting clear", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::FC);
		}
	}
}