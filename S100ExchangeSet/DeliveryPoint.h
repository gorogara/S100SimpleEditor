#pragma once

#include <string>

namespace Dataset
{
	class DeliveryPoint
	{
	public :
		DeliveryPoint();
		virtual ~DeliveryPoint();

	private:
		std::wstring CharacterString;

	public:
		void SetCharacterString(std::wstring value);
		std::wstring GetCharacterString();
	};
}