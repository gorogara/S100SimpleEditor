#include "stdafx.h"
#include "SouthBoundLongitude.h"
namespace Dataset
{
	SouthBoundLongitude::SouthBoundLongitude()
	{

	}

	SouthBoundLongitude::~SouthBoundLongitude()
	{

	}

	void SouthBoundLongitude::SetDecimal(double value) 
	{
		Decimal = value;
	}
	double SouthBoundLongitude::GetDecimal()
	{
		return Decimal;
	}
}