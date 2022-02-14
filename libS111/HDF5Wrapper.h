#pragma once
class HDF5Wrapper
{
public:
	HDF5Wrapper();
	virtual ~HDF5Wrapper();

	static bool ReadMetadataIntegerAttribute(int id, char* attributeName, int& attributeValue);
	static bool ReadMetadataInteger64Attribute(int id, char* attributeName, __int64& attributeValue);
	static bool ReadMetadataFloatAttribute(int id, char* attributeName, float& attributeValue);
	static bool ReadMetadataDoubleAttribute(int id, char* attributeName, double& attributeValue);
	static bool ReadMetadataStringAttribute(int id, char* attributeName, std::string& attributeValue);
};