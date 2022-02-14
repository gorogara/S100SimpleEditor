#include "stdafx.h"
#include "PostalCode.h"
namespace Dataset
{
	PostalCode::PostalCode()
	{


	}
	PostalCode::~PostalCode()
	{

	}


	void PostalCode::SetCharacterString(std::wstring value)
	{
		CharacterString = value;
	}

	std::wstring PostalCode::GetCharacterString()
	{
		return CharacterString;
	}

}
