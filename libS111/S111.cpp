#include "stdafx.h"
#include "S111.h"

#include "..\\libS100HDF5\\HDF5Wrapper.h"

#include <hdf5.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable:4305)
D2D1::ColorF S111::color[S111_STEP_COUNT+1] = {
	D2D1::ColorF(118 / 255.0, 82 / 255.0, 226 / 255.0),
	D2D1::ColorF(72 / 255.0, 152 / 255.0, 211 / 255.0),
	D2D1::ColorF(97 / 255.0, 203 / 255.0, 229 / 255.0),
	D2D1::ColorF(109 / 255.0, 188 / 255.0, 69 / 255.0),
	D2D1::ColorF(180 / 255.0, 220 / 255.0, 0 / 255.0),
	D2D1::ColorF(205 / 255.0, 193 / 255.0, 0 / 255.0),
	D2D1::ColorF(248 / 255.0, 167 / 255.0, 24 / 255.0),
	D2D1::ColorF(247 / 255.0, 162 / 255.0, 157 / 255.0),
	D2D1::ColorF(255 / 255.0, 30 / 255.0, 30 / 255.0),
	D2D1::ColorF(0 / 255.0, 0 / 255.0, 0 / 255.0)
};

float S111::SPEED_RANGE[S111_STEP_COUNT] =
{ 
	0,
	0.49,
	0.99,
	1.99,
	2.99,
	4.99,
	6.99,
	9.99,
	12.99
};

ClibS111App* S111::app = nullptr;
 
S111::S111()
	: x(nullptr)
	, y(nullptr)
	, curNumberOfTimes(0)
{
	type = 0;
}


#pragma warning(disable:4018)
S111::~S111()
{
	if (x)
		delete[] x;

	if (y)
		delete[] y;

	for (int i = 0; i < speed.size(); i++)
	{
		if (speed.at(i))
		{
			delete[] speed.at(i);
			speed.at(i) = nullptr;
		}

	}

	speed.clear();

	for (int i = 0; i < direction.size(); i++)
	{
		if (direction.at(i))
		{
			delete[] direction.at(i);
			direction.at(i) = nullptr;
		}
	}

	direction.clear();

	delete _S111;
}


char* ConvertWCtoC(wchar_t* str) 
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


wchar_t* ConvertCtoWC(char* str) 
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

bool S111::Open(CString _filePath)
{                 

	CFile tmp_file;
	if (tmp_file.Open(_filePath, CFile::modeRead | CFile::shareDenyNone)) {
		m_FilePath = tmp_file.GetFilePath();
		m_FileName = tmp_file.GetFileTitle();
		tmp_file.Close();
	}
	herr_t status = 0;

	const char* filePath = ConvertWCtoC(
		(wchar_t*)std::wstring(_filePath).c_str());

	hid_t file_id = H5Fopen(filePath, H5F_ACC_RDWR, H5P_DEFAULT);
	delete[] filePath;

	if (file_id < 0)
	{ 
		return false;
	}


	if (!Open0p0p12(file_id))
	{
		return false;
	}                            

	status = H5Fclose(file_id);

	return true;
}

bool S111::Open0p0p12(__int64 file_id)
{
	hid_t surfaceCurrent_id = H5Gopen(file_id, "SurfaceCurrent", H5P_DEFAULT);

	if (surfaceCurrent_id < 0)
	{
		OutputDebugString(_T("Failed to open SurfaceCurrent Group\n"));
		return false;
	}

	__int64 dataCodingFormat = 0;
	HDF5Wrapper::ReadMetadataInteger64Attribute(surfaceCurrent_id, "dataCodingFormat", dataCodingFormat);
	metadata.dataCodingFormat = (DataCodingFormat)dataCodingFormat;

	ReadSurfaceCurrent01Attribute(file_id);

	switch (dataCodingFormat)
	{
	case 1:
		ReadTimeSeries0p0p12(file_id);
		break;
	case 2:
		ReadRegularGrid0p0p12(file_id);
		break;
	case 3:
		ReadIrregularGrid0p0p12(file_id);
		break;
	case 4:
		ReadLagrangianDrifter0p0p12(file_id);
		break;
	default:
		OutputDebugString(_T("Unsupported data coding format\n"));
	}

	ReadMetadata0p0p12(file_id);

	H5Gclose(surfaceCurrent_id);

	return true;
}

