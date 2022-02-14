
#include "stdafx.h"
#include "lua_functions.h"

#include "..\\FeatureCatalog\\FeatureCatalogue.h"
#include "..\\FeatureCatalog\\FeatureType.h"
#include "..\\FeatureCatalog\\InformationType.h"
#include "..\\FeatureCatalog\\InformationBinding.h"
#include "..\\FeatureCatalog\\Role.h"
#include "..\\FeatureCatalog\\InformationAssociation.h"
#include "..\\FeatureCatalog\\FeatureAssociation.h"
#include "..\\FeatureCatalog\\SimpleAttribute.h"

using namespace std;
FeatureCatalogue *pTheFC;      

static lua_variant NullIfEmpty(string s)
{
	if (s == "")
		return nullptr;
	else
		return s;
}

static lua_variant NullIfEmpty(wstring s)
{
	if (s == L"")
		return nullptr;
	else
		return string(s.begin(), s.end());
}


lua_ref_ptr CreateSpatialAssociation(lua_session *ls, const spatial_association *spatial_association)
{
	return ls->call<lua_ref_ptr>("CreateSpatialAssociation", { spatial_association->spatial_type, spatial_association->spatial_id, spatial_association->orientation, spatial_association->scale_minimum, spatial_association->scale_maximum });
}

lua_ref_ptr CreatePoint(lua_session *ls, point point)
{
	return ls->call<lua_ref_ptr>("CreatePoint", { point.x, point.y, point.z });
}

lua_ref_ptr CreateMultiPoint(lua_session *ls, multipoint multipoint)
{
	vector<lua_ref_ptr> points;

	for (auto point : multipoint.points)
		points.push_back(CreatePoint(ls, point));

	return ls->call<lua_ref_ptr>("CreateMultiPoint", { points });
}

lua_ref_ptr CreateCurveSegment(lua_session *ls, curve_segment curve_segment)
{
	vector<lua_ref_ptr> control_points;

	for (auto control_point : curve_segment.control_points)
		control_points.push_back(CreatePoint(ls, control_point));

	return ls->call<lua_ref_ptr>("CreateCurveSegment", { control_points, curve_segment.interpolation });
}

lua_ref_ptr CreateCurve(lua_session *ls, curve curve)
{
	vector<lua_ref_ptr> segments;

	for (auto segment : curve.segments)
		segments.push_back(CreateCurveSegment(ls, segment));

	return ls->call<lua_ref_ptr>("CreateCurve", { CreateSpatialAssociation(ls, &curve.start_point), CreateSpatialAssociation(ls, &curve.end_point), segments });
}

lua_ref_ptr CreateCompositeCurve(lua_session *ls, composite_curve composite_curve)
{
	vector<lua_ref_ptr> curve_associations;

	for (auto curve_association : composite_curve.curve_associations)
		curve_associations.push_back(CreateSpatialAssociation(ls, &curve_association));

	return ls->call<lua_ref_ptr>("CreateCompositeCurve", { curve_associations });
}

lua_ref_ptr CreateSurface(lua_session *ls, surface surface)
{
	if (surface.interior_rings.has_value())
	{
		vector<lua_ref_ptr> interior_rings;

		for (auto interior_ring : surface.interior_rings.value())
			interior_rings.push_back(CreateSpatialAssociation(ls, &interior_ring));

		return ls->call<lua_ref_ptr>("CreateSurface", { CreateSpatialAssociation(ls, &surface.exterior_ring), interior_rings });
	}
	else
	{
		return ls->call<lua_ref_ptr>("CreateSurface", { CreateSpatialAssociation(ls, &surface.exterior_ring) });
	}
}

lua_ref_ptr CreateArcByCenterPoint(lua_session *ls, spatial_association center_point, double radius, double start_angle, double angular_distance)
{
	return ls->call<lua_ref_ptr>("CreateArcByCenterPoint", { CreateSpatialAssociation(ls, &center_point), radius, start_angle, angular_distance });
}

lua_ref_ptr CreateCircleByCenterPoint(lua_session *ls, spatial_association center_point, double radius, double start_angle, double angular_distance)
{
	return ls->call<lua_ref_ptr>("CreateArcByCenterPoint", { CreateSpatialAssociation(ls, &center_point), radius, start_angle, angular_distance });
}       

