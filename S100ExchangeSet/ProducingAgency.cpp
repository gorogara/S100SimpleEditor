#include "stdafx.h"
#include "ProducingAgency.h"
namespace Dataset
{
	ProducingAgency::ProducingAgency() 
	{

	}
	ProducingAgency::~ProducingAgency()
	{

	}

	void ProducingAgency::SetAttribute(std::unordered_map<std::wstring, std::wstring> value)
	{
		attribute = value;
	}

	std::unordered_map<std::wstring, std::wstring> ProducingAgency::GetAttribute()
	{
		return attribute;
	}

	void ProducingAgency::SetOrganisationName(OrganisationName value)
	{
		organisationName = value;
	}
	
	OrganisationName ProducingAgency::GetOrganisagtionName()
	{
		return organisationName;
	}

	void ProducingAgency::SetContactInfo(ContactInfo value) 
	{
		contactInfo = value;
	}

	ContactInfo ProducingAgency::GetContactInfo()
	{
		return contactInfo;
	}

	void ProducingAgency::SetRole(Role value) 
	{
		role = value;
	}

	Role ProducingAgency::GetRole() 
	{
		return role;
	}
}
