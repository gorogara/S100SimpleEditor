#pragma once
class RgnData
{
public:
	RgnData();
	virtual ~RgnData();

	CRgn* pRgn;
	void* pData;
};