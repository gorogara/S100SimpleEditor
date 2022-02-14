#pragma once
#include "CI_RoleCode.h"

namespace Dataset
{
	class Role
	{
	public:
		Role(); 
		virtual ~Role();

	private:
		CI_RoleCode ci_roleCode;
	
	public:
		void SetCi_roleCode(CI_RoleCode value);
		CI_RoleCode GetCi_roleCode();
	};
} 