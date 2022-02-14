#include "stdafx.h"
#include "HDF5Wrapper.h"

#include <hdf5.h>


HDF5Wrapper::HDF5Wrapper()
{
}


HDF5Wrapper::~HDF5Wrapper()
{
}


bool HDF5Wrapper::ReadMetadataIntegerAttribute(__int64 id, char* attributeName, int& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(id, attributeName);

	if (id_attribute < 0)
	{
		return false;
	}

	status = H5Aread(id_attribute, H5T_NATIVE_INT, &attributeValue);

	if (status != 0)
	{
		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		return false;
	}

	return true;
}


bool HDF5Wrapper::ReadMetadataInteger64Attribute(__int64 id, char* attributeName, __int64& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(id, attributeName);

	if (id_attribute < 0)
	{
		return false;
	}

	status = H5Aread(id_attribute, H5T_NATIVE_INT64, &attributeValue);

	if (status != 0)
	{
		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		return false;
	}

	return true;
}



bool HDF5Wrapper::ReadMetadataFloatAttribute(__int64 id, char* attributeName, float& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(id, attributeName);

	if (id_attribute < 0)
	{
		return false;
	}

	status = H5Aread(id_attribute, H5T_IEEE_F32LE, &attributeValue);

	if (status != 0)
	{
		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		return false;
	}

	return true;
}


bool HDF5Wrapper::ReadMetadataDoubleAttribute(__int64 id, char* attributeName, double& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(id, attributeName);

	if (id_attribute < 0)
	{
		return false;
	}

	status = H5Aread(id_attribute, H5T_IEEE_F64LE, &attributeValue);

	if (status != 0)
	{
		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		return false;
	}

	return true;
}



bool HDF5Wrapper::ReadMetadataStringAttribute(__int64 id, char* attributeName, std::string& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(id, attributeName);

	if (id_attribute < 0)
	{
		return false;
	}

	hid_t type = H5Aget_type(id_attribute);

	if (type < 0)
	{
		H5Aclose(id_attribute);
		return false;
	}

	auto size = H5Aget_storage_size(id_attribute);

	char* buf = new char[(unsigned int)(size + 1)];
	memset(buf, 0, (size_t)(sizeof(char) * (size + 1)));

	hid_t type_class = H5Tget_class(type);

	if (type_class != H5T_STRING)
	{
		H5Tclose(type);
		H5Aclose(id_attribute);
		return false;
	}

	hid_t type_mem = H5Tget_native_type(type, H5T_DIR_ASCEND);

	if (type_mem < 0)
	{
		H5Tclose(type);
		H5Aclose(id_attribute);
		return false;
	}

	status = H5Aread(id_attribute, type_mem, buf);

	if (status != 0)
	{
		H5Tclose(type);
		H5Aclose(id_attribute);
		return false;
	}

	status = H5Tclose(type);

	if (status != 0)
	{
		H5Aclose(id_attribute);
		return false;
	}

	attributeValue = buf;
	delete[] buf;

	if (status != 0)
	{
		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		return false;
	}

	return true;
}


bool HDF5Wrapper::ReadMetadataVariableLengthStringAttribute(__int64 id, char* attributeName, std::string& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(id, attributeName);

	if (id_attribute < 0)
	{
		return false;
	}

	hid_t type = H5Aget_type(id_attribute);

	if (type < 0)
	{
		H5Aclose(id_attribute);
		return false;
	}

	hid_t cstype = H5Tcopy(H5T_C_S1);

	H5Tset_size(type, H5T_VARIABLE);

	char* vbuf = nullptr;

	status = H5Aread(id_attribute, type, &vbuf);

	if (status < 0)
	{
		delete[] vbuf;
		H5Tclose(type);
		H5Aclose(id_attribute);
		return false;
	}

	status = H5Tclose(type);

	if (status != 0)
	{
		H5Aclose(id_attribute);
		return false;
	}

	attributeValue = vbuf; 

	if (status != 0)
	{
		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		return false;
	}

	return true;
}