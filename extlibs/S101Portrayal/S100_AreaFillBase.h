#pragma once
#include <string>
class S100_AreaFillBase
{
public:
	S100_AreaFillBase();
	virtual ~S100_AreaFillBase();
public: 
	int type; 

	std::wstring fileTitle;

public:
	void SetFileTitle(std::wstring& value);
	std::wstring GetFileTitle();
};