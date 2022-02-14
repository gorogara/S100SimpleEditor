#pragma once

#include <map>
#include "AreaPatternBitmap.h"

#include "CStringCompareNoCaseLessThan.h"

class AreaFillInfo
{
public:
	AreaFillInfo();
	virtual ~AreaFillInfo();

	std::map<CString, AreaPatternBitmap*, CStringCompareNoCaseLessThan> patternMap;
};