#pragma once

#include<string>

namespace S100_SVG_D2D1_DLL
{
	class DrawingPattern
	{
	public:
		DrawingPattern();
		virtual ~DrawingPattern();

	public:
		int type;
		std::wstring className; 
		std::wstring style;
	};
}
