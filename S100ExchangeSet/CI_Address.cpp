#include "stdafx.h"
#include "CI_Address.h"

namespace Dataset
{

	CI_Address::CI_Address() 
	{

	}
	CI_Address::~CI_Address() 
	{

	}

	void CI_Address::SetDeliveryPoint(DeliveryPoint value)
	{
		deliveryPoint = value;
	}
	
	DeliveryPoint CI_Address::GetDeliveryPoint() 
	{
		return deliveryPoint;
	}

	void CI_Address::SetCity(City value)
	{
		city = value;
	}

	City CI_Address::GetCity() 
	{
		return city;
	}

	void CI_Address::SetPostalCode(PostalCode value)
	{
		postalCode = value;
	}
	
	PostalCode CI_Address::GetPostalCode() 
	{
		return postalCode;
	}





}