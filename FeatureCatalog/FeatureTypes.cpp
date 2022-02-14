#include "StdAfx.h"
#include "FeatureTypes.h"

#include "..\\DLL_MessageProcess\DLL_MessageProcess.h"

FeatureTypes::FeatureTypes(void)
{ 
}

FeatureTypes::~FeatureTypes(void)
{
}

void FeatureTypes::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr pChildNode = pNodeList->Getitem(i);
		if (pChildNode == NULL)
			continue;
		bstr_t bstr = pChildNode->baseName;
		if (!!bstr)//?
		{
			std::string baseName = std::string(bstr);

			if (baseName.compare("S100_FC_FeatureType") == 0)
			{
				FeatureType ft;
				ft.GetContents(pChildNode);
				featureType.insert(
					std::unordered_map<std::wstring, FeatureType>::value_type(ft.code.GetValueString(), ft)
				);
			}
		}
	} 
	ApplySuperType();
}
void FeatureTypes::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100FC:S100_FC_FeatureType"))
		{
			FeatureType sa;
			sa.GetContents(instruction);
			featureType[sa.code.GetValueString()] = sa;

			if (instruction.attribute("isAbstract"))
			{
				XML_Attribute attr;
				attr.Setname("isAbstract");
				attr.Setvalue((char*)instruction.attribute("isAbstract").value());
				SetAttributes(attr);
			}
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:S100_FC_FeatureType Setting clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else 
		{
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC another data value",KRS_MSG_PROCESS::User_Developer_Mode,KRS_MSG_PROCESS::FC);
		}
	}
	ApplySuperType();
}
void FeatureTypes::ApplySuperType()
{
	for (auto itor = featureType.begin(); itor != featureType.end(); itor++)
	{
		FeatureType *ft = &itor->second;

		SetAttributeFromSuperType(ft);
		SetAssociationFromSuperType(ft);
	}
}

bool FeatureTypes::SetAttributeFromSuperType(FeatureType* ft)
{
	if (ft->superType.size() > 0)
	{
		auto itor = featureType.find(ft->superType);
		if (itor == featureType.end())
		{
			return false;
		}
		else
		{
			FeatureType* sft = &itor->second;
			if (SetAttributeFromSuperType(sft))
			{
				ft->attributeBinding.insert(ft->attributeBinding.begin(), sft->attributeBinding.begin(), sft->attributeBinding.end());
			}
			return true;
		}

	}
	else
		return true;

	return false;

}


bool FeatureTypes::SetAssociationFromSuperType(FeatureType* ft)
{
	if (ft->superType.size() > 0)
	{
		auto itor = featureType.find(ft->superType);
		if (itor == featureType.end())
		{
			return false;
		}
		else
		{
			FeatureType* sft = &itor->second;
			if (SetAssociationFromSuperType(sft))
			{
				ft->featureBinding.insert(sft->featureBinding.begin(), sft->featureBinding.end());
				ft->informationBinding.insert(sft->informationBinding.begin(), sft->informationBinding.end());
			}
			return true;
		}

	}
	else
		return true;

	return false;

}
