#pragma once

#include "libS100HDF5.h"

#include <string>

class LIBS100HDF5_API HDF5Wrapper
{
public:
	HDF5Wrapper();
	virtual ~HDF5Wrapper();

	static bool ReadMetadataIntegerAttribute(__int64 id, char* attributeName, int& attributeValue);
	static bool ReadMetadataInteger64Attribute(__int64 id, char* attributeName, __int64& attributeValue);
	static bool ReadMetadataFloatAttribute(__int64 id, char* attributeName, float& attributeValue);
	static bool ReadMetadataDoubleAttribute(__int64 id, char* attributeName, double& attributeValue);
	static bool ReadMetadataStringAttribute(__int64 id, char* attributeName, std::string& attributeValue);
	static bool ReadMetadataVariableLengthStringAttribute(__int64 id, char* attributeName, std::string& attributeValue);
};