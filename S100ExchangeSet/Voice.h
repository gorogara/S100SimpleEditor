#pragma once
#include <string>
namespace Dataset
{
	class Voice
	{
	public:
		Voice();
		~Voice();

	private:
		std::wstring CharacterString;

	public:
		void SetCharacterString(std::wstring value);
		std::wstring GetCharacterString();
	};
}