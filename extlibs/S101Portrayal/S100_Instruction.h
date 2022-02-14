#pragma once

#include "S100_FeatureReference.h"
#include "S100_SpatialReference.h"
#include "S100_LineStyle.h"

#include <string>

class S100_Instruction
{
public:
	S100_Instruction();
	virtual ~S100_Instruction();

public: 
	unsigned type;

	S100_FeatureReference featureReference;
	std::list<S100_SpatialReference*> spatialReference;
	std::wstring viewingGroup;
	std::wstring displayPlane;
	std::wstring drawingPriority;
	std::wstring scaleMinimum;
	std::wstring scaleMaximum;

public:
	void GetContents(MSXML2::IXMLDOMNodeListPtr pNodeList);
	void GetContents(pugi::xml_node node);
};

