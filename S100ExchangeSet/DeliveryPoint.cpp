#include "stdafx.h"
#include "DeliveryPoint.h"
namespace Dataset
{
	DeliveryPoint::DeliveryPoint()
	{

	}
	DeliveryPoint::~DeliveryPoint() 
	{

	}

	void DeliveryPoint::SetCharacterString(std::wstring value) 
	{
		CharacterString = value;
	}

	std::wstring DeliveryPoint::GetCharacterString() 
	{
		return CharacterString;
	}
}