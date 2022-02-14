#pragma once
#include "NamedFeature.h"
#include <string>

class R_FeatureRecord;

class S100NamedFeature : public NamedFeature
{
public:
	S100NamedFeature();
	virtual ~S100NamedFeature();

public:
	R_FeatureRecord* m_fe;
	std::wstring m_name;
};