bool S111::ReadSurfaceCurrent01Attribute(__int64 file_id)
{
	hid_t surfaceCurrent01_id = H5Gopen(file_id, "SurfaceCurrent/SurfaceCurrent.01", H5P_DEFAULT);

	if (surfaceCurrent01_id < 0)
	{
		OutputDebugString(_T("Failed to open SurfaceCurrent Group\n"));
		return false;
	}

	__int64 numberOfStations = 0;
	HDF5Wrapper::ReadMetadataInteger64Attribute(surfaceCurrent01_id, "numberOfStations", numberOfStations);
	metadata.numberOfStations = (int)numberOfStations;

	__int64 numberOfNodes = 0;
	HDF5Wrapper::ReadMetadataInteger64Attribute(surfaceCurrent01_id, "numberOfNodes", numberOfNodes);
	metadata.numberOfNodes = (int)numberOfNodes;

	__int64 numberOfTimes = 0;
	HDF5Wrapper::ReadMetadataInteger64Attribute(surfaceCurrent01_id, "numberOfTimes", numberOfTimes);
	metadata.numberOfTimes = (int)numberOfTimes;

	__int64 numPointsLatitudinal = 0;
	HDF5Wrapper::ReadMetadataInteger64Attribute(surfaceCurrent01_id, "numPointsLatitudinal", numPointsLatitudinal);
	metadata.numberPointsLat = (int)numPointsLatitudinal;

	__int64 numPointsLongitudinal = 0;
	HDF5Wrapper::ReadMetadataInteger64Attribute(surfaceCurrent01_id, "numPointsLongitudinal", numPointsLongitudinal);
	metadata.numberPointsLong = (int)numPointsLongitudinal;

	double gridOriginLatitude = 0;
	HDF5Wrapper::ReadMetadataDoubleAttribute(surfaceCurrent01_id, "gridOriginLatitude", gridOriginLatitude);
	metadata.gridOriginLatitude = (float)gridOriginLatitude;

	double gridOriginLongitude = 0;
	HDF5Wrapper::ReadMetadataDoubleAttribute(surfaceCurrent01_id, "gridOriginLongitude", gridOriginLongitude);
	metadata.gridOriginLongitude = (float)gridOriginLongitude;

	double gridSpacingLatitudinal = 0;
	HDF5Wrapper::ReadMetadataDoubleAttribute(surfaceCurrent01_id, "gridSpacingLatitudinal", gridSpacingLatitudinal);
	metadata.gridSpacingLatitudinal = (float)gridSpacingLatitudinal;

	double gridSpacingLongitudinal = 0;
	HDF5Wrapper::ReadMetadataDoubleAttribute(surfaceCurrent01_id, "gridSpacingLongitudinal", gridSpacingLongitudinal);
	metadata.gridSpacingLongitudinal = (float)gridSpacingLongitudinal;

	if (metadata.numberOfNodes == 0)
	{
		metadata.numberOfNodes = metadata.numberPointsLat * metadata.numberPointsLong;
	}

	return true;
}



struct positioning {
	double lon = 0;
	double lat = 0;
};


bool S111::ReadData0p0p12(__int64 file_id, int groupNum, float*& dir, float*&spd)
{
	CString wstr;
	wstr.Format(_T("SurfaceCurrent/SurfaceCurrent.01/Group_%03d/values"), groupNum);

	char* path = ConvertWCtoC((wchar_t*)std::wstring(wstr).c_str());

	hid_t id_dataset = H5Dopen2(file_id, path, H5P_DEFAULT);
	delete[] path;

	struct SpeedDirection {
		float direction = 0;
		float speed = 0;
	};

	if (this->metadata.dataCodingFormat == DataCodingFormat::RegularlyGriddedArrays)
	{
		int size = (int)H5Dget_storage_size(id_dataset) / sizeof(SpeedDirection);

		dir = new float[size];
		memset(dir, 0, sizeof(float)* size);

		spd = new float[size];
		memset(spd, 0, sizeof(float)* size);

		SpeedDirection* speedDirection = new SpeedDirection[size];

		hid_t spdDirType = H5Tcreate(H5T_COMPOUND, sizeof(SpeedDirection));
		H5Tinsert(spdDirType, "surfaceCurrentDirection", 0, H5T_IEEE_F32LE);
		H5Tinsert(spdDirType, "surfaceCurrentSpeed", sizeof(float), H5T_IEEE_F32LE);

		H5Dread(id_dataset, spdDirType, H5S_ALL, H5S_ALL, H5P_DEFAULT, speedDirection);

		for (int i = 0; i < size; i++)
		{
			dir[i] = speedDirection[i].direction;
			spd[i] = speedDirection[i].speed;
		}

		H5Tclose(spdDirType);

		delete[] speedDirection;
	}
	else if (this->metadata.dataCodingFormat == DataCodingFormat::TimeSeriesAtStations)
	{
		int size = (int)H5Dget_storage_size(id_dataset) / sizeof(double);

		double *buf = new double[size];

		H5Dread(id_dataset, H5T_IEEE_F64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);

		dir = new float[size / 2];
		memset(dir, 0, sizeof(float)* (size / 2));

		spd = new float[size / 2];
		memset(spd, 0, sizeof(float)* (size / 2));

		for (int i = 0; i < size / 2; i++)
		{
			spd[i] = buf[i * 2];
			dir[i] = buf[(i * 2) + 1];
		}

		delete[] buf;
	}

	H5Dclose(id_dataset);

	return true;
}

