#include "stdafx.h"
#include "S104.h"

#include <hdf5.h>

S104::S104()
{
	rasterXSize = 0;
	rasterYSize = 0;
	xmin = 0;
	ymin = 0;
	xmax = 0;
	ymax = 0;
}


S104::~S104()
{
	delete s104;
	s104 = nullptr;

	for (auto i = waterLevel.begin(); i != waterLevel.end(); i++)
	{
		delete *i;
		*i = nullptr;
	}

	waterLevel.clear();
}


char* ConvertWCtoC2(wchar_t* str) 
{ 
	char* pStr = nullptr; 
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	if (strSize <= 0)
	{ 
		return nullptr;
	} 
	pStr = new char[strSize]; 
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
	return pStr;
}


wchar_t* ConvertCtoWC2(char* str) 
{ 
	wchar_t* pStr = nullptr; 
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);

	if (strSize <= 0)
	{ 
		return nullptr;
	} 
	pStr = new WCHAR[strSize]; 
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);
	return pStr;
}

bool S104::Open(CString _filePath)
{
	WCHAR cScaleLevel = _filePath.GetAt(_filePath.GetLength() - 18);

	herr_t status = 0;

	char* filePath = ConvertWCtoC2(
		(wchar_t*)std::wstring(_filePath).c_str());

	bool result = Open(filePath);
	delete[] filePath;
	return result;
}

bool S104::Open(char* path)
{
	s104 = new S100HDF5::S104();

	CString filepath = CString(path);
	CFile tmp_file;
	if (tmp_file.Open(filepath, CFile::modeRead | CFile::shareDenyNone)) {
		m_FilePath = tmp_file.GetFilePath();
		m_FileName = tmp_file.GetFileTitle();
		tmp_file.Close();
	}

	return s104->Open(path);

	hid_t file_id = 0;
	file_id = H5Fopen(path, H5F_ACC_RDONLY, H5P_DEFAULT);
	
	bool result = s104->Open(path);

	auto boundingBox = s104->GetMBR();
	xmin = boundingBox.xmin;
	ymin = boundingBox.ymin;
	xmax = boundingBox.xmax;
	ymax = boundingBox.ymax;

	if (auto feature = s104->GetRegularGrid(0))
	{
		if (auto gridInfo = feature->GetRegularGridInformation())
		{
			rasterXSize = gridInfo->GetNumPointLongitudinal();
			rasterYSize = gridInfo->GetNumPointLatitudinal();
			gridCount = rasterXSize * rasterYSize;
		}

		if (auto timeInfo = feature->GetTimeInformation())
		{
			startTime = timeInfo->GetDateTimeOfFirstRecord();
			endTime = timeInfo->GetDateTimeOfLastRecord();
		}
	}

	return result;
}

bool S104::GetIndex(int x, int y, int& index)
{
	if (x < xmin ||
		y < ymin ||
		x > xmax ||
		y > ymax)
	{
		return false;
	}

	double xOffset = x - xmin;
	double yOffset = y - ymin;

	int gridSpacingX = (xmax - xmin) / rasterXSize;
	int gridSpacingY = (ymax - ymin) / rasterYSize;
	int xIndex = 0, yIndex = 0;
	if (x == xmax)
	{
		xIndex = rasterXSize - 1;
	}
	else
	{
		xIndex = xOffset / gridSpacingX;
	}

	if (y == xmax)
	{
		yIndex = rasterYSize - 1;
	}
	else
	{
		yIndex = yOffset / gridSpacingY;
	}

	index = (xIndex * rasterXSize) + yIndex % rasterXSize;
	return true;
}

#pragma warning(disable:4018)
bool S104::Get(int index, int x, int y, double &value)
{
	if (s104)
	{
		auto feature = s104->GetRegularGrid(0);
		auto boundingBox = s104->GetMBR();

		if (feature)
		{
			auto timeInfo = feature->GetTimeInformation();
			if (timeInfo)
			{
				int numTime = timeInfo->GetNumberOfTimes();
				if (index < 0 ||
					index >= numTime ||
					x < (boundingBox.xmin) ||
					y < (boundingBox.ymin) ||
					x > (boundingBox.xmax)||
					y > (boundingBox.ymax))
				{
					return false;
				}

				double xOffset = x - boundingBox.xmin;
				double yOffset = y - boundingBox.ymin;

				int xIndex = 0;
				int yIndex = 0;

				if (auto gridInfo = feature->GetRegularGridInformation())
				{
					float gridSpacingX = gridInfo->GetGridSpacingLongitudinal();
					float gridSpacingY = gridInfo->GetGridSpacingLatitudinal();

					if (x == xmax)
					{
						xIndex = rasterXSize - 1;
					}
					else
					{
						xIndex = xOffset / gridSpacingX;
					}

					if (y == ymax)
					{
						yIndex = rasterYSize - 1;
					}
					else
					{
						yIndex = yOffset / gridSpacingY;
					}

					value = GetFromIndex(index, xIndex, yIndex);

					return true;
				}
			}
		}
	}

	return false;
}


