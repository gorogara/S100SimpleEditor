#pragma once
#include "Attribute.h"
#include "AttributeValueType.h"
#include "UnitOfMeasure.h"
#include "QuantitySpecification.h"
#include "AttributeConstraints.h"
#include "ListedValues.h"

#include <pugixml.hpp>

class SimpleAttribute :
	public Attribute
{
public:
	SimpleAttribute();
	virtual ~SimpleAttribute();

public:
	AttributeValueType valueType;
	UnitOfMeasure uom; 
	QuantitySpecification quantitySpecification; 
	AttributeConstraints constraints; 
	std::list<ListedValues> listedValues;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

};