bool S111::ReadLagrangianDrifter0p0p12(__int64 file_id)
{
	hid_t surfaceCurrent01_id = H5Gopen(file_id, "SurfaceCurrent/SurfaceCurrent.01", H5P_DEFAULT);

	if (surfaceCurrent01_id < 0)
	{
		OutputDebugString(_T("Failed to open SurfaceCurrent Group\n"));
		return false;
	}

	int size = 0;

	ReadXY0p0p12(file_id, x, y, size);    

	float* dir = nullptr;
	float* spd = nullptr;
	ReadData0p0p12(file_id, 1, dir, spd);
	speed.push_back(spd);
	direction.push_back(dir);

	return true;
}

bool S111::ReadIrregularGrid0p0p12(__int64 file_id)
{
	hid_t surfaceCurrent01_id = H5Gopen(file_id, "SurfaceCurrent/SurfaceCurrent.01", H5P_DEFAULT);

	if (surfaceCurrent01_id < 0)
	{
		OutputDebugString(_T("Failed to open SurfaceCurrent Group\n"));
		return false;
	}

	int size = 0;

	ReadXY0p0p12(file_id, x, y, size);    

	for (int i = 0; i < metadata.numberOfTimes; i++)
	{
		float* dir = nullptr;
		float* spd = nullptr;
		ReadData0p0p12(file_id, i + 1, dir, spd);
		speed.push_back(spd);
		direction.push_back(dir);
	}

	return true;
}
bool S111::ReadRegularGrid0p0p12(__int64 file_id)
{
	hid_t surfaceCurrent01_id = H5Gopen(file_id, "SurfaceCurrent/SurfaceCurrent.01", H5P_DEFAULT);

	if (surfaceCurrent01_id < 0)
	{
		OutputDebugString(_T("Failed to open SurfaceCurrent Group\n"));
		return false;
	}

	for (int i = 0; i < metadata.numberOfTimes; i++)
	{
		float* dir = nullptr;
		float* spd = nullptr;
		ReadData0p0p12(file_id, i + 1, dir, spd);
		speed.push_back(spd);
		direction.push_back(dir);
	}


	return true;
}



bool S111::ReadTimeSeries0p0p12(__int64 file_id)
{
	hid_t surfaceCurrent01_id = H5Gopen(file_id, "SurfaceCurrent/SurfaceCurrent.01", H5P_DEFAULT);

	if (surfaceCurrent01_id < 0)
	{
		OutputDebugString(_T("Failed to open SurfaceCurrent Group\n"));
		return false;
	}

	int size = 0;

	ReadXY0p0p12(file_id, x, y, size);    

	for (int i = 0; i < metadata.numberOfStations; i++)
	{
		char group_NNN_name[100];
		sprintf_s(group_NNN_name, 100, "SurfaceCurrent/SurfaceCurrent.01/Group_%03d", i + 1);
		hid_t group_NNN_id = H5Gopen(file_id, group_NNN_name, H5P_DEFAULT);

		if (group_NNN_id < 0)
		{
			return false;
		}

		std::string name;
		HDF5Wrapper::ReadMetadataVariableLengthStringAttribute(group_NNN_id, "nameSubregion", name);
		CString cName(name.c_str());
		stationNames.push_back(cName);
		H5Gclose(group_NNN_id);

		float* dir = nullptr;
		float* spd = nullptr;
		ReadData0p0p12(file_id, i + 1, dir, spd);
		speed.push_back(spd);
		direction.push_back(dir);
	}

	return true;
}

bool S111::ReadXY0p0p12(__int64 file_id, double*& bufX, double*& bufY, int& size)
{


	hid_t status = 0;

	char* path = "/SurfaceCurrent/SurfaceCurrent.01/Positioning/geometryValues";

	hid_t id_dataset = H5Dopen2(file_id, path, H5P_DEFAULT);

	if (id_dataset < 0)
	{
		CString str;
		str.Format(_T("Failed to open dataset XY\n"));
		OutputDebugString(str);
		return false;
	}

	switch ((int)metadata.dataCodingFormat)
	{
	case 1:
		size = metadata.numberOfStations;
		break;
	case 3:
		size = metadata.numberOfNodes;
		break;
	case 4:
		size = metadata.numberOfTimes;
		break;
	default:
		size = 0;
	}

	if (this->metadata.dataCodingFormat == DataCodingFormat::RegularlyGriddedArrays)
	{
		bufX = new double[size];
		bufY = new double[size];
		memset(bufX, 0, sizeof(double)* size);
		memset(bufY, 0, sizeof(double)* size);

		positioning* tmpBuf = new positioning[size];
		memset(tmpBuf, 0, sizeof(positioning)* size);

		hid_t positioningType = H5Tcreate(H5T_COMPOUND, sizeof(positioning));
		status = H5Tinsert(positioningType, "Longitude", 0, H5T_IEEE_F64LE);
		status = H5Tinsert(positioningType, "Latitude", sizeof(double), H5T_IEEE_F64LE);

		status = H5Dread(id_dataset, positioningType, H5S_ALL, H5S_ALL, H5P_DEFAULT, tmpBuf);

		for (int i = 0; i < size; i++)
		{
			bufX[i] = tmpBuf[i].lon;
			bufY[i] = tmpBuf[i].lat;
		}

		delete[] tmpBuf;

		if (status < 0)
		{
			OutputDebugString(_T("Failed to read dataset\n"));
			return false;
		}
	}
	else if (this->metadata.dataCodingFormat == DataCodingFormat::TimeSeriesAtStations)
	{
		bufX = new double[size];
		bufY = new double[size];
		memset(bufX, 0, sizeof(double)* size);
		memset(bufY, 0, sizeof(double)* size);

		double *buf = new double[size * 2];
		status = H5Dread(id_dataset, H5T_IEEE_F64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);

		for (int i = 0; i < size; i++)
		{
			bufX[i] = buf[2 * i];
			bufY[i] = buf[(2 * i) + 1];
		}
	}

	status = H5Dclose(id_dataset);

	if (status != 0)
	{
		OutputDebugString(_T("Failed to close dataset\n"));
		return false;
	}

	return true;
}



