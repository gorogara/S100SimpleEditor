#pragma once
#include "EdtCommand.h"
#include <vector>

class EdtWorkUnit
{
public: 
	EdtCommand cmd;
	std::vector<DWORD_PTR> data;
};