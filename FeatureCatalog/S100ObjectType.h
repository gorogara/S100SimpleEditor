#pragma once
#include "NamedType.h"
#include "InformationBinding.h"
#include <pugixml.hpp>

class S100ObjectType :
	public NamedType
{
public:
	S100ObjectType();
	virtual ~S100ObjectType();

public:
	std::unordered_map<std::wstring, InformationBinding> informationBinding;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};