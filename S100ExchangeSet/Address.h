#pragma once
#include "CI_Address.h"

namespace Dataset
{
	class Address
	{
	public :
		Address();
		virtual ~Address();

	private:
		CI_Address ci_telephone;

	public:
		void SetCi_TelePhone(CI_Address value);
		CI_Address GetCi_TelePhone();
	};
}