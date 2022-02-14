// libS111.cpp : Defines the initialization routines for the DLL. 

#include "stdafx.h"
#include "libS111.h"
#include "S111.h"
#include "S104.h"
#include "S413.h"
#include "Bag.h"

#include "..\\S100Engine\\S100Engine.h"
#include "GeoMetryLibrary\\Scaler.h"
#include "..\\libS100HDF5\\S102.h"
#include "..\\LibMFCUtil\\LibMFCUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif                         

BEGIN_MESSAGE_MAP(ClibS111App, CWinApp)
END_MESSAGE_MAP() 

ClibS111App::ClibS111App()
{  
	m_pDirect2dFactory = nullptr;
	m_pBrush = nullptr;
	m_pBlackBrush = nullptr;
	S111::app = this;
	on = true;
	timeIndex = -1;

	viewType = 0;

	bDrawSelectedGrid = false;
	ptSelectedGrid = new GeoPoint();
} 

ClibS111App theApp;

const GUID CDECL _tlid = { 0x66E51720, 0x61CF, 0x4E59, { 0xAD, 0xB7, 0x55, 0xED, 0xC3, 0x5B, 0x94, 0x9D } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0; 

BOOL ClibS111App::InitInstance()
{
	CWinApp::InitInstance();  
	COleObjectFactory::RegisterAll();

	theApp.s100Engine = new S100Engine();  

	return TRUE;
}                                                


HRESULT ClibS111App::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK; 
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
	
	if (SUCCEEDED(hr))
	{
		hr = m_pDirect2dFactory->CreateStrokeStyle(
			D2D1::StrokeStyleProperties1(
				D2D1_CAP_STYLE_ROUND,
				D2D1_CAP_STYLE_ROUND,
				D2D1_CAP_STYLE_ROUND,
				D2D1_LINE_JOIN_ROUND,
				10.0f,
				D2D1_DASH_STYLE_SOLID,
				0.0f,
				D2D1_STROKE_TRANSFORM_TYPE_FIXED),
			NULL,
			0,
			&m_pStrokeStyle);
	}

	theApp.s100Engine->CreateSVGGeometry(m_pDirect2dFactory);

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&_pDWriteFactory)
	);

	if (!SUCCEEDED(hr))
	{
		return false;
	}

	hr = _pDWriteFactory->CreateTextFormat(
		L"Arial", 
		NULL, 
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15.0f,
		L"en-us",
		&_pTextFormat
	);

	_pTextFormat->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP); 
	_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	return hr;
}


HRESULT ClibS111App::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!m_pRenderTarget)
	{
		D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(
			DXGI_FORMAT_B8G8R8A8_UNORM,
			D2D1_ALPHA_MODE_IGNORE),
			0,
			0,
			D2D1_RENDER_TARGET_USAGE_NONE,
			D2D1_FEATURE_LEVEL_DEFAULT
			);


		hr = m_pDirect2dFactory->CreateDCRenderTarget(&props, &m_pRenderTarget);

		if (SUCCEEDED(hr))
		{ 
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Black),
				&m_pBrush
				);	
			
			hr = m_pRenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Black),
				&m_pBlackBrush
				);
		}
	}

	return hr;
}


void ClibS111App::DiscardDeviceResources()
{
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pBrush);
	SafeRelease(&m_pBlackBrush);
	SafeRelease(&m_pS111ArrowGeometry);
	SafeRelease(&m_pStrokeStyle);
	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&_pDWriteFactory);
	SafeRelease(&_pTextFormat);
}


bool ClibS111App::CreateDirect2DS111ArrowGeometry()
{
	double dotPerMM = 3.77952;
	double l = dotPerMM * S111_LREF;

	HRESULT hr = m_pDirect2dFactory->CreatePathGeometry(&m_pS111ArrowGeometry);

	ID2D1GeometrySink* pSink = nullptr;
	m_pS111ArrowGeometry->Open(&pSink);

	pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
	pSink->BeginFigure(
		D2D1::Point2F(0, -l / 2),
		D2D1_FIGURE_BEGIN_FILLED);

	D2D1_POINT_2F points[7] = {
		D2D1::Point2F(l / 5.0f, -(3.0f / 20.0f) * l),
		D2D1::Point2F(l / 10.0f, -(3.0f / 20.0f) * l),
		D2D1::Point2F(l / 20.0f, l / 2.0f),
		D2D1::Point2F(-l / 20.0f, l / 2.0f),
		D2D1::Point2F(-l / 10.0f, -(3.0f / 20.0f) * l),
		D2D1::Point2F(-(l / 5.0f), -(3.0f / 20.0f) * l),
		D2D1::Point2F(0.0f, -l / 2.0f)
	};

	pSink->AddLines(points, ARRAYSIZE(points));

	pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	pSink->Close();

	return true;
}


bool libS111::Init()
{
	SetVariables(5, 30, 20);
	SetDay();

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (S_OK != theApp.CreateDeviceIndependentResources())
	{ 
		return false;
	}
	
	if (S_OK != theApp.CreateDeviceResources())
	{ 
		return false;
	}

	theApp.CreateDirect2DS111ArrowGeometry();

	return true;
}


bool libS413::Open(std::wstring path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	S413 *s413 = new S413();
	
	if (!s413->Open(path.c_str()))
	{
		return false;
	}

	theApp.s413vector.push_back(s413);

	return true;
}


bool libS111::Open(std::wstring _filePath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	S111* s111 = new S111();
	if (s111->Open(_filePath.c_str()))
	{
		theApp.s111vector.push_back(s111);
		if (s111->metadata.dataCodingFormat == DataCodingFormat::RegularlyGriddedArrays)
		{
			for (unsigned i = 0; i < theApp.times.size(); i++)
			{
				bool bFind = false;
			}

			for (unsigned i = 0; i < s111->times.size(); i++)
			{
				CTime curTime(s111->times.at(i).wYear,
					s111->times.at(i).wMonth,
					s111->times.at(i).wDay,
					s111->times.at(i).wHour,
					s111->times.at(i).wMinute,
					s111->times.at(i).wSecond);

				bool bFind = false;
				for (unsigned j = 0; j < theApp.times.size(); j++)
				{
					if (curTime == theApp.times.at(j))
					{
						bFind = true;
						break;
					}
				}

				if (!bFind)
					theApp.times.push_back(curTime);
			}

			sort(theApp.times.begin(), theApp.times.end());
			theApp.timeIndex = 0;
		}

		time_t now = time(nullptr);
		libS111::SetFromTime(now);

		return true;
	}
	else
		delete s111;

	return false;
}


