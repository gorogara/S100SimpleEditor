#include "stdafx.h"
#include "Address.h"

namespace Dataset
{
	Address::Address() 
	{

	}
	Address::~Address() 
	{

	}
	void Address::SetCi_TelePhone(CI_Address value)
	{
		ci_telephone = value;
	}
	 
	CI_Address Address::GetCi_TelePhone() 
	{
		return ci_telephone;
	}
}