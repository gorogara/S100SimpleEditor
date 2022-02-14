#pragma once
#include "stdafx.h"


#include "rapidxml.hpp"

#include "..\\FeatureCatalog\\Item.h"
#include "..\\FeatureCatalog\\Attribute.h"
#include "..\\FeatureCatalog\\ListedValue.h"
#include "..\\FeatureCatalog\\SimpleAttribute.h"
#include "..\\FeatureCatalog\\AttributeBinding.h"
#include "..\\FeatureCatalog\\ComplexAttribute.h"
#include "..\\FeatureCatalog\\Role.h"
#include "..\\FeatureCatalog\\InformationAssociation.h"
#include "..\\FeatureCatalog\\FeatureAssociation.h"
#include "..\\FeatureCatalog\\InformationType.h"
#include "..\\FeatureCatalog\\FeatureBinding.h"
#include "..\\FeatureCatalog\\FeatureType.h"

#include <string>
#include <optional>
#include <vector>
#include <map>
class FeatureCatalogue;

enum class S100_FC_RoleType
{
	unknown,
	association,
	aggregation,
	composition
};

extern std::map<S100_FC_RoleType, std::string> S100_FC_RoleType_Names;

enum class S100_CD_FeatureUseType
{
	unknown,
	geographic,
	meta,
	cartographic,
	theme
};

extern std::map<S100_CD_FeatureUseType, std::string> S100_CD_FeatureUseType_Names;

enum class S100_FC_SpatialPrimitiveType
{
	unknown,
	point,
	pointSet,
	curve,
	surface,
	coverage,
	noGeometry
};

extern std::map<S100_FC_SpatialPrimitiveType, std::string> S100_FC_SpatialPrimitiveType_Names;

enum class S100_CD_AttributeValueType
{
	unknown,
	boolean,
	enumeration,
	integer,
	real,
	text,
	date,
	time,
	dateTime,
	URI,
	URL,
	URN,
	S100_CodeList,
	S100_TruncatedDate
};

extern std::map<S100_CD_AttributeValueType, std::string> S100_CD_AttributeValueType_Names;

enum class S100_CD_QuantitySpecification
{
	unknown,
	angularVelocity,
	area,
	density,
	duration,
	frequency,
	length,
	planeAngle,
	power,
	pressure,
	salinity,
	speed,
	temperature,
	volume,
	weight,
	otherQuantity
};

extern std::map<S100_CD_QuantitySpecification, std::string> S100_CD_QuantitySpecification_Names;

enum class S100_IntervalType
{
	unknown,
	openInterval,
	geLtInterval,
	gtLeInterval,
	closedInterval,
	gtSemiInterval,
	geSemiInterval,
	ltSemiInterval,
	leSemiInterval
};

extern std::map<S100_IntervalType, std::string> S100_IntervalType_Names;

template <class T> T enum_by_name(std::map<T, std::string> m, std::string s)
{
	for (auto kvp : m)
		if (kvp.second == s)
			return kvp.first;

	return T::unknown;
}

template <class T> std::string enum_to_string(T e);            

class S100_FC;

template <class T>
class S100_FC_ItemReference
{
public:
	S100_FC_ItemReference() = default;
	S100_FC_ItemReference(rapidxml::xml_node<>* node)
	{
		referenceCode = node->first_attribute("ref")->value();
	}
	S100_FC_ItemReference(Reference* node)
	{
		for (auto a : node->attributes)
		{
			if (a.name == L"ref")
			{
				referenceCode = std::string(a.value.begin(), a.value.end());
			}
		}
	}
	std::string referenceCode;

	const T* dereference(FeatureCatalogue *fc) const;
};                          

class UnlimitedInteger_LUA
{
public:
	UnlimitedInteger_LUA() = default;
	UnlimitedInteger_LUA(rapidxml::xml_node<>* node);
	UnlimitedInteger_LUA(Multiplicity* node);

	bool infinite;
	std::optional<int> value;
};

class S100_Multiplicity
{
public:
	S100_Multiplicity() = default;
	S100_Multiplicity(rapidxml::xml_node<>* node);
	S100_Multiplicity(Multiplicity* node);

	int lower;
	UnlimitedInteger_LUA upper;
};

class S100_UnitOfMeasure
{
public:
	S100_UnitOfMeasure() = default;
	S100_UnitOfMeasure(rapidxml::xml_node<>* node);
	S100_UnitOfMeasure(UnitOfMeasure* uom);

	std::string name;
	std::optional<std::string> definition;
	std::optional<std::string> symbol;
};

