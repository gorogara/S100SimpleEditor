#pragma once
#include "S100SpatialObject.h"
#include "S111Group.h"
#include "S111Metadata.h"
#include "PointXY.h" 

#define S111_STEP_COUNT 9


class PCOutputSchemaManager;
class R_FeatureRecord;
struct S111SpeedDirection;

class S111Cell : public S100SpatialObject
{
public:
	S111Cell();
	virtual ~S111Cell();

public:
	S111Metadata metadata;
	std::vector<PointXY> points;
	std::vector<SYSTEMTIME> times;
	std::vector<Data> data;
	double* x = nullptr;
	double* y = nullptr;
	std::vector<S111SpeedDirection *> speedDirections;
	int curNumberOfTimes = 0;
	static D2D1::ColorF color[S111_STEP_COUNT];
	CMap<__int64, __int64, R_FeatureRecord*, R_FeatureRecord*&> m_feaMap;

public:
	bool Open(CString _filePath);
	bool Open0p0p12(__int64 file_id);

	void Draw(HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawArrow(ID2D1DCRenderTarget* pRenderTarget, int _x, int _y,
		float _spd, float _dir, Scaler* scaler, double offset = 0);
	void DrawTimeSeries(ID2D1DCRenderTarget* pRenderTarget, Scaler* scaler, double offset = 0);
	void DrawRegularGrid(ID2D1DCRenderTarget* pRenderTarget, Scaler* scaler, double offset = 0);
	void DrawIrregularGrid(ID2D1DCRenderTarget* pRenderTarget, Scaler* scaler, double offset = 0);
	void DrawLagrangianDrifter(ID2D1DCRenderTarget* pRenderTarget, Scaler* scaler, double offset = 0);

	bool ReadMetadata0p0p12(__int64 file_id);
	bool ReadXY0p0p12(__int64 file_id, double*& bufX, double*& bufY, int& size);
	bool ReadData0p0p12(__int64 file_id, int groupNum);

	bool ReadSurfaceCurrent01Attribute(__int64 file_id);
	bool ReadTimeSeries0p0p12(__int64 file_id);
	bool ReadRegularGrid0p0p12(__int64 file_id);
	bool ReadIrregularGrid0p0p12(__int64 file_id);
	bool ReadLagrangianDrifter0p0p12(__int64 file_id);

	int GetGroupCnt(__int64 file_id);
	bool ReadXY(__int64 file_id);
	bool ReadX(__int64 file_id, float*& buf, int& size);
	bool ReadY(__int64 file_id, float*& buf, int& size);
	bool ReadXYsegment(__int64 file_id, float*& buf, int& size, bool isX);
	bool ReadX(__int64 file_id, double*& buf, int& size);
	bool ReadY(__int64 file_id, double*& buf, int& size);
	bool ReadXYsegment(__int64 file_id, double*& buf, int& size, bool isX);
	bool SetTime(); 
	void SetMBR();
	void SetMBRfromTimeSeries();
	void SetMBRfromRegularGrid();
	void SetMBRfromIrregularGrid();
	void SetMBRfromLagrangianDrifter();

	void SetCurNumberOfTimes(int _curNumberOfTimes);
	void NextTimeIndex();
	void PrevTimeIndex();

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

	void ReadPCManager();
};