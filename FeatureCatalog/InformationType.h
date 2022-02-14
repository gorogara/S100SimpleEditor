#pragma once
#include "S100ObjectType.h"

#include <pugixml.hpp>

class InformationType :
	public S100ObjectType
{
public:
	InformationType(); 
	virtual ~InformationType();

public:
	std::wstring superType; 
	std::list<std::wstring> subType; 

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

}; 

