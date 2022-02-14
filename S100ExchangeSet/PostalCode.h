#pragma once
#include <string>
namespace Dataset
{
	class PostalCode
	{
	public:
		PostalCode();
		virtual ~PostalCode();
	
	private:
		std::wstring CharacterString;
	
	public:
		void SetCharacterString(std::wstring value);
		std::wstring GetCharacterString();
	};
}