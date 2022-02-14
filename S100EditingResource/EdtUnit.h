#pragma once
#include <vector>

class EdtUnit
{
public:
	EdtUnit()
	{
		unitType = 0;
	}
public: 
	int unitType;
	std::vector<DWORD_PTR> data;
};