double S104::GetFromIndex(int dataIndex, int xIndex, int yIndex)
{
	double value = 0;

	if (auto feature = s104->GetRegularGrid(0))
	{
		if (auto timeInfo = feature->GetTimeInformation())
		{
			int numTime = timeInfo->GetNumberOfTimes();

			if (xIndex < 0 ||
				yIndex < 0 ||
				xIndex >= rasterXSize ||
				yIndex >= rasterYSize ||
				dataIndex < 0 ||
				dataIndex >= numTime)
			{
				return 0;
			}

			int valueIndex = xIndex + (yIndex * rasterXSize);
			if (auto featureValue = feature->GetRegularGridFeatureValues(dataIndex))
			{
				if (auto floatValue = featureValue->GetFloatValues(0))
				{
					if (auto value = floatValue->GetValues())
					{
						return value[valueIndex];
					}
				}
			}
		}
	}

	return 0;
}


bool HDF5ReadIntegerAttribute(int id, char* attributeName, int& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(id, attributeName);

	if (id_attribute < 0)
	{
		CString str;
		str.Format(_T("Failed to read attribute : %S\n"), attributeName); 
		return false;
	}

	status = H5Aread(id_attribute, H5T_NATIVE_INT, &attributeValue);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aread() : %S\n"), attributeName); 

		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aclose() : %S\n"), attributeName); 
		return false;
	}

	return true;
}


bool HDF5ReadFloat64Attribute(int id, char* attributeName, double& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(id, attributeName);

	if (id_attribute < 0)
	{
		CString str;
		str.Format(_T("Failed to read attribute : %S\n"), attributeName); 
		return false;
	}

	status = H5Aread(id_attribute, H5T_IEEE_F64LE, &attributeValue);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aread() : %S\n"), attributeName); 

		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aclose() : %S\n"), attributeName); 
		return false;
	}

	return true;
}


bool HDF5ReadStringAttribute(int id, char* attributeName, std::string& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(id, attributeName);

	if (id_attribute < 0)
	{
		CString str;
		str.Format(_T("Failed to read attribute : %S\n"), attributeName); 
		return false;
	}

	hid_t type = H5Aget_type(id_attribute);

	if (type < 0)
	{
		CString str;
		str.Format(_T("Failed to get attribute type : %S"), attributeName); 

		H5Aclose(id_attribute);
		return false;
	}

	int size = H5Aget_storage_size(id_attribute);

	char* buf = new char[size + 1];
	memset(buf, 0, sizeof(char) * (size + 1));

	hid_t type_class = H5Tget_class(type);

	if (type_class != H5T_STRING)
	{
		CString str;
		str.Format(_T("Attribute type is not H5T_STRING : %S\n"), attributeName); 

		H5Tclose(type);
		H5Aclose(id_attribute);
		return false;
	}

	hid_t type_mem = H5Tget_native_type(type, H5T_DIR_ASCEND);

	if (type_mem < 0)
	{
		CString str;
		str.Format(_T("Fail to get native type : %S\n"), attributeName); 

		H5Tclose(type);
		H5Aclose(id_attribute);
		return false;
	}

	status = H5Aread(id_attribute, type_mem, buf);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to read attribute : %S\n"), attributeName); 

		H5Tclose(type);
		H5Aclose(id_attribute);
		return false;
	}

	status = H5Tclose(type);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Faield to close type : %S\n"), attributeName); 

		H5Aclose(id_attribute);
		return false;
	}

	attributeValue = buf;
	delete[] buf;

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aread() : %S\n"), attributeName); 

		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aclose() : %S\n"), attributeName); 
		return false;
	}

	return true;
}