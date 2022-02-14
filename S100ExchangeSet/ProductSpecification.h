#pragma once
#include <string>

namespace Dataset
{
	class ProductSpecification
	{
	public:
		ProductSpecification();
		virtual ~ProductSpecification();

	private:
		std::wstring name;
		std::wstring version;
		std::wstring data;

	public:
		void SetName(std::wstring value);
		std::wstring GetName();

		void SetVersion(std::wstring value);
		std::wstring GetVersion();

		void SetData(std::wstring value);
		std::wstring GetData();
	};
}