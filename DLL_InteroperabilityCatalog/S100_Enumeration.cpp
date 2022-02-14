#include "stdafx.h"
#include "S100_Enumeration.h"


S100_requirementType StringToEnum_RequirementType(std::wstring name)
{
	if (name.compare(L"IHO") == 0)	{ return IHO; }
	else if (name.compare(L"OEM") == 0)	{ return OEM; }
	else if (name.compare(L"national") == 0)	{ return national; }
	else if (name.compare(L"local") == 0)	{ return local; }
	else if (name.compare(L"port") == 0)	{ return port; }
	else if (name.compare(L"company") == 0)	{ return company; }
	else if (name.compare(L"master") == 0)	{ return master; }
	else if (name.compare(L"pilot") == 0)	{ return pilot; }
	else if (name.compare(L"other") == 0)	{ return other; }

	return IHO;
}

S100_geometry StringToEnum_Geometry(std::wstring name)
{
		 if (name.compare(L"A") == 0)	{ return A; }
	else if (name.compare(L"L") == 0)	{ return L; }
	else if (name.compare(L"P") == 0)	{ return P; }
	else return NO_GEOMETRY;
}

std::wstring EnumToString_Geometry(S100_geometry dp)
{
	switch (dp)
	{
	case A:	 return L"A";
	case L:	 return L"L";
	case P:	 return L"P";
	default:	 return L"NO_Geometry";
	}
}

S100_dataProduct StringToEnum_DataProduct(std::wstring name)
{
	if (name.compare(L"S-101") == 0)	{ return S_101; }
	else if (name.compare(L"S-102") == 0)	{ return S_102; }
	else if (name.compare(L"S-111") == 0)	{ return S_111; }
	else if (name.compare(L"S-112") == 0)	{ return S_112; }
	else if (name.compare(L"S-121") == 0) { return S_121; }
	else if (name.compare(L"S-122") == 0) { return S_122; }
	else if (name.compare(L"S-123") == 0)	{ return S_123; }
	else if (name.compare(L"S-124") == 0)	{ return S_124; }
	else if (name.compare(L"S-127") == 0)	{ return S_127; }
	else if (name.compare(L"S-128") == 0)	{ return S_128; }
	else if (name.compare(L"S-129") == 0)	{ return S_129; }
	else if (name.compare(L"S-421") == 0)	{ return S_421; }
	else if (name.compare(L"S-201") == 0)	{ return S_201; }
	else if (name.compare(L"S-411") == 0)	{ return S_411; }
	else if (name.compare(L"S-412") == 0)	{ return S_412; }
	else if (name.compare(L"HYBRID") == 0)	{ return HYBRID; }

	return S_100;
}

std::wstring EnumToString_DataProduct(S100_dataProduct dp)
{
	switch (dp)
	{
	case S_101:	 return L"S-101";
	case S_102:	 return L"S-102";
	case S_111:	 return L"S-111";
	case S_112:	 return L"S-112";
	case S_121:	 return L"S-121";
	case S_122:	 return L"S-122";
	case S_123:	 return L"S-123";
	case S_124:	 return L"S-124";
	case S_127:	 return L"S-127";
	case S_128:	 return L"S-128";
	case S_129:	 return L"S-129";
	case S_421:	 return L"S-421";
	case S_201:	 return L"S-201";
	case S_411:	 return L"S-411";
	case S_412:	 return L"S-412";
	case HYBRID: return L"HYBRID";
	default:	 return L"S-100";
	}
}



std::wstring CreateHashMapKey(std::vector<std::wstring> &values)
{
	std::wstring ret;
	for (unsigned i = 0; i < values.size(); i++)
	{
		ret.append(values[i]);

		if (i != values.size() - 1)
			ret.append(L"^");
	}
	values.clear();

	return ret;
}