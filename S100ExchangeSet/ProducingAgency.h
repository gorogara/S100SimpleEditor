#pragma once
#include "OrganisationName.h"
#include "ContactInfo.h"
#include "Role.h"

#include <string>
#include <unordered_map>

namespace Dataset
{
	class ProducingAgency
	{
	public:
		ProducingAgency();
		virtual ~ProducingAgency();

	private:
		std::unordered_map<std::wstring, std::wstring> attribute;
		OrganisationName organisationName;
		ContactInfo contactInfo;
		Role role;

	public:
		void SetAttribute(std::unordered_map<std::wstring, std::wstring> value);
		std::unordered_map<std::wstring, std::wstring> GetAttribute();

		void SetOrganisationName(OrganisationName value);
		OrganisationName GetOrganisagtionName();

		void SetContactInfo(ContactInfo value);
		ContactInfo GetContactInfo();

		void SetRole(Role value);
		Role GetRole();
	};
}