#pragma once

class SENC_SpatialReference
{
public: 
	int RCNM = 0;
	unsigned int reference = 0;
	bool bForward = true;

public:
	void SetRCNM(std::wstring& value);
};