#pragma warning(disable:4018)
#pragma warning(disable:4305)
void libS413::Draw(HDC &hDC, Rect rectF, Scaler *scaler)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (!theApp.m_pRenderTarget || !theApp.onS413)
	{

		return;
	}

	CDC* pDC = CDC::FromHandle(hDC);
	CRect rect(rectF.GetLeft(), rectF.GetTop(), rectF.GetRight(), rectF.GetBottom());

	theApp.m_pRenderTarget->BindDC(*pDC, rect);
	theApp.m_pRenderTarget->BeginDraw();

	theApp.m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	for (auto i = theApp.s413vector.begin();
		i != theApp.s413vector.end();
		i++)
	{
		S413* s413 = *i;
		CString str;
		str.Format(_T("S-413 Time Index : %d\n"), s413->_currentTimeIndex);
		OutputDebugString(str);

		switch (theApp.onS413Type)
		{
		case S413FeatureType::None:
			break;
		case S413FeatureType::AvgWaveDir:
			s413->DrawDirection(
				theApp.m_pRenderTarget,
				theApp.m_pBrush,
				theApp.m_pStrokeStyle,
				theApp._pDWriteFactory,
				theApp._pTextFormat,
				rectF,
				s413->_S413->GetIrregularGridFeature("AvgWaveDir"),
				scaler
			);
			break;
		case S413FeatureType::AvgWavePrd:
			theApp.m_pRenderTarget->EndDraw();
			if (!s413->bBMP)
			{
				s413->CreateBitmap(pDC, 1);
			}
			s413->DrawBitmap(hDC, rectF, scaler);
			theApp.m_pRenderTarget->BeginDraw();
			break;
		case S413FeatureType::Humidity:
			theApp.m_pRenderTarget->EndDraw();
			if (!s413->bBMP)
			{
				s413->CreateBitmap(pDC, 2);
			}
			s413->DrawBitmap(hDC, rectF, scaler);
			theApp.m_pRenderTarget->BeginDraw();
			break;
		case S413FeatureType::MaxWaveDir:
			s413->DrawDirection(
				theApp.m_pRenderTarget,
				theApp.m_pBrush,
				theApp.m_pStrokeStyle,
				theApp._pDWriteFactory,
				theApp._pTextFormat,
				rectF,
				s413->_S413->GetIrregularGridFeature("MaxWaveDir"),
				scaler
			);
			break;
		case S413FeatureType::MaxWpkPrd:
			theApp.m_pRenderTarget->EndDraw();
			if (!s413->bBMP)
			{
				s413->CreateBitmap(pDC, 4);
			}
			s413->DrawBitmap(hDC, rectF, scaler);
			theApp.m_pRenderTarget->BeginDraw();
			break;
		case S413FeatureType::NewSnowAmout3hr:
			theApp.m_pRenderTarget->EndDraw();
			if (!s413->bBMP)
			{
				s413->CreateBitmap(pDC, 5);
			}
			s413->DrawBitmap(hDC, rectF, scaler);
			theApp.m_pRenderTarget->BeginDraw();
			break;
		case S413FeatureType::OceanCurrent:
			s413->DrawOceanCurrent(
				theApp.m_pRenderTarget,
				theApp.m_pBrush,
				theApp.m_pStrokeStyle,
				theApp._pDWriteFactory,
				theApp._pTextFormat,
				rectF,
				s413->_S413->GetIrregularGridFeature("OceanCurrent"),
				scaler
			);
			break;
		case S413FeatureType::Pressure:
			theApp.m_pRenderTarget->EndDraw();
			if (!s413->bBMP)
			{
				s413->CreateBitmap(pDC, 7);
			}
			s413->DrawBitmap(hDC, rectF, scaler);
			theApp.m_pRenderTarget->BeginDraw();
			break;
		case S413FeatureType::RainAmount3hr:
			theApp.m_pRenderTarget->EndDraw();
			if (!s413->bBMP)
			{
				s413->CreateBitmap(pDC, 8);
			}
			s413->DrawBitmap(hDC, rectF, scaler);
			theApp.m_pRenderTarget->BeginDraw();
			break;
		case S413FeatureType::SkyStatus:
			s413->DrawSkyStatus(
				theApp.m_pRenderTarget,
				theApp.m_pBrush,
				theApp.m_pStrokeStyle,
				theApp._pDWriteFactory,
				theApp._pTextFormat,
				rectF,
				s413->_S413->GetIrregularGridFeature("SkyStatus"),
				scaler
			);
			break;
		case S413FeatureType::Temperature3hr:
			theApp.m_pRenderTarget->EndDraw();
			if (!s413->bBMP)
			{
				s413->CreateBitmap(pDC, 2);
			}
			s413->DrawBitmap(hDC, rectF, scaler);
			theApp.m_pRenderTarget->BeginDraw();
			break;
		case S413FeatureType::Visibility:
			s413->DrawVisibility(
				theApp.m_pRenderTarget,
				theApp.m_pBrush,
				theApp.m_pStrokeStyle,
				theApp._pDWriteFactory,
				theApp._pTextFormat,
				rectF,
				s413->_S413->GetIrregularGridFeature("Visibility"),
				scaler
			);
			break;
		case S413FeatureType::WaterSalt:
			theApp.m_pRenderTarget->EndDraw();
			if (!s413->bBMP)
			{
				s413->CreateBitmap(pDC, 12);
			}
			s413->DrawBitmap(hDC, rectF, scaler);
			theApp.m_pRenderTarget->BeginDraw();
			break;
		case S413FeatureType::WaterTemperature:
			theApp.m_pRenderTarget->EndDraw();
			if (!s413->bBMP)
			{
				s413->CreateBitmap(pDC, 13);
			}
			s413->DrawBitmap(hDC, rectF, scaler);
			theApp.m_pRenderTarget->BeginDraw();
			break;
		case S413FeatureType::WaveHeightInst:
			theApp.m_pRenderTarget->EndDraw();
			if (!s413->bBMP)
			{
				s413->CreateBitmap(pDC, 14);
			}
			s413->DrawBitmap(hDC, rectF, scaler);
			theApp.m_pRenderTarget->BeginDraw();
			break;
		case S413FeatureType::WaveLength:
			theApp.m_pRenderTarget->EndDraw();
			if (!s413->bBMP)
			{
				s413->CreateBitmap(pDC, 15);
			}
			s413->DrawBitmap(hDC, rectF, scaler);
			theApp.m_pRenderTarget->BeginDraw();
			break;
		case S413FeatureType::WaveWind:
			s413->DrawWaveWind(
				theApp.m_pRenderTarget,
				theApp.m_pBrush,
				theApp.m_pStrokeStyle,
				rectF,
				s413->_S413->GetIrregularGridFeature("WaveWind"),
				scaler
			);
			break;
		}
	}

	theApp.m_pRenderTarget->EndDraw();
}


