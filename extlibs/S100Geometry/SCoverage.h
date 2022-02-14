#pragma once
#include "SGeometry.h"


class SBoundary;
class SCoverage :
	public SGeometry
{
public:
	SCoverage();
	virtual ~SCoverage();

	SBoundary* m_pBoundary; 
	
	int m_xIndex;
	int m_yIndex;
};