bool S111::ReadMetadata0p0p12(__int64 file_id)
{
	hid_t surfaceCurrent01_id = H5Gopen(file_id, "/SurfaceCurrent/SurfaceCurrent.01", H5P_DEFAULT);

	if (surfaceCurrent01_id < 0)
	{
		OutputDebugString(_T("Faield to open SurfaceCurrent0.1 Group\n"));
		return false;
	}
	
	std::string dateTimeOfFirstRecord;
	std::string dateTimeOfLastRecord;
	HDF5Wrapper::ReadMetadataStringAttribute(surfaceCurrent01_id, "dateTimeOfFirstRecord", dateTimeOfFirstRecord);
	HDF5Wrapper::ReadMetadataStringAttribute(surfaceCurrent01_id, "dateTimeOfLastRecord", dateTimeOfLastRecord);

	__int64 timeRecordInterval = 0;
	HDF5Wrapper::ReadMetadataInteger64Attribute(surfaceCurrent01_id, "timeRecordInterval", timeRecordInterval);

	metadata.dateTimeOfFirstRecord = dateTimeOfFirstRecord;
	metadata.dateTimeOfLastRecord = dateTimeOfLastRecord;
	metadata.timeRecordInterval = (int)timeRecordInterval;

	SetTime();

	return true;
}


void S111::Draw(int index, ID2D1RenderTarget* pRenderTarget, ID2D1SolidColorBrush* pBrush, Gdiplus::Rect rectF,
	double S111_SREF, double S111_LREF, double S111_SHIGH, double S111_Alpha)
{
	declutter_rect.clear();

	curNumberOfTimes = index;
	pBrush->SetOpacity(S111_Alpha);

	switch (metadata.dataCodingFormat)
	{
	case 1:
		DrawTimeSeries(pRenderTarget);
		break;
	case 2:
		DrawRegularGrid(pRenderTarget);
		break;
	case 3: 
		break;
	case 4:
		DrawLagrangianDrifter(pRenderTarget);
		break;
	default:
		break;
	}

	return;
}


void S111::DrawArrow(ID2D1RenderTarget* pRenderTarget, ID2D1SolidColorBrush* pBrush,
	double S111_SREF, double S111_LREF, double S111_SHIGH, double S111_Alpha,
	int _x, int _y, float _spd, float _dir)
{
	if (_spd <= S111::SPEED_RANGE[1])
		pBrush->SetColor(color[0]);
	else if (_spd <= S111::SPEED_RANGE[2])
		pBrush->SetColor(color[1]);
	else if (_spd <= S111::SPEED_RANGE[3])
		pBrush->SetColor(color[2]);
	else if (_spd <= S111::SPEED_RANGE[4])
		pBrush->SetColor(color[3]);
	else if (_spd <= S111::SPEED_RANGE[5])
		pBrush->SetColor(color[4]);
	else if (_spd <= S111::SPEED_RANGE[6])
		pBrush->SetColor(color[5]);
	else if (_spd <= S111::SPEED_RANGE[7])
		pBrush->SetColor(color[6]);
	else if (_spd <= S111::SPEED_RANGE[8])
		pBrush->SetColor(color[7]);
	else
		pBrush->SetColor(color[8]);


	double scaleFactor = 1;
	if (_spd > S111_SHIGH)
	{
		scaleFactor = S111_SHIGH / S111_SREF;
	}
	else
	{
		scaleFactor = _spd / S111_SREF;
	} 
	D2D1_RECT_F rect_arrow;
	app->m_pS111ArrowGeometry->GetBounds(nullptr, &rect_arrow); 
	rect_arrow.left *= scaleFactor;
	rect_arrow.top *= scaleFactor;
	rect_arrow.bottom *= scaleFactor;
	rect_arrow.right *= scaleFactor;                            

	const D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(_dir);
	const D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Translation(_x, _y);
	const D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(
		D2D1::SizeF(scaleFactor, scaleFactor), D2D1::Point2F(_x, _y));

	libS111::S111NumericalInfo s111NumericalInfo;
	s111NumericalInfo.speed = _spd;
	s111NumericalInfo.direction = _dir;
	s111NumericalInfo.matrix = rot * trans * scale;     

	pRenderTarget->SetTransform(rot * trans * scale);
	pRenderTarget->FillGeometry(
		app->m_pS111ArrowGeometry,
		pBrush);

	
	pBrush->SetColor(color[S111_STEP_COUNT]);

	pRenderTarget->DrawGeometry(
		app->m_pS111ArrowGeometry,
		pBrush, 2);
	
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}