lua_ref_ptr CreateItem(lua_session *ls, const Item *item) 
{
	string code = string(item->code.valueString.begin(), item->code.valueString.end());
	string name = string(item->name.begin(), item->name.end());
	string definition = string(item->definition.begin(), item->definition.end());

	optional<string> remarks;
	if (item->remarks != L"")
		remarks = string(item->remarks.begin(), item->remarks.end());

	vector<string> alias;

	for (auto a : item->alias)
	{
		alias.push_back(string(a.begin(), a.end()));
	}

	return ls->call<lua_ref_ptr>("CreateItem", { code, name, definition, remarks, alias });
}           

lua_ref_ptr CreateNamedType(lua_session *ls, const NamedType *named_type) 
{
	auto item = CreateItem(ls, named_type);

	vector<lua_ref_ptr> attribute_bindings;

	for (auto ab : named_type->attributeBinding)
		attribute_bindings.push_back(CreateAttributeBinding(ls, &ab));

	bool isAbstract = false;

	for (auto a : named_type->attributes)
	{
		if (a.Getname() == L"isAbstract")
		{
			isAbstract = named_type->value == L"true";
		}
	}

	return ls->call<lua_ref_ptr>("CreateNamedType", { item, isAbstract, attribute_bindings });
}         

lua_ref_ptr CreateObjectType(lua_session *ls, const S100ObjectType *object_type) 
{
	vector<lua_ref_ptr> information_bindings;

	for (auto ib : object_type->informationBinding)
		information_bindings.push_back(CreateInformationBinding(ls, &ib.second));

	return ls->call<lua_ref_ptr>("CreateObjectType", { CreateNamedType(ls, object_type), information_bindings });
}             

lua_ref_ptr CreateInformationType(lua_session *ls, const InformationType *information_type) 
{
	auto object_type = CreateObjectType(ls, information_type); 

	vector<string> sub_types;
	string sub_type;
	for (auto st : information_type->subType)
	{		
		string sub_type = std::string(st.begin(), st.end());
		sub_types.push_back(sub_type);
	}

	return ls->call<lua_ref_ptr>("CreateInformationType", { object_type, NullIfEmpty(information_type->superType), sub_types });
}                       

lua_ref_ptr CreateFeatureType(lua_session *ls, const FeatureType *feature_type) 
{
	auto object_type = CreateObjectType(ls, feature_type);

	vector<string> permitted_primitives;

	for (auto pp : feature_type->permittedPrimitives)
		permitted_primitives.push_back(string(pp.valueString.begin(), pp.valueString.end())); 

	vector<lua_ref_ptr> feature_bindings;

	for (auto fb : feature_type->featureBinding)
		feature_bindings.push_back(CreateFeatureBinding(ls, &fb.second));

	auto featureUseType = string(feature_type->featureUseType.valueString.begin(), feature_type->featureUseType.valueString.end());

	vector<string> sub_types;
	string sub_type;
	for (auto st : feature_type->subType)
	{
		string sub_type = std::string(st.begin(), st.end());
		sub_types.push_back(sub_type);
	}

	return ls->call<lua_ref_ptr>("CreateFeatureType", { object_type, featureUseType, permitted_primitives, feature_bindings, NullIfEmpty(feature_type->superType), sub_types }); 
}                  

lua_ref_ptr CreateInformationAssociation(lua_session *ls, const InformationAssociation *information_association) 
{
	auto named_type = CreateNamedType(ls, information_association);

	vector<lua_ref_ptr> ia_roles;

	std::wstring referenceCode;

	for (auto ia_role : information_association->role)
	{
		for (auto a : ia_role.Getattributes())
		{
			if (a.Getname() == L"ref")
			{
				referenceCode = a.Getvalue();
			}
		}

		for (auto s = pTheFC->roles.role.begin(); s != pTheFC->roles.role.end(); s++)
		{
			Role* sa = &s->second;
			if (sa->code.valueString== referenceCode)
				ia_roles.push_back(CreateRole(ls, sa));
		}
	}

	vector<string> sub_types;
	string sub_type;
	for (auto st : information_association->subType)
	{
		string sub_type = std::string(st.begin(), st.end());
		sub_types.push_back(sub_type);
	}

	return ls->call<lua_ref_ptr>("CreateInformationAssociation", { named_type, ia_roles, NullIfEmpty(information_association->superType), sub_types });
}                

