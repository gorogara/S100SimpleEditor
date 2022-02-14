#pragma once
#include "S111Metadata.h"

#include "..\\libS100HDF5\\S104.h"

#include <vector>
bool HDF5ReadIntegerAttribute(int id, char* attributeName, int& attributeValue);
bool HDF5ReadFloat64Attribute(int id, char* attributeName, double& attributeValue);
bool HDF5ReadStringAttribute(int id, char* attributeName, std::string& attributeValue);

class S104
{
public:
	S104();
	virtual ~S104();

	bool Open(char* path);
	bool Open(CString path);
	bool Get(int index, int x, int y, double &value);
	bool GetIndex(int x, int y, int& index);

	double GetFromIndex(int dataIndex, int xIndex, int yIndex);

	
public:
	DataCodingFormat dataCodingFormat;
	int rasterXSize;
	int rasterYSize;
	int gridCount;
	int xmin;
	int ymin;
	int xmax;
	int ymax;
	CTime startTime;
	CTime endTime;

	CString m_FilePath; 
	CString m_FileName; 

	std::vector<float *> waterLevel;
	S100HDF5::S104 *s104 = nullptr;




};