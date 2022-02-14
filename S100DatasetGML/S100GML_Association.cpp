#include "stdafx.h"
#include "S100GML_Association.h"
namespace S100DatasetGML
{
	S100GML_Association::S100GML_Association() 
	{

	}

	S100GML_Association::~S100GML_Association() 
	{

	}

	std::wstring S100GML_Association::GetTag()
	{
		return tag;
	}

	void S100GML_Association::SetTag(std::wstring value) 
	{
		tag = value;
	}

	std::wstring S100GML_Association::GetId() 
	{
		return id;
	}

	void S100GML_Association::SetId(std::wstring value) 
	{
		id = value;
	}
	
	std::wstring S100GML_Association::GetHref()
	{
		return href;
	}

	void S100GML_Association::SetHref(std::wstring value)
	{
		href = value;

	}

	std::wstring S100GML_Association::GetRole() 
	{
		return role;
	}

	void S100GML_Association::SetRole(std::wstring value) 
	{
		role = value;
	}
}