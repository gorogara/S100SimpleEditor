#pragma once
namespace S100_SVG_D2D1_DLL 
{
	class DrawingPathUnit
	{
	public:
		DrawingPathUnit() { type = 0; };
		virtual ~DrawingPathUnit() {};  
	public:
		int type;
	};
}
