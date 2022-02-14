#pragma once

namespace S100DatasetGML
{
	class GMLPoint
	{
	public:
		GMLPoint(double _x, double _y);
		virtual ~GMLPoint();

	public:
		double GetX();
		void SetX(double value);

		double GetY();
		void SetY(double value);

	public:
		double x = 0;
		double y = 0;
	};
}