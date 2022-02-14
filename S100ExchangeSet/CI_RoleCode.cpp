#include "stdafx.h"
#include "CI_RoleCode.h"

namespace Dataset
{
	CI_RoleCode::CI_RoleCode()
	{

	}

	CI_RoleCode::~CI_RoleCode()
	{

	}

	void CI_RoleCode::SetAttribute(std::unordered_map<std::wstring, std::wstring> value)
	{
		attribute = value;
	}

	std::unordered_map<std::wstring, std::wstring> CI_RoleCode::GetAttribute() 
	{
		return attribute;
	}
}
