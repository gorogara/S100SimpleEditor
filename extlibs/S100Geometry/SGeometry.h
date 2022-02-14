#pragma once
#include "stdafx.h"

#include "..\\GeoMetryLibrary\\GeoPoint.h"

#include <unordered_map>     


class SSurface;
class Symbol;
class R_FeatureRecord;
class SENC_SymbolFill;                      

class SGeometry : public Geometry
{
public:
	SGeometry();
	virtual ~SGeometry();

public:
	static int sizeOfPoint; 
	static POINT   *viewPoints;    
	int type;

	R_FeatureRecord *m_pFeature;

public:    
	int GetType();

	bool IsPoint();
	bool IsCurve();
	bool IsSurface();
	bool IsMultiPoint();
};
