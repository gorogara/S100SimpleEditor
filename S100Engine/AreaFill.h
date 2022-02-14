#pragma once

#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"
#include <vector>

#import <msxml4.dll>
using namespace std;

class AreaFill
{
public:
	AreaFill();
	virtual ~AreaFill();

public: 
	wstring _name; 
	wstring _exposition; 
	wstring _areaCRS; 
	wstring _symbolReference; 
	float v1_x;
	float v1_y;
	float v2_x;
	float v2_y;

public:

	bool Read(wstring path);
	bool ReadByPugi(wstring path);
	bool initializeCOM();
	wstring getNodeValue(IXMLDOMDocumentPtr &pDoc, BSTR selectSingleNode);
	wstring getNodeValue(pugi::xml_node node);
	wstring getNodeAttribute(IXMLDOMDocumentPtr &pDoc, BSTR selectSingleNode);
	wstring getNodeAttribute(pugi::xml_node node);
};