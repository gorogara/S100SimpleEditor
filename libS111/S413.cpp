#include "stdafx.h"
#include "S111.h"
#include "S413.h"

#include "..\\LibMFCUtil\\LibMFCUtil.h"
#include "..\\S100Engine\\S100Engine.h"
#include "GeoMetryLibrary\\Scaler.h" 

double interpolate(double val, double y0, double x0, double y1, double x1) {
	return (val - x0)*(y1 - y0) / (x1 - x0) + y0;
}

double base(double val) {
	if (val <= -0.75) return 0;
	else if (val <= -0.25) return interpolate(val, 0.0, -0.75, 1.0, -0.25);
	else if (val <= 0.25) return 1.0;
	else if (val <= 0.75) return interpolate(val, 1.0, 0.25, 0.0, 0.75);
	else return 0.0;
}

double red(double gray) {
	return base(gray - 0.5);
}
double green(double gray) {
	return base(gray);
}
double blue(double gray) {
	return base(gray + 0.5);
}

S413::S413()
{
}

S413::~S413()
{
	if (bmpGrid.GetSafeHandle())
	{
		dc.DeleteDC();
		bmpGrid.DeleteObject();
		bBMP = false;
	}

	delete _S413;
	_S413 = nullptr;
}

bool S413::Open(CString path)
{
	CFile tmp_file;
	if (tmp_file.Open(path, CFile::modeRead | CFile::shareDenyNone)) {
		m_FilePath = tmp_file.GetFilePath();
		m_FileName = tmp_file.GetFileTitle();
		tmp_file.Close();
	}

	_S413 = new S100HDF5::S413();
	
	char *cpath = LibMFCUtil::ConvertWCtoC((wchar_t *)std::wstring(path).c_str());

	if (!_S413->Open(cpath))
	{
		delete[] cpath;
		return false;
	}

	auto feature = _S413->GetIrregularGridFeature(0);
	if (feature)
	{
		auto timeInfo = feature->GetTimeInformation();
		if (timeInfo)
		{
			_timeCount = timeInfo->GetNumberOfTimes();
			time_t now = time(nullptr);
			_currentTimeIndex = timeInfo->GetNearestTimeIndex(now);
		}

		auto gridInfo = feature->GetIrregularGridInformation();
		ncols = (int)sqrt(gridInfo->GetNumberOfNodes());
		nrows = ncols;
		auto boundingBox = _S413->GetMBR();
		xmin = (float)boundingBox.xmin;
		ymin = (float)boundingBox.ymin;
		xmax = (float)boundingBox.xmax;
		ymax = (float)boundingBox.ymax;
		dx = (xmax - xmin) / ncols;
		dy = (ymax - ymin) / nrows;
	}

	delete[] cpath;

	return true;
}

void S413::DrawTextFeature(
	ID2D1RenderTarget* pRenderTarget,
	ID2D1SolidColorBrush* pBrush,
	ID2D1StrokeStyle1* pStroke,
	IDWriteFactory* pDWriteFactory,
	IDWriteTextFormat* pTextFormat,
	Gdiplus::Rect rectF,
	S100HDF5::IrregularGridFeature *feature,
	Scaler *scaler)
{
	if (!feature)
	{
		return;
	}

	S100HDF5::IrregularGridInformation *gridInfo = feature->GetIrregularGridInformation();

	if (!gridInfo)
	{
		return;
	}

	int numberOfNodes = gridInfo->GetNumberOfNodes();
	S100HDF5::Point *positions = gridInfo->GetPositioning();

	if (!positions)
	{
		return;
	}

	pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Aquamarine));

	for (int i = 0; i < numberOfNodes; i++)
	{
		S100HDF5::IrregularGridFeatureValues *featureValues = feature->GetIrregularGridFeatureValues(_currentTimeIndex);

		if (!featureValues)
		{
			return;
		}

		S100HDF5::FloatValues *directionValues = featureValues->GetFloatValues(0);

		if (!directionValues)
		{
			return;
		}

		float *dir = directionValues->GetValues();

		CPoint screenPoint;
		GeoPoint mapPoint;
		mapPoint.x = positions[i].X;
		mapPoint.y = positions[i].Y;

		scaler->WorldToDevice(mapPoint.x, mapPoint.y, &screenPoint.x, &screenPoint.y); 

		CString strValue;

		double currentDir = dir[i];

		if (currentDir < 0)
		{
			continue;
		}

		strValue.Format(_T("%.2f"), currentDir);

		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		D2D1_RECT_F d2Rect = { 
			(FLOAT)screenPoint.x - 5, 
			(FLOAT)screenPoint.y - 5,
			(FLOAT)screenPoint.x + 5,
			(FLOAT)screenPoint.y + 5 };

		if (S111::app)
		{
			pRenderTarget->DrawTextW(
				strValue,
				strValue.GetLength(),
				pTextFormat,
				d2Rect,
				pBrush
			);
		}
	}
}

