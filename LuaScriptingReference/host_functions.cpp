
#include "stdafx.h"
#include "stdio.h"
#include "host_data.h"
#include "lua_functions.h"
#include "host_functions.h"
#include "feature_catalog.h"

#include "..\\FeatureCatalog\\FeatureCatalogue.h"
#include "..\\FeatureCatalog\\FeatureTypes.h"
#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"

#include <iostream>
#include <algorithm>
#include <assert.h>
#include <afxcmn.h>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib" )


using namespace std;


#ifdef _DEBUG
FILE *file_pointer;
FILE *file_pointer2;
#endif

std::list<Result_DrawingInstruction> resultDrawingInstructions;

DWORD HostGetFeatureIDs_speed = 0;
DWORD HostFeatureGetCode_speed = 0;
DWORD HostGetInformationTypeIDs_speed = 0;
DWORD HostInformationTypeGetCode_speed = 0;
DWORD HostFeatureGetSimpleAttribute_speed = 0;
DWORD HostFeatureGetComplexAttributeCount_speed = 0;
DWORD HostFeatureGetSpatialAssociations_speed = 0;
DWORD HostFeatureGetAssociatedFeatureIDs_speed = 0;
DWORD HostFeatureGetAssociatedInformationIDs_speed = 0;
DWORD HostGetSpatialIDs_speed = 0;
DWORD HostGetSpatial_speed = 0;
DWORD HostSpatialGetAssociatedInformationIDs_speed = 0;
DWORD HostSpatialGetAssociatedFeatureIDs_speed = 0;
DWORD HostInformationTypeGetSimpleAttribute_speed = 0;
DWORD HostInformationTypeGetComplexAttributeCount_speed = 0;
DWORD HostGetFeatureTypeCodes_speed = 0;
DWORD HostGetInformationTypeCodes_speed = 0;
DWORD HostGetSimpleAttributeTypeCodes_speed = 0;
DWORD HostGetComplexAttributeTypeCodes_speed = 0;
DWORD HostGetRoleTypeCodes_speed = 0;
DWORD HostGetInformationAssociationTypeCodes_speed = 0;
DWORD HostGetFeatureAssociationTypeCodes_speed = 0;
DWORD HostGetFeatureTypeInfo_speed = 0;
DWORD HostGetInformationTypeInfo_speed = 0;
DWORD HostGetSimpleAttributeTypeInfo_speed = 0;
DWORD HostGetComplexAttributeTypeInfo_speed = 0;
DWORD HostSpatialRelate_speed = 0;
DWORD HostDebuggerEntry_speed = 0;
DWORD HostPortrayalEmit_speed = 0;   
extern string g_unknown_attribute_value;

