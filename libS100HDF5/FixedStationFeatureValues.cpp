#include "stdafx.h"
#include "FixedStationFeatureValues.h"


using namespace S100HDF5;


FixedStationFeatureValues::FixedStationFeatureValues()
{
}


FixedStationFeatureValues::~FixedStationFeatureValues()
{
	for (auto i = _Values.begin(); i != _Values.end(); i++)
	{
		delete *i;
		*i = nullptr;
	}

	delete[] _SubregionName;
	_SubregionName = nullptr;
}


void FixedStationFeatureValues::SetName(const char * subregionName)
{
	delete[] _SubregionName;
	_SubregionName = nullptr;

	auto length = strlen(subregionName);
	if (length > 0)
	{
		_SubregionName = new char[length + 1];
		strcpy_s(_SubregionName, length + 1, subregionName);
	}
}


const char * FixedStationFeatureValues::GetName()
{
	return _SubregionName;
}


void FixedStationFeatureValues::AddFloatValues(FloatValues* floatValues)
{
	_Values.push_back(floatValues);
}


FloatValues* FixedStationFeatureValues::GetFloatValues(int index)
{
	try
	{
		return _Values.at(index);
	}
	catch (std::out_of_range)
	{
		return nullptr;
	}

	return nullptr;
}


int FixedStationFeatureValues::GetFloatValuesCount()
{
	return _Values.size();
}