#pragma warning(disable:4018)
#pragma warning(disable:4305)
void libS111::Draw(HDC &hDC, Scaler *scaler, Rect rectF)
{
	if (!theApp.m_pRenderTarget)
	{
		return;
	}
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	theApp.s111matrix.clear();

	if (theApp.on == false) return;

	CDC* pDC = CDC::FromHandle(hDC);
	CRect rect(rectF.GetLeft(), rectF.GetTop(), rectF.GetRight(), rectF.GetBottom());


	theApp.m_pRenderTarget->BindDC(*pDC, rect);
	theApp.m_pRenderTarget->BeginDraw();

	theApp.m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	for (unsigned i = 0; i < theApp.s111vector.size(); i++)
	{
		S111* s111 = (S111*)theApp.s111vector.at(i);

		for (int j = 0; j < s111->GetNumberOfTimes(); j++)
		{
			SYSTEMTIME systemtime = s111->GetSystemTime(j);
			CTime ctime(systemtime.wYear,
				systemtime.wMonth,
				systemtime.wDay,
				systemtime.wHour,
				systemtime.wMinute,
				systemtime.wSecond);

			if ((theApp.timeIndex >= 0) && (theApp.timeIndex < theApp.times.size()))
			{
				if (ctime == theApp.times.at(theApp.timeIndex))
				{
					s111->Draw(j, theApp.m_pRenderTarget, theApp.m_pBrush, rectF,
						theApp.S111_SREF, theApp.S111_LREF, theApp.S111_SHIGH, theApp.S111_Alpha);
				}
			}
		}
	}

	GeoPoint outputPt;
	float spd, dir;
	if (theApp.selectArrowPos)
	{
		if (GetData(*theApp.selectArrowPos, outputPt, dir, spd) && theApp.bDrawSelectedArrow == true)
		{
			D2D1_COLOR_F color;
			color.r = 192.0 / 255.0;
			color.g = 192.0 / 255.0;
			color.b = 192.0 / 255.0;
			color.a = 1;
			theApp.m_pBrush->SetColor(color);

			double scaleFactor = 1;
			if (spd > theApp.S111_SHIGH)
			{
				scaleFactor = theApp.S111_SHIGH / theApp.S111_SREF;
			}
			else
			{
				scaleFactor = spd / theApp.S111_SREF;
			}

			const D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(dir);

			CPoint pt;
			scaler->WorldToDevice(outputPt.x, outputPt.y, &pt.x, &pt.y);
			const D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Translation(pt.x, pt.y);
			const D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(
				D2D1::SizeF(scaleFactor, scaleFactor), D2D1::Point2F(pt.x, pt.y));
			theApp.m_pRenderTarget->SetTransform(rot * trans * scale);
			theApp.m_pRenderTarget->FillGeometry(
				theApp.m_pS111ArrowGeometry,
				theApp.m_pBrush);

			theApp.m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		}
	}

	theApp.m_pRenderTarget->EndDraw();
}

void libS111::Draw(HDC &hDC, Scaler *scaler, Rect rectF, double scale)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	theApp.s111matrix.clear();

	if (theApp.on == false) return;

	CDC* pDC = CDC::FromHandle(hDC);
	CRect rect(rectF.GetLeft(), rectF.GetTop(), rectF.GetRight(), rectF.GetBottom());
	theApp.m_pRenderTarget->BindDC(*pDC, rect);
	theApp.m_pRenderTarget->BeginDraw();

	theApp.m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	for (int i = 0; i < theApp.s111vector.size(); i++)
	{
		S111* s111 = (S111*)theApp.s111vector.at(i);

		if (s111->type != theApp.viewType)
			continue;  
		{
			for (int j = 0; j < s111->GetNumberOfTimes(); j++)
			{
				SYSTEMTIME systemtime = s111->GetSystemTime(j);
				CTime ctime(systemtime.wYear,
					systemtime.wMonth,
					systemtime.wDay,
					systemtime.wHour,
					systemtime.wMinute,
					systemtime.wSecond);

				if ((theApp.timeIndex >= 0) && (theApp.timeIndex < theApp.times.size()))
				{
					if (ctime == theApp.times.at(theApp.timeIndex))
					{
						s111->Draw(j, theApp.m_pRenderTarget, theApp.m_pBrush, rectF,
							theApp.S111_SREF, theApp.S111_LREF, theApp.S111_SHIGH, theApp.S111_Alpha);
					}
				}
			}
		}		
	}

	GeoPoint outputPt;
	float spd, dir;
	if (GetData(*theApp.selectArrowPos, outputPt, dir, spd) && theApp.bDrawSelectedArrow == true)
	{
		D2D1_COLOR_F color;
		color.r = 192.0 / 255.0;
		color.g = 192.0 / 255.0;
		color.b = 192.0 / 255.0;
		color.a = 1;
		theApp.m_pBrush->SetColor(color);

		double scaleFactor = 1;
		if (spd > theApp.S111_SHIGH)
		{
			scaleFactor = theApp.S111_SHIGH / theApp.S111_SREF;
		}
		else
		{
			scaleFactor = spd / theApp.S111_SREF;
		}

		const D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation(dir);

		CPoint pt;

		scaler->WorldToDevice(outputPt.x, outputPt.y, &pt.x, &pt.y);

		const D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Translation(pt.x, pt.y);
		const D2D1::Matrix3x2F scale = D2D1::Matrix3x2F::Scale(
			D2D1::SizeF(scaleFactor, scaleFactor), D2D1::Point2F(pt.x, pt.y));
		theApp.m_pRenderTarget->SetTransform(rot * trans * scale);
		theApp.m_pRenderTarget->FillGeometry(
			theApp.m_pS111ArrowGeometry,
			theApp.m_pBrush);

		theApp.m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}

	theApp.m_pRenderTarget->EndDraw();
}


int libS111::GetTimeCount()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.times.size();
}


bool libS111::SetTime(int index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if ((index >= 0) && (index < theApp.times.size()))
	{
		theApp.timeIndex = index;
		theApp.currentS104TimeIndex = index;
		return true;
	}

	theApp.timeIndex = -1;
	return false;
}


bool libS111::SetNextTime()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int newTimeIndex = theApp.timeIndex + 1;
	
	libS104::SetNextTime();
	if (libS102::GetColorMode() == true)
	{
		libS102::SetColorMode(100);
	}
	else
	{
		libS102::SetColorMode(200);
	}

	if ((newTimeIndex >= 0) && (newTimeIndex < theApp.times.size()))
	{
		theApp.timeIndex = newTimeIndex;
		return true;
	}

	return false;
}