bool S111::ReadData(__int64 file_id)
{
	int size = 0;

	int cntGroup = GetGroupCnt(file_id);
	if ((metadata.dataCodingFormat == 1) ||
		(metadata.dataCodingFormat == 3) ||
		(metadata.dataCodingFormat == 4))
		cntGroup--;

	for (int i = 1; i <= cntGroup; i++)
	{
		float* dir = nullptr;
		float* spd = nullptr;

		ReadData(file_id, i, dir, size, true);
		ReadData(file_id, i, spd, size, false);

		Data tData;

		for (int j = 0; j < size; j++)
		{
			DataPerPoint dataPerPoint;
			dataPerPoint.dir = dir[j];
			dataPerPoint.spd = spd[j];

			tData.dataPerPoint.push_back(dataPerPoint);
		}

		data.push_back(tData);

		speed.push_back(spd);
		direction.push_back(dir);
	}

	return true;
}


bool S111::ReadData(__int64 file_id, int groupNum, float*& buf, int& size, bool isDir)
{
	CString wstr;
	wstr.Format(_T("/Group %d/"), groupNum);

	if (isDir)
	{
		wstr.Append(_T("Direction"));
	}
	else
	{
		wstr.Append(_T("Speed"));
	}

	char* path = ConvertWCtoC((wchar_t*)std::wstring(wstr).c_str());

	hid_t id_dataset = H5Dopen2(file_id, path, H5P_DEFAULT);
	delete[] path;

	size = (int)H5Dget_storage_size(id_dataset) / sizeof(float);

	buf = new float[size];
	memset(buf, 0, sizeof(float) * size);

	H5Dread(id_dataset, H5T_IEEE_F32LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);

	H5Dclose(id_dataset);

	return true;
}


int S111::GetGroupCnt(__int64 file_id)
{
	hid_t id_root = H5Gopen2(file_id, "/", H5P_DEFAULT);

	hsize_t cnt = 0;
	H5Gget_num_objs(id_root, &cnt);

	return (int)cnt;
}



bool S111::ReadX(__int64 file_id, float*& buf, int& size)
{
	ReadXYsegment(file_id, buf, size, true);

	return true;
}


bool S111::ReadY(__int64 file_id, float*& buf, int& size)
{
	ReadXYsegment(file_id, buf, size, false);

	return true;
}


bool S111::ReadXYsegment(__int64 file_id, float*& buf, int& size, bool isX)
{
	hid_t status = 0;

	char* path = nullptr;

	if (isX)
	{
		path = "/Group XY/X";
	}
	else
	{
		path = "/Group XY/Y";
	}

	hid_t id_dataset = H5Dopen2(file_id, path, H5P_DEFAULT);

	if (id_dataset < 0)
	{
		CString str;
		str.Format(_T("Failed to open dataset XY\n")); 
		return false;
	}

	size = (int)H5Dget_storage_size(id_dataset) / sizeof(float);

	buf = new float[size];
	memset(buf, 0, sizeof(float) * size);

	status = H5Dread(id_dataset, H5T_IEEE_F32LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);

	if (status < 0)
	{ 
		return false;
	}

	status = H5Dclose(id_dataset);

	if (status != 0)
	{ 
		return false;
	}

	return true;
}


bool S111::ReadXY(__int64 file_id)
{
	float* bufX = nullptr;
	float* bufY = nullptr;
	int sizeX = 0;
	int sizeY = 0;

	ReadX(file_id, bufX, sizeX);
	ReadY(file_id, bufY, sizeY);

	x = new double[sizeX];
	y = new double[sizeY];

	for (int i = 0; i < sizeX; i++)
	{
		double x = bufX[i];
		double y = bufY[i];
		PointXY pt;
		pt.x = x;
		pt.y = y;
		points.push_back(pt);
		this->x[i] = pt.x;
		this->y[i] = pt.y;
	}

	delete[] bufX;
	delete[] bufY;

	return true;
}