void S413::DrawHumidity(
	ID2D1RenderTarget* pRenderTarget,
	ID2D1SolidColorBrush* pBrush,
	ID2D1StrokeStyle1* pStroke,
	IDWriteFactory* pDWriteFactory,
	IDWriteTextFormat* pTextFormat,
	Gdiplus::Rect rectF,
	S100HDF5::IrregularGridFeature *feature, 
	Scaler *scaler)
{
	if (!feature)
	{
		return;
	}

	S100HDF5::IrregularGridInformation *gridInfo = feature->GetIrregularGridInformation();

	if (!gridInfo)
	{
		return;
	}

	int numberOfNodes = gridInfo->GetNumberOfNodes();
	S100HDF5::Point *positions = gridInfo->GetPositioning();

	if (!positions)
	{
		return;
	}

	for (int i = 0; i < numberOfNodes; i++)
	{
		S100HDF5::IrregularGridFeatureValues *featureValues = feature->GetIrregularGridFeatureValues(_currentTimeIndex);

		if (!featureValues)
		{
			return;
		}

		S100HDF5::FloatValues *humidityValues = featureValues->GetFloatValues(0);

		if (!humidityValues)
		{
			return;
		}

		float *humidity = humidityValues->GetValues();

		CPoint screenPoint;
		GeoPoint mapPoint;
		mapPoint.x = positions[i].X;
		mapPoint.y = positions[i].Y;

		scaler->WorldToDevice(mapPoint.x, mapPoint.y, &screenPoint.x, &screenPoint.y);

		CString symbolName;

		double currentHumidity = humidity[i];
		if (currentHumidity < 0)
		{
			continue;
		}
		else if (currentHumidity < 90)
		{
			symbolName = _T("HUMDTY01");
		}
		else 
		{
			symbolName = _T("HUMDTY02");
		}

		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		if (S111::app)
		{
			S111::app->s100Engine->DrawSymbol(
				std::wstring(symbolName),
				pRenderTarget,
				pBrush,
				pStroke,
				D2D1::Point2F(screenPoint.x, screenPoint.y),
				0,
				2.5);
		}
	}
}

void S413::DrawOceanCurrent(
	ID2D1RenderTarget* pRenderTarget,
	ID2D1SolidColorBrush* pBrush,
	ID2D1StrokeStyle1* pStroke,
	IDWriteFactory* pDWriteFactory,
	IDWriteTextFormat* pTextFormat,
	Gdiplus::Rect rectF,
	S100HDF5::IrregularGridFeature *feature,
	Scaler *scaler)
{
	if (!feature)
	{
		return;
	}

	S100HDF5::IrregularGridInformation *gridInfo = feature->GetIrregularGridInformation();

	if (!gridInfo)
	{
		return;
	}

	int numberOfNodes = gridInfo->GetNumberOfNodes();
	S100HDF5::Point *positions = gridInfo->GetPositioning();

	if (!positions)
	{
		return;
	}

	for (int i = 0; i < numberOfNodes; i++)
	{
		S100HDF5::IrregularGridFeatureValues *featureValues = feature->GetIrregularGridFeatureValues(_currentTimeIndex);

		if (!featureValues)
		{
			return;
		}

		S100HDF5::FloatValues *directionValues = featureValues->GetFloatValues(0);
		S100HDF5::FloatValues *speedValues = featureValues->GetFloatValues(1);

		if (!directionValues || !directionValues)
		{
			return;
		}

		float *direction = directionValues->GetValues();
		float *speed = speedValues->GetValues();

		CPoint screenPoint;
		GeoPoint mapPoint;
		mapPoint.x = positions[i].X;
		mapPoint.y = positions[i].Y;

		scaler->WorldToDevice(mapPoint.x, mapPoint.y, &screenPoint.x, &screenPoint.y);

		CString symbolName;

		double currentSpeed = speed[i];
		if (currentSpeed < 0)
		{
			continue;
		}
		else if (currentSpeed <= 0.49)
		{
			symbolName = _T("SCAROW01");
		}
		else if (currentSpeed <= 0.99)
		{
			symbolName = _T("SCAROW02");
		}
		else 
		{
			symbolName = _T("SCAROW09");
		}
		
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		if (S111::app)
		{
			S111::app->s100Engine->DrawSymbol(
				std::wstring(symbolName),
				pRenderTarget,
				pBrush,
				pStroke,
				D2D1::Point2F(screenPoint.x, screenPoint.y),
				direction[i],
				2.5);
		}
	}
}

void S413::DrawDirection(
	ID2D1RenderTarget* pRenderTarget,
	ID2D1SolidColorBrush* pBrush,
	ID2D1StrokeStyle1* pStroke,
	IDWriteFactory* pDWriteFactory,
	IDWriteTextFormat* pTextFormat,
	Gdiplus::Rect rectF,
	S100HDF5::IrregularGridFeature *feature,
	Scaler *scaler)
{
	if (!feature)
	{
		return;
	}

	S100HDF5::IrregularGridInformation *gridInfo = feature->GetIrregularGridInformation();

	if (!gridInfo)
	{
		return;
	}

	int numberOfNodes = gridInfo->GetNumberOfNodes();
	S100HDF5::Point *positions = gridInfo->GetPositioning();

	if (!positions)
	{
		return;
	}

	for (int i = 0; i < numberOfNodes; i++)
	{
		S100HDF5::IrregularGridFeatureValues *featureValues = feature->GetIrregularGridFeatureValues(_currentTimeIndex);

		if (!featureValues)
		{
			return;
		}

		S100HDF5::FloatValues *directionValues = featureValues->GetFloatValues(0);

		if (!directionValues)
		{
			return;
		}

		float *direction = directionValues->GetValues();

		CPoint screenPoint;
		GeoPoint mapPoint;
		mapPoint.x = positions[i].X;
		mapPoint.y = positions[i].Y;

		scaler->WorldToDevice(mapPoint.x, mapPoint.y, &screenPoint.x, &screenPoint.y);

		CString symbolName;
		symbolName = _T("SCAROW01");
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		if (S111::app)
		{
			S111::app->s100Engine->DrawSymbol(
				std::wstring(symbolName),
				pRenderTarget,
				pBrush,
				pStroke,
				D2D1::Point2F(screenPoint.x, screenPoint.y),
				direction[i],
				2.5);
		}
	}
}

