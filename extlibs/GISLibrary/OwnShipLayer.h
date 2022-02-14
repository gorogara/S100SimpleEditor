#pragma once

#include "Layer.h"
#include "ShipInfo.h"
#include "ENCFactory.h"
#include "..\\GeoMetryLibrary\\GeoPoint.h" 


class LayerManager;
class Scaler;
class ShipInfo;

class OwnShipLayer : public Layer
{
public:
	OwnShipLayer();
	virtual ~OwnShipLayer();

public:
	ShipInfo* m_info;
	ENCFactory m_encFactory;
	double m_lastShipReportTime;
	LayerManager* m_pLayerManager;
	Scaler* m_pScaler;

public:
	void Draw(HDC &hDC, Scaler *scaler, int offset = 0);
	void CheckShipReporting();
	GeoPoint GetCoordinate();
	void SetGeometryCoordinate(Scaler *scaler, double lon, double lat);
};