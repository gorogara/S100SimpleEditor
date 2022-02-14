#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h" 
#include "libS102Decl.h"
#include "libS111Decl.h"

#include "GeoMetryLibrary\\GeoPoint.h"

#include <d2d1_1.h>
#include <vector>
#include <string>
class Scaler;
class Bag;

namespace libS413
{
	enum S413FeatureType
	{
		None,
		AvgWaveDir,
		AvgWavePrd,
		Humidity,
		MaxWaveDir,
		MaxWpkPrd,
		NewSnowAmout3hr,
		OceanCurrent,
		Pressure,
		RainAmount3hr,
		SkyStatus,
		Temperature3hr,
		Visibility,
		WaterSalt,
		WaterTemperature,
		WaveHeightInst,
		WaveLength,
		WaveWind
	};

	extern LIBS111_API bool Open(std::wstring path);
	extern LIBS111_API void Draw(HDC &hDC, Rect rectF, Scaler *scaler);
	extern LIBS111_API void On(S413FeatureType type);
	extern LIBS111_API S413FeatureType GetCurrentS413FeatureType();
	extern LIBS111_API void Off();

	extern LIBS111_API void SetNextTime();
	extern LIBS111_API void SetPrevTime();
	extern LIBS111_API void SetNowTime();
	extern LIBS111_API CString GetTime();

	extern LIBS111_API CString GetTypeString(S413FeatureType type);
	extern LIBS111_API S413FeatureType GetType(CString type);

	extern __declspec(dllexport) CString PickReport(float x, float y);


	extern __declspec(dllexport) void GetLayerInformation(int &count, std::vector<std::wstring> &filenames);
}

namespace libS111
{   
	extern LIBS111_API bool Init();    
	extern LIBS111_API bool Open(std::wstring _filePath);   
	extern LIBS111_API void Draw(HDC &hDC, Scaler *scaler, Rect rectF);    
	extern LIBS111_API void Draw(HDC &hDC, Scaler *scaler, Rect rectF, double scale);       
	extern LIBS111_API bool GetData(GeoPoint inputPt, GeoPoint& outputPt, float& dir, float& spd);

	extern LIBS111_API CString PickReportRegularGrid(float x, float y);
	extern LIBS111_API void PickReportFixedStation(float x, float y, CString& name, std::vector<float>& directions, std::vector<float>& speeds);    
	extern LIBS111_API bool SetSelectedData(GeoPoint selectedPt, Scaler *scaler); 
	extern LIBS111_API void ClearSelectedData(); 
	extern LIBS111_API void On(); 
	extern LIBS111_API void Off();   
	extern LIBS111_API bool IsOn();    
	extern LIBS111_API void SetVariables(double sref, double lref, double shigh); 
	extern LIBS111_API void SetDay(); 
	extern LIBS111_API void SetNight(); 
	extern LIBS111_API void SetDusk();  
	extern LIBS111_API int GetTimeCount();    
	extern LIBS111_API bool SetTime(int index);   
	extern LIBS111_API bool SetNextTime();   
	extern LIBS111_API bool SetPrevTime();  
	extern LIBS111_API int GetCurTimeIndex();  
	extern LIBS111_API SYSTEMTIME GetCurTime();  
	extern LIBS111_API void SetFromTime(time_t time);    
	extern LIBS111_API void SetViewType(int type);


	extern LIBS111_API std::vector<float> GetS111Range();
	extern LIBS111_API void CalculateSpeedMinMax();


	extern __declspec(dllexport) void GetLayerInformation(int &count, std::vector<std::wstring> &filenames);

	struct S111NumericalInfo
	{ 
		int lat;
		int lon;
		float speed;
		float direction;
		D2D1::Matrix3x2F matrix;
	};
}

namespace libS104
{    
	extern LIBS111_API bool Open(std::wstring _filePath);      
	extern LIBS111_API bool GetData(GeoPoint inputPt, time_t time, double &variableDepth);

	extern LIBS111_API bool GetData(float x, float y, time_t time, double &variableDepth);

	extern LIBS111_API bool GetData(float x, float, double &variableDepth);      
	extern LIBS111_API bool GetData(time_t time, int xIndex, int yIndex, double &variableDepth);

	extern LIBS111_API void PickReportFixedStation(float x, float y, CString& name, std::vector<float>& values);

	extern LIBS111_API bool SetNextTime();
	extern LIBS111_API bool SetPrevTime();
	extern LIBS111_API void SetNow();

	extern LIBS111_API void GetLayerInformation(int &count, std::vector<std::wstring> &filenames);
}

namespace libS102
{    
	extern LIBS102_API bool Open(std::wstring _filePath);    
	extern LIBS102_API void Draw(HDC &hDC, Scaler *scaler, Rect rectF, int scale);  
	extern LIBS102_API void SetDC(CDC* pDC);

	extern LIBS102_API void SetDC(HDC& hDC);       
	extern LIBS102_API bool GetData(GeoPoint *inputPt, GeoPoint *outputPt, float& depth, float scale);     
	extern LIBS102_API bool SetSelectedData(GeoPoint* selectedPt, float scale); 
	extern LIBS102_API void ClearSelectedData(); 
	extern LIBS102_API void On(); 
	extern LIBS102_API void Off();   
	extern LIBS102_API bool IsOn();

	extern LIBS102_API void CalculateDepthMinMax();
	extern LIBS102_API void SetColorMode(int mode);
	extern LIBS102_API int GetColorMode();
	extern LIBS102_API void SetSafetyDepth(float depth);
	extern LIBS102_API void SetTime(time_t time);
	extern LIBS102_API std::vector<int> GetS102Range();

	extern LIBS102_API void CombineS104();
	extern LIBS102_API void Close();

	extern LIBS102_API int GetNumberOfOpenFile();

	extern LIBS102_API void GetLayerInformation(int &count, std::vector<std::wstring> &filenames);
	extern LIBS102_API bool GetS104Mode();
}

class S413;
class S100Engine;

class ClibS111App : public CWinApp
{
public:
	ClibS111App();
	virtual BOOL InitInstance(); 
	HRESULT CreateDeviceIndependentResources(); 
	HRESULT CreateDeviceResources(); 
	void DiscardDeviceResources();

	bool CreateDirect2DS111ArrowGeometry();   
	ID2D1Factory1* m_pDirect2dFactory; 
	ID2D1DCRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pBrush;
	ID2D1SolidColorBrush* m_pBlackBrush;
	ID2D1StrokeStyle1* m_pStrokeStyle = nullptr;
	IDWriteFactory* _pDWriteFactory = nullptr;
	IDWriteTextFormat* _pTextFormat = nullptr; 
	std::vector<void*> s104vector; 
	double S111_SREF;
	double S111_LREF;
	double S111_SHIGH;
	double S111_Alpha;  
	int viewType;

	std::vector<void*> s111vector;
	std::vector<CTime> times; 
	int timeIndex; 

	std::vector<time_t> s104Times;
	int currentS104TimeIndex = 0;

	ID2D1PathGeometry* m_pS111ArrowGeometry;

	std::vector<libS111::S111NumericalInfo> s111matrix;
	
	bool bDrawSelectedArrow;
	int selectedArrowIndex;
	GeoPoint* selectArrowPos; 
	std::vector<S413*> s413vector;
	bool onS413 = true;
	libS413::S413FeatureType onS413Type = libS413::S413FeatureType::WaveWind;

	S100Engine* s100Engine;

	std::vector<Bag*> bags;
	bool on;
	bool bDrawSelectedGrid;
	GeoPoint* ptSelectedGrid;

	CDC* pDC;
	bool bS104 = false;

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};