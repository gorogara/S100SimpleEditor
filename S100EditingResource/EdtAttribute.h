#pragma once
#include "EdtUnit.h"

class EdtAttribute : public EdtUnit
{
public:
	EdtAttribute()
	{
		unitType = 2;
		type = 0;
		deleted = false;
	}

public: 
	int type;
	bool deleted;
};