bool libS111::SetPrevTime()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int newTimeIndex = theApp.timeIndex - 1;
	libS104::SetPrevTime();
	if (libS102::GetColorMode() == true)
	{
		libS102::SetColorMode(100);
	}
	else
	{
		libS102::SetColorMode(200);
	}

	if ((newTimeIndex >= 0) && (newTimeIndex < theApp.times.size()))
	{
		theApp.timeIndex = newTimeIndex;
		return true;
	}

	return false;
}


int libS111::GetCurTimeIndex()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString str;
	str.AppendFormat(_T("S-104 Current Time Index : %d\n"), theApp.currentS104TimeIndex);
	str.AppendFormat(_T("S-111 Current Time Index : %d\n"), theApp.timeIndex);
	OutputDebugString(str);

	return theApp.timeIndex;
}


CString libS111::PickReportRegularGrid(float x, float y)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString result = _T("");

	GeoPoint queryPoint;
	queryPoint.x = x;
	queryPoint.y = y;

	GeoPoint resultPoint;
	float dir = 0;
	float spd = 0;

	GetData(queryPoint, resultPoint, dir, spd);

	result.Format(_T("SurfaceCurrentDirection : %.2f\r\nSurfaceCurrentSpeed : %.2f"), dir, spd);

	return result;
}


void libS111::PickReportFixedStation(float x, float y, CString& name, std::vector<float>& directions, std::vector<float>& speeds)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	for (
		auto i = theApp.s111vector.begin(); 
		i != theApp.s111vector.end();
		i++)
	{
		S111 *s111 = (S111 *)(*i);
		if (s111->metadata.dataCodingFormat == DataCodingFormat::TimeSeriesAtStations)
		{
			int nearestStationIndex = -1;
			float shortestDistance = 0;

			for (int j = 0; j < s111->metadata.numberOfStations; j++)
			{
				float dx = s111->x[j] - x;
				float dy = s111->y[j] - y;
				float currentDistance = (dx * dx) + (dy * dy);

				if ((j == 0) || (currentDistance < shortestDistance))
				{
					shortestDistance = currentDistance;
					nearestStationIndex = j;
				}
			}

			if (nearestStationIndex >= 0)
			{
				try {
					name = s111->stationNames.at(nearestStationIndex);
					for (int j = 0; j < s111->metadata.numberOfTimes; j++)
					{
						directions.push_back(s111->direction.at(nearestStationIndex)[j]);
						speeds.push_back(s111->speed.at(nearestStationIndex)[j]);
					}
				}
				catch (std::out_of_range)
				{
					return;
				}
			}
		}
	}
	return;
}


bool libS111::GetData(GeoPoint inputPt, GeoPoint& outputPt, float& dir, float& spd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (theApp.on == false) return false;

	libS111::S111NumericalInfo *curMatrix = NULL, *nearestMatrix = NULL;
	int nearestDistance = INT_MAX;
	for (int i = 0; i < theApp.s111matrix.size(); i++)
	{
		int distance = abs(inputPt.y - theApp.s111matrix.at(i).lat) + abs(inputPt.x - theApp.s111matrix.at(i).lon);
		curMatrix = &theApp.s111matrix.at(i);
		if (distance < nearestDistance && (curMatrix->direction >= 0 && curMatrix->direction <= 360))
		{
			nearestMatrix = curMatrix;
			nearestDistance = distance;
		}
	}
	if (nearestMatrix)
	{
		dir = nearestMatrix->direction;
		spd = nearestMatrix->speed;
		return true;
	}
	else
		return false;
}


bool libS111::SetSelectedData(GeoPoint selectedPt, Scaler *scaler)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CPoint screenInputPt;
	scaler->WorldToDevice(selectedPt.x, selectedPt.y, &screenInputPt.x, &screenInputPt.y);
	
	BOOL bContain = FALSE;
	for (int i = 0; i < theApp.s111matrix.size(); i++)
	{
		theApp.m_pS111ArrowGeometry->FillContainsPoint(D2D1::Point2F(screenInputPt.x, screenInputPt.y), theApp.s111matrix.at(i).matrix, &bContain);

		if (bContain)
		{
			theApp.selectedArrowIndex = i;
			theApp.bDrawSelectedArrow = true; 
			theApp.selectArrowPos->x = theApp.s111matrix.at(i).lon;
			theApp.selectArrowPos->y = theApp.s111matrix.at(i).lat;
			return true;
		}
	}

	theApp.bDrawSelectedArrow = false;
	return false;
}


void libS111::ClearSelectedData()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.bDrawSelectedArrow = false;
}


SYSTEMTIME libS111::GetCurTime()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	SYSTEMTIME systemtime;
	memset(&systemtime, 0, sizeof(SYSTEMTIME));

	if ((theApp.timeIndex >= 0) && (theApp.timeIndex < theApp.times.size()))
	{
		systemtime.wYear = theApp.times.at(theApp.timeIndex).GetYear();
		systemtime.wMonth = theApp.times.at(theApp.timeIndex).GetMonth();
		systemtime.wDay = theApp.times.at(theApp.timeIndex).GetDay();

		systemtime.wHour = theApp.times.at(theApp.timeIndex).GetHour();
		systemtime.wMinute = theApp.times.at(theApp.timeIndex).GetMinute();
		systemtime.wSecond = theApp.times.at(theApp.timeIndex).GetSecond();
	}

	return systemtime;
}


void libS111::SetViewType(int type)
{
	theApp.viewType = type;
}

void libS111::SetFromTime(time_t time)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	libS104::SetNow();
	if (libS102::GetColorMode() == true)
	{
		libS102::SetColorMode(100);
	}
	else
	{
		libS102::SetColorMode(200);
	}

	if (theApp.s111vector.size() <= 0) return;

	tm timeStruct;
	localtime_s(&timeStruct, &time);

	CTime inputTime(timeStruct.tm_year + 1900,
		timeStruct.tm_mon + 1,
		timeStruct.tm_mday,
		timeStruct.tm_hour,
		timeStruct.tm_min,
		timeStruct.tm_sec);

	if (inputTime < *theApp.times.begin())
		SetTime(0);

	if (inputTime >= theApp.times.back())
		SetTime(theApp.times.size() - 1);

	for (int i = 0; i < theApp.times.size() - 1; i++)
	{
		CTime curTime = theApp.times.at(i);
		CTime nextTime = theApp.times.at(i + 1);
		if ((inputTime >= curTime) && (inputTime < nextTime))
		{
			CTimeSpan prevTimeSpan = inputTime - curTime;
			CTimeSpan nextTimeSpan = nextTime - inputTime;

			if (prevTimeSpan > nextTimeSpan)
				SetTime(i + 1);
			else
				SetTime(i);

			return;
		}
		else
			continue;
	}
}


void libS111::SetVariables(double sref, double lref, double shigh)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.S111_SREF = sref;
	theApp.S111_LREF = lref;
	theApp.S111_SHIGH = shigh;
}


