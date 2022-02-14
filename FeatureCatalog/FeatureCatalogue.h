#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "ResponsibleParty.h"
#include "DefinitionSources.h"
#include "SimpleAttributes.h"
#include "ComplexAttributes.h"
#include "Roles.h"
#include "InformationAssociations.h"
#include "FeatureAssociations.h"
#include "InformationTypes.h"
#include "FeatureTypes.h"

#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

#include <string>

class SimpleAttribute;
class ComplexAttribute;
class FeatureType;
class InformationType;

class FeatureCatalogue
{
public:
	FeatureCatalogue();
	virtual ~FeatureCatalogue();

public: 
	std::wstring product = L""; 
	std::wstring name = L"";
	std::wstring scope = L"";
	std::wstring fieldOfApplication = L""; 
	std::wstring versionNumber = L"";
	std::wstring versionDate = L""; 

	ResponsibleParty producer; 
	DefinitionSources definitionSources; 
	SimpleAttributes simpleAttributes;
	ComplexAttributes complexAttributes;
	Roles roles;
	InformationAssociations informationAssociations;
	FeatureAssociations featureAssociations;
	InformationTypes informationTypes;
	FeatureTypes featureTypes;

public: 
	SimpleAttribute* GetSimpleAttribute(std::wstring Code);
	SimpleAttribute* GetSimpleAttributeFromName(std::wstring name);

	ComplexAttribute* GetComplexAttribute(std::wstring Code);
	ComplexAttribute* GetComplexAttributeFromName(std::wstring name);

	FeatureType* GetFeatureType(std::wstring Code);
	FeatureType* GetFeatureTypeName(std::wstring Name);
	FeatureType* GetFeatureTypeFromIndex(int indexnum);

	InformationType* GetInformationType(std::wstring Code);
	InformationType* GetInformationTypeFromName(std::wstring name);

	FeatureAssociation* GetFeatureAssociation(std::wstring Code);
	FeatureAssociation* GetFeatureAssociationFromName(std::wstring name);

	InformationAssociation* GetInformationAssociation(std::wstring Code);
	InformationAssociation* GetInformationAssociationFromName(std::wstring name);

	Role* GetRole(std::wstring Code);
	Role* GetRoleFromName(std::wstring name);

	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

	void SetFullAssociations();
	void SetSubAssociation(FeatureType* ft);
	void SetSubAssociation(InformationType* it);
	void SetFeatureAssociationFromSuperType(FeatureType* ft, std::wstring superTypeName, std::wstring roleName, std::wstring associationName);
	void SetInformationAssociationFromSuperType(FeatureType* ft, std::wstring superTypeName, std::wstring roleName, std::wstring associationName);
	void SetInformationAssociationFromSuperType(InformationType* it, std::wstring superTypeName, std::wstring roleName, std::wstring associationName);

	void AddFeatureBinding(FeatureType* ft, std::wstring bindedTypeName, std::wstring roleName, std::wstring associationName);
	void AddInformationBinding(FeatureType* ft, std::wstring bindedTypeName, std::wstring roleName, std::wstring associationName);
	void AddInformationBinding(InformationType* it, std::wstring bindedTypeName, std::wstring roleName, std::wstring associationName);
};