#pragma once

#include "lua_session.h"
#include "feature_catalog.h"
#include "host_data.h"      

lua_ref_ptr CreateSpatialAssociation(lua_session *ls, const spatial_association *spatial_association);

lua_ref_ptr CreatePoint(lua_session *ls, point point);

lua_ref_ptr CreateMultiPoint(lua_session *ls, multipoint multipoint);

lua_ref_ptr CreateCurveSegment(lua_session *ls, curve_segment curve_segment);

lua_ref_ptr CreateCurve(lua_session *ls, curve curve);

lua_ref_ptr CreateCompositeCurve(lua_session *ls, composite_curve composite_curve);

lua_ref_ptr CreateSurface(lua_session *ls, surface surface);

lua_ref_ptr CreateArcByCenterPoint(lua_session *ls, spatial_association center_point, double radius, double start_angle, double angular_distance);

lua_ref_ptr CreateCircleByCenterPoint(lua_session *ls, spatial_association center_point, double radius, double start_angle, double angular_distance);   

lua_ref_ptr CreateItem(lua_session *ls, const S100_FC_Item *item);
lua_ref_ptr CreateItem(lua_session *ls, const Item *item);

lua_ref_ptr CreateNamedType(lua_session *ls, const S100_FC_NamedType *named_type);
lua_ref_ptr CreateNamedType(lua_session *ls, const NamedType *named_type);

lua_ref_ptr CreateObjectType(lua_session *ls, const S100_FC_ObjectType *object_type);
lua_ref_ptr CreateObjectType(lua_session *ls, const S100ObjectType *object_type);

lua_ref_ptr CreateInformationType(lua_session *ls, const S100_FC_InformationType *information_type);
lua_ref_ptr CreateInformationType(lua_session *ls, const InformationType *information_type);

lua_ref_ptr CreateFeatureType(lua_session *ls, const S100_FC_FeatureType *feature_type);
lua_ref_ptr CreateFeatureType(lua_session *ls, const FeatureType *feature_type);

lua_ref_ptr CreateInformationAssociation(lua_session *ls, const S100_FC_InformationAssociation *information_association);
lua_ref_ptr CreateInformationAssociation(lua_session *ls, const InformationAssociation *information_association);

lua_ref_ptr CreateFeatureAssociation(lua_session *ls, const S100_FC_FeatureAssociation *feature_association);
lua_ref_ptr CreateFeatureAssociation(lua_session *ls, const FeatureAssociation *feature_association);

lua_ref_ptr CreateRole(lua_session *ls, const S100_FC_Role *role);
lua_ref_ptr CreateRole(lua_session *ls, const Role *role);

lua_ref_ptr CreateAttributeConstraints(lua_session *ls, const S100_CD_AttributeConstraints *attribute_constraints);
lua_ref_ptr CreateAttributeConstraints(lua_session *ls, const AttributeConstraints *attribute_constraints);

lua_ref_ptr CreateSimpleAttribute(lua_session *ls, const S100_FC_SimpleAttribute *simple_attribute);
lua_ref_ptr CreateSimpleAttribute(lua_session *ls, const SimpleAttribute *simple_attribute);

lua_ref_ptr CreateComplexAttribute(lua_session *ls, const S100_FC_ComplexAttribute *complex_attribute);
lua_ref_ptr CreateComplexAttribute(lua_session *ls, const ComplexAttribute *complex_attribute);

lua_ref_ptr CreateListedValue(lua_session *ls, const S100_FC_ListedValue *listed_value);
lua_ref_ptr CreateListedValue(lua_session *ls, const ListedValue *listed_value);

lua_ref_ptr CreateAttributeBinding(lua_session *ls, const S100_FC_AttributeBinding *attribute_binding);
lua_ref_ptr CreateAttributeBinding(lua_session *ls, const AttributeBinding *attribute_binding);

lua_ref_ptr CreateInformationBinding(lua_session *ls, const S100_FC_InformationBinding *information_binding);
lua_ref_ptr CreateInformationBinding(lua_session *ls, const InformationBinding *information_binding);

lua_ref_ptr CreateFeatureBinding(lua_session *ls, const S100_FC_FeatureBinding *feature_binding);
lua_ref_ptr CreateFeatureBinding(lua_session *ls, const FeatureBinding *feature_binding);         

