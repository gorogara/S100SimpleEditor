#pragma once
#include <string>

namespace Dataset
{
	class City
	{
	public:
		City();
		virtual ~City();

	private:
		std::wstring CharacterString;

	public:
		void SetCharacterString(std::wstring value);
		std::wstring GetCharacterString();
	};
}