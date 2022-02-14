#pragma once

#include <string>
#include <vector>

enum S100_requirementType
{
	IHO = 1, 
	OEM , 
	national, 
	local, 
	port, 
	company, 
	master, 
	pilot, 
	other 
};

S100_requirementType StringToEnum_RequirementType(std::wstring name);

enum S100_geometry
{
	A = 1, 
	L, 
	P, 
	NO_GEOMETRY
};

S100_geometry StringToEnum_Geometry(std::wstring name);
std::wstring EnumToString_Geometry(S100_geometry dp);

enum S100_dataProduct
{
	S_100 = 1, 
	S_101, 
	S_102, 
	S_111, 
	S_112,
	S_122,
	S_121,
	S_123,
	S_124,
	S_127,
	S_128,
	S_129,
	S_201,
	S_411,
	S_412,
	S_421,
	HYBRID
};

S100_dataProduct StringToEnum_DataProduct(std::wstring name);
std::wstring EnumToString_DataProduct(S100_dataProduct dp);


std::wstring CreateHashMapKey(std::vector<std::wstring> &values);