#include "stdafx.h"
#include "City.h"
namespace Dataset
{
	City::City() 
	{
	}

	City::~City()
	{
	}

	void City::SetCharacterString(std::wstring value)
	{
		CharacterString = value;
	}

	std::wstring City::GetCharacterString() 
	{
		return CharacterString;
	}
}
