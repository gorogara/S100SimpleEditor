// FeatureCatalog.cpp : 해당 DLL의 초기화 루틴을 정의합니다. 

#include "stdafx.h"
#include "FeatureCatalogue.h"
#include "Role.h" 
#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"

#include <atlstr.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

FeatureCatalogue::FeatureCatalogue(void)
{ 
}
FeatureCatalogue::~FeatureCatalogue(void)
{

}  

SimpleAttribute* FeatureCatalogue::GetSimpleAttribute(std::wstring code)
{
	auto itor = simpleAttributes.simpleAttribute.find(code);

	if (itor == simpleAttributes.simpleAttribute.end())
		return nullptr; 
	else
		return &itor->second;
}
SimpleAttribute* FeatureCatalogue::GetSimpleAttributeFromName(std::wstring name)
{
	for (auto i = simpleAttributes.simpleAttribute.begin();
		i != simpleAttributes.simpleAttribute.end();
		i++)
	{
		if (i->second.name.compare(name) == 0)
			return &i->second;
	}

	return nullptr;

}

ComplexAttribute* FeatureCatalogue::GetComplexAttribute(std::wstring code)
{
	auto itor = complexAttributes.complexAttribute.find(code);

	if (itor == complexAttributes.complexAttribute.end())
		return NULL; 
	else
		return &itor->second;
}

ComplexAttribute* FeatureCatalogue::GetComplexAttributeFromName(std::wstring name)
{
	for (auto i = complexAttributes.complexAttribute.begin();
		i != complexAttributes.complexAttribute.end();
		i++)
	{
		if (i->second.name.compare(name) == 0)
			return &i->second;
	}

	return nullptr;
}

FeatureType* FeatureCatalogue::GetFeatureType(std::wstring code)
{
	auto itor = featureTypes.featureType.find(code);

	if (itor == featureTypes.featureType.end())
		return NULL; 
	else
		return &itor->second;
}

FeatureType* FeatureCatalogue::GetFeatureTypeName(std::wstring name)
{
	for (auto i = featureTypes.featureType.begin();
		i != featureTypes.featureType.end();
		i++)
	{
		if (i->second.name.compare(name) == 0)
			return &i->second;
	}

	return nullptr;     
}


FeatureType* FeatureCatalogue::GetFeatureTypeFromIndex(int indexnum)
{ 
	int num = 0;
	for (auto i= featureTypes.featureType.begin(); i!=featureTypes.featureType.end(); i++)
	{
		if (num==indexnum)
		{
			auto dfsf = &i->second;
			OutputDebugString(L"");
			return &i->second;
		}
		
		num++;
	}


	return nullptr;    
}

InformationType* FeatureCatalogue::GetInformationType(std::wstring code)
{
	auto itor = informationTypes.informationType.find(code);

	if (itor == informationTypes.informationType.end())
		return NULL; 
	else
		return &itor->second;
}


InformationType* FeatureCatalogue::GetInformationTypeFromName(std::wstring name)
{
	for (auto itor = informationTypes.informationType.begin();
		itor != informationTypes.informationType.end();
		itor++)
	{
		if (itor->second.name.compare(name) == 0)
			return &itor->second;
	}

	return NULL;
}

FeatureAssociation* FeatureCatalogue::GetFeatureAssociation(std::wstring code)
{
	auto itor = featureAssociations.featureAssociation.find(code);

	if (itor == featureAssociations.featureAssociation.end())
		return NULL; 
	else
		return &itor->second;
}

FeatureAssociation* FeatureCatalogue::GetFeatureAssociationFromName(std::wstring name)
{
	for (auto itor = featureAssociations.featureAssociation.begin();
		itor != featureAssociations.featureAssociation.end();
		itor++)
	{
		if (itor->second.name.compare(name) == 0)
			return &itor->second;
	}

	return NULL;
}

InformationAssociation* FeatureCatalogue::GetInformationAssociation(std::wstring code)
{
	auto itor = informationAssociations.informationAssociation.find(code);

	if (itor == informationAssociations.informationAssociation.end())
		return NULL; 
	else
		return &itor->second;
}