lua_ref_ptr CreateFeatureAssociation(lua_session *ls, const FeatureAssociation *feature_association) 
{
	auto named_type = CreateNamedType(ls, feature_association);

	vector<lua_ref_ptr> fa_roles;

	std::wstring referenceCode;

	for (auto fa_role : feature_association->role)
	{
		for (auto a : fa_role.Getattributes())
		{
			if (a.Getname() == L"ref")
			{
				referenceCode = a.Getvalue();
			}
		}

		for (auto s = pTheFC->roles.role.begin(); s != pTheFC->roles.role.end(); s++)
		{
			Role* role = &s->second;
			if (role->code.valueString == referenceCode)
				fa_roles.push_back(CreateRole(ls, role));
		}
	} 
	vector<string> sub_types;

	for (auto st : feature_association->subType)
	{
		string sub_type = std::string(st.begin(), st.end());
		sub_types.push_back(sub_type);
	}

	return ls->call<lua_ref_ptr>("CreateFeatureAssociation", { named_type, fa_roles, NullIfEmpty(feature_association->superType), sub_types });

}            

lua_ref_ptr CreateRole(lua_session *ls, const Role *role) 
{             

	return ls->call<lua_ref_ptr>("CreateRole", { CreateItem(ls, role) });
}                   

lua_ref_ptr CreateAttributeConstraints(lua_session *ls, const AttributeConstraints *attribute_constraints)
{
	optional<double> rangeLower;
	optional<double> rangeUpper;
	optional<string> rangeClosure;

	if (string(attribute_constraints->range.value.begin(), attribute_constraints->range.value.end()) != "")
	{
		rangeLower = attribute_constraints->range.lowerBound;
		rangeUpper = attribute_constraints->range.upperBound;
		rangeClosure = string(attribute_constraints->range.intervalType.valueString.begin(), attribute_constraints->range.intervalType.valueString.end());
	}

	optional<string> textPattern = string(attribute_constraints->textPattern.begin(), attribute_constraints->textPattern.end());

	return ls->call<lua_ref_ptr>("CreateAttributeConstraints", { attribute_constraints->stringLength, textPattern, rangeLower, rangeUpper, rangeClosure, attribute_constraints->precision });
}                                 

lua_ref_ptr CreateSimpleAttribute(lua_session *ls, const SimpleAttribute *simple_attribute) 
{
	auto item = CreateItem(ls, simple_attribute);

	auto valueType = string(simple_attribute->valueType.valueString.begin(), simple_attribute->valueType.valueString.end());

	optional<string> uom;

	optional<string> quantitySpecification;


	vector<lua_ref_ptr> listedValues;


	if (string(simple_attribute->uom.name.begin(), simple_attribute->uom.name.end()) != "")
		uom = std::string(simple_attribute->uom.name.begin(), simple_attribute->uom.name.end());

	if (string(simple_attribute->quantitySpecification.value.begin(), simple_attribute->quantitySpecification.value.end()) != "")
		quantitySpecification = string(simple_attribute->quantitySpecification.value.begin(), simple_attribute->quantitySpecification.value.end());

	for (auto a : simple_attribute->listedValues)
	{
		for (auto b = a.listedValue.begin(); b != a.listedValue.end(); b++)
		{
			listedValues.push_back(CreateListedValue(ls, &(*b).second));//E-r
		}
	}

	lua_ref_ptr attributeContraints = nullptr;

	if (string(simple_attribute->constraints.value.begin(), simple_attribute->constraints.value.end()) != "")//E-r
		attributeContraints = CreateAttributeConstraints(ls, &simple_attribute->constraints);

	return ls->call<lua_ref_ptr>("CreateSimpleAttribute", { item, valueType, uom, quantitySpecification, attributeContraints, listedValues });
}           

lua_ref_ptr CreateComplexAttribute(lua_session *ls, const ComplexAttribute *complex_attribute)
{
	auto item = CreateItem(ls, complex_attribute);

	vector<lua_ref_ptr> attribute_bindings;

	for (auto ab : complex_attribute->subAttributeBinding)
		attribute_bindings.push_back(CreateAttributeBinding(ls, &ab));

	return ls->call<lua_ref_ptr>("CreateComplexAttribute", { item, attribute_bindings });
}    

