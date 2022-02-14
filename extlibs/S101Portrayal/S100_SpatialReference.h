#pragma once
#include <string>
class S100_SpatialReference
{
public:
	S100_SpatialReference();
	virtual ~S100_SpatialReference();
public: 
	std::wstring type;  
	std::wstring reference; 
	std::wstring forward;
public:
	void SetType(std::string &value);
	void SetReference(std::string &value);
	void SetForward(std::string &value);

	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
};

