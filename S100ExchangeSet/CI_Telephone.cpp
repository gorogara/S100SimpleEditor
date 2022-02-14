#include "stdafx.h"
#include "CI_Telephone.h"

namespace Dataset
{
	CI_Telephone::CI_Telephone()
	{

	}
	CI_Telephone::~CI_Telephone()
	{

	}

	void CI_Telephone::SetVoice(Voice value)
	{
		voice = value;
	}

	Voice CI_Telephone::GetVoice() 
	{
		return voice;
	}
}
