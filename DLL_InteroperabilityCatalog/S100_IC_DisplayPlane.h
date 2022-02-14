#pragma once
#include "ELE_features.h"
#include "S100_IC_SaturationOffset.h"
class S100_IC_DisplayPlane
{
public:
	S100_IC_DisplayPlane();
	virtual ~S100_IC_DisplayPlane();

	std::wstring identifier;
	std::wstring name;
	int displayPriority;
	std::wstring description; 
	S100_IC_SaturationOffset S100_IC_SaturationOffset;
	ELE_features features;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
	void BuildHashMap();
};

