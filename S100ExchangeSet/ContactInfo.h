#pragma once
#include "CI_Contact.h"

namespace Dataset
{
	class ContactInfo
	{
	public:
		ContactInfo();
		virtual ~ContactInfo();

	private:
		CI_Contact ci_contact;

	public:
		void SetCi_Contact(CI_Contact value);
		CI_Contact GetCi_Contact();
	};
}