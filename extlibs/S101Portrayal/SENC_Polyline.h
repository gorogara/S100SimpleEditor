#pragma once
#include <list>
#include "SENC_VectorPoint.h"

class SENC_Polyline
{
public:
	SENC_Polyline();
	~SENC_Polyline();

public:
	std::list<SENC_VectorPoint> points;
};

