#pragma once
#include "EdtUnit.h"
#include "EdtDateType.h"

class EdtVector : public EdtUnit
{
public:
	EdtVector()
	{
		unitType = 1;
		type = E_NULL;
		deleted = false;
	}

public: 
	EdtDateType type;
	bool deleted;
};
