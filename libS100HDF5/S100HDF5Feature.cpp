#include "stdafx.h"
#include "S100HDF5Feature.h"

using namespace S100HDF5;

S100HDF5Feature::S100HDF5Feature()
{
}


S100HDF5Feature::~S100HDF5Feature()
{
	delete _TimeInformation;
	_TimeInformation = nullptr;

	delete[] _Name;
	_Name = nullptr;
}


void S100HDF5Feature::SetDataCodingFormat(DataCodingFormat dataCodingFormat)
{
	_DataCodingFormat = dataCodingFormat;
}


void S100HDF5Feature::SetName(const char *name)
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


void S100HDF5Feature::SetTimeInformation(TimeInformation* timeInformation)
{
	if (!timeInformation)
	{
		return;
	}

	_TimeInformation = timeInformation;
}


DataCodingFormat S100HDF5Feature::GetDataCodingFormat()
{
	return _DataCodingFormat;
}


const char *S100HDF5Feature::GetName()
{
	return _Name;
}


TimeInformation* S100HDF5Feature::GetTimeInformation()
{
	return _TimeInformation;
}