lua_ref_ptr CreateListedValue(lua_session *ls, const ListedValue *listed_value)
{
	string label = string(listed_value->label.begin(), listed_value->label.end());
	string definition = string(listed_value->definition.begin(), listed_value->definition.end());
	int code = listed_value->code.valueInteger;

	optional<string> remarks;
	if (listed_value->remarks != L"")
		remarks = string(listed_value->remarks.begin(), listed_value->remarks.end());

	vector<string> alias;
	for (auto a : listed_value->alias)
	{
		alias.push_back(string(a.begin(), a.end()));
	}

	return ls->call<lua_ref_ptr>("CreateListedValue", { label, definition, code, remarks, alias });
}

lua_ref_ptr CreateAttributeBinding(lua_session *ls, const AttributeBinding *attribute_binding) 
{
	lua_ref_ptr Attributeb;

	string referenceCode;

	bool sequential = false;

	for (auto a : attribute_binding->attribute.attributes)
	{
		if (a.Getname() == L"ref")
		{
			referenceCode = a.GetvalueString();
		}
	}

	sequential = attribute_binding->attribute.value.compare(L"true") == 0;

	vector<int> permittedValues;

	for (auto s : attribute_binding->permittedValues.value)
	{
		permittedValues.push_back(s);
	}

	optional<int> muluppvalue;

	if (attribute_binding->multiplicity.upper.value != L"")
	{
		muluppvalue = std::stoi(attribute_binding->multiplicity.upper.value);
	}

	return ls->call<lua_ref_ptr>("CreateAttributeBinding", { referenceCode, attribute_binding->multiplicity.lower, muluppvalue, sequential, permittedValues });
}          

lua_ref_ptr CreateInformationBinding(lua_session *ls, const InformationBinding *information_binding) 
{
	string role;
	string information_association;

	std::wstring referenceCode;
	std::string itreferenceCode;

	for (auto a : information_binding->role.attributes)
	{
		if (a.Getname() == L"ref")
		{
			referenceCode = a.Getvalue();
		}
	}

	role = string(information_binding->role.value.begin(), information_binding->role.value.end());       

	for (auto a : information_binding->association.attributes)
	{
		if (a.Getname() == L"ref")
		{
			referenceCode = a.Getvalue();
		}
	}

	information_association = string(information_binding->association.value.begin(), information_binding->association.value.end());       

	for (auto a : information_binding->informationType.attributes)
	{
		if (a.Getname() == L"ref")
		{
			itreferenceCode = a.GetvalueString(); 
		}
	}

	optional<int> muluppvalue;

	if (information_binding->multiplicity.upper.value != L"")
		muluppvalue = std::stoi(information_binding->multiplicity.upper.value);

	auto roleType = string(information_binding->role.value.begin(), information_binding->role.value.end()); 


	return ls->call<lua_ref_ptr>("CreateInformationBinding", { itreferenceCode, information_binding->multiplicity.lower, muluppvalue, roleType, role, information_association });

}          

lua_ref_ptr CreateFeatureBinding(lua_session *ls, const FeatureBinding *feature_binding)
{
	string role;
	string feature_association;

	std::wstring referenceCode;
	std::string ftreferenceCode;

	for (auto a : feature_binding->role.attributes)
	{
		if (a.Getname() == L"ref")
		{
			referenceCode = a.Getvalue();
		}
	}



	role = string(feature_binding->role.value.begin(), feature_binding->role.value.end());      

	for (auto a : feature_binding->association.attributes)
	{
		if (a.Getname() == L"ref")
		{
			referenceCode = a.Getvalue();
		}
	}

	feature_association = string(feature_binding->association.value.begin(), feature_binding->association.value.end());      

	for (auto a : feature_binding->featureType.attributes)
	{
		if (a.Getname()== L"ref")
		{
			ftreferenceCode = a.GetvalueString(); 
		}
	}

	optional<int> muluppvalue;

	if (feature_binding->multiplicity.upper.value!= L"")
		muluppvalue = std::stoi(feature_binding->multiplicity.upper.value);


	auto roleType = string(feature_binding->role.value.begin(), feature_binding->role.value.end());

	return ls->call<lua_ref_ptr>("CreateFeatureBinding", { ftreferenceCode, feature_binding->multiplicity.lower, muluppvalue, roleType, role, feature_association });
}      

