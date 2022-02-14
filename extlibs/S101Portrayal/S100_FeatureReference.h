#pragma once
#include <string>
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"
class S100_FeatureReference
{
public:
	S100_FeatureReference();
	virtual ~S100_FeatureReference();

public:
	std::wstring reference;
public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