void S413::DrawTemperature(
		ID2D1RenderTarget* pRenderTarget,
		ID2D1SolidColorBrush* pBrush,
		ID2D1StrokeStyle1* pStroke,
		IDWriteFactory* pDWriteFactory,
		IDWriteTextFormat* pTextFormat,
		Gdiplus::Rect rectF,
		S100HDF5::IrregularGridFeature *feature,
		Scaler *scaler)
{
	if (!feature)
	{
		return;
	}

	S100HDF5::IrregularGridInformation *gridInfo = feature->GetIrregularGridInformation();

	if (!gridInfo)
	{
		return;
	}

	int numberOfNodes = gridInfo->GetNumberOfNodes();
	S100HDF5::Point *positions = gridInfo->GetPositioning();

	if (!positions)
	{
		return;
	}

	for (int i = 0; i < numberOfNodes; i++)
	{
		S100HDF5::IrregularGridFeatureValues *featureValues = feature->GetIrregularGridFeatureValues(_currentTimeIndex);

		if (!featureValues)
		{
			return;
		}

		S100HDF5::FloatValues *humidityValues = featureValues->GetFloatValues(0);

		if (!humidityValues)
		{
			return;
		}

		float *humidity = humidityValues->GetValues();

		CPoint screenPoint;
		GeoPoint mapPoint;
		mapPoint.x = positions[i].X;
		mapPoint.y = positions[i].Y;


		scaler->WorldToDevice(mapPoint.x, mapPoint.y, &screenPoint.x, &screenPoint.y);

		CString symbolName;

		double currentHumidity = humidity[i];
		if (currentHumidity < 0)
		{
			continue;
		}
		else if (currentHumidity < 20)
		{
			symbolName = _T("TEMPER01");
		}
		else
		{
			symbolName = _T("TEMPER02");
		}

		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		if (S111::app)
		{
			S111::app->s100Engine->DrawSymbol(
				std::wstring(symbolName),
				pRenderTarget,
				pBrush,
				pStroke,
				D2D1::Point2F(screenPoint.x, screenPoint.y),
				0,
				2.5);
		}
	}
}

void S413::DrawWaterSalt(
	ID2D1RenderTarget* pRenderTarget,
	ID2D1SolidColorBrush* pBrush,
	ID2D1StrokeStyle1* pStroke,
	IDWriteFactory* pDWriteFactory,
	IDWriteTextFormat* pTextFormat,
	Gdiplus::Rect rectF,
	S100HDF5::IrregularGridFeature *feature,
	Scaler *scaler)
{
	if (!feature)
	{
		return;
	}

	S100HDF5::IrregularGridInformation *gridInfo = feature->GetIrregularGridInformation();

	if (!gridInfo)
	{
		return;
	}

	int numberOfNodes = gridInfo->GetNumberOfNodes();
	S100HDF5::Point *positions = gridInfo->GetPositioning();

	if (!positions)
	{
		return;
	}

	for (int i = 0; i < numberOfNodes; i++)
	{
		S100HDF5::IrregularGridFeatureValues *featureValues = feature->GetIrregularGridFeatureValues(_currentTimeIndex);

		if (!featureValues)
		{
			return;
		}

		S100HDF5::FloatValues *humidityValues = featureValues->GetFloatValues(0);

		if (!humidityValues)
		{
			return;
		}

		float *humidity = humidityValues->GetValues();

		CPoint screenPoint;
		GeoPoint mapPoint;
		mapPoint.x = positions[i].X;
		mapPoint.y = positions[i].Y;

		scaler->WorldToDevice(mapPoint.x, mapPoint.y, &screenPoint.x, &screenPoint.y);

		CString symbolName;

		double currentHumidity = humidity[i];
		if (currentHumidity < 0)
		{
			continue;
		}
		else if (currentHumidity < 31)
		{
			symbolName = _T("WATSLT01");
		}
		else 
		{
			symbolName = _T("WATSLT02");
		}

		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		if (S111::app)
		{
			S111::app->s100Engine->DrawSymbol(
				std::wstring(symbolName),
				pRenderTarget,
				pBrush,
				pStroke,
				D2D1::Point2F(screenPoint.x, screenPoint.y),
				0,
				2.5);
		}
	}
}

void S413::DrawSkyStatus(
	ID2D1RenderTarget* pRenderTarget,
	ID2D1SolidColorBrush* pBrush,
	ID2D1StrokeStyle1* pStroke,
	IDWriteFactory* pDWriteFactory,
	IDWriteTextFormat* pTextFormat,
	Gdiplus::Rect rectF,
	S100HDF5::IrregularGridFeature *feature,
	Scaler *scaler)
{
	if (!feature)
	{
		return;
	}

	S100HDF5::IrregularGridInformation *gridInfo = feature->GetIrregularGridInformation();

	if (!gridInfo)
	{
		return;
	}

	int numberOfNodes = gridInfo->GetNumberOfNodes();
	S100HDF5::Point *positions = gridInfo->GetPositioning();

	if (!positions)
	{
		return;
	}

	for (int i = 0; i < numberOfNodes; i++)
	{
		S100HDF5::IrregularGridFeatureValues *featureValues = feature->GetIrregularGridFeatureValues(_currentTimeIndex);

		if (!featureValues)
		{
			return;
		}

		S100HDF5::FloatValues *humidityValues = featureValues->GetFloatValues(0);

		if (!humidityValues)
		{
			return;
		}

		float *humidity = humidityValues->GetValues();

		CPoint screenPoint;
		GeoPoint mapPoint;
		mapPoint.x = positions[i].X;
		mapPoint.y = positions[i].Y;

		scaler->WorldToDevice(mapPoint.x, mapPoint.y, &screenPoint.x, &screenPoint.y);

		CString symbolName;

		double currentHumidity = humidity[i];
		if (currentHumidity < 1.1)
		{
			symbolName = _T("SUNNYW01");
		}
		else if (currentHumidity < 2.1)
		{
			symbolName = _T("LOWCLD01");
		}
		else if (currentHumidity < 3.1)
		{
			symbolName = _T("HIGCLD01");
		}
		else if (currentHumidity < 4.1)
		{
			symbolName = _T("CLOUDY01");
		}

		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		if (S111::app)
		{
			S111::app->s100Engine->DrawSymbol(
				std::wstring(symbolName),
				pRenderTarget,
				pBrush,
				pStroke,
				D2D1::Point2F(screenPoint.x, screenPoint.y),
				0,
				2.5);
		}
	}
}

