#include "stdafx.h"
#include "WestBoundLongitude.h"
namespace Dataset
{
	WestBoundLongitude::WestBoundLongitude() 
	{

	}
	WestBoundLongitude::~WestBoundLongitude()
	{

	}

	void WestBoundLongitude::SetDecimal(double value) 
	{
		Decimal = value;
	}
	double WestBoundLongitude::GetDecimal() 
	{
		return Decimal;
	}
}
