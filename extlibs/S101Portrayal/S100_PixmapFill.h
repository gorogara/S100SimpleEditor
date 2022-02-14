#pragma once
#include "S100_PatternFill.h"
#include "S100_Pixmap.h"
class S100_PixmapFill :
	public S100_PatternFill
{
public:
	S100_PixmapFill();
	virtual ~S100_PixmapFill();

public:
	S100_Pixmap pixmap;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNodeList);
	void GetContents(pugi::xml_node node);
};