void S413::DrawWaterTemperature(
	ID2D1RenderTarget* pRenderTarget,
	ID2D1SolidColorBrush* pBrush,
	ID2D1StrokeStyle1* pStroke,
	IDWriteFactory* pDWriteFactory,
	IDWriteTextFormat* pTextFormat,
	Gdiplus::Rect rectF,
	S100HDF5::IrregularGridFeature *feature,
	Scaler *scaler)
{
	if (!feature)
	{
		return;
	}

	S100HDF5::IrregularGridInformation *gridInfo = feature->GetIrregularGridInformation();

	if (!gridInfo)
	{
		return;
	}

	int numberOfNodes = gridInfo->GetNumberOfNodes();
	S100HDF5::Point *positions = gridInfo->GetPositioning();

	if (!positions)
	{
		return;
	}

	for (int i = 0; i < numberOfNodes; i++)
	{
		S100HDF5::IrregularGridFeatureValues *featureValues = feature->GetIrregularGridFeatureValues(_currentTimeIndex);

		if (!featureValues)
		{
			return;
		}

		S100HDF5::FloatValues *humidityValues = featureValues->GetFloatValues(0);

		if (!humidityValues)
		{
			return;
		}

		float *humidity = humidityValues->GetValues();

		CPoint screenPoint;
		GeoPoint mapPoint;
		mapPoint.x = positions[i].X;
		mapPoint.y = positions[i].Y;

		scaler->WorldToDevice(mapPoint.x, mapPoint.y, &screenPoint.x, &screenPoint.y);

		CString symbolName;

		double currentHumidity = humidity[i];
		if (currentHumidity < 0)
		{
			continue;
		}
		else if (currentHumidity < 20)
		{
			symbolName = _T("WATEMP01");
		}
		else 
		{
			symbolName = _T("WATEMP02");
		}

		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		if (S111::app)
		{
			S111::app->s100Engine->DrawSymbol(
				std::wstring(symbolName),
				pRenderTarget,
				pBrush,
				pStroke,
				D2D1::Point2F(screenPoint.x, screenPoint.y),
				0,
				2.5);
		}
	}
}

void S413::DrawVisibility(
	ID2D1RenderTarget* pRenderTarget,
	ID2D1SolidColorBrush* pBrush,
	ID2D1StrokeStyle1* pStroke,
	IDWriteFactory* pDWriteFactory,
	IDWriteTextFormat* pTextFormat,
	Gdiplus::Rect rectF,
	S100HDF5::IrregularGridFeature *feature, 
	Scaler *scaler)
{
	if (!feature)
	{
		return;
	}

	S100HDF5::IrregularGridInformation *gridInfo = feature->GetIrregularGridInformation();

	if (!gridInfo)
	{
		return;
	}

	int numberOfNodes = gridInfo->GetNumberOfNodes();
	S100HDF5::Point *positions = gridInfo->GetPositioning();

	if (!positions)
	{
		return;
	}

	for (int i = 0; i < numberOfNodes; i++)
	{
		S100HDF5::IrregularGridFeatureValues *featureValues = feature->GetIrregularGridFeatureValues(_currentTimeIndex);

		if (!featureValues)
		{
			return;
		}

		S100HDF5::FloatValues *humidityValues = featureValues->GetFloatValues(0);

		if (!humidityValues)
		{
			return;
		}

		float *humidity = humidityValues->GetValues();

		CPoint screenPoint;
		GeoPoint mapPoint;
		mapPoint.x = positions[i].X;
		mapPoint.y = positions[i].Y;

		scaler->WorldToDevice(mapPoint.x, mapPoint.y, &screenPoint.x, &screenPoint.y);

		CString symbolName;

		double currentHumidity = humidity[i];
		if (currentHumidity < 0)
		{
			continue;
		}
		else if (currentHumidity < 20)
		{
			symbolName = _T("SCVISIBILITY01");
		}
		else if (currentHumidity < 21)
		{
			symbolName = _T("SCVISIBILITY06");
		}
		else if (currentHumidity < 22)
		{
			symbolName = _T("SCVISIBILITY02");
		}
		else if (currentHumidity < 23)
		{
			symbolName = _T("SCVISIBILITY05");
		}
		else if (currentHumidity < 24)
		{
			symbolName = _T("SCVISIBILITY03");
		}
		else if (currentHumidity)
		{
			symbolName = _T("SCVISIBILITY04");
		}

		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		if (S111::app)
		{
			S111::app->s100Engine->DrawSymbol(
				std::wstring(symbolName),
				pRenderTarget,
				pBrush,
				pStroke,
				D2D1::Point2F(screenPoint.x, screenPoint.y),
				0,
				2.5);
		}
	}
}

