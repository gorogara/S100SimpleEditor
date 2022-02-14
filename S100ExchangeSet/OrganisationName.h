#pragma once
#include <string>

namespace Dataset
{
	class OrganisationName
	{
	public:
		OrganisationName();
		virtual ~OrganisationName();

	private:
		std::wstring CharacterString;

	public: 
		void SetCharacterString(std::wstring value);
		std::wstring GetCharacterString();
	};
}