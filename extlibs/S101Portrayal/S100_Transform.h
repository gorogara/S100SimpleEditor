#pragma once

#include "S100_Template.h"
#include "S100_Include.h"
#include "SENC_Rule.h"

#include <vector>
class S100_Transform
{
public:
	S100_Transform();
	virtual ~S100_Transform();

public:
	bool isTransfer; 
	std::vector<S100_Template*> templates;
	std::vector<S100_Include*> includes;

public:
	bool ReadRuleFile(std::wstring path);
	void GetContents(MSXML2::IXMLDOMNodeListPtr pNodeList);

	void ExcuteIncludeRuleFile();
	void CopyTo(S100_Transform* toObject);
};

