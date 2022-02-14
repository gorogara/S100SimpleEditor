#pragma once
#include "CI_Telephone.h"

namespace Dataset
{
	class Phone
	{
	public:
		Phone();
		virtual	~Phone();

	private:
		CI_Telephone ci_telephone;

	public:
		void SetCi_Telephone(CI_Telephone value);
		CI_Telephone GetCi_Telephone();
	};
}