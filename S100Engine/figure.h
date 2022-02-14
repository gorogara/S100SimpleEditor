#pragma once

#include <string>

using namespace std;

namespace libS100Engine
{

	enum FigureType
	{
		none = 0,
		line = 1,
		circle = 2,
		rect = 3,
		pivotPoint = 4
	};

	class Figure
	{
	public:
		Figure();
		virtual ~Figure();

	public:
		FigureType type;
		wstring colorName;
		double strokeWidth;
		wstring strokeDasharray;
		int rotation;
		bool fill;
		float alpha = 1.0f;
	};

}