bool S111::SetTime()
{
	std::string firstTime = metadata.dateTimeOfFirstRecord;
	std::string lastTime = metadata.dateTimeOfLastRecord;
	int interval = metadata.timeRecordInterval;
	int num = metadata.numberOfTimes;

	SYSTEMTIME sTime = { 0, };
	SYSTEMTIME eTime = { 0, };

	try
	{
		sTime.wYear = std::stoi(firstTime.substr(0, 4));
		sTime.wMonth = std::stoi(firstTime.substr(4, 2));
		sTime.wDay = std::stoi(firstTime.substr(6, 2));
		sTime.wHour = std::stoi(firstTime.substr(9, 2));
		sTime.wMinute = std::stoi(firstTime.substr(11, 2));
		sTime.wSecond = std::stoi(firstTime.substr(13, 2));

		eTime.wYear = std::stoi(lastTime.substr(0, 4));
		eTime.wMonth = std::stoi(lastTime.substr(4, 2));
		eTime.wDay = std::stoi(lastTime.substr(6, 2));
		eTime.wHour = std::stoi(lastTime.substr(9, 2));
		eTime.wMinute = std::stoi(lastTime.substr(11, 2));
		eTime.wSecond = std::stoi(lastTime.substr(13, 2));
	}
	catch (std::invalid_argument)
	{ 
		sTime.wYear = 2018;
		sTime.wMonth = 11;
		sTime.wDay = 15;
		sTime.wHour = 00;
		sTime.wMinute = 00;
		sTime.wSecond = 00;

		int total = interval * (num - 1);

		int day = total / (60 * 60 * 24);
		total = total % (60 * 60 * 24);
		int hour = total / (60 * 60);
		total = total % (60 * 60);
		int min = total / (60);
		int sec = total % 60;

		eTime.wYear = sTime.wYear;
		eTime.wMonth = sTime.wMonth;
		eTime.wDay = sTime.wDay + day;
		eTime.wHour = sTime.wHour + hour;
		eTime.wMinute = sTime.wMinute + min;
		eTime.wSecond = sTime.wSecond + sec;
	}

	CTime sCTime(sTime.wYear, sTime.wMonth, sTime.wDay,
		sTime.wHour, sTime.wMinute, sTime.wSecond);
	CTime eCTime(eTime.wYear, eTime.wMonth, eTime.wDay,
		eTime.wHour, eTime.wMinute, eTime.wSecond);

	sCTime.GetAsSystemTime(sTime);
	eCTime.GetAsSystemTime(eTime);

	SYSTEMTIME tTime;
	CTime tCTime;
	times.push_back(sTime);

	while (true)
	{
		tCTime = sCTime + CTimeSpan(0, 0, 0, interval);

		if (tCTime > eCTime)
		{
			break;
		}
		else
		{
			tCTime.GetAsSystemTime(tTime);
			times.push_back(tTime);
			sCTime = tCTime;
		}
	}

	CTime lastCTime(times.back());

	if (lastCTime != eCTime)
	{
		eCTime.GetAsSystemTime(tTime);
		times.push_back(tTime);
	}

	if (metadata.numberOfTimes != times.size())
	{ 
		return false;
	}

	return true;
}


int S111::GetNumberOfTimes()
{
	return metadata.numberOfTimes;
}


SYSTEMTIME S111::GetSystemTime(int index)
{
	SYSTEMTIME systemTime;

	try
	{
		systemTime = times.at(index);
	}
	catch (std::out_of_range)
	{
		memset(&systemTime, 0, sizeof(SYSTEMTIME));
	}

	return systemTime;
}


void S111::DrawTimeSeries(ID2D1RenderTarget* pRenderTarget)
{
	for (int i = 0; i < metadata.numberOfStations; i++)
	{
		if (speed.at(curNumberOfTimes)[i] < 0.1)
			continue;       
	}
}


int S111::GetNumberOfNodesForAllTypes()
{
	int cnt = 0;

	switch (metadata.dataCodingFormat)
	{
	case TimeSeriesAtStations:
		cnt = metadata.numberOfStations;
		break;
	case RegularlyGriddedArrays:
		cnt = metadata.numberPointsLong * metadata.numberPointsLat;
		break;
	case IrregularlyGriddedArrays:
		cnt = metadata.numberOfNodes;
		break;
	case LagrangianDrifters:
		cnt = metadata.numberOfTimes;
		break;
	default:
		;
	}

	return cnt;
}


void S111::GetDirectionAndSpeedFromRegularlyGrid(int _indexTime, int _indexPoint, double& _direction, double& _speed)
{
	int cntGridPoints = metadata.numberPointsLat * metadata.numberPointsLong;

	int curIndex = 0;

	for (int i = 0; i < metadata.numberPointsLat; i++)
	{
		for (int j = 0; j < metadata.numberPointsLong; j++)
		{
			if (curIndex == _indexPoint)
			{  

				_speed = speed.at(_indexTime)[(metadata.numberPointsLong * i) + j];
				_direction = direction.at(_indexTime)[(metadata.numberPointsLong * i) + j];
				return;
			}
			else
			{
				curIndex++;
			}
		} 
	}
	curIndex = 0;
	return;
}


