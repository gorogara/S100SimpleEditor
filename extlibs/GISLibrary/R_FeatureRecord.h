#pragma once

#include "R_VectorRecord.h"
#include "F_FRID.h"
#include "F_FOID.h"
#include "OrientedCurveRecord.h"

#include <map>

class S101Cell;
class SGeometry;
class SENC_Template;
class S101_ConditionalSymbol;
class R_CurveRecord;
class R_PointRecord;
class F_ATTR;
class F_INAS;
class F_SPAS;
class F_FASC;
class F_MASK;
struct ATTR; 
class R_FeatureRecord : Record
{
public:
	R_FeatureRecord();
	virtual ~R_FeatureRecord();

public: 
	F_FRID m_frid;
	F_FOID m_foid;

	std::list<F_ATTR*> m_attr;
	std::list<F_INAS*> m_inas;
	std::list<F_SPAS*> m_spas;
	std::list<F_FASC*> m_fasc;
	std::list<F_MASK*> m_mask; 
	SGeometry *m_geometry = nullptr; 

	int m_scaleMin = 0;
	int m_scaleMax = 0;
	int m_bShownAllScale = 0;

	int m_displayPriority = 0;
	int m_viewingGroup = 0;
	int m_displayCategory = 0;
	int m_radarOver = 0;
	bool m_hasTextPlacement = false; 
	float* m_textBearing = NULL;

	std::list<R_PointRecord*> m_pointList;
	std::list<OrientedCurveRecord> m_curveList;
	std::list<R_CurveRecord*> m_maskCurveList;

public:
	BOOL ReadRecord(DRDirectoryInfo *dir, BYTE*& buf);
	BOOL Save(CFile *file);
	void Draw(CDC *pDC, Scaler *scaler, double offset = 0);
	void Draw(HDC &hDC, Scaler *scaler, double offset = 0); 
	void Draw(HDC &hDC, Scaler *scaler, int type, int priority, double offset = 0);

	void CreateCS(S101Cell *cell, CString csName, bool bSENC);

	MBR GetMBR();

	int GetRCID();

	void GetXYPointOfTheVisiblePoints(double &x, double &y);

	int GetAttributeIndex(ATTR* value);

	int GetAssociationCount();
	int GetFeatureAssociationCount();
	int GetInformationAssociationCount();

	int GetNumericCode();
};

