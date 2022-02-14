#include "stdafx.h"
#include "FloatValues.h"

using namespace S100HDF5;

FloatValues::FloatValues()
{

}


FloatValues::~FloatValues()
{
	delete[] _Values;
	_Values = nullptr;

	delete[] _Name;
	_Name = nullptr;
}


const char *FloatValues::GetName()
{
	return (const char *)_Name;
}


float* FloatValues::GetValues()
{
	return _Values;
}


int FloatValues::GetValueCount()
{
	return _ValueCount;
}


void FloatValues::SetName(const char *name)
{
	delete[] _Name;
	_Name = nullptr;

	auto length = strlen(name);
	if (length > 0)
	{
		_Name = new char[length + 1];
		strcpy_s(_Name, length + 1, name);
	}
}


void FloatValues::SetValues(float* values, int count)
{
	if (count > 0)
	{
		_Values = new float[count];
		memcpy_s(_Values, sizeof(float) * count, values, sizeof(float) * count);
		_ValueCount = count;
	}
	
}