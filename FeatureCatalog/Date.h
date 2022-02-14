#pragma once
#include "XML_Item.h"
#include "DateExt.h"
#include "DateTypeCode.h"

#include <pugixml.hpp>

class Date :
	public XML_Item
{
public:
	Date();
	virtual ~Date();

private:
	DateExt date;
	DateTypeCode dateType;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

	void SetDate(DateExt& value);
	DateExt& GetDate();

	void SetDateType(DateTypeCode& value);
	DateTypeCode& GetDateType();
};

