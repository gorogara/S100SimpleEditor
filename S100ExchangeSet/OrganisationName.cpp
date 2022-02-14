#include "stdafx.h"
#include "OrganisationName.h"
namespace Dataset
{
	OrganisationName::OrganisationName() 
	{

	}

	OrganisationName::~OrganisationName()
	{

	}

	void OrganisationName::SetCharacterString(std::wstring value)
	{
		CharacterString = value;
	}

	std::wstring OrganisationName::GetCharacterString() 
	{
		return CharacterString;
	}
}
