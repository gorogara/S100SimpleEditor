#pragma once
#include <string>
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"  

class S100_Catalogue
{
public:
	S100_Catalogue();
	virtual ~S100_Catalogue(); 
	std::wstring name; 
	std::wstring scope; 
	std::wstring fieldOfApplication; 
	std::wstring versionNumber;  
	std::wstring versionDate; 
	std::wstring language; 
	std::wstring locale;  
	std::wstring characterSet;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

