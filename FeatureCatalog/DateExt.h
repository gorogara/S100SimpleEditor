#pragma once
#include "XML_Item.h"
#include <pugixml.hpp> 
class DateExt : public XML_Item
{
public:
	DateExt();
	virtual ~DateExt();

private:
	std::wstring date;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

	void SetDate(char* value);
	std::wstring GetDate();
};