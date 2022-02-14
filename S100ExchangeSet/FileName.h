#pragma once
#include <unordered_map>
#include <string>

namespace Dataset
{
	class FileName
	{
	public:
		FileName();
		~FileName();

	private:
		std::unordered_map<std::wstring, std::wstring> attribute;
		std::wstring value;
	
	public:
		void SetAttribute(std::unordered_map<std::wstring, std::wstring> value);
		void Setvalue(std::wstring _value);

		std::unordered_map<std::wstring, std::wstring> GetAttribute();
		std::wstring Getvalue();
	};
}