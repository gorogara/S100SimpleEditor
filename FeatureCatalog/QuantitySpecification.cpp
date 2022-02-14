#include "stdafx.h"
#include "QuantitySpecification.h"


QuantitySpecification::QuantitySpecification()
{
	InsertValue(L"angularVelocity");
	InsertValue(L"area");
	InsertValue(L"density");
	InsertValue(L"duration");
	InsertValue(L"frequency");
	InsertValue(L"length");
	InsertValue(L"mass");
	InsertValue(L"planeAngle");
	InsertValue(L"power");
	InsertValue(L"pressure");
	InsertValue(L"salinity");
	InsertValue(L"speed");
	InsertValue(L"temperature");
	InsertValue(L"volume");
	InsertValue(L"weight");
	InsertValue(L"otherQuantity");
}


QuantitySpecification::~QuantitySpecification()
{
}

void QuantitySpecification::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	SetValueString(std::wstring(pNode->Gettext()));
}

void QuantitySpecification::GetContents(pugi::xml_node& node)
{
	SetValueString(pugi::as_wide(node.child_value()));
}