void S111::GetDirectionAndSpeedFromIrregularyGrid(int _indexTime, int _indexPoint, double& _direction, double& _speed)
{
	_direction = direction.at(_indexTime)[_indexPoint];
	_speed = speed.at(_indexTime)[_indexPoint];
}


void S111::GetDirectionAndSpeedFromLagrangianDrifters(int _indexTime, int _indexPoint, double& _direction, double& _speed)
{
	_direction = direction.at(0)[_indexPoint];
	_speed = speed.at(0)[_indexPoint];
}


void S111::GetDirectionAndSpeed(int _indexTime, int _indexPoint, double& _direction, double& _speed)
{
	if (_indexTime < 0 || _indexTime >= GetNumberOfTimes())
	{
		return;
	}

	int cntNodes = GetNumberOfNodesForAllTypes();

	if (_indexPoint < 0 || _indexPoint >= cntNodes)
	{
		return;
	}

	switch (metadata.dataCodingFormat)
	{
	case TimeSeriesAtStations:
		GetDirectionAndSpeedFromTimeSeries(_indexTime, _indexPoint, _direction, _speed);
		break;
	case RegularlyGriddedArrays:
		GetDirectionAndSpeedFromRegularlyGrid(_indexTime, _indexPoint, _direction, _speed);
		break;
	case IrregularlyGriddedArrays:
		GetDirectionAndSpeedFromIrregularyGrid(_indexTime, _indexPoint, _direction, _speed);
		break;
	case LagrangianDrifters:
		GetDirectionAndSpeedFromLagrangianDrifters(_indexTime, _indexPoint, _direction, _speed);
		break;
	default:
		;
	}
}


void S111::GetDirectionAndSpeedFromTimeSeries(int _indexTime, int _indexPoint, double& _direction, double& _speed)
{
	_speed = speed.at(_indexTime)[_indexPoint];
	_direction = direction.at(_indexTime)[_indexPoint];
}


void S111::GetXYFromTimeSeries(int _index, double& _x, double& _y)
{
	_x = x[_index];
	_y = y[_index];
}


void S111::GetXYFromRegularlyGrid(int _index, double& _x, double& _y)
{
	int cntGridPoints = metadata.numberPointsLat * metadata.numberPointsLong;

	double xOrigin = metadata.gridOriginLongitude;
	double yOrigin = metadata.gridOriginLatitude ;

	double xSpacing = metadata.gridSpacingLongitudinal ;
	double ySpacing = metadata.gridSpacingLatitudinal ;         

	int curIndex = 0;

	for (int i = 0; i < metadata.numberPointsLat; i++)
	{
		for (int j = 0; j < metadata.numberPointsLong; j++)
		{
			if (curIndex == _index)
			{
				_x = xOrigin + (xSpacing * j);
				_y = yOrigin + (ySpacing * i);
				return;
			}
			else
			{
				curIndex++;
			}
		}
	}
}


void S111::GetXYFromIrregularyGrid(int _index, double& _x, double& _y)
{
	_x = x[_index];
	_y = y[_index];
}


void S111::GetXYFromLagrangianDrifters(int _index, double& _x, double& _y)
{
	_x = x[_index];
	_y = y[_index];
}


void S111::GetXY(int _index, double& _x, double& _y)
{
	int cntNodes = GetNumberOfNodesForAllTypes();

	if (_index < 0 || _index >= cntNodes)
	{
		return;
	}

	double retX = 0;
	double retY = 0;

	switch (metadata.dataCodingFormat)
	{
	case TimeSeriesAtStations:
		GetXYFromTimeSeries(_index, retX, retY);
		break;
	case RegularlyGriddedArrays:
		GetXYFromRegularlyGrid(_index, retX, retY);
		break;
	case IrregularlyGriddedArrays:
		GetXYFromIrregularyGrid(_index, retX, retY);
		break;
	case LagrangianDrifters:
		GetXYFromLagrangianDrifters(_index, retX, retY);
		break;
	default:
		;
	}

	_x = retX;
	_y = retY;
}


void S111::DrawRegularGrid(ID2D1RenderTarget* pRenderTarget)
{
	int cntGridPoints = metadata.numberPointsLat * metadata.numberPointsLong;

	double xOrigin = metadata.gridOriginLongitude;
	double yOrigin = metadata.gridOriginLatitude;

	for (int i = 0; i < metadata.numberPointsLat; i++)
	{
		for (int j = 0; j < metadata.numberPointsLong; j++)
		{
			double mx = 0;//xOrigin + (metadata.gridSpacingLongitudinal * j);
			double my = 0;// yOrigin + (metadata.gridSpacingLatitudinal * i);
			double speed = 0;
			double dir = 0;

			int index = i * metadata.numberPointsLong + j;
			GetXY(index, mx, my);
			GetDirectionAndSpeed(curNumberOfTimes, index, dir, speed);

			if (speed < 0)
				continue;       
		}
	}
}


