#pragma once
#include "S100_Polyline.h"
#include "S100_Arc3Points.h"
#include "S100_ArcByRadius.h"
#include "S100_Annulus.h"

class S100_Path
{
public:
	S100_Path();
	virtual ~S100_Path();

public:
	std::vector<S100_Polyline> polylines;
	std::vector<S100_Arc3Points> arc3Pointses;
	std::vector<S100_ArcByRadius> arcByRadiuses;
	std::vector<S100_Annulus> annuluses;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node node);
};

