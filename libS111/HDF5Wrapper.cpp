#include "stdafx.h"
#include "HDF5Wrapper.h"

#include <hdf5.h>


HDF5Wrapper::HDF5Wrapper()
{
}


HDF5Wrapper::~HDF5Wrapper()
{
}


bool HDF5Wrapper::ReadMetadataIntegerAttribute(int id, char* attributeName, int& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(id, attributeName);

	if (id_attribute < 0)
	{
		CString str;
		str.Format(_T("Failed to read attribute : %S\n"), attributeName);
		OutputDebugString(str);
		return false;
	}

	status = H5Aread(id_attribute, H5T_NATIVE_INT, &attributeValue);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aread() : %S\n"), attributeName);
		OutputDebugString(str);

		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aclose() : %S\n"), attributeName);
		OutputDebugString(str);
		return false;
	}

	return true;
}


bool HDF5Wrapper::ReadMetadataInteger64Attribute(int id, char* attributeName, __int64& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(id, attributeName);

	if (id_attribute < 0)
	{
		CString str;
		str.Format(_T("Failed to read attribute : %S\n"), attributeName);
		OutputDebugString(str);
		return false;
	}

	status = H5Aread(id_attribute, H5T_NATIVE_INT64, &attributeValue);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aread() : %S\n"), attributeName);
		OutputDebugString(str);

		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aclose() : %S\n"), attributeName);
		OutputDebugString(str);
		return false;
	}

	return true;
}



bool HDF5Wrapper::ReadMetadataFloatAttribute(int id, char* attributeName, float& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(id, attributeName);

	if (id_attribute < 0)
	{
		CString str;
		str.Format(_T("Failed to read attribute : %S\n"), attributeName);
		OutputDebugString(str);
		return false;
	}

	status = H5Aread(id_attribute, H5T_IEEE_F32LE, &attributeValue);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aread() : %S\n"), attributeName);
		OutputDebugString(str);

		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aclose() : %S\n"), attributeName);
		OutputDebugString(str);
		return false;
	}

	return true;
}


bool HDF5Wrapper::ReadMetadataDoubleAttribute(int id, char* attributeName, double& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(id, attributeName);

	if (id_attribute < 0)
	{
		CString str;
		str.Format(_T("Failed to read attribute : %S\n"), attributeName);
		OutputDebugString(str);
		return false;
	}

	status = H5Aread(id_attribute, H5T_IEEE_F64LE, &attributeValue);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aread() : %S\n"), attributeName);
		OutputDebugString(str);

		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aclose() : %S\n"), attributeName);
		OutputDebugString(str);
		return false;
	}

	return true;
}



bool HDF5Wrapper::ReadMetadataStringAttribute(int id, char* attributeName, std::string& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(id, attributeName);

	if (id_attribute < 0)
	{
		CString str;
		str.Format(_T("Failed to read attribute : %S\n"), attributeName);
		OutputDebugString(str);
		return false;
	}

	hid_t type = H5Aget_type(id_attribute);

	if (type < 0)
	{
		CString str;
		str.Format(_T("Failed to get attribute type : %S"), attributeName);
		OutputDebugString(str);

		H5Aclose(id_attribute);
		return false;
	}

	int size = (int)H5Aget_storage_size(id_attribute);

	char* buf = new char[size + 1];
	memset(buf, 0, sizeof(char) * (size + 1));

	hid_t type_class = H5Tget_class(type);

	if (type_class != H5T_STRING)
	{
		CString str;
		str.Format(_T("Attribute type is not H5T_STRING : %S\n"), attributeName);
		OutputDebugString(str);

		H5Tclose(type);
		H5Aclose(id_attribute);
		return false;
	}

	hid_t type_mem = H5Tget_native_type(type, H5T_DIR_ASCEND);

	if (type_mem < 0)
	{
		CString str;
		str.Format(_T("Fail to get native type : %S\n"), attributeName);
		OutputDebugString(str);

		H5Tclose(type);
		H5Aclose(id_attribute);
		return false;
	}

	status = H5Aread(id_attribute, type_mem, buf);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to read attribute : %S\n"), attributeName);
		OutputDebugString(str);

		H5Tclose(type);
		H5Aclose(id_attribute);
		return false;
	}

	status = H5Tclose(type);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Faield to close type : %S\n"), attributeName);
		OutputDebugString(str);

		H5Aclose(id_attribute);
		return false;
	}

	attributeValue = buf;
	delete[] buf;

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aread() : %S\n"), attributeName);
		OutputDebugString(str);

		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aclose() : %S\n"), attributeName);
		OutputDebugString(str);
		return false;
	}

	return true;
}