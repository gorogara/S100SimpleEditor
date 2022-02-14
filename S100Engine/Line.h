#pragma once

#include "figure.h"
#include <vector>

using namespace std;

namespace libS100Engine
{

	class Line : public Figure
	{
	public:
		Line();
		Line(vector<wstring> points);
		Line(POINTF points[], int pointsCount);
		virtual ~Line();

	public:
		vector<POINTF> m_points;

	public:
		void AddPoint(POINTF point);
		void AddPoints(vector<wstring> points);
		void SetFill(bool fill);
		void SetStrokeWidth(float width);

	private:
		void initialize();
	};

}