void S413::DrawWaveWind(
	ID2D1RenderTarget* pRenderTarget,
	ID2D1SolidColorBrush* pBrush,
	ID2D1StrokeStyle1* pStroke,
	Gdiplus::Rect rectF,
	S100HDF5::IrregularGridFeature *feature,
	Scaler *scaler)
{
	if (!feature)
	{
		return;
	}

	S100HDF5::IrregularGridInformation *gridInfo = feature->GetIrregularGridInformation();

	if (!gridInfo)
	{
		return;
	}

	int numberOfNodes = gridInfo->GetNumberOfNodes();
	S100HDF5::Point *positions = gridInfo->GetPositioning();

	if (!positions)
	{
		return;
	}

	for (int i = 0; i < numberOfNodes; i++)
	{
		S100HDF5::IrregularGridFeatureValues *featureValues = feature->GetIrregularGridFeatureValues(_currentTimeIndex);

		if (!featureValues)
		{
			return;
		}

		S100HDF5::FloatValues *directionValues = featureValues->GetFloatValues(0);
		S100HDF5::FloatValues *speedValues = featureValues->GetFloatValues(1);

		if (!directionValues || !directionValues)
		{
			return;
		}

		float *direction = directionValues->GetValues();
		float *speed = speedValues->GetValues();

		CPoint screenPoint;
		GeoPoint mapPoint;
		mapPoint.x = positions[i].X;
		mapPoint.y = positions[i].Y;

		scaler->Projection(&mapPoint.x, &mapPoint.y);

		scaler->WorldToDevice(mapPoint.x, mapPoint.y, &screenPoint.x, &screenPoint.y);

		CString symbolName;

		double currentSpeed = speed[i];
		if (currentSpeed < 0)
		{
			continue;
		}
		else if (currentSpeed <= 5)
		{
			symbolName = _T("SUWIND05");
		}
		else if (currentSpeed <= 10)
		{
			symbolName = _T("SUWIND10");
		}
		else if (currentSpeed <= 15)
		{
			symbolName = _T("SUWIND15");
		}
		else if (currentSpeed <= 20)
		{
			symbolName = _T("SUWIND20");
		}
		else if (currentSpeed <= 25)
		{
			symbolName = _T("SUWIND25");
		}
		else if (currentSpeed <= 30)
		{
			symbolName = _T("SUWIND30");
		}
		else if (currentSpeed <= 35)
		{
			symbolName = _T("SUWIND35");
		}
		else if (currentSpeed <= 40)
		{
			symbolName = _T("SUWIND40");
		}
		else if (currentSpeed <= 45)
		{
			symbolName = _T("SUWIND45");
		}
		else if (currentSpeed <= 50)
		{
			symbolName = _T("SUWIND50");
		}
		else if (currentSpeed <= 55)
		{
			symbolName = _T("SUWIND55");
		}
		else if (currentSpeed <= 60)
		{
			symbolName = _T("SUWIND60");
		}
		else if (currentSpeed <= 65)
		{
			symbolName = _T("SUWIND65");
		}
		else if (currentSpeed <= 70)
		{
			symbolName = _T("SUWIND70");
		}
		else if (currentSpeed <= 75)
		{
			symbolName = _T("SUWIND75");
		}
		else if (currentSpeed <= 80)
		{
			symbolName = _T("SUWIND80");
		}
		else if (currentSpeed <= 85)
		{
			symbolName = _T("SUWIND85");
		}
		else if (currentSpeed <= 90)
		{
			symbolName = _T("SUWIND90");
		}
		else if (currentSpeed <= 95)
		{
			symbolName = _T("SUWIND95");
		}
		else if (currentSpeed <= 100)
		{
			symbolName = _T("SUWIND100");
		}
		else if (currentSpeed <= 105)
		{
			symbolName = _T("SUWIND105");
		}
		else if (currentSpeed <= 110)
		{
			symbolName = _T("SUWIND110");
		}
		else if (currentSpeed <= 115)
		{
			symbolName = _T("SUWIND115");
		}
		else if (currentSpeed <= 120)
		{
			symbolName = _T("SUWIND120");
		}
		else if (currentSpeed <= 125)
		{
			symbolName = _T("SUWIND125");
		}
		else if (currentSpeed <= 130)
		{
			symbolName = _T("SUWIND130");
		}
		else if (currentSpeed <= 135)
		{
			symbolName = _T("SUWIND135");
		}
		else
		{
			symbolName = _T("SUWIND140");
		}

		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		if (S111::app)
		{
			S111::app->s100Engine->DrawSymbol(
				std::wstring(symbolName),
				pRenderTarget,
				pBrush,
				pStroke,
				D2D1::Point2F(screenPoint.x, screenPoint.y),
				direction[i],
				2.5);
		}
	}
}

void S413::Draw(
	ID2D1RenderTarget* pRenderTarget,
	ID2D1SolidColorBrush* pBrush,
	ID2D1StrokeStyle1* pStroke,
	Gdiplus::Rect rectF,
	Scaler *scaler)
{
	if (!_S413)
	{
		return;
	}

	int featureCount = _S413->GetIrregularGridFeatureCount();

	for (int i = 0; i < featureCount; i++)
	{
		S100HDF5::IrregularGridFeature *feature = _S413->GetIrregularGridFeature(i);

		if (!feature)
		{
			return;
		}


		if (strcmp(feature->GetName(), "AvgWaveDir") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "AvgWavePrd") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "Humidity") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "MaxWaveDir") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "MaxWpkPrd") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "NewSnowAmout3hr") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "OceanCurrent") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "Pressure") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "RainAmount3hr") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "SkyStatus") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "Temperature3hr") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "Visibility") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "WaterSalt") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "WaterTemperature") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "WaveHeightInst") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "WaveLength") == 0)
		{

		}
		else if (strcmp(feature->GetName(), "WaveWind") == 0)
		{
			DrawWaveWind(pRenderTarget, pBrush, pStroke, rectF, feature, scaler);
		}
	}
}

void S413::Draw(
	std::string featureName,
	ID2D1RenderTarget* pRenderTarget,
	ID2D1SolidColorBrush* pBrush,
	ID2D1StrokeStyle1* pStroke,
	Gdiplus::Rect rectF,
	Scaler *scaler)
{
	if (!_S413)
	{
		return;
	}

	int featureCount = _S413->GetIrregularGridFeatureCount();

	for (int i = 0; i < featureCount; i++)
	{
		S100HDF5::IrregularGridFeature *feature = _S413->GetIrregularGridFeature(i);

		if (!feature)
		{
			return;
		}

		if (strcmp(feature->GetName(), featureName.c_str()) == 0)
		{
			if (strcmp(feature->GetName(), "AvgWaveDir") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"AvgWavePrd") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"Humidity") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"MaxWaveDir") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"MaxWpkPrd") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"NewSnowAmout3hr") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"OceanCurrent") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"Pressure") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"RainAmount3hr") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"SkyStatus") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"Temperature3hr") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"Visibility") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"WaterSalt") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"WaterTemperature") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"WaveHeightInst") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"WaveLength") == 0)
			{

			}
			else if (strcmp(feature->GetName(),"WaveWind") == 0)
			{
				DrawWaveWind(pRenderTarget, pBrush, pStroke, rectF, feature, scaler);
			}
		}
	}
}

