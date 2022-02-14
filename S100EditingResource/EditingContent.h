#pragma once

#include "EdtVector.h"
#include "EdtWorkUnit.h"
#include "EdtOrient.h"
#include "EdtTopologyIndicator.h"

class S101Cell;
class R_FeatureRecord;
class R_SurfaceRecord;
class R_CompositeRecord;
class R_CurveRecord;
class R_MultiPointRecord;
class R_PointRecord;

class CGISLibraryApp; 


class EditingContent
{
public:
	EditingContent();
	virtual ~EditingContent();

public:
	S101Cell* pWorkSheet = nullptr;
	R_FeatureRecord* pWorkTable; 
	EdtVector* curVector = nullptr;
	std::vector<EdtWorkUnit> workingList;
	std::vector<EdtWorkUnit>::iterator curWorkIterator;
	std::vector<EdtVector> vectorList;
	int ex_X, ex_Y;

public:
	void ImportFeature(S101Cell* pCell, R_FeatureRecord* pFe);
	void Draw(CDC* pDC, CGISLibraryApp *pGisLib, const int _offX = 0, const int _offY = 0);
	BOOL SelectWorkPoint(EdtVector* _ev);
	BOOL SelectWorkPoint(int x, int y, CGISLibraryApp *pGisLib);
	BOOL MouseButtonDown(int x, int y, CGISLibraryApp *pGisLib);
	BOOL MouseButtonDownOnLine(int x, int y, CGISLibraryApp *pGisLib);
	BOOL MouseMove(int x, int y);
	BOOL LButtonUp(int x, int y);
	BOOL Undo();
	BOOL Redo();
	BOOL DumpWorkingList(bool isAll = true);
	void SetVectorXY(EdtVector* ev, int x, int y);
	BOOL DeleteCurrentVector();
	BOOL AddVectorAfterCurrentVector();
	void AddVectorToPoint(int x, int y, EdtVector* ev);
	void MoveVectorToPoint(int x, int y, bool intoWorkList = false);
	void ReleaseEditVector();
	void Apply();
	void Cancel();

private:
	BOOL ImportVector(R_SurfaceRecord* pVe, EdtOrient orient = EdtOrient::E_FORWARD);
	BOOL ImportVector(R_CompositeRecord* pVe, EdtOrient orient = EdtOrient::E_FORWARD);
	BOOL ImportVector(R_CurveRecord* pVe, EdtOrient orient = EdtOrient::E_FORWARD);
	BOOL ImportVector(R_MultiPointRecord* pVe);
	BOOL ImportVector(R_PointRecord* pVe, EdtTopologyIndicator topologyIndicator = EdtTopologyIndicator::E_TOPI_BEGNNING, EdtOrient orient = EdtOrient::E_FORWARD);
};