void libS111::SetDay()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.S111_Alpha = 1.0;
}


void libS111::SetNight()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.S111_Alpha = 0.4;
}


void libS111::SetDusk()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.S111_Alpha = 0.2;
}

int ClibS111App::ExitInstance()
{
	for (int i = 0; i < theApp.s111vector.size(); i++)
	{
		S111* s111 = (S111*)theApp.s111vector.at(i);
		delete s111;
	}

	for (auto i = theApp.s104vector.begin();
		i != theApp.s104vector.end();
		i++)
	{
		delete *i;
		*i = nullptr;
	}

	for (auto i = theApp.s413vector.begin();
		i != theApp.s413vector.end();
		i++)
	{
		delete *i;
		*i = nullptr;
	}

	delete theApp.s100Engine;

	for (unsigned i = 0; i < theApp.bags.size(); i++)
	{
		delete theApp.bags.at(i);
	}

	delete ptSelectedGrid;

	return CWinApp::ExitInstance();
}


void libS111::On()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.on = true;
}


void libS111::Off()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.on = false;
}


bool libS111::IsOn()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.on;
}


bool libS104::Open(std::wstring _filePath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	S104* s104 = new S104();
	if (s104->Open(_filePath.c_str()))
	{
		if (s104->s104)
		{
			auto feature = s104->s104->GetRegularGrid(0);
			if (feature)
			{
				auto timeInfo = feature->GetTimeInformation();
				if (timeInfo)
				{
					int numTime = timeInfo->GetNumberOfTimes();
					for (int i = 0; i < numTime; i++)
					{
						theApp.s104Times.push_back(timeInfo->GetTime(i));
					}

					std::sort(theApp.s104Times.begin(), theApp.s104Times.end());
					theApp.s104Times.erase(std::unique(theApp.s104Times.begin(), theApp.s104Times.end()), theApp.s104Times.end());
				}
			}
		}

		theApp.s104vector.push_back(s104);
		SetNow();    

		return true;
	}
	else
		delete s104;

	return false;
}


