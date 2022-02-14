#pragma once

#include "S111Metadata.h"
#include "libS111.h"

#include "..\\libS100HDF5\\S111.h"

class S111
{
public:
	S111();
	virtual ~S111();

	bool Open(CString _filePath);
	bool Open0p0p12(__int64 file_id);

	void Draw(int index, ID2D1RenderTarget* pRenderTarget, ID2D1SolidColorBrush* pBrush, Rect rectF,
		double S111_SREF, double S111_LREF, double S111_SHIGH, double S111_Alpha);
	void DrawArrow(ID2D1RenderTarget* pRenderTarget, ID2D1SolidColorBrush* pBrush,
		double S111_SREF, double S111_LREF, double S111_SHIGH, double S111_Alpha,
		int _x, int _y, float _spd, float _dir);
	void DrawTimeSeries(ID2D1RenderTarget* pRenderTarget);
	void DrawRegularGrid(ID2D1RenderTarget* pRenderTarget);
	void DrawIrregularGrid(ID2D1RenderTarget* pRenderTarget);
	void DrawLagrangianDrifter(ID2D1RenderTarget* pRenderTarget);

	bool ReadMetadata0p0p12(__int64 file_id);
	bool ReadXY0p0p12(__int64 file_id, double*& bufX, double*& bufY, int& size);
	bool ReadData0p0p12(__int64 file_id, int groupNum, float*& dir, float*&spd);

	bool ReadSurfaceCurrent01Attribute(__int64 file_id);
	bool ReadTimeSeries0p0p12(__int64 file_id);
	bool ReadRegularGrid0p0p12(__int64 file_id);
	bool ReadIrregularGrid0p0p12(__int64 file_id);
	bool ReadLagrangianDrifter0p0p12(__int64 file_id);



	bool ReadData(__int64 file_id);
	bool ReadData(__int64 file_id, int groupNum, float*& buf, int& size, bool isDir);
	int GetGroupCnt(__int64 file_id);
	bool ReadXY(__int64 file_id);
	bool ReadX(__int64 file_id, float*& buf, int& size);
	bool ReadY(__int64 file_id, float*& buf, int& size);
	bool ReadXYsegment(__int64 file_id, float*& buf, int& size, bool isX);
	bool ReadX(__int64 file_id, double*& buf, int& size);
	bool ReadY(__int64 file_id, double*& buf, int& size);
	bool ReadXYsegment(__int64 file_id, double*& buf, int& size, bool isX);
	bool SetTime();

	bool ReadTimeSeries(__int64 file_id);
	bool ReadRegularGrid(__int64 file_id);
	bool ReadIrregularGrid(__int64 file_id);
	bool ReadLagrangianDrifter(__int64 file_id);

	void SetCurNumberOfTimes(int _curNumberOfTimes);

	int GetNumberOfTimes();
	SYSTEMTIME GetSystemTime(int index);


	int GetNumberOfNodesForAllTypes(); 
	void GetXY(int _index, double& _x, double& _y);
	void GetDirectionAndSpeed(int _indexTime, int _indexPoint, double& _direction, double& _speed); 
	void GetXYFromTimeSeries(int _index, double& _x, double& _y);
	void GetXYFromRegularlyGrid(int _index, double& _x, double& _y);
	void GetXYFromIrregularyGrid(int _index, double& _x, double& _y);
	void GetXYFromLagrangianDrifters(int _index, double& _x, double& _y);


	void GetDirectionAndSpeedFromTimeSeries(int _indexTime, int _indexPoint, double& _direction, double& _speed);
	void GetDirectionAndSpeedFromRegularlyGrid(int _indexTime, int _indexPoint, double& _direction, double& _speed);
	void GetDirectionAndSpeedFromIrregularyGrid(int _indexTime, int _indexPoint, double& _direction, double& _speed);
	void GetDirectionAndSpeedFromLagrangianDrifters(int _indexTime, int _indexPoint, double& _direction, double& _speed);

	S111Metadata metadata;
	std::vector<PointXY> points;
	std::vector<SYSTEMTIME> times;
	std::vector<Data> data;

	std::vector<CString> stationNames;

	double* x;
	double* y;
	std::vector<float*> speed;
	std::vector<float*> direction;
	int curNumberOfTimes;

	std::vector<CRect> declutter_rect;

	static D2D1::ColorF color[S111_STEP_COUNT + 1];
	static float SPEED_RANGE[S111_STEP_COUNT];

	static ClibS111App* app; 


	CString m_FilePath; 
	CString m_FileName;    
	int type;

	S100HDF5::S111 *_S111 = nullptr;
};