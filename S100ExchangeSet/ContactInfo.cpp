#include "stdafx.h"
#include "ContactInfo.h"

namespace Dataset
{
	ContactInfo::ContactInfo() 
	{

	}
	ContactInfo::~ContactInfo()
	{

	}

	void ContactInfo::SetCi_Contact(CI_Contact value)
	{
		ci_contact = value;
	}
	
	CI_Contact ContactInfo::GetCi_Contact() 
	{
		return ci_contact;
	}
}