bool libS104::GetData(float x, float y, time_t time, double &variableDepth)
{
	for (auto it = theApp.s104vector.begin(); it != theApp.s104vector.end(); it++)
	{
		S104* s104 = (S104*)*it;
		if (s104->s104)
		{
			auto boundingBox = s104->s104->GetMBR();
			if (boundingBox.PtInMBR(x, y))
			{
				if (auto feature = s104->s104->GetRegularGrid(0))
				{
					auto timeInfo = feature->GetTimeInformation();
					if (timeInfo)
					{
						int nearestTimeIndex = timeInfo->GetNearestTimeIndex(time);
						int numTime = timeInfo->GetNumberOfTimes();
						if ((nearestTimeIndex >= 0) && (nearestTimeIndex < numTime))
						{
							double xOffset = x - boundingBox.xmin;
							double yOffset = y - boundingBox.ymin;

							int xIndex = 0;
							int yIndex = 0;

							if (auto gridInfo = feature->GetRegularGridInformation())
							{
								float gridSpacingX = gridInfo->GetGridSpacingLongitudinal();
								float gridSpacingY = gridInfo->GetGridSpacingLatitudinal();

								if (x == s104->xmax)
								{
									xIndex = s104->rasterXSize - 1;
								}
								else
								{
									xIndex = xOffset / gridSpacingX;
								}

								if (y == s104->ymax)
								{
									yIndex = s104->rasterYSize - 1;
								}
								else
								{
									yIndex = yOffset / gridSpacingY;
								}

								int valueIndex = xIndex + (yIndex * s104->rasterXSize);
								if (auto featureValue = feature->GetRegularGridFeatureValues(nearestTimeIndex))
								{
									if (auto floatValue = featureValue->GetFloatValues(0))
									{
										if (auto value = floatValue->GetValues())
										{
											variableDepth = value[valueIndex];
											return true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return false;
}


bool libS104::GetData(float x, float y, double &variableDepth)
{
	for (auto it = theApp.s104vector.begin(); it != theApp.s104vector.end(); it++)
	{
		S104* s104 = (S104*)*it;
		if (s104->s104)
		{
			auto boundingBox = s104->s104->GetMBR();
			if (boundingBox.PtInMBR(x, y))
			{
				if (auto feature = s104->s104->GetRegularGrid(0))
				{
					auto timeInfo = feature->GetTimeInformation();
					if (timeInfo)
					{
						int numTime = timeInfo->GetNumberOfTimes();
						if ((theApp.currentS104TimeIndex >= 0) && (theApp.currentS104TimeIndex < numTime))
						{
							double xOffset = x - boundingBox.xmin;
							double yOffset = y - boundingBox.ymin;

							int xIndex = 0;
							int yIndex = 0;

							if (auto gridInfo = feature->GetRegularGridInformation())
							{
								float gridSpacingX = gridInfo->GetGridSpacingLongitudinal();
								float gridSpacingY = gridInfo->GetGridSpacingLatitudinal();

								if (x == s104->xmax)
								{
									xIndex = s104->rasterXSize - 1;
								}
								else
								{
									xIndex = xOffset / gridSpacingX;
								}

								if (y == s104->ymax)
								{
									yIndex = s104->rasterYSize - 1;
								}
								else
								{
									yIndex = yOffset / gridSpacingY;
								}

								int valueIndex = xIndex + (yIndex * s104->rasterXSize);
								if (auto featureValue = feature->GetRegularGridFeatureValues(theApp.currentS104TimeIndex))
								{
									if (auto floatValue = featureValue->GetFloatValues(0))
									{
										if (auto value = floatValue->GetValues())
										{
											variableDepth = value[valueIndex];
											return true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return false;
}


bool libS104::GetData(GeoPoint inputPt, time_t time, double &variableDepth)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL bContain = FALSE;

	for (auto it = theApp.s104vector.begin(); it != theApp.s104vector.end(); it++)
	{
		S104* s104 = (S104*)*it;
		if (s104->s104)
		{
			auto boundingBox = s104->s104->GetMBR();
			if (boundingBox.PtInMBR(inputPt.x, inputPt.y))
			{
				if (auto feature = s104->s104->GetRegularGrid(0))
				{
					auto timeInfo = feature->GetTimeInformation();
					if (timeInfo)
					{
						int nearestTimeIndex = timeInfo->GetNearestTimeIndex(time);
						int numTime = timeInfo->GetNumberOfTimes();
						if ((nearestTimeIndex >= 0) && (nearestTimeIndex < numTime))
						{
							struct tm struct_time;
							localtime_s(&struct_time, &time);

							double varDepth1 = 0., varDepth2 = 0.;

							if (s104->Get(nearestTimeIndex, inputPt.x, inputPt.y, variableDepth))
							{
								return true;
							}
						}
					}
				}
			}
		}
	}

	return false;
}


bool libS104::GetData(time_t time, int xIndex, int yIndex, double &variableDepth)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL bContain = FALSE;

	for (auto it = theApp.s104vector.begin(); it != theApp.s104vector.end(); it++)
	{
		S104* s104 = (S104*)*it;

		double varDepth1 = 0., varDepth2 = 0.;

		time_t uTime = time;
		time_t tTime = uTime + 3600;
		
		struct tm struct_time1;
		struct tm struct_time2;
		localtime_s(&struct_time1, &uTime);
		localtime_s(&struct_time2, &uTime);

		varDepth1 =	s104->GetFromIndex(struct_time1.tm_hour, xIndex, yIndex);
		varDepth2 = s104->GetFromIndex(struct_time2.tm_hour, xIndex, yIndex);

		variableDepth = varDepth1 + ((varDepth2 - varDepth1) / 60) * struct_time1.tm_min;
	}

	return false;
}


void libS104::PickReportFixedStation(float x, float y, CString& name, std::vector<float>& values)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	for (auto i = theApp.s104vector.begin(); i != theApp.s104vector.end(); i++)
	{
		S104* s104 = (S104*)*i;
		if (auto feature = s104->s104->GetFixedStation(0))
		{
			if (!feature)
				continue;
			auto stationInfo = feature->GetFixedStationInformation();
			if (stationInfo)
			{ 
				int numberOfStations = stationInfo->GetNumberOfNode();
				S100HDF5::Point* points = stationInfo->GetPositioning();

				if (points)
				{
					float shortestDistance = 0;
					int nearestStationIndex = 0;
					for (int j = 0; j < numberOfStations; j++)
					{
						float dx = points[j].X - x;
						float dy = points[j].Y - y;

						float currentDistance = (dx * dx) + (dy * dy);
						if ((j == 0) || (currentDistance < shortestDistance))
						{
							shortestDistance = currentDistance;
							nearestStationIndex = j;
						}
					}

					if (nearestStationIndex)
					{
						auto featureValues = feature->GetFixedStationFeatureValues(nearestStationIndex);
						if (featureValues)
						{
							name = featureValues->GetName();

							int numberOfTimes = stationInfo->GetNumberOfTimes();
							S100HDF5::FloatValues *waterLevelsValues = featureValues->GetFloatValues(0);
							if (waterLevelsValues)
							{
								float *waterLevels = waterLevelsValues->GetValues();
								if (waterLevels)
								{
									for (int j = 0; j < numberOfTimes; j++)
									{
										values.push_back(waterLevels[j]);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}


bool libS104::SetNextTime()
{
	auto timeList = theApp.s104Times;
	int size = (int)timeList.size();
	CString str;
	str.Format(_T("S-104 Time Size : %d\n"), size);
	OutputDebugString(str);
	if ((size - 1) > theApp.currentS104TimeIndex)
	{
		theApp.currentS104TimeIndex++;
		return true;
	}
	return false;
}


bool libS104::SetPrevTime()
{
	if (theApp.currentS104TimeIndex > 0)
	{
		theApp.currentS104TimeIndex--;
		return true;
	}
	return false;
}


void libS104::SetNow()
{
	if (theApp.s104vector.size() > 0)
	{
		time_t now = time(nullptr);

		S104 *s104File = (S104 *)theApp.s104vector.front();

		if (s104File)
		{
			if (auto s104 = s104File->s104)
			{
				if (auto feature = s104->GetRegularGrid(0))
				{
					if (auto timeInfo = feature->GetTimeInformation())
					{
						theApp.currentS104TimeIndex = timeInfo->GetNearestTimeIndex(now);
						return;
					}
				}
			}
		}
	}
}


void libS111::CalculateSpeedMinMax()
{
	float maxSpeed = 0;
	for (auto it = theApp.s111vector.begin(); it != theApp.s111vector.end(); it++)
	{
		S111* c = (S111*)*it;  

		for (auto sit = c->speed.begin(); sit != c->speed.end(); sit++){
			float* fs = *sit;

			for (int i = 0; i < c->metadata.numberOfNodes; i++)
			{
				float s = fs[i];

				maxSpeed = maxSpeed > s ? maxSpeed : s;
			}
		}
	}

	float unit = maxSpeed / S111_STEP_COUNT;
	S111::SPEED_RANGE[0] = 0;
	for (int i = 1; i < S111_STEP_COUNT - 1; i++)
	{
		S111::SPEED_RANGE[i] = unit * i;
	}
	S111::SPEED_RANGE[S111_STEP_COUNT - 1] = maxSpeed;
}


std::vector<float> libS111::GetS111Range()
{
	std::vector<float> range;
	range.push_back(S111::SPEED_RANGE[0]);
	range.push_back(S111::SPEED_RANGE[1]);
	range.push_back(S111::SPEED_RANGE[2]);
	range.push_back(S111::SPEED_RANGE[3]);
	range.push_back(S111::SPEED_RANGE[4]);
	range.push_back(S111::SPEED_RANGE[5]);
	range.push_back(S111::SPEED_RANGE[6]);
	range.push_back(S111::SPEED_RANGE[7]);
	range.push_back(S111::SPEED_RANGE[8]);

	return range;
}


void libS413::On(S413FeatureType type)
{
	for (
		auto i = theApp.s413vector.begin();
		i != theApp.s413vector.end();
		i++)
	{
		(*i)->bmpGrid.DeleteObject();
		(*i)->dc.DeleteDC();
		(*i)->bBMP = false;
	}

	theApp.onS413Type = type;
}


void libS413::Off()
{
	theApp.onS413Type = S413FeatureType::None;
}


libS413::S413FeatureType libS413::GetType(CString type)
{
	if (!type.CompareNoCase(_T("AvgWaveDir")))
		return AvgWaveDir;
	else if (!type.CompareNoCase(_T("AvgWavePrd")))
		return AvgWavePrd;

	else if (!type.CompareNoCase(_T("Humidity")))
		return Humidity;

	else if (!type.CompareNoCase(_T("MaxWaveDir")))
		return MaxWaveDir;

	else if (!type.CompareNoCase(_T("MaxWpkPrd")))
		return MaxWpkPrd;

	else if (!type.CompareNoCase(_T("NewSnowAmout3hr")))
		return NewSnowAmout3hr;

	else if (!type.CompareNoCase(_T("OceanCurrent")))
		return OceanCurrent;

	else if (!type.CompareNoCase(_T("Pressure")))
		return Pressure;

	else if (!type.CompareNoCase(_T("RainAmount3hr")))
		return RainAmount3hr;

	else if (!type.CompareNoCase(_T("SkyStatus")))
		return SkyStatus;

	else if (!type.CompareNoCase(_T("Temperature3hr")))
		return Temperature3hr;

	else if (!type.CompareNoCase(_T("Visibility")))
		return Visibility;
		
	else if (!type.CompareNoCase(_T("WaterSalt")))
		return WaterSalt;
		
	else if (!type.CompareNoCase(_T("WaterTemperature")))
		return WaterTemperature;
		
	else if (!type.CompareNoCase(_T("WaveHeightInst")))
		return WaveHeightInst;
		
	else if (!type.CompareNoCase(_T("WaveLength")))
		return WaveLength;
		
	else if (!type.CompareNoCase(_T("WaveWind")))
		return WaveWind;

	return None;
}


CString libS413::GetTypeString(S413FeatureType type)
{
	switch (type)
	{
	case AvgWaveDir:
		return _T("AvgWaveDir");
		break;
	case AvgWavePrd: 
		return _T("AvgWavePrd");
		break;
	case Humidity: 
		return _T("Humidity");
		break;
	case MaxWaveDir: 
		return _T("MaxWaveDir");
		break;
	case MaxWpkPrd: 
		return _T("MaxWpkPrd");
		break;
	case NewSnowAmout3hr: 
		return _T("NewSnowAmout3hr");
		break;
	case OceanCurrent: 
		return _T("OceanCurrent");
		break;
	case Pressure: 
		return _T("Pressure");
		break;
	case RainAmount3hr: 
		return _T("RainAmount3hr");
		break;
	case SkyStatus: 
		return _T("SkyStatus");
		break;
	case Temperature3hr: 
		return _T("Temperature3hr");
		break;
	case Visibility: 
		return _T("Visibility");
		break;
	case WaterSalt:
		return _T("WaterSalt");
		break;
	case WaterTemperature: 
		return _T("WaterTemperature");
		break;
	case WaveHeightInst:
		return _T("WaveHeightInst");
		break;
	case WaveLength:
		return _T("WaveLength");
		break;
	case WaveWind: 
		return _T("WaveWind");
		break;
	default:
		break;
	}

	return _T("");
}


libS413::S413FeatureType libS413::GetCurrentS413FeatureType()
{
	return theApp.onS413Type;
}


void libS413::SetNextTime()
{
	for (
		auto i = theApp.s413vector.begin();
		i != theApp.s413vector.end();
		i++)
	{
		(*i)->bmpGrid.DeleteObject();
		(*i)->dc.DeleteDC();
		(*i)->bBMP = false;
		(*i)->SetNextTime();
	}
}


void libS413::SetPrevTime()
{
	for (
		auto i = theApp.s413vector.begin();
		i != theApp.s413vector.end();
		i++)
	{
		(*i)->bmpGrid.DeleteObject();
		(*i)->dc.DeleteDC();
		(*i)->bBMP = false;
		(*i)->SetPrevTime();
	}
}


CString libS413::GetTime()
{
	if (theApp.s413vector.size() > 0)
	{
		auto s413 = theApp.s413vector.front();
		auto h5 = s413->_S413;
		if (h5)
		{
			if (auto feature = h5->GetIrregularGridFeature(0))
			{
				if (auto timeInfo = feature->GetTimeInformation())
				{
					auto time = timeInfo->GetTime(s413->_currentTimeIndex);
					tm stTM;
					localtime_s(&stTM, &time);
					CString str;
					str.Format(_T("%04d-%02d-%02d %02d:%02d"), stTM.tm_year + 1900, stTM.tm_mon + 1, stTM.tm_mday, stTM.tm_hour, stTM.tm_min);
					return str;
				}
			}
		}
	}

	return _T("");
}


void libS413::SetNowTime()
{
	for (
		auto i = theApp.s413vector.begin();
		i != theApp.s413vector.end();
		i++)
	{
		(*i)->bmpGrid.DeleteObject();
		(*i)->dc.DeleteDC();
		(*i)->bBMP = false;
		(*i)->SetNowTime();
	}
}


CString libS413::PickReport(float x, float y)
{
	CString result = _T("");

	for (
		auto i = theApp.s413vector.begin();
		i != theApp.s413vector.end();
		i++)
	{
		result = (*i)->PickReport(x, y);

		if (!result.IsEmpty())
		{
			return result;
		}
	}

	return result;
}


void libS413::GetLayerInformation(int &count, std::vector<std::wstring> &filenames)
{
	count = theApp.s413vector.size();

	for (
		auto i = theApp.s413vector.begin();
		i != theApp.s413vector.end();
		i++)
	{
		S413* s413 = *i;
		filenames.push_back(std::wstring(s413->m_FileName));
		s413->m_FileName.ReleaseBuffer();
	}
}


void libS111::GetLayerInformation(int &count, std::vector<std::wstring> &filenames)
{
	count = theApp.s111vector.size();

	for (
		auto i = theApp.s111vector.begin();
		i != theApp.s111vector.end();
		i++)
	{
		S111* s111 = (S111*)*i;
		filenames.push_back(std::wstring(s111->m_FileName));
		s111->m_FileName.ReleaseBuffer();
	}
}

void libS104::GetLayerInformation(int &count, std::vector<std::wstring> &filenames)
{
	count = theApp.s104vector.size();

	for ( 
		auto i = theApp.s104vector.begin();
		i != theApp.s104vector.end();
		i++)
	{
		S104* s104 = (S104*)*i;
		filenames.push_back(std::wstring(s104->m_FileName)); 
		s104->m_FileName.ReleaseBuffer();
	}
}


void libS102::CalculateDepthMinMax()
{ 
	int minDepth = 0, maxDepth = 0;
	for (auto itor = theApp.bags.begin(); itor != theApp.bags.end(); itor++)
	{
		Bag* bag = *itor;
		bag->CalcDepthMinMax();
		int curMin = 0, curMax = 0;
		bag->GetDepthMinMax(curMin, curMax);
		minDepth = minDepth < curMin ? minDepth : curMin;
		maxDepth = maxDepth < curMax ? maxDepth : curMax;
	}
	for (auto itor = theApp.bags.begin(); itor != theApp.bags.end(); itor++)
	{
		Bag* bag = *itor;
		bag->SetDepthMinMax(minDepth, maxDepth);
	}

	int gap = maxDepth - minDepth;

	float unit = gap / (S102_STEP_COUNT - 1);

	Bag::DEPTH_RANGE[0] = maxDepth;
	for (int i = 1; i < S102_STEP_COUNT - 1; i++)
	{
		Bag::DEPTH_RANGE[i] = maxDepth - unit * i;
	}
	Bag::DEPTH_RANGE[S102_STEP_COUNT - 1] = minDepth;
}


bool libS102::Open(std::wstring _filePath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	const char* filePath = LibMFCUtil::ConvertWCtoC((wchar_t*)std::wstring(_filePath).c_str());
	S100HDF5::S102 *s102 = new S100HDF5::S102();
	bool result = s102->Open(filePath);

	if (result)
	{
		Bag *bag = new Bag();
		bag->_pathName = filePath;
		bag->_S102 = s102;
		bag->SetMetadata();
		bag->CalcDepthMinMax();
		theApp.bags.push_back(bag);
		CalculateDepthMinMax();
	}

	delete[] filePath;

	return result;
}


void libS102::Draw(HDC &hDC, Scaler *scaler, Rect rectF, int scale)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (theApp.on == false) return;

	for (unsigned i = 0; i < theApp.bags.size(); i++)
	{
		Bag* bag = theApp.bags.at(i);
		bag->Draw(hDC, scaler, rectF);
	}

	int currentTimeIndex = libS111::GetCurTimeIndex();

	if (theApp.bDrawSelectedGrid)
	{
		CPoint pt;

		scaler->WorldToDevice(theApp.ptSelectedGrid->x, theApp.ptSelectedGrid->y,
			&pt.x, &pt.y); 
		CDC* pDC = CDC::FromHandle(hDC);

		CBrush brush;
		brush.CreateSolidBrush(RGB(192, 192, 192));

		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(192, 192, 192));

		pDC->SelectObject(&brush);
		pDC->SelectObject(&pen);
		pDC->Ellipse(pt.x - 5, pt.y - 5, pt.x + 5, pt.y + 5);
	}
}


void libS102::SetDC(CDC* pDC)
{
	theApp.pDC = pDC;

	auto bagList = theApp.bags;

	for (unsigned i = 0; i < bagList.size(); i++)
	{
		bagList.at(i)->CreateBitmap(theApp.pDC);
		bagList.at(i)->Close();
	}
}


void libS102::SetDC(HDC& hDC)
{
	theApp.pDC = CDC::FromHandle(hDC);

	SetDC(theApp.pDC);
}


bool libS102::GetData(GeoPoint* inputPt, GeoPoint* outputPt, float& depth, float scale)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	auto bagList = theApp.bags;
	for (unsigned i = 0; i < bagList.size(); i++)
	{
		Bag *bag = bagList.at(i);
		if (bag->IsContain(inputPt->x, inputPt->y))
		{
			if (!bag->IsOpen())
			{
				auto numOpenFile = GetNumberOfOpenFile();
				if (numOpenFile > 0)
				{
					for (auto j = bagList.begin(); j != bagList.end(); j++)
					{
						(*j)->Close();
					}
				}
				bag->ReOpen();
			}

			if (bagList.at(i)->GetData(*inputPt, *outputPt, depth))
			{
				return true;
			}
		}
	}

	theApp.bDrawSelectedGrid = false;
	return false;
}


bool libS102::SetSelectedData(GeoPoint* selectedPt, float scale)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	bool isValid = false;
	GeoPoint outputPt;
	for (unsigned i = 0; i < theApp.bags.size(); i++)
	{
		Bag* bag = theApp.bags.at(i);
		float x = selectedPt->x;
		float y = selectedPt->y;
		float depth = 0;

		if (x >= bag->xmin && x <= bag->xmax &&
			y >= bag->ymin && y <= bag->ymax)
		{
			isValid = bag->GetData(*selectedPt, outputPt, depth);
		}

		if (isValid) break;
	}

	if (isValid)
	{
		*theApp.ptSelectedGrid = outputPt;
		theApp.bDrawSelectedGrid = true;
	}
	else
	{
		theApp.bDrawSelectedGrid = false;
	}

	return false;
}


void libS102::ClearSelectedData()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.bDrawSelectedGrid = false;
}


void libS102::On()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.on = true;
}


void libS102::Off()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	theApp.on = false;
}


bool libS102::IsOn()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.on;
}  
void libS102::SetColorMode(int mode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (mode == 0 ||
		mode == 1 ||
		mode == 2)
	{
		Bag::DRAWING_MODE = mode;
		if (theApp.pDC)
			SetDC(theApp.pDC);
	}

	if (mode == 100)
	{
		theApp.bS104 = true;
		if (theApp.pDC)
			SetDC(theApp.pDC);
	}
	else if (mode == 200)
	{
		theApp.bS104 = false;
		if (theApp.pDC)
			SetDC(theApp.pDC);
	}

	return;            


}

int libS102::GetColorMode()
{ 
	return theApp.bS104;
}

void libS102::SetTime(time_t time)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	for (unsigned i = 0; i < theApp.bags.size(); i++)
	{
		Bag* bag = theApp.bags.at(i);

		bag->SetSummaryValues();
	}
}

void libS102::SetSafetyDepth(float depth)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	Bag::SAFETY_DEPTH = -depth;

	if (Bag::DRAWING_MODE == 1 || Bag::DRAWING_MODE == 101)
		SetDC(theApp.pDC);
}

std::vector<int> libS102::GetS102Range()
{
	std::vector<int> range;
	range.push_back(Bag::DEPTH_RANGE[0]);
	range.push_back(Bag::DEPTH_RANGE[1]);
	range.push_back(Bag::DEPTH_RANGE[2]);
	range.push_back(Bag::DEPTH_RANGE[3]);
	range.push_back(Bag::DEPTH_RANGE[4]);
	range.push_back(Bag::DEPTH_RANGE[5]);
	range.push_back(Bag::DEPTH_RANGE[6]);
	return range;
}

void libS102::CombineS104()
{
	auto bagList = theApp.bags;
	for (auto i = bagList.begin(); i != bagList.end(); i++)
	{
		Bag *bag = (*i);

	}
}


void libS102::Close()
{
	auto bagList = theApp.bags;
	for (auto i = bagList.begin(); i != bagList.end(); i++)
	{
		Bag *bag = (*i);
		bag->Close();
	}
}


int libS102::GetNumberOfOpenFile()
{
	int num = 0;
	auto bagList = theApp.bags;
	for (auto i = bagList.begin(); i != bagList.end(); i++)
	{
		Bag *bag = (*i);
		if (bag->IsOpen())
		{
			num++;
		}
	}

	return num;
}


void libS102::GetLayerInformation(int &count, std::vector<std::wstring> &filenames)
{
	count = theApp.bags.size();

	for (
		auto i = theApp.bags.begin();
		i != theApp.bags.end();
		i++)
	{
		Bag* bag = (Bag*)*i; 
		filenames.push_back(std::wstring(bag->fileName));
		bag->fileName.ReleaseBuffer();
	}
}


bool libS102::GetS104Mode()
{
	return theApp.bS104;
}