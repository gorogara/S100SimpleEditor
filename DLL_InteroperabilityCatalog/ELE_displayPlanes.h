#pragma once
#include <vector>
#include <unordered_map>
#include "S100_IC_DisplayPlane.h"

class ELE_displayPlanes
{
public:
	ELE_displayPlanes();
	virtual ~ELE_displayPlanes();

	std::vector<S100_IC_DisplayPlane*> S100_IC_DisplayPlanes;       
	std::unordered_map<std::wstring, S100_IC_DisplayPlane*> map_DPID;       
	std::unordered_map<std::wstring, S100_IC_DisplayPlane*> map_DPNM;           
	std::unordered_map<std::wstring, std::list<S100_IC_Feature*>> map_DP_FCODE;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
	void BuildHashMap();
};

