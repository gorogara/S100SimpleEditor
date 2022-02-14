#pragma once
#include "XML_Item.h"
#include "IntervalType.h"

#include <pugixml.hpp>

class NumericRange :
	public XML_Item
{
public:
	NumericRange();
	virtual ~NumericRange();

public:
	double lowerBound;
	double upperBound;
	IntervalType intervalType;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

	void SetLowerBound(double value);
	double GetLowerBound();

	void SetUpperBound(double value);
	double GetUpperBound();

	void SetIntervalType(IntervalType value);
	IntervalType GetIntervalType();

};