InformationAssociation* FeatureCatalogue::GetInformationAssociationFromName(std::wstring name)
{
	for (auto itor = informationAssociations.informationAssociation.begin();
		itor != informationAssociations.informationAssociation.end();
		itor++)
	{
		if (itor->second.name.compare(name) == 0)
			return &itor->second;
	}

	return NULL;
}

Role* FeatureCatalogue::GetRole(std::wstring code)
{
	auto itor = roles.role.find(code);

	if (itor == roles.role.end())
		return NULL; 
	else
		return &itor->second;
}

Role* FeatureCatalogue::GetRoleFromName(std::wstring name)
{
	for (auto itor = roles.role.begin();
		itor != roles.role.end();
		itor++)
	{
		if (itor->second.name.compare(name) == 0)
			return &itor->second;
	}

	return NULL;
}

void FeatureCatalogue::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		std::string str = std::string(W2A(pChildNode->baseName));

		if (str.compare("name") == 0)
		{
			name = pChildNode->Gettext();
		}
		else if (str.compare("product") == 0)
		{
			product = pChildNode->Gettext();
		}
		else if (str.compare("scope") == 0)
		{
			scope = pChildNode->Gettext();
		}
		else if (str.compare("fieldOfApplication") == 0)
		{
			fieldOfApplication = pChildNode->Gettext();
		}
		else if (str.compare("versionNumber") == 0)
		{
			versionNumber = pChildNode->Gettext();
		}
		else if (str.compare("versionDate") == 0)
		{
			versionDate = pChildNode->Gettext();
		}
		else if (str.compare("producer") == 0)
		{
			producer.GetContents(pChildNode);
		}
		else if (str.compare("S100_FC_DefinitionSources") == 0)
		{
			definitionSources.GetContents(pChildNode);
		}
		else if (str.compare("S100_FC_SimpleAttributes") == 0)
		{
			simpleAttributes.GetContents(pChildNode);
		}
		else if (str.compare("S100_FC_ComplexAttributes") == 0)
		{
			complexAttributes.GetContents(pChildNode);
		}
		else if (str.compare("S100_FC_Roles") == 0)
		{
			roles.GetContents(pChildNode);
		}
		else if (str.compare("S100_FC_InformationAssociations") == 0)
		{
			informationAssociations.GetContents(pChildNode);
		}
		else if (str.compare("S100_FC_FeatureAssociations") == 0)
		{
			featureAssociations.GetContents(pChildNode);
		}
		else if (str.compare("S100_FC_InformationTypes") == 0)
		{
			informationTypes.GetContents(pChildNode);
		}
		else if (str.compare("S100_FC_FeatureTypes") == 0)
		{
			featureTypes.GetContents(pChildNode);
		}
	}
	OutputDebugString(L"");
}
void FeatureCatalogue::GetContents(pugi::xml_node& node)
{  
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();

		if (!strcmp(instructionName, "S100FC:name"))
		{
			if (instruction.child_value() != nullptr) 
			{
				name = pugi::as_wide(instruction.child_value());
			}
			else
			{
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_WARNING, L"S100FC:name value is null",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
			}
		}
		else if (!strcmp(instructionName, "S100FC:scope"))
		{
			if (instruction.child_value() != nullptr)
			{
				scope = pugi::as_wide(instruction.child_value());
			}
			else
			{
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:scope value is null",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
			}
		}
		else if (!strcmp(instructionName,"S100FC:product"))
		{
			if (instruction.child_value()!=nullptr)
			{
				product = pugi::as_wide(instruction.child_value());
			}
			else 
			{
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:product value is null",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
			}
			

		}
		else if (!strcmp(instructionName, "S100FC:fieldOfApplication"))
		{
			if (instruction.child_value() != nullptr)
			{
				fieldOfApplication = pugi::as_wide(instruction.child_value());
			}
			else
			{
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_WARNING, L"S100FC:fieldOfApplication value is null",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
			}
		} 
		else if (!strcmp(instructionName, "S100FC:versionNumber"))
		{
			if (instruction.child_value() != nullptr)
			{
				versionNumber = pugi::as_wide(instruction.child_value());
			}
			else
			{
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_WARNING, L"S100FC:versionNumber value is null",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
			}
		}
		else if (!strcmp(instructionName, "S100FC:versionDate"))
		{
			if (instruction.child_value() != nullptr)
			{
				versionDate = pugi::as_wide(instruction.child_value());
			}
			else
			{
				KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_WARNING, L"S100FC:versionDate value is null",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
			}
		}
		else if (!strcmp(instructionName, "S100FC:producer"))
		{
			producer.GetContents(instruction);
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:producer setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100FC:S100_FC_definitionSources"))
		{
			definitionSources.GetContents(instruction);
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:S100_FC_definitionSources setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100FC:S100_FC_SimpleAttributes"))
		{
			simpleAttributes.GetContents(instruction);
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:S100_FC_SimpleAttributes setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100FC:S100_FC_ComplexAttributes"))
		{
			complexAttributes.GetContents(instruction);
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:S100_FC_ComplexAttributes setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100FC:S100_FC_Roles"))
		{
			roles.GetContents(instruction);
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:S100_FC_Roles setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100FC:S100_FC_InformationAssociations"))
		{
			informationAssociations.GetContents(instruction);
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:S100_FC_InformationAssociations setting Clear",KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100FC:S100_FC_FeatureAssociations"))
		{
			featureAssociations.GetContents(instruction);
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:S100_FC_FeatureAssociations setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100FC:S100_FC_InformationTypes"))
		{
			informationTypes.GetContents(instruction);
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:S100_FC_InformationTypes setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100FC:S100_FC_FeatureTypes"))
		{
			featureTypes.GetContents(instruction);
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100FC:S100_FC_FeatureTypes setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else 
		{
			std::wstring anotherName = pugi::as_wide(instructionName);
			anotherName.append(L"is another FCDateName");
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, anotherName.c_str(),KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
	} 
	SetFullAssociations();
}
void FeatureCatalogue::SetFullAssociations()
{ 
	
	for (auto itor = featureTypes.featureType.begin(); itor != featureTypes.featureType.end(); itor++)
	{
		FeatureType *ft = &itor->second;
		SetSubAssociation(ft);
	}

	for (auto itor = informationTypes.informationType.begin(); itor != informationTypes.informationType.end(); itor++)
	{
		InformationType *it = &itor->second;
		SetSubAssociation(it);
	}

}

void FeatureCatalogue::SetSubAssociation(FeatureType* ft)
{
	for (auto fbi = ft->featureBinding.begin();
		fbi != ft->featureBinding.end();
		fbi++)
	{
		auto fb = &fbi->second;
		auto bindedFeatureName = fb->featureType.GetReference(); 
		SetFeatureAssociationFromSuperType(ft, bindedFeatureName, fb->role.GetReference(), fb->association.GetReference());
	}

	for (auto ibi = ft->informationBinding.begin();
		ibi != ft->informationBinding.end();
		ibi++)
	{
		auto ib = &ibi->second;
		auto bindedinformationName = ib->informationType.GetReference(); 
		SetInformationAssociationFromSuperType(ft, bindedinformationName, ib->role.GetReference(), ib->association.GetReference());
	}

	return;
}

void FeatureCatalogue::SetSubAssociation(InformationType* it)
{
	for (auto ibi = it->informationBinding.begin();
		ibi != it->informationBinding.end();
		ibi++)
	{
		auto ib = &ibi->second;
		auto bindedinformationName = ib->informationType.GetReference(); 
		SetInformationAssociationFromSuperType(it, bindedinformationName, ib->role.GetReference(), ib->association.GetReference());
	}

	return;
}


void FeatureCatalogue::SetFeatureAssociationFromSuperType(FeatureType* ft, std::wstring superTypeName, std::wstring roleName, std::wstring associationName)
{
	for (auto fti = featureTypes.featureType.begin(); fti != featureTypes.featureType.end(); fti++)
	{ 
		auto currentFeautreType = &fti->second;
		auto currentFeautreCode = currentFeautreType->code.GetValueString();

		if (superTypeName.compare(currentFeautreCode) == 0)
			continue;

		auto duplicationCheckIter = ft->featureBinding.find(currentFeautreCode);
		if (duplicationCheckIter != ft->featureBinding.end())
			continue;;

		if (superTypeName.compare(currentFeautreType->superType) == 0)
		{
			AddFeatureBinding(ft, currentFeautreType->code.GetValueString(), roleName, associationName);

			if (currentFeautreType->superType.size() > 0)
			{
				SetFeatureAssociationFromSuperType(ft, currentFeautreType->superType, roleName, associationName);
			}
		}
	}
	return;
}

void FeatureCatalogue::SetInformationAssociationFromSuperType(FeatureType* ft, std::wstring superTypeName, std::wstring roleName, std::wstring associationName)
{
	for (auto iti = informationTypes.informationType.begin(); iti != informationTypes.informationType.end(); iti++)
	{ 
		auto currentInformationType = &iti->second;
		auto currentInformationCode = currentInformationType->code.GetValueString();
		
		if (superTypeName.compare(currentInformationCode) == 0)
			continue;

		auto duplicationCheckIter = ft->informationBinding.find(currentInformationCode);
		if (duplicationCheckIter != ft->informationBinding.end())
			continue;;

		if (superTypeName.compare(currentInformationType->superType) == 0)
		{
			AddInformationBinding(ft, currentInformationType->code.GetValueString(), roleName, associationName);

			if (currentInformationType->superType.size() > 0)
			{
				SetInformationAssociationFromSuperType(ft, currentInformationType->superType, roleName, associationName);
			}
		}
	}

	return;
}
void FeatureCatalogue::SetInformationAssociationFromSuperType(InformationType* it, std::wstring superTypeName, std::wstring roleName, std::wstring associationName)
{
	for (auto iti = informationTypes.informationType.begin(); iti != informationTypes.informationType.end(); iti++)
	{ 
		auto currentInformationType = &iti->second;
		auto currentInformationCode = currentInformationType->code.GetValueString();

		if (superTypeName.compare(currentInformationCode) == 0)
			continue;

		auto duplicationCheckIter = it->informationBinding.find(currentInformationCode);
		if (duplicationCheckIter != it->informationBinding.end())
			continue;;

		if (superTypeName.compare(currentInformationType->superType) == 0)
		{
			AddInformationBinding(it, currentInformationType->code.GetValueString(), roleName, associationName);

			if (currentInformationType->superType.size() > 0)
			{
				SetInformationAssociationFromSuperType(it, currentInformationType->superType, roleName, associationName);
			}
		}
	}

	return;
}

void FeatureCatalogue::AddFeatureBinding(FeatureType* ft, std::wstring bindedTypeName, std::wstring roleName, std::wstring associationName)
{
	FeatureBinding fb;

	fb.featureType.SetReference(bindedTypeName);
	fb.role.SetReference(roleName);
	fb.association.SetReference(associationName);
	
	ft->featureBinding.insert(
		std::unordered_map<std::wstring, FeatureBinding>::value_type(
			bindedTypeName,
			fb));
}

void FeatureCatalogue::AddInformationBinding(FeatureType* ft, std::wstring bindedTypeName, std::wstring roleName, std::wstring associationName)
{
	InformationBinding ib;
	ib.informationType.SetReference(bindedTypeName);
	ib.role.SetReference(roleName);
	ib.association.SetReference(associationName);
	
	ft->informationBinding.insert(
		std::unordered_map<std::wstring, InformationBinding>::value_type(
			bindedTypeName,
			ib));
}

void FeatureCatalogue::AddInformationBinding(InformationType* it, std::wstring bindedTypeName, std::wstring roleName, std::wstring associationName)
{
	InformationBinding ib;
	ib.informationType.SetReference(bindedTypeName);
	ib.role.SetReference(roleName);
	ib.association.SetReference(associationName);

	it->informationBinding.insert(
		std::unordered_map<std::wstring, InformationBinding>::value_type(
			bindedTypeName,
			ib));
}