class S100_NumericRange
{
public:
	S100_NumericRange() = default;
	S100_NumericRange(rapidxml::xml_node<>* node);

	std::optional<double> lower;
	std::optional<double> upper;
	S100_IntervalType closure;
};

class S100_CD_AttributeConstraints
{
public:
	S100_CD_AttributeConstraints() = default;
	S100_CD_AttributeConstraints(rapidxml::xml_node<>* node);

	std::optional<int> stringLength;
	std::optional<std::string> textPattern;
	std::optional<S100_NumericRange> range;
	std::optional<int> precision;
};   

class S100_FC_Item
{
public:
	S100_FC_Item() = default;
	S100_FC_Item(rapidxml::xml_node<>* node);
	S100_FC_Item(Item* node);

	std::string name;
	std::string definition;
	std::string code;
	std::optional<std::string> remarks;
	std::vector<std::string> alias;
};

class S100_FC_Role : public S100_FC_Item
{
public:
	S100_FC_Role() = default;
	S100_FC_Role(rapidxml::xml_node<>* node) : S100_FC_Item(node) {};
	S100_FC_Role(Role* a) : S100_FC_Item((Item*)a) {};
};

class S100_FC_Attribute : public S100_FC_Item
{
public:
	S100_FC_Attribute() = default;
	S100_FC_Attribute(rapidxml::xml_node<>* node) : S100_FC_Item(node) {};
	S100_FC_Attribute(Attribute* a) : S100_FC_Item((Item*)a) {};
};

class S100_FC_ListedValue
{
public:
	S100_FC_ListedValue() = default;
	S100_FC_ListedValue(rapidxml::xml_node<>* node);
	S100_FC_ListedValue(ListedValue* a);

	std::string label;
	std::string definition;
	int code;
	std::optional<std::string> remarks;
	std::vector<std::string> alias;
};

class S100_FC_SimpleAttribute : public S100_FC_Attribute
{
public:
	S100_FC_SimpleAttribute() = default;
	S100_FC_SimpleAttribute(rapidxml::xml_node<>* node);// : S100_FC_Attribute(node) {};
	S100_FC_SimpleAttribute(SimpleAttribute* sa);

	S100_CD_AttributeValueType valueType;
	std::optional<S100_UnitOfMeasure> uom;
	std::optional<S100_CD_QuantitySpecification> quantitySpecification;
	std::optional<S100_CD_AttributeConstraints> constraints;
	std::vector<S100_FC_ListedValue> listedValue;
};

class S100_FC_AttributeBinding// : public S100_FC_Attribute
{
public:
	S100_FC_AttributeBinding() = default;
	S100_FC_AttributeBinding(rapidxml::xml_node<>* node);
	S100_FC_AttributeBinding(AttributeBinding* node);

	S100_Multiplicity multiplicity;
	bool sequential;
	S100_FC_ItemReference<S100_FC_Attribute> attribute;
	std::vector<int> permittedValues;
};

class S100_FC_ComplexAttribute : public S100_FC_Attribute
{
public:
	S100_FC_ComplexAttribute() = default;
	S100_FC_ComplexAttribute(rapidxml::xml_node<>* node);
	S100_FC_ComplexAttribute(ComplexAttribute* node);

	std::vector<S100_FC_AttributeBinding> attributeBinding;
};

class S100_FC_NamedType : public S100_FC_Item
{
public:
	S100_FC_NamedType() = default;
	S100_FC_NamedType(rapidxml::xml_node<>* node);
	S100_FC_NamedType(NamedType* node);

	bool isAbstract;
	std::vector<S100_FC_AttributeBinding> attributeBinding;
};

class S100_FC_InformationAssociation : public S100_FC_NamedType
{
public:
	S100_FC_InformationAssociation() = default;
	S100_FC_InformationAssociation(rapidxml::xml_node<>* node);
	S100_FC_InformationAssociation(InformationAssociation* node);

	std::vector<S100_FC_ItemReference<S100_FC_Role>> role;
	S100_FC_ItemReference<S100_FC_InformationAssociation> superType;
	std::vector<S100_FC_ItemReference<S100_FC_InformationAssociation>> subType;
};

class S100_FC_InformationType;

class S100_FC_InformationBinding
{
public:
	S100_FC_InformationBinding() = default;
	S100_FC_InformationBinding(rapidxml::xml_node<>* node);
	S100_FC_InformationBinding(InformationBinding* node);

