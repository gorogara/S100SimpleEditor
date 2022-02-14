#include "stdafx.h"
#include "FileName.h"

namespace Dataset
{
	FileName::FileName() 
	{

	}
	FileName::~FileName() 
	{

	}

	void FileName::SetAttribute(std::unordered_map<std::wstring, std::wstring> value) 
	{
		attribute = value;
	}
	
	std::unordered_map<std::wstring, std::wstring> FileName::GetAttribute()
	{
		return attribute;
	}

	void FileName::Setvalue(std::wstring _value)
	{
		value = _value;
	}

	std::wstring FileName::Getvalue() 
	{
		return value;
	}

}