void S413::SetNextTime()
{
	if (_currentTimeIndex >= 0 &&
		_currentTimeIndex < (_timeCount - 1))
	{
		_currentTimeIndex++;
	}
}

void S413::SetPrevTime()
{
	if (_currentTimeIndex >= 1 &&
		_currentTimeIndex < _timeCount)
	{
		_currentTimeIndex--;
	}
}

void S413::SetNowTime()
{
	auto feature = _S413->GetIrregularGridFeature(0);
	if (feature)
	{
		auto timeInfo = feature->GetTimeInformation();
		if (timeInfo)
		{
			time_t now = time(nullptr);
			_currentTimeIndex = timeInfo->GetNearestTimeIndex(now);
		}
	}
}

CString S413::PickReport(float x, float y)
{
	CString result = _T("");

	auto feature = _S413->GetIrregularGridFeature(0);
	if (!feature)
	{
		return result;
	}

	auto timeInfo = feature->GetTimeInformation();
	if (!timeInfo)
	{
		return result;
	}

	time_t currentTime = timeInfo->GetTime(_currentTimeIndex);
	S100HDF5::PickReportResult pickReportResult;
	std::string featureName = "";

	switch (libS413::GetCurrentS413FeatureType())
	{
	case libS413::S413FeatureType::AvgWaveDir:
		featureName = "AvgWaveDir";
		break;
	case libS413::S413FeatureType::AvgWavePrd:
		featureName = "AvgWavePrd";
		break;
	case libS413::S413FeatureType::Humidity:
		featureName = "Humidity";
		break;
	case libS413::S413FeatureType::MaxWaveDir:
		featureName = "MaxWaveDir";
		break;
	case libS413::S413FeatureType::MaxWpkPrd:
		featureName = "MaxWpkPrd";
		break;
	case libS413::S413FeatureType::NewSnowAmout3hr:
		featureName = "NewSnowAmout3hr";
		break;
	case libS413::S413FeatureType::OceanCurrent:
		featureName = "OceanCurrent";
		break;
	case libS413::S413FeatureType::Pressure:
		featureName = "Pressure";
		break;
	case libS413::S413FeatureType::RainAmount3hr:
		featureName = "RainAmount3hr";
		break;
	case libS413::S413FeatureType::SkyStatus:
		featureName = "SkyStatus";
		break;
	case libS413::S413FeatureType::Temperature3hr:
		featureName = "Temperature3hr";
		break;
	case libS413::S413FeatureType::Visibility:
		featureName = "Visibility";
		break;
	case libS413::S413FeatureType::WaterSalt:
		featureName = "WaterSalt";
		break;
	case libS413::S413FeatureType::WaterTemperature:
		featureName = "WaterTemperature";
		break;
	case libS413::S413FeatureType::WaveHeightInst:
		featureName = "WaveHeightInst";
		break;
	case libS413::S413FeatureType::WaveLength:
		featureName = "WaveLength";
		break;
	case libS413::S413FeatureType::WaveWind:
		featureName = "WaveWind";
		break;
	}

	pickReportResult = _S413->PickReport(x, y, currentTime, featureName.c_str());

	switch (libS413::GetCurrentS413FeatureType())
	{
	case libS413::S413FeatureType::AvgWaveDir:
		result.Format(_T("AvgWaveDir : %.2f"), pickReportResult.GetValue(0));
		break;
	case libS413::S413FeatureType::AvgWavePrd:
		result.Format(_T("AvgWavePrd : %.2f"), pickReportResult.GetValue(0));
		break;
	case libS413::S413FeatureType::Humidity:
		result.Format(_T("Humidity : %.2f"), pickReportResult.GetValue(0));
		break;
	case libS413::S413FeatureType::MaxWaveDir:
		result.Format(_T("MaxWaveDir : %.2f"), pickReportResult.GetValue(0));
		break;
	case libS413::S413FeatureType::MaxWpkPrd:
		result.Format(_T("MaxWpkPrd : %.2f"), pickReportResult.GetValue(0));
		break;
	case libS413::S413FeatureType::NewSnowAmout3hr:
		result.Format(_T("NewSnowAmout3hr : %.2f"), pickReportResult.GetValue(0));
		break;
	case libS413::S413FeatureType::OceanCurrent:
		result.Format(
			_T("OceanCurrentDirection : %.2f\r\nOCeanCurrentSpeed : %.2f"), 
			pickReportResult.GetValue(0),
			pickReportResult.GetValue(1));
		break;
	case libS413::S413FeatureType::Pressure:
		result.Format(_T("Pressure : %.2f"), pickReportResult.GetValue(0));
		break;
	case libS413::S413FeatureType::RainAmount3hr:
		result.Format(_T("RainAmount3hr : %.2f"), pickReportResult.GetValue(0));
		break;
	case libS413::S413FeatureType::SkyStatus:
		result.Format(_T("SkyStatus : %.2f"), pickReportResult.GetValue(0));
		break;
	case libS413::S413FeatureType::Temperature3hr:
		result.Format(_T("Temperature3hr : %.2f"), pickReportResult.GetValue(0));
		break;
	case libS413::S413FeatureType::Visibility:
		result.Format(_T("Visibility : %.2f"), pickReportResult.GetValue(0));
		break;
	case libS413::S413FeatureType::WaterSalt:
		result.Format(_T("WaterSalt : %.2f"), pickReportResult.GetValue(0));
		break;
	case libS413::S413FeatureType::WaterTemperature:
		result.Format(_T("WaterTemperature : %.2f"), pickReportResult.GetValue(0));
		break;
	case libS413::S413FeatureType::WaveHeightInst:
		result.Format(_T("WaveHeightInst : %.2f"), pickReportResult.GetValue(0));
		break;
	case libS413::S413FeatureType::WaveLength:
		result.Format(_T("WaveLength : %.2f"), pickReportResult.GetValue(0));
		break;
	case libS413::S413FeatureType::WaveWind:
		result.Format(
			_T("WaveWindDirection : %.2f\r\nWaveWindSpeed : %.2f"), 
			pickReportResult.GetValue(0),
			pickReportResult.GetValue(1));
		break;
	}

	return result;
}

