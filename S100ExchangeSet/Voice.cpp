#include "stdafx.h"
#include "Voice.h"
namespace Dataset
{
	Voice::Voice() 
	{
	}

	Voice::~Voice() 
	{
	}

	void Voice::SetCharacterString(std::wstring value)
	{
		CharacterString = value;
	}

	std::wstring Voice::GetCharacterString() 
	{
		return CharacterString;
	}
}
