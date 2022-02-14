#pragma once
#include "NamedFeature.h"
#include <string>

class ENC_Feature;
class S57NamedFeature : public NamedFeature
{
public:
	S57NamedFeature();
	virtual ~S57NamedFeature();

public:
	ENC_Feature* m_fe;
	std::wstring m_name;
};
