#include "stdafx.h"
#include "RgnData.h"


RgnData::RgnData()
{
	pRgn = nullptr;
	pData = nullptr;
}


RgnData::~RgnData()
{
	if (pRgn)
	{
		pRgn->DeleteObject();
		delete pRgn;
	}

	if (pData)
	{
		delete pData;
	}
}