static void set_unknown_attributes(const S100_FC_NamedType *named_type, string path, string attributeCode, vector<string> &values)
{ 

	auto attribute_bindings = named_type->attributeBinding;
	std::list<AttributeBinding>* featureAttributeBinding = NULL;
	size_t offset = 0;
	size_t found;

	if (!path.empty())
		path += ";";

	while ((found = path.find_first_of(';', offset)) != string::npos)
	{
		auto path_item = path.substr(offset, found - offset);

		auto split = path_item.find(':', 0);

		auto code = path_item.substr(0, split);

		wstring wcode = wstring(code.begin(), code.end());
		auto codeFindIter = pTheFC->featureTypes.featureType.find(wcode);
		if (codeFindIter != pTheFC->featureTypes.featureType.end())
		{
			FeatureType* ft = &codeFindIter->second;
			featureAttributeBinding = &ft->attributeBinding;
		}

		offset = found + 1;
	}


	for (auto attr_binding : attribute_bindings)
	{
		if (attr_binding.attribute.referenceCode == attributeCode && attr_binding.multiplicity.lower > 0)
		{
			for (unsigned i = 0; i < values.size(); i++)
			{
				if (values[i] == "")
					values[i] = g_unknown_attribute_value;
			}
		}
	}
} 
int HostGetFeatureIDs(lua_State *l)
{
#ifdef _DEBUG
	if (fopen_s(&file_pointer, "..\\ProgramData\\LuaLog\\output.txt", "w+") == 0)
	{
		fclose(file_pointer);
	}    
#endif

	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	ls->push(hd_get_feature_ids());

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostGetFeatureIDs_speed += dwTotalTime1;
	return 1;
} 
int HostFeatureGetCode(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto featureID = ls->pop<string>();

	ls->push(hd_get_feature_code(featureID));

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostFeatureGetCode_speed += dwTotalTime1;

	return 1;
} 
int HostGetInformationTypeIDs(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	ls->push(hd_get_information_type_ids());

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostGetInformationTypeIDs_speed += dwTotalTime1;

	return 1;
} 
int HostInformationTypeGetCode(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto informationTypeID = ls->pop<string>();

	ls->push(hd_get_information_type_code(informationTypeID));

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostInformationTypeGetCode_speed += dwTotalTime1;

	return 1;
} 
int HostFeatureGetSimpleAttribute(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto attributeCode = ls->pop<string>();
	auto path = ls->pop<string>();
	auto featureID = ls->pop<string>();

	auto values = hd_get_feature_simple_attribute_values(featureID, path, attributeCode); 

	ls->push(values);

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostFeatureGetSimpleAttribute_speed += dwTotalTime1;

	return 1;
} 
int HostFeatureGetComplexAttributeCount(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto attributeCode = ls->pop<string>();
	auto path = ls->pop<string>();
	auto featureID = ls->pop<string>();

	{      
	}

	auto count = hd_get_feature_complex_attribute_count(featureID, path, attributeCode);

	ls->push(count);

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostFeatureGetComplexAttributeCount_speed += dwTotalTime1;

	return 1;
} 
int HostFeatureGetSpatialAssociations(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto featureID = ls->pop<string>();

	auto sas = hd_get_feature_spatial_associations(featureID);

	vector<lua_ref_ptr> sas_refs;

	for (auto sa : sas)
		sas_refs.push_back(CreateSpatialAssociation(ls, &sa));

	ls->push(sas_refs);

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostFeatureGetSpatialAssociations_speed += dwTotalTime1;

	return 1;
}

int HostFeatureGetAssociatedFeatureIDs(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	assert(false); 

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostFeatureGetAssociatedFeatureIDs_speed += dwTotalTime1;

	return 0;
} 
int HostFeatureGetAssociatedInformationIDs(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto roleCode = ls->pop<string>();
	auto associationCode = ls->pop<string>();
	auto featureID = ls->pop<string>();

	ls->push(hd_get_feature_associated_information_ids(featureID, associationCode, roleCode));

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostFeatureGetAssociatedInformationIDs_speed += dwTotalTime1;

	return 1;
}

