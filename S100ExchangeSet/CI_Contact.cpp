#include "stdafx.h"
#include "CI_Contact.h"

namespace Dataset
{
	CI_Contact::CI_Contact() 
	{

	}
	CI_Contact::~CI_Contact() 
	{

	}

	void CI_Contact::SetPhone(Phone value) 
	{
		phone = value;
	}

	Phone CI_Contact::GetPhone()
	{
		return phone;
	}

	void CI_Contact::SetAddress(Address value)
	{
		address = value;
	}
	
	Address CI_Contact::GetAddress()
	{
		return address;
	}

}