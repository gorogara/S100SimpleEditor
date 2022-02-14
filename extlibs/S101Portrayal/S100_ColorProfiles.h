#pragma once

#include "stdafx.h"

#include <unordered_map>
#include <string>

#include "..\\extlibs\pugixml\include\pugixml.hpp"

class S100_ColorProfile;
class S100_ColorProfiles
{
public:
	S100_ColorProfiles();
	virtual ~S100_ColorProfiles();

public: 
	std::unordered_map<std::wstring, S100_ColorProfile*> colorProfileFiles;

public: 
	bool ReadColorProfiles(std::wstring path);
	void GetContents(pugi::xml_node& node);
	S100_ColorProfile* GetColorProfile();
};