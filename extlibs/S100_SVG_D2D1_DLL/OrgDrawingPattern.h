#pragma once

#include <list>

namespace S100_SVG_D2D1_DLL 
{
	class CSSStyle;

	class OrgDrawingPattern
	{
	public:
		OrgDrawingPattern();
		virtual ~OrgDrawingPattern();
	public:     
		int type;  
		bool fill; 
		COLORREF *color;  
		int width;  
	};
}