void S413::CreateBitmap(CDC* pDC, int featureType)
{
	if (!_S413)
	{
		return;
	}

	auto regularGrid = _S413->GetIrregularGridFeature(featureType);
	if (regularGrid)
	{
		auto featureValue = regularGrid->GetIrregularGridFeatureValues(_currentTimeIndex);
		auto gridInfo = regularGrid->GetIrregularGridInformation();
		if (gridInfo && featureValue)
		{
			int ncols = sqrt(gridInfo->GetNumberOfNodes());
			int nrows = ncols;

			if (bmpGrid.GetSafeHandle())
			{
				dc.DeleteDC();
				bmpGrid.DeleteObject();
				bBMP = false;
			}

			if (!bBMP)
			{
				if (bmpGrid.CreateBitmap(ncols, nrows, 1, 32, NULL) == 0)
				{
					return;
				}

				dc.CreateCompatibleDC(pDC);
				dc.SelectObject(bmpGrid);

				BITMAP pBitmap;
				bmpGrid.GetBitmap(&pBitmap);

				int *bmpBuffer = new int[pBitmap.bmWidth * pBitmap.bmHeight];
				memset(bmpBuffer, RGB(255, 255, 255), sizeof(int) * (pBitmap.bmWidth * pBitmap.bmHeight));

				float gridOriginX = xmin;
				float gridOriginY = ymin;

				auto valueCount = featureValue->GetFloatValuesCount();
				if (1 == valueCount)
				{
					if (auto floatValue = featureValue->GetFloatValues(0))
					{
						if (auto value = floatValue->GetValues())
						{
							int numPoints = gridInfo->GetNumberOfNodes();
							if (auto positioning = gridInfo->GetPositioning())
							{
								for (int i = 0; i < numPoints; i++)
								{
									float curX = positioning[i].X;
									float curY = positioning[i].Y;

									float offsetX = curX - xmin;
									float offsetY = curY - ymin;

									int indexX = offsetX / dx;
									int indexY = offsetY / dy;

									if (indexX < 0)
									{
										indexX = 0;
									}
									else if (indexX >= ncols)
									{
										indexX = ncols;
									}

									if (indexY < 0)
									{
										indexY = 0;
									}
									else if (indexY >= nrows)
									{
										indexY = nrows;
									}  
									dc.SetPixel(indexX, nrows - indexY - 1, GetColor(value[i], featureType));
									dc.SetPixel(indexX + 1, nrows - indexY - 1, GetColor(value[i], featureType));
								}

										
							}
						}
					}
				}
				else if (2 == valueCount)
				{
					auto floatValue1 = featureValue->GetFloatValues(0);
					auto floatValue2 = featureValue->GetFloatValues(1);
					if (floatValue1 && floatValue2)
					{
						auto value1 = floatValue1->GetValues();
						auto value2 = floatValue2->GetValues();
						if (value1 && value2)
						{
							for (int irow = 0; irow < nrows; irow++)
							{
								for (int icol = 0; icol < ncols; icol++)
								{
									int index = icol + (irow * ncols);
									int bmpIndex = icol + ((nrows - 1 - irow) * ncols); 
									if (bmpIndex < 0 || bmpIndex >= (pBitmap.bmWidth * pBitmap.bmHeight))
									{
										continue;
									}
									bmpBuffer[bmpIndex] = GetColor(value1[index], value2[index], featureType);
								}
							}
						}
					}
				} 

				delete[] bmpBuffer;

				bBMP = true;
			}
		}
	}
}

int S413::GetColor(float value1, float value2, int featureType)
{        

	return 0;
} 
int S413::GetColor(float value, int featureType)
{
	switch (featureType)
	{
	case 0:
		return GetColorByMinMax(value, 0.0, 360.0);
		break;
	case 1:
		return GetColorByMinMax(value, 2.5, 8.0);
		break;
	case 2:
		return GetColorByMinMax(value, 70.0, 100.0);
		break;
	case 3:
		return GetColorByMinMax(value, 0.0, 360.0);
		break;
	case 4:
		return GetColorByMinMax(value, 1.0, 15.0);
		break;
	case 5:
		return GetColorByMinMax(value, 0.0, 100.0);
		break;
	case 7:
		return GetColorByMinMax(value, 950.0, 1030.0);
	case 8:
		return GetColorByMinMax(value, 0.0, 10.0);
	case 9:
		return GetColorByMinMax(value, 1.0, 4.0);
	case 10:
		return GetColorByMinMax(value, -10.0, 40.0);
	case 11:
		return GetColorByMinMax(value, 0.1, 30.0);
	case 12:
		return GetColorByMinMax(value, 25.0, 35.0);
	case 13:
		return GetColorByMinMax(value, 18.0, 22.0);
	case 14:
		return GetColorByMinMax(value, 0.0, 5.0);
	case 15:
		return GetColorByMinMax(value, 30.0, 70.0);
		break;
	}

	return 0;
}

