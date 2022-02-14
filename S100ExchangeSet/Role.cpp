#include "stdafx.h"
#include "Role.h"
namespace Dataset
{
	Role::Role() 
	{

	}
	Role::~Role() 
	{

	}
	void Role::SetCi_roleCode(CI_RoleCode value) 
	{
		ci_roleCode = value;
	}

	CI_RoleCode Role::GetCi_roleCode() 
	{
		return ci_roleCode;
	}

}
