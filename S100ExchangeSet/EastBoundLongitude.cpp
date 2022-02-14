#include "stdafx.h"
#include "EastBoundLongitude.h"

namespace Dataset 
{
	EastBoundLongitude::EastBoundLongitude() 
	{

	}
	EastBoundLongitude::~EastBoundLongitude()
	{

	}

	void EastBoundLongitude::SetDecimal(double value) 
	{
		Decimal = value;
	}
	
	double EastBoundLongitude::GetDecimal() 
	{
		return Decimal;
	}
}