int S413::GetColorByMinMax(float _v, float vmin, float vmax)
{
	int r = 255;
	int g = 255;
	int b = 255;

	float changeColorValue = 255 / 24.;

	float v = _v;

	if (v < vmin)
		v = vmin;
	if (v > vmax)
		v = vmax;
	
	float gap = vmax - vmin;

	float calc_v = (v-vmin) / gap * 100 ;

	if (calc_v < 12)
	{
		r = 0;
		g = 0;
		b = 135 + (int)(calc_v * 10);
	}
	else if (calc_v < 36)
	{
		r = 0;
		g = (int)(changeColorValue * (calc_v - 12));
		b = 255;
		if (g > 255)
		{
			g = 255;
		}
	}
	else if (calc_v < 64)
	{
		r = (int)(changeColorValue * (calc_v - 36));
		g = 255;
		b = 255 + (int)(changeColorValue * (36 - calc_v));;

		if (r > 255)
			r = 255;
		if (b < 0)
			b = 0;
	}
	else if (calc_v < 88)
	{
		r = 255;
		g = 255 + (int)(changeColorValue * (64 - calc_v));
		b = 0;
		if (g < 0)
		{
			g = 0;
		}
	}
	else
	{
		r = 255 + (int)(changeColorValue * (88 - calc_v));
		g = 0;
		b = 0;
	}

	return RGB(r, g, b);
}

void S413::DrawBitmap(HDC &hDC, Rect rectF, Scaler *scaler)
{ 
	GeoPoint mLeftBottom;
	GeoPoint mRightTop;

	mLeftBottom.x = xmin;
	mLeftBottom.y = ymin;

	mRightTop.x = xmax;
	mRightTop.y = ymax; 
	GeoPoint viewLeftBottom;
	GeoPoint viewRightTop;

	scaler->DeviceToWorld(rectF.X, rectF.Y + rectF.Height, &viewLeftBottom.x, &viewLeftBottom.y);
	scaler->DeviceToWorld(rectF.X + rectF.Width, rectF.Y, &viewRightTop.x, &viewRightTop.y); 
	CRect bagRect(mLeftBottom.x, mLeftBottom.y, mRightTop.x, mRightTop.y);
	CRect viewRect(viewLeftBottom.x, viewLeftBottom.y, viewRightTop.x, viewRightTop.y);
	CRect intersectRect;

	if (intersectRect.IntersectRect(bagRect, viewRect))
	{ 
		int xLeftIndex = (intersectRect.left - mLeftBottom.x) / dx;
		int xRightIndex = (intersectRect.right - mLeftBottom.x) / dx;
		int yTopIndex = (intersectRect.bottom - mLeftBottom.y) / dy;
		int yBottomIndex = (intersectRect.top - mLeftBottom.y) / dy; 
		if (xRightIndex >= ncols) xRightIndex = ncols - 1;
		if (yTopIndex >= nrows) yTopIndex = nrows - 1; 
		int nWidth = xRightIndex - xLeftIndex + 1;
		int nHeight = yTopIndex - yBottomIndex + 1; 
		intersectRect.left = mLeftBottom.x + (dx * xLeftIndex);
		intersectRect.right = mLeftBottom.x + (dx * (xRightIndex + 1));
		intersectRect.top = mLeftBottom.y + (dy * (yTopIndex + 1));
		intersectRect.bottom = mLeftBottom.y + (dy * yBottomIndex);

		GeoPoint newLeftBottom;
		GeoPoint newRightTop;
		newLeftBottom.x = intersectRect.left;
		newLeftBottom.y = intersectRect.bottom;
		newRightTop.x = intersectRect.right;
		newRightTop.y = intersectRect.top; 
		CPoint newSLeftBottom;
		CPoint newSRightTop;

		newLeftBottom.x -= 1000;
		newLeftBottom.y -= 1000;
		newRightTop.x += 1000;
		newRightTop.y += 1000;

		scaler->WorldToDevice(newLeftBottom.x, newLeftBottom.y, &newSLeftBottom.x, &newSLeftBottom.y);
		scaler->WorldToDevice(newRightTop.x, newRightTop.y, &newSRightTop.x, &newSRightTop.y); 
		SetStretchBltMode(hDC, COLORONCOLOR);

		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 255;
		bf.AlphaFormat = 0;  
		CDC::FromHandle(hDC)->TransparentBlt(newSLeftBottom.x, newSRightTop.y, newSRightTop.x - newSLeftBottom.x, newSLeftBottom.y - newSRightTop.y, &dc, xLeftIndex, nrows - yTopIndex - 1, nWidth, nHeight, RGB(255, 255, 255));
		return;
	}
}

void S413::SetFilePath(CString value)
{
	m_FilePath = value;
}

CString S413::GetFilePath()
{
	return m_FilePath;
}

void S413::SetFileName(CString value) 
{
	m_FileName = value;
}

CString S413::GetFileName()
{
	return m_FileName;
}

void S413::SetTimeCount(int value)
{
	_timeCount = value;
}

int S413::GetTimeCount()
{
	return _timeCount;
}

void S413::SetCurrentTimeIndex(int value)
{
	_currentTimeIndex = value;
}

int S413::GetCurrentTimeIndex() 
{
	return _currentTimeIndex;
}                   

void S413::SetBMP(bool value) 
{
	bBMP = value;
}

bool S413::GetBMP() 
{
	return bBMP;
}

void S413::SetCols(int value) 
{
	ncols = value;
}

int S413::GetCols() 
{
	return ncols;
}

void S413::SetRows(int value) 
{
	nrows = value;
}

int S413::GetRows() 
{
	return nrows;
}

void S413::SetDx(int value) 
{
	dx = value;
}

int S413::GetDx() 
{
	return dx;
}

void S413::SetDy(int value) 
{
	dy = value;
}

int S413::GetDy() 
{
	return dy;
}

void S413::SetXMin(int value) 
{
	xmin = value;
}

int S413::GetXMin() 
{
	return xmin;
}

void S413::SetYMin(int value) 
{
	ymin = value;
}

int S413::GetYMin()
{
	return ymin;

}

void S413::SetXMax(int value) 
{
	xmax = value;
}

int S413::GetXMax() 
{
	return xmax;
}

void S413::SetYMax(int value) 
{
	ymax = value;
}

int S413::GetYMax() 
{
	return ymax;
}