void S111::DrawIrregularGrid(ID2D1RenderTarget* pRenderTarget)
{
	for (int i = 0; i < metadata.numberOfNodes; i++)
	{
		if (speed.at(curNumberOfTimes)[i] < 0.1)
			continue;       
	}
}


void S111::DrawLagrangianDrifter(ID2D1RenderTarget* pRenderTarget)
{
	for (int i = 0; i < metadata.numberOfTimes; i++)
	{
		if (speed.at(0)[i] < 0.1)
			continue;       
	}
}


bool S111::ReadTimeSeries(__int64 file_id)
{
	int size = 0;
	ReadX(file_id, x, size);
	ReadY(file_id, y, size);

	for (int i = 0; i < metadata.numberOfTimes; i++)
	{
		float* _speed = new float[metadata.numberOfStations];
		float* _direction = new float[metadata.numberOfStations];
		memset(_speed, 0, sizeof(float) * metadata.numberOfStations);
		memset(_direction, 0, sizeof(float) * metadata.numberOfStations);
		speed.push_back(_speed);
		direction.push_back(_direction);
	}

	for (int i = 0; i < metadata.numberOfStations; i++)
	{
		float* dir = nullptr;
		float* spd = nullptr;

		ReadData(file_id, i + 1, dir, size, true);
		ReadData(file_id, i + 1, spd, size, false);

		for (int j = 0; j < metadata.numberOfTimes; j++)
		{
			speed.at(j)[i] = spd[j];
			direction.at(j)[i] = dir[j];
		}

		delete[] dir;
		delete[] spd;
	}

	return true;
}


bool S111::ReadRegularGrid(__int64 file_id)
{
	int size = 0;
	for (int i = 0; i < metadata.numberOfTimes; i++)
	{
		float* dir = nullptr;
		float* spd = nullptr;

		ReadData(file_id, i + 1, dir, size, true);
		ReadData(file_id, i + 1, spd, size, false);

		speed.push_back(spd);
		direction.push_back(dir);
	}

	return true;
}


bool S111::ReadIrregularGrid(__int64 file_id)
{
	int size = 0;
	ReadX(file_id, x, size);
	ReadY(file_id, y, size);

	for (int i = 0; i < metadata.numberOfTimes; i++)
	{
		float* dir = nullptr;
		float* spd = nullptr;

		ReadData(file_id, i + 1, dir, size, true);
		ReadData(file_id, i + 1, spd, size, false);

		speed.push_back(spd);
		direction.push_back(dir);
	}

	return true;
}


bool S111::ReadLagrangianDrifter(__int64 file_id)
{
	int size = 0;
	ReadX(file_id, x, size);
	ReadY(file_id, y, size);

	float* dir = nullptr;
	float* spd = nullptr;
	ReadData(file_id, 1, dir, size, true);
	ReadData(file_id, 1, spd, size, false);
	speed.push_back(spd);
	direction.push_back(dir);

	return true;
}


bool S111::ReadX(__int64 file_id, double*& buf, int& size)
{
	ReadXYsegment(file_id, buf, size, true);

	return true;
}


bool S111::ReadY(__int64 file_id, double*& buf, int& size)
{
	ReadXYsegment(file_id, buf, size, false);

	return true;
}


bool S111::ReadXYsegment(__int64 file_id, double*& buf, int& size, bool isX)
{
	hid_t status = 0;

	char* path = nullptr;

	if (isX)
	{
		path = "/Group XY/X";
	}
	else
	{
		path = "/Group XY/Y";
	}

	hid_t id_dataset = H5Dopen2(file_id, path, H5P_DEFAULT);

	if (id_dataset < 0)
	{
		CString str;
		str.Format(_T("Failed to open dataset XY\n")); 
		return false;
	}

	size = (int)H5Dget_storage_size(id_dataset) / sizeof(float);

	buf = new double[size];
	memset(buf, 0, sizeof(double) * size);

	float* tmpBuf = new float[size];
	memset(tmpBuf, 0, sizeof(float) * size);

	status = H5Dread(id_dataset, H5T_IEEE_F32LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, tmpBuf);

	for (int i = 0; i < size; i++)
		buf[i] = (double)tmpBuf[i];

	delete[] tmpBuf;

	if (status < 0)
	{ 
		return false;
	}

	status = H5Dclose(id_dataset);

	if (status != 0)
	{ 
		return false;
	}

	return true;
}


void S111::SetCurNumberOfTimes(int _curNumberOfTimes)
{
	if (_curNumberOfTimes < 0 || _curNumberOfTimes >= metadata.numberOfTimes)
		return;

	curNumberOfTimes = _curNumberOfTimes;
}