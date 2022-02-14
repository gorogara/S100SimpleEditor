#pragma once
#include "DeliveryPoint.h"
#include "City.h"
#include "PostalCode.h"
namespace Dataset
{
	class CI_Address
	{
	public:
		CI_Address();
		virtual ~CI_Address();

	private:
		DeliveryPoint deliveryPoint;
		City city;
		PostalCode postalCode;
	
	public:
		void SetDeliveryPoint(DeliveryPoint value);
		DeliveryPoint GetDeliveryPoint();

		void SetCity(City value);
		City GetCity();

		void SetPostalCode(PostalCode value);
		PostalCode GetPostalCode();
	};
}