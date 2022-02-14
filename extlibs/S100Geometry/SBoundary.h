#pragma once
class SBoundary
{
public:
	SBoundary()
	{
		xmin = 180.0;
		ymin = 90.0;
		xmax = -180.0;
		ymax = -90.0;
	};
	virtual ~SBoundary() {};

	double xmin;
	double ymin;
	double xmax;
	double ymax;
};