	S100_Multiplicity multiplicity;
	S100_FC_RoleType roleType;
	S100_FC_ItemReference<S100_FC_InformationType> informationType;
	S100_FC_ItemReference<S100_FC_Role> role;
	S100_FC_ItemReference<S100_FC_InformationAssociation> association;
};

class S100_FC_ObjectType : public S100_FC_NamedType
{
public:
	S100_FC_ObjectType() = default;
	S100_FC_ObjectType(rapidxml::xml_node<>* node);
	S100_FC_ObjectType(S100ObjectType* a);

	std::vector<S100_FC_InformationBinding> informationBinding;
};

class S100_FC_InformationType : public S100_FC_ObjectType
{
public:
	S100_FC_InformationType() = default;
	S100_FC_InformationType(rapidxml::xml_node<>* node);
	S100_FC_InformationType(InformationType* node);

	S100_FC_ItemReference<S100_FC_InformationType> superType;
	std::vector<S100_FC_ItemReference<S100_FC_InformationType>> subType;
};

class S100_FC_FeatureAssociation : public S100_FC_NamedType
{
public:
	S100_FC_FeatureAssociation() = default;
	S100_FC_FeatureAssociation(rapidxml::xml_node<>* node);
	S100_FC_FeatureAssociation(FeatureAssociation* node);

	std::vector<S100_FC_ItemReference<S100_FC_Role>> role;
	S100_FC_ItemReference<S100_FC_FeatureAssociation> superType;
	std::vector<S100_FC_ItemReference<S100_FC_FeatureAssociation>> subType;
};

class S100_FC_FeatureType;

class S100_FC_FeatureBinding
{
public:
	S100_FC_FeatureBinding() = default;
	S100_FC_FeatureBinding(rapidxml::xml_node<>* node);
	S100_FC_FeatureBinding(FeatureBinding* node);

	S100_Multiplicity multiplicity;
	S100_FC_RoleType roleType;
	S100_FC_ItemReference<S100_FC_FeatureType> featureType;
	S100_FC_ItemReference<S100_FC_Role> role;
	S100_FC_ItemReference<S100_FC_FeatureAssociation> association;
};

class S100_FC_FeatureType : public S100_FC_ObjectType
{
public:
	S100_FC_FeatureType() = default;
	S100_FC_FeatureType(rapidxml::xml_node<>* node);
	S100_FC_FeatureType(FeatureType* node);

	S100_CD_FeatureUseType featureUseType;
	std::vector<S100_FC_SpatialPrimitiveType> permittedPrimitives;
	std::vector<S100_FC_FeatureBinding> featureBinding;
	S100_FC_ItemReference<S100_FC_FeatureType> superType;
	std::vector<S100_FC_ItemReference<S100_FC_FeatureType>> subType;
};   

class S100_FC
{
template <class T>
friend class S100_FC_ItemReference;

public:
	S100_FC() = default;
	S100_FC(std::string feature_catalog);

	void load_catalog(std::string feature_catalog);
	void load_catalog(FeatureCatalogue* feature_catalog);
	void unload_catalog();

	bool b_load = false;

	std::vector<std::string> get_simple_attribute_codes();
	std::vector<std::string> get_complex_attribute_codes();
	std::vector<std::string> get_role_codes();
	std::vector<std::string> get_information_association_codes();
	std::vector<std::string> get_feature_association_codes();
	std::vector<std::string> get_information_type_codes();
	std::vector<std::string> get_feature_type_codes();

	const S100_FC_SimpleAttribute* get_simple_attribute(std::string code);
	const S100_FC_ComplexAttribute* get_complex_attribute(std::string code);
	const S100_FC_Role* get_role(std::string code);
	const S100_FC_InformationAssociation* get_information_association(std::string code);
	const S100_FC_FeatureAssociation* get_feature_association(std::string code);
	const S100_FC_InformationType* get_information_type(std::string code);
	const S100_FC_FeatureType* get_feature_type(std::string code);

private:
	std::map<std::string, const S100_FC_SimpleAttribute*> m_simple_attributes;
	std::map<std::string, const S100_FC_ComplexAttribute*> m_complex_attributes;
	std::map<std::string, const S100_FC_Role*> m_roles;
	std::map<std::string, const S100_FC_InformationAssociation*> m_information_associations;
	std::map<std::string, const S100_FC_FeatureAssociation*> m_feature_associations;
	std::map<std::string, const S100_FC_InformationType*> m_information_types;
	std::map<std::string, const S100_FC_FeatureType*> m_feature_types;

	template <class T> std::vector<std::string> make_code_list(T item_map);
}; 
extern FeatureCatalogue *pTheFC;
