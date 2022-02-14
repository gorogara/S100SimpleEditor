#pragma once
#include <list>
#include "SENC_PatternFill.h"
#include "SENC_Hatch.h"

class SENC_HatchFill :
	public SENC_PatternFill
{
public:
	SENC_HatchFill();
	~SENC_HatchFill();
	
public:
	std::list<SENC_Hatch*> hatches;
};

