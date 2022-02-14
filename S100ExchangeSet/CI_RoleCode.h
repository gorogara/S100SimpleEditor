#pragma once
#include <unordered_map>
#include <string>

namespace Dataset
{
	class CI_RoleCode
	{
	public :
		CI_RoleCode();
		virtual ~CI_RoleCode();

	private:
		std::unordered_map<std::wstring, std::wstring> attribute;

	public :
		void SetAttribute(std::unordered_map<std::wstring, std::wstring> value);
		std::unordered_map<std::wstring, std::wstring> GetAttribute();
	};
}

