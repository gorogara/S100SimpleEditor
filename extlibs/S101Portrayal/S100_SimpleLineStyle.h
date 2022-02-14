#pragma once

#include "S100_Pen.h"
#include "S100_Dash.h"

#include <string>
class S100_SimpleLineStyle
{
public:
	S100_SimpleLineStyle();
	virtual ~S100_SimpleLineStyle();

public:
	std::wstring capStyle;
	std::wstring joinStyle;
	std::wstring offset;
	S100_Pen *pen;
	S100_Dash *dash;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	
};

