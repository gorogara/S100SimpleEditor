#pragma once
#include "Phone.h"
#include "Address.h"

namespace Dataset
{
	class CI_Contact
	{
	public :
		CI_Contact();
		virtual ~CI_Contact();

	private:
		Phone phone;
		Address address;
	
	public:
		void SetPhone(Phone value);
		Phone GetPhone();

		void SetAddress(Address value);
		Address GetAddress();
	};
}
