#include "stdafx.h"
#include "ProductSpecification.h"
namespace Dataset
{
	ProductSpecification::ProductSpecification() 
	{

	}
	ProductSpecification::~ProductSpecification()
	{

	}

	void ProductSpecification::SetName(std::wstring value)
	{
		name = value;
	}
	
	std::wstring ProductSpecification::GetName() 
	{
		return name;
	}

	void ProductSpecification::SetVersion(std::wstring value)
	{
		version = value;
	}


	std::wstring ProductSpecification::GetVersion()
	{
		return version;
	}

	void ProductSpecification::SetData(std::wstring value)
	{
		data = value;
	}

	std::wstring ProductSpecification::GetData()
	{
		return data;
	}

}
