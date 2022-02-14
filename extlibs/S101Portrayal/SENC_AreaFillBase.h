#pragma once

class PortrayalCatalogue;

class SENC_AreaFillBase
{
public: 
	SENC_AreaFillBase();
	virtual ~SENC_AreaFillBase();

public:  
	int type;

	std::wstring fileTitle; 

public: 
	void SetType(int value);
	int GetType();

	virtual void ChangePallete(PortrayalCatalogue *pc) {};

	void SetFileTitle(std::wstring& value);
	std::wstring GetFileTitle();
};