#pragma once
#include"stdafx.h"
#include "S100_LineStyleBase.h"
#include "S100_Pen.h"
#include "S100_Dash.h"
#include "S100_LineSymbol.h"

#include "..\\extlibs\pugixml\include\pugixml.hpp"

#include <string>
#include <list>

class S100_LineStyle : public S100_LineStyleBase
{
public:
	S100_LineStyle();
	virtual ~S100_LineStyle();

public: 
	std::wstring capStyle;
	std::wstring joinStyle;
	std::wstring offset;

	std::wstring intervalLength;
	S100_Pen m_pen;
	std::list<S100_Dash> m_dash;
	std::list<S100_LineSymbol> m_symbol;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);
};

