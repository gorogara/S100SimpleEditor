#pragma once
#include "S100_VectorPoint.h"
#include "S100_LineStyle.h"
#include "S100_LineStyleReference.h"
#include "S100_CompositeLineStyle.h"

class S100_Hatch
{
public:
	S100_Hatch();
	virtual ~S100_Hatch(); 
public: 
	S100_LineStyle lineStyle;
	S100_LineStyleReference lineStyleReference;
	S100_CompositeLineStyle compositeLineStyle; 

	S100_VectorPoint direction;
	std::wstring distance;
public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNodeList);
	void GetContents(pugi::xml_node node);
};

