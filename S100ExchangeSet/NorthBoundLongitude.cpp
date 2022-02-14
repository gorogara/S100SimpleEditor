#include "stdafx.h"
#include "NorthBoundLongitude.h"
namespace Dataset
{
	NorthBoundLongitude::NorthBoundLongitude()
	{

	}

	NorthBoundLongitude::~NorthBoundLongitude()
	{

	}

	void NorthBoundLongitude::SetDecimal(double value) 
	{                    
		Decimal = value;
	}

	double NorthBoundLongitude::GetDecimal()
	{
		return Decimal;
	}
}