int HostGetSpatialIDs(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	assert(false); 

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostGetSpatialIDs_speed += dwTotalTime1;

	return 0;
} 
int HostGetSpatial(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto spatialID = ls->pop<string>();

	switch (hd_get_spatial_type(spatialID))
	{
	case spatial_type::point:
		ls->push(CreatePoint(ls, hd_get_point(spatialID)));
		break;

	case spatial_type::multi_point:
		ls->push(CreateMultiPoint(ls, hd_get_multipoint(spatialID)));
		break;

	case spatial_type::curve:
		ls->push(CreateCurve(ls, hd_get_curve(spatialID)));
		break;

	case spatial_type::composite_curve:
		ls->push(CreateCompositeCurve(ls, hd_get_composite_curve(spatialID)));
		break;

	case spatial_type::surface:
		ls->push(CreateSurface(ls, hd_get_surface(spatialID)));
		break;

	default: 
		assert(false);
		return 0;
	}

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostGetSpatial_speed += dwTotalTime1;

	return 1;
} 
int HostSpatialGetAssociatedInformationIDs(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto roleCode = ls->pop<string>();
	auto associationCode = ls->pop<string>();
	auto spatialID = ls->pop<string>();

	ls->push(hd_get_spatial_associated_information_ids(spatialID, associationCode, roleCode));

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostSpatialGetAssociatedInformationIDs_speed += dwTotalTime1;

	return 1;
} 
int HostSpatialGetAssociatedFeatureIDs(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto spatialID = ls->pop<string>();

	auto feature_ids = hd_get_spatial_associated_feature_ids(spatialID);

	if (feature_ids.empty())
		return 0;

	ls->push(feature_ids);

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostSpatialGetAssociatedFeatureIDs_speed += dwTotalTime1;

	return 1;
} 
int HostInformationTypeGetSimpleAttribute(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto attributeCode = ls->pop<string>();
	auto path = ls->pop<string>();
	auto informationTypeID = ls->pop<string>();

	auto values = hd_get_information_type_simple_attribute_values(informationTypeID, path, attributeCode);

	ls->push(values);

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostInformationTypeGetSimpleAttribute_speed += dwTotalTime1;

	return 1;
} 
int HostInformationTypeGetComplexAttributeCount(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto attributeCode = ls->pop<string>();
	auto path = ls->pop<string>();
	auto informationTypeID = ls->pop<string>();

	auto count = hd_get_information_type_complex_attribute_count(informationTypeID, path, attributeCode);

	ls->push(count);

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostInformationTypeGetComplexAttributeCount_speed += dwTotalTime1;

	return 1;
}    
int HostGetFeatureTypeCodes(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l); 

	auto feature_types = pTheFC->featureTypes.featureType;

	std::vector<std::string> ret_feature_codes;

	for (auto iit = feature_types.begin(); iit != feature_types.end(); iit++)
	{
		wstring name = iit->first; 

		string ret = std::string(name.begin(), name.end());

		ret_feature_codes.push_back(ret);
	}

	ls->push(ret_feature_codes);

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostGetFeatureTypeCodes_speed += dwTotalTime1;

	return 1;
} 
int HostGetInformationTypeCodes(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l); 

	auto information_types = pTheFC->informationTypes.informationType;

	std::vector<std::string> ret_information_codes;

	for (auto iit = information_types.begin(); iit != information_types.end(); iit++)
	{
		wstring name = iit->first; 

		string ret = std::string(name.begin(), name.end());

		ret_information_codes.push_back(ret);
	}

	ls->push(ret_information_codes);

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostGetInformationTypeCodes_speed += dwTotalTime1;

	return 1;
} 
int HostGetSimpleAttributeTypeCodes(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l); 

	auto simpleattribute_types = pTheFC->simpleAttributes.simpleAttribute;

	std::vector<std::string> ret_simpleattribute_codes;

	for (auto iit = simpleattribute_types.begin(); iit != simpleattribute_types.end(); iit++)
	{
		wstring name = iit->first; 

		string ret = std::string(name.begin(), name.end());

		ret_simpleattribute_codes.push_back(ret);
	}

	ls->push(ret_simpleattribute_codes);

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostGetSimpleAttributeTypeCodes_speed += dwTotalTime1;

	return 1;
} 
int HostGetComplexAttributeTypeCodes(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l); 
	auto complexattribute_types = pTheFC->complexAttributes.complexAttribute;

	std::vector<std::string> ret_complexattribute_codes;

	for (auto iit = complexattribute_types.begin(); iit != complexattribute_types.end(); iit++)
	{
		wstring name = iit->first; 

		string ret = std::string(name.begin(), name.end());

		ret_complexattribute_codes.push_back(ret);
	}

	ls->push(ret_complexattribute_codes);

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostGetComplexAttributeTypeCodes_speed += dwTotalTime1;

	return 1;
} 
int HostGetRoleTypeCodes(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l); 
	auto role_types = pTheFC->roles.role;

	std::vector<std::string> ret_role_codes;

	for (auto iit = role_types.begin(); iit != role_types.end(); iit++)
	{
		Role* role = &iit->second;
		wstring name = role->code.GetValueString(); 

		string ret = std::string(name.begin(), name.end());

		ret_role_codes.push_back(ret);
		sort(ret_role_codes.begin(), ret_role_codes.end());
	}

	ls->push(ret_role_codes);

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostGetRoleTypeCodes_speed += dwTotalTime1;

	return 1;
} 
int HostGetInformationAssociationTypeCodes(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l); 

	auto information_association_types = pTheFC->informationAssociations.informationAssociation;

	std::vector<std::string> ret_information_association_codes;

	for (auto iit = information_association_types.begin(); iit != information_association_types.end(); iit++)
	{
		wstring name = iit->first; 

		string ret = std::string(name.begin(), name.end());

		ret_information_association_codes.push_back(ret);
	}

	ls->push(ret_information_association_codes);

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostGetInformationAssociationTypeCodes_speed += dwTotalTime1;

	return 1;
} 
int HostGetFeatureAssociationTypeCodes(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l); 

	auto feature_association_types = pTheFC->featureAssociations.featureAssociation;

	std::vector<std::string> ret_feature_association_codes;

	for (auto iit = feature_association_types.begin(); iit != feature_association_types.end(); iit++)
	{
		wstring name = iit->first; 

		string ret = std::string(name.begin(), name.end());

		ret_feature_association_codes.push_back(ret);
	}

	ls->push(ret_feature_association_codes);


	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostGetFeatureAssociationTypeCodes_speed += dwTotalTime1;

	return 1;
} 
int HostGetFeatureTypeInfo(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto featureCode = ls->pop<string>();

	wstring wfeatureCode = wstring(featureCode.begin(), featureCode.end());

	const FeatureType* ft = pTheFC->GetFeatureType(wfeatureCode);
	
	ls->push(CreateFeatureType(ls, ft));

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostGetFeatureTypeInfo_speed += dwTotalTime1;

	return 1;
} 
int HostGetInformationTypeInfo(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto informationCode = ls->pop<string>();

	wstring winformationCode = wstring(informationCode.begin(), informationCode.end());

	auto it = pTheFC->GetInformationType(winformationCode);

	ls->push(CreateInformationType(ls, it));

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostGetInformationTypeInfo_speed += dwTotalTime1;

	return 1;
} 
int HostGetSimpleAttributeTypeInfo(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto attributeCode = ls->pop<string>();

	wstring wsimpleattributeCode = wstring(attributeCode.begin(), attributeCode.end());

	auto attr = pTheFC->GetSimpleAttribute(wsimpleattributeCode);

	ls->push(CreateSimpleAttribute(ls, attr));

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostGetSimpleAttributeTypeInfo_speed += dwTotalTime1;

	return 1;
} 
int HostGetComplexAttributeTypeInfo(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto attributeCode = ls->pop<string>();

	wstring wattributeCode = wstring(attributeCode.begin(), attributeCode.end());

	auto attr = pTheFC->GetComplexAttribute(wattributeCode);

	ls->push(CreateComplexAttribute(ls, attr));

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostGetComplexAttributeTypeInfo_speed += dwTotalTime1;

	return 1;
}   

int HostSpatialRelate(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	assert(false); 

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostSpatialRelate_speed += dwTotalTime1;

	return 0;
}   

int HostDebuggerEntry(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto command = ls->peek<string>(1);

	if (command == "trace")
	{
		auto text = ls->peek<string>(2);

		cout << '\t' << text << endl;
		OutputDebugStringA(text.c_str());


#ifdef _DEBUG       
#endif
	}
	else
	{
		auto text = ls->peek<string>(2);
		cout << '\t' << text << endl;
	}


	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostDebuggerEntry_speed += dwTotalTime1;

	return 0;
}    

int HostPortrayalEmit(lua_State *l)
{
	DWORD dwStartTime1 = timeGetTime(); 
	auto ls = lua_session::get_session(l);

	auto observedParameters = ls->pop<string>();
	auto drawingInstructions = ls->pop<string>();
	auto featureID = ls->pop<string>();

	Result_DrawingInstruction rdi;

	rdi.featureID = featureID;
	rdi.observedParameters = observedParameters;
	rdi.drawingInstructions = drawingInstructions;  

	int id = stoi(rdi.featureID.c_str());

	resultDrawingInstructions.push_back(rdi);

#ifdef _DEBUG
	if (fopen_s(&file_pointer, "..\\ProgramData\\LuaLog\\output.txt", "a+") == 0)
	{ 
		cout << featureID << endl;
		cout << drawingInstructions << endl;
		cout << observedParameters << endl;
		fprintf(file_pointer, "%s | %s | %s\n", rdi.featureID.c_str(), rdi.drawingInstructions.c_str(), rdi.observedParameters.c_str()); 

		fclose(file_pointer);
	}
#endif

	ls->push(true);

	DWORD dwEndTime1 = timeGetTime();
	DWORD dwTotalTime1 = dwEndTime1 - dwStartTime1;

	HostPortrayalEmit_speed += dwTotalTime1;

	return 1;
}