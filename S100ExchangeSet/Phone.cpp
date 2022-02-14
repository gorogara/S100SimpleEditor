#include "stdafx.h"
#include "Phone.h"

namespace Dataset
{

	Phone::Phone() 
	{

	}

	Phone::~Phone()
	{

	}

	void Phone::SetCi_Telephone(CI_Telephone value) 
	{
		ci_telephone = value;
	}

	CI_Telephone Phone::GetCi_Telephone()
	{
		return ci_telephone;
	}
}

