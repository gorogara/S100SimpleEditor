#include "stdafx.h"
#include "EditingContent.h"

#include "GISLibrary\\GISLibrary.h"
#include "GISLibrary\\F_CUCO.h"
#include "GISLibrary\\F_PTAS.h"
#include "GISLibrary\\F_SPAS.h"
#include "GISLibrary\\F_C2IL.h"
#include "GISLibrary\\F_C2IT.h"
#include "GISLibrary\\F_RIAS.h"
#include "GISLibrary\\R_SurfaceRecord.h"
#include "GISLibrary\\R_PointRecord.h"
#include "GISLibrary\\R_MultiPointRecord.h"
#include "GISLibrary\\R_CurveRecord.h"
#include "GISLibrary\\R_CompositeRecord.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\IC2D.h"
#include "GISLibrary\\CUCO.h"
#include "GISLibrary\\PTAS.h"
#include "GISLibrary\\SPAS.h"
#include "GISLibrary\\RIAS.h"

EditingContent::EditingContent()
{
	curWorkIterator = workingList.begin();
}

EditingContent::~EditingContent()
{
}

void EditingContent::ImportFeature(S101Cell* pCell, R_FeatureRecord* pFe)
{
	pWorkSheet = pCell;
	pWorkTable = pFe;

	R_PointRecord *pr = nullptr;
	R_MultiPointRecord *mpr = nullptr;
	R_CompositeRecord *ccr = nullptr;
	R_CurveRecord *cr = nullptr;
	R_SurfaceRecord *sr = nullptr;
	for (auto itorParent = pFe->m_spas.begin(); itorParent != pFe->m_spas.end(); itorParent++)
	{
		F_SPAS *spasParent = *itorParent;

		for (auto itor = spasParent->m_arr.begin(); itor != spasParent->m_arr.end(); itor++)
		{
			SPAS* spas = *itor;
			__int64 iKey = ((__int64)spas->m_name.RCNM) << 32 | spas->m_name.RCID;
			switch (spas->m_name.RCNM)
			{
			case 110: 
				pCell->m_ptMap.Lookup(iKey, pr);
				ImportVector(pr);
				break;
			case 115: 
				pCell->m_mpMap.Lookup(iKey, mpr);
				ImportVector(mpr);
				break;
			case 120: 
				pCell->m_curMap.Lookup(iKey, cr);
				ImportVector(cr);
				break;
			case 125: 
				pCell->m_comMap.Lookup(iKey, ccr);
				ImportVector(ccr);
				break;
			case 130: 
				pCell->m_surMap.Lookup(iKey, sr);
				ImportVector(sr);
				break;
			}
		}
	}
}

BOOL EditingContent::ImportVector(R_PointRecord* pVe, EdtTopologyIndicator topologyIndicator, EdtOrient orient)
{
	EdtVector ev;
	DWORD_PTR ptr1 = (DWORD_PTR)pVe;
	DWORD_PTR ptr2 = (DWORD_PTR)pVe->m_c2it;
	ev.type = EdtDateType::E_F_C2IT;
	ev.data.push_back(ptr1);
	ev.data.push_back(ptr2);
	ev.data.push_back(topologyIndicator);
	ev.data.push_back(orient);

	vectorList.push_back(ev);

	return TRUE;
}

BOOL EditingContent::ImportVector(R_MultiPointRecord* pVe)
{
	return TRUE;
}

BOOL EditingContent::ImportVector(R_CurveRecord* pVe, EdtOrient orient)
{
	POSITION ptasPos = NULL;
	PTAS *ptas = NULL;
	R_PointRecord *spr = NULL, *epr = NULL;
	__int64 iKey;

	if (orient == EdtOrient::E_FORWARD)
	{
		ptasPos = pVe->m_ptas->m_arr.GetHeadPosition();

		while (ptasPos)
		{
			ptas = pVe->m_ptas->m_arr.GetNext(ptasPos);

			iKey = ((__int64)ptas->m_name.RCNM) << 32 | ptas->m_name.RCID;
			if (ptas->m_topi == 1 
				)
			{
				pWorkSheet->m_ptMap.Lookup(iKey, spr);
			}
			else if (ptas->m_topi == 2 
				)
			{
				pWorkSheet->m_ptMap.Lookup(iKey, epr);
			}
			else if (ptas->m_topi == 3)
			{
				pWorkSheet->m_ptMap.Lookup(iKey, spr);
				epr = spr;
			}
		}

		ImportVector(spr, EdtTopologyIndicator::E_TOPI_BEGNNING);
		for (auto itor = pVe->m_c2il.begin(); itor != pVe->m_c2il.end(); itor++)
		{
			F_C2IL* f_ic2d = *itor;

			for (auto itor2d = f_ic2d->m_arr.begin(); itor2d != f_ic2d->m_arr.end(); itor2d++)
			{
				EdtVector ev;
				IC2D *ic2d = *itor2d;
				DWORD_PTR ptr1 = (DWORD_PTR)pVe;
				DWORD_PTR ptr2 = (DWORD_PTR)f_ic2d;
				DWORD_PTR ptr3 = (DWORD_PTR)ic2d;
				ev.type = EdtDateType::E_F_C2IL;
				ev.data.push_back(ptr1);
				ev.data.push_back(ptr2);
				ev.data.push_back(ptr3);
				ev.data.push_back(orient);

				vectorList.push_back(ev);
			}
		}
		ImportVector(epr, EdtTopologyIndicator::E_TOPI_END);
	}
	else if (orient == EdtOrient::E_BACKWARD)
	{
		ptasPos = pVe->m_ptas->m_arr.GetHeadPosition();

		while (ptasPos)
		{
			ptas = pVe->m_ptas->m_arr.GetNext(ptasPos);

			iKey = ((__int64)ptas->m_name.RCNM) << 32 | ptas->m_name.RCID;
			if (ptas->m_topi == 1 
				)
			{
				pWorkSheet->m_ptMap.Lookup(iKey, spr);
			}
			else if (ptas->m_topi == 2 
				)
			{
				pWorkSheet->m_ptMap.Lookup(iKey, epr);
			}
			else if (ptas->m_topi == 3)
			{
				pWorkSheet->m_ptMap.Lookup(iKey, spr);
				epr = spr;
			}
		}

		ImportVector(epr, EdtTopologyIndicator::E_TOPI_BEGNNING);
		for (auto itor = pVe->m_c2il.begin(); itor != pVe->m_c2il.end(); itor++)
		{
			F_C2IL* f_ic2d = *itor;

			for (auto itor2d = f_ic2d->m_arr.rbegin(); itor2d != f_ic2d->m_arr.rend(); itor2d++)
			{
				EdtVector ev;
				IC2D *ic2d = *itor2d;
				DWORD_PTR ptr1 = (DWORD_PTR)pVe;
				DWORD_PTR ptr2 = (DWORD_PTR)f_ic2d;
				DWORD_PTR ptr3 = (DWORD_PTR)ic2d;
				ev.type = EdtDateType::E_F_C2IL;
				ev.data.push_back(ptr1);
				ev.data.push_back(ptr2);
				ev.data.push_back(ptr3);
				ev.data.push_back(orient);

				vectorList.push_back(ev);
			}
		}
		ImportVector(spr, EdtTopologyIndicator::E_TOPI_END);
	}
	return TRUE;
}

BOOL EditingContent::ImportVector(R_CompositeRecord* pVe, EdtOrient orient)
{
	R_CurveRecord *cr;
	R_CompositeRecord *ccr;
	R_SurfaceRecord *sr;


	for (auto itor = pVe->m_cuco.begin(); itor != pVe->m_cuco.end(); itor++)
	{
		F_CUCO* f_cuco = *itor;

		if (orient == EdtOrient::E_FORWARD)
		{
			for (auto itorCuco = f_cuco->m_arr.begin(); itorCuco != f_cuco->m_arr.end(); itorCuco++)
			{
				CUCO *cuco = *itorCuco;

				EdtOrient applyOrient;
				if (cuco->m_ornt == 1)
				{
					applyOrient = EdtOrient::E_FORWARD;
				}
				else if (cuco->m_ornt == 2)
				{
					applyOrient = EdtOrient::E_BACKWARD;
				}

				if (orient == EdtOrient::E_BACKWARD)
				{
					if (applyOrient == EdtOrient::E_FORWARD)
						applyOrient = EdtOrient::E_BACKWARD;
					else if (applyOrient == EdtOrient::E_BACKWARD)
						applyOrient = EdtOrient::E_FORWARD;
				}

				__int64 iKey = ((__int64)cuco->m_name.RCNM) << 32 | cuco->m_name.RCID;

				switch (cuco->m_name.RCNM)
				{
				case 120: 
					pWorkSheet->m_curMap.Lookup(iKey, cr);
					ImportVector(cr, applyOrient);
					break;
				case 125: 
					pWorkSheet->m_comMap.Lookup(iKey, ccr);
					ImportVector(ccr, applyOrient);
					break;
				case 130: 
					pWorkSheet->m_surMap.Lookup(iKey, sr);
					ImportVector(sr, applyOrient);
					break;
				}
			}
		}
		else if (orient == EdtOrient::E_BACKWARD)
		{
			for (auto itorCuco = f_cuco->m_arr.rbegin(); itorCuco != f_cuco->m_arr.rend(); itorCuco++)
			{
				CUCO *cuco = *itorCuco;

				EdtOrient applyOrient;
				if (cuco->m_ornt == 1)
				{
					applyOrient = EdtOrient::E_FORWARD;
				}
				else if (cuco->m_ornt == 2)
				{
					applyOrient = EdtOrient::E_BACKWARD;
				}

				if (orient == EdtOrient::E_BACKWARD)
				{
					if (applyOrient == EdtOrient::E_FORWARD)
						applyOrient = EdtOrient::E_BACKWARD;
					else if (applyOrient == EdtOrient::E_BACKWARD)
						applyOrient = EdtOrient::E_FORWARD;
				}

				__int64 iKey = ((__int64)cuco->m_name.RCNM) << 32 | cuco->m_name.RCID;

				switch (cuco->m_name.RCNM)
				{
				case 120: 
					pWorkSheet->m_curMap.Lookup(iKey, cr);
					ImportVector(cr, applyOrient);
					break;
				case 125: 
					pWorkSheet->m_comMap.Lookup(iKey, ccr);
					ImportVector(ccr, applyOrient);
					break;
				case 130: 
					pWorkSheet->m_surMap.Lookup(iKey, sr);
					ImportVector(sr, applyOrient);
					break;
				}
			}
		}
	}

	return TRUE;
}

BOOL EditingContent::ImportVector(R_SurfaceRecord* pVe, EdtOrient orient)
{
	R_CurveRecord *cr;
	R_CompositeRecord *ccr;
	R_SurfaceRecord *sr;

	for (auto itor = pVe->m_rias.begin(); itor != pVe->m_rias.end(); itor++)
	{
		F_RIAS* f_rias = *itor;

		for (auto itorRias = f_rias->m_arr.begin(); itorRias != f_rias->m_arr.end(); itorRias++)
		{
			RIAS *rias = *itorRias;

			EdtOrient applyOrient;
			if (rias->m_ornt == 1)
			{
				applyOrient = EdtOrient::E_FORWARD;
			}
			else if (rias->m_ornt == 2)
			{
				applyOrient = EdtOrient::E_BACKWARD;
			}

			if (orient == EdtOrient::E_BACKWARD)
			{
				if (applyOrient == EdtOrient::E_FORWARD)
					applyOrient = EdtOrient::E_BACKWARD;
				else if (applyOrient == EdtOrient::E_BACKWARD)
					applyOrient = EdtOrient::E_FORWARD;
			}

			__int64 iKey = ((__int64)rias->m_name.RCNM) << 32 | rias->m_name.RCID;

			switch (rias->m_name.RCNM)
			{
			case 120: 
				pWorkSheet->m_curMap.Lookup(iKey, cr);
				ImportVector(cr, applyOrient);
				break;
			case 125: 
				pWorkSheet->m_comMap.Lookup(iKey, ccr);
				ImportVector(ccr, applyOrient);
				break;
			case 130: 
				pWorkSheet->m_surMap.Lookup(iKey, sr);
				ImportVector(sr, applyOrient);
				break;
			}
		}
	}

	return TRUE;
}

void EditingContent::Draw(CDC* pDC, CGISLibraryApp *pGisLib, const int _offX, const int _offY)
{
	if (pWorkSheet == nullptr)
	{
		return;
	}

	CPen newPen, newPen2, newPen3;
	newPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	newPen2.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	newPen3.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

	S101Cell* cell = (S101Cell*)pWorkSheet;
	CPen* oldPen = pDC->SelectObject(&newPen);

	SolidBrush brush(Color(255, 0, 0));

	int ptSize = vectorList.size();
	Gdiplus::Point* points = new Gdiplus::Point[ptSize];
	Gdiplus::Point curPoint;

	R_VectorRecord* vr = NULL;
	IC2D* ic = NULL;
	F_C2IL* fc2il = NULL;
	F_C2IT* fc2it = NULL;
	int index = 0;

	int compX = cell->m_dsgir.m_dssi.m_cmfx;
	int compY = cell->m_dsgir.m_dssi.m_cmfy;
	double dx = 0;
	double dy = 0;

	Graphics gPick(pDC->GetSafeHdc());

	int beginX = INT_MIN;
	int beginY = INT_MIN;
	std::vector<int> beginIndex;
	std::vector<int> segmentSize;
	int segSize = 0;

	int pointIndex = 0;
	for (auto i = vectorList.begin(); i != vectorList.end(); i++)
	{
		EdtVector* ev = &*i;

		if (ev->deleted)
			continue;
		switch (ev->type)
		{
		case 1:
			vr = (R_VectorRecord*)ev->data[0];
			fc2il = (F_C2IL*)ev->data[1];
			ic = (IC2D*)ev->data[2];

			dx = ic->m_xcoo / (double)compX;
			dy = ic->m_ycoo / (double)compY;

			break;
		case 2:
			vr = (R_VectorRecord*)ev->data[0];
			fc2it = (F_C2IT*)ev->data[1];

			dx = fc2it->m_xcoo / (double)compX;
			dy = fc2it->m_ycoo / (double)compY;

			if (beginX == INT_MIN && beginY == INT_MIN)
			{
				beginX = fc2it->m_xcoo;
				beginY = fc2it->m_ycoo;
				beginIndex.push_back(pointIndex);
			}
			else if (beginX == fc2it->m_xcoo && beginY == fc2it->m_ycoo)
			{
				beginX = INT_MIN;
				beginY = INT_MIN;
				segmentSize.push_back(segSize);
				segSize = 0;
			}

			break;
		}

		pGisLib->Projection(&dx, &dy);
		pGisLib->WorldToDevice(dx, dy, (long*)(&points[pointIndex].X), (long*)(&points[pointIndex].Y));
		points[pointIndex].X += _offX;
		points[pointIndex].Y += _offY;

		if (curVector == ev)
		{
			curPoint = points[pointIndex];
		}

		pointIndex++;
		segSize++;
	}

	for (int i = 0; i < pointIndex; i++)
	{ 
		pDC->Ellipse(points[i].X - 5, points[i].Y - 5, points[i].X + 5, points[i].Y + 5); 
	}    

	gPick.DrawLines(&Pen(&brush, 2), points, pointIndex); 
	pDC->SelectObject(&newPen2);
	pDC->Ellipse(curPoint.X - 5, curPoint.Y - 5, curPoint.X + 5, curPoint.Y + 5); 


	delete[] points;

	pDC->SelectObject(oldPen);
	newPen.DeleteObject();
	newPen2.DeleteObject();
}

BOOL EditingContent::SelectWorkPoint(EdtVector* _ev)
{
	ReleaseEditVector();
	R_VectorRecord* vr = NULL;
	IC2D* ic = NULL;
	F_C2IL* fc2il = NULL;
	F_C2IT* fc2it = NULL;
	int index = 0;

	for (auto itor = vectorList.begin(); itor != vectorList.end(); itor++)
	{
		EdtVector* ev = &*itor;
		if (ev->deleted)
			continue;

		if (_ev->type != ev->type)
			continue;

		switch (ev->type)
		{
		case 1:
			if ((IC2D*)ev->data[2] == (IC2D*)_ev->data[2])			curVector = ev;
			break;
		case 2:
			if ((F_C2IT*)ev->data[1] == (F_C2IT*)_ev->data[1])		curVector = ev;
			break;
		}

		if (curVector)
			return TRUE;
	}

	return FALSE;
}

BOOL EditingContent::SelectWorkPoint(int _x, int _y, CGISLibraryApp *pGisLib)
{
	int distance2times = 50;
	ReleaseEditVector();
	R_VectorRecord* vr = NULL;
	IC2D* ic = NULL;
	F_C2IL* fc2il = NULL;
	F_C2IT* fc2it = NULL;
	int index = 0;

	int compX = pWorkSheet->m_dsgir.m_dssi.m_cmfx;
	int compY = pWorkSheet->m_dsgir.m_dssi.m_cmfy;
	double dx = 0, dy = 0;

	for (auto itor = vectorList.begin(); itor != vectorList.end(); itor++)
	{
		EdtVector* ev = &*itor;
		if (ev->deleted)
			continue;
		switch (ev->type)
		{
		case 1:
			vr = (R_VectorRecord*)ev->data[0];
			fc2il = (F_C2IL*)ev->data[1];
			ic = (IC2D*)ev->data[2];

			ex_X = ic->m_xcoo;
			ex_Y = ic->m_ycoo;

			dx = ic->m_xcoo / (double)compX;
			dy = ic->m_ycoo / (double)compY;

			break;
		case 2:
			vr = (R_VectorRecord*)ev->data[0];
			fc2it = (F_C2IT*)ev->data[1];

			ex_X = fc2it->m_xcoo;
			ex_Y = fc2it->m_ycoo;

			dx = fc2it->m_xcoo / (double)compX;
			dy = fc2it->m_ycoo / (double)compY;
			break;
		}

		long sx = 0;
		long sy = 0;

		pGisLib->Projection(&dx, &dy);
		pGisLib->WorldToDevice(dx, dy, &sx, &sy);

		int x = sx - _x;
		int y = sy - _y;

		int sum = x * x + y * y;

		if (sum < distance2times)
		{
			sum = distance2times;
			curVector = ev;
			return TRUE;
		}
	}
	return FALSE;
}


BOOL EditingContent::MouseButtonDown(int x, int y, CGISLibraryApp *pGisLib)
{
	return SelectWorkPoint(x, y, pGisLib);
}

bool PointSegmentDistanceSquared(PointF point, PointF lineStart, PointF lineEnd, double &distance, PointF &intersectPoint)
{
	const double kMinSegmentLenSquared = 0.00000001; 
	const double kEpsilon = 1.0E-14; 
	double dX = lineEnd.X - lineStart.X;
	double dY = lineEnd.Y - lineStart.Y;
	double dp1X = point.X - lineStart.X;
	double dp1Y = point.Y - lineStart.Y;
	double segLenSquared = (dX * dX) + (dY * dY);
	double t = 0.0;

	if (segLenSquared >= -kMinSegmentLenSquared && segLenSquared <= kMinSegmentLenSquared)
	{ 
		intersectPoint = lineStart;
		t = 0.0;
		distance = ((dp1X * dp1X) + (dp1Y * dp1Y));
	}
	else
	{    
		t = ((dp1X * dX) + (dp1Y * dY)) / segLenSquared;
		if (t < kEpsilon)
		{   
			if (t > -kEpsilon)
			{ 
				t = 0.0;
			} 
			intersectPoint = lineStart;  
		}
		else if (t > (1.0 - kEpsilon))
		{   
			if (t < (1.0 + kEpsilon))
			{ 
				t = 1.0;
			} 
			intersectPoint = lineEnd;  
		}
		else
		{  
			intersectPoint = PointF((float)(lineStart.X + (t * dX)), (float)(lineStart.Y + (t * dY)));
		}   
		double dpqX = point.X - intersectPoint.X;
		double dpqY = point.Y - intersectPoint.Y;

		distance = ((dpqX * dpqX) + (dpqY * dpqY));
	}

	return true;
}

BOOL EditingContent::MouseButtonDownOnLine(int _x, int _y, CGISLibraryApp *pGisLib)
{
	int distance2times = 25;
	ReleaseEditVector();
	R_VectorRecord* vr = NULL;
	IC2D* ic = NULL;
	F_C2IL* fc2il = NULL;
	F_C2IT* fc2it = NULL;
	int index = 0;

	int compX = pWorkSheet->m_dsgir.m_dssi.m_cmfx;
	int compY = pWorkSheet->m_dsgir.m_dssi.m_cmfy;
	double dx = 0, dy = 0;

	PointF point((REAL)_x, (REAL)_y);
	PointF lineStart, lineEnd;
	double distance;
	PointF intersectPoint;  

	for (auto itor = vectorList.begin(); itor != vectorList.end(); itor++)
	{
		EdtVector* ev = &*itor;
		if (ev->deleted)
			continue;
		switch (ev->type)
		{
		case 1:
			vr = (R_VectorRecord*)ev->data[0];
			fc2il = (F_C2IL*)ev->data[1];
			ic = (IC2D*)ev->data[2];

			dx = ic->m_xcoo / (double)compX;
			dy = ic->m_ycoo / (double)compY;

			break;
		case 2:
			vr = (R_VectorRecord*)ev->data[0];
			fc2it = (F_C2IT*)ev->data[1];

			dx = fc2it->m_xcoo / (double)compX;
			dy = fc2it->m_ycoo / (double)compY;
			break;
		}
		long sx, sy;
		pGisLib->Projection(&dx, &dy);
		pGisLib->WorldToDevice(dx, dy, &sx, &sy);

		if (itor == vectorList.begin())
		{
			lineStart.X = (REAL)sx;
			lineStart.Y = (REAL)sy;
			lineEnd.X = (REAL)sx;
			lineEnd.Y = (REAL)sy;

			continue;
		}
		else
		{
			lineStart.X = lineEnd.X;
			lineStart.Y = lineEnd.Y;
			lineEnd.X = (REAL)sx;
			lineEnd.Y = (REAL)sy;
		}

		PointSegmentDistanceSquared(point, lineStart, lineEnd, distance, intersectPoint);

		if (distance < distance2times)
		{
			pGisLib->DeviceToWorld((long)intersectPoint.X, (long)intersectPoint.Y, &dx, &dy);
			pGisLib->InverseProjection(&dx, &dy);
			ex_X = (int)(dx * compX);
			ex_Y = (int)(dy * compY);

			curVector = ev;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL EditingContent::MouseMove(int x, int y)
{
	if (curVector)
	{
		MoveVectorToPoint(x, y);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
BOOL EditingContent::LButtonUp(int x, int y)
{
	if (curVector)
	{
		MoveVectorToPoint(x, y, true);
		ReleaseEditVector();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void EditingContent::AddVectorToPoint(int _x, int _y, EdtVector* ev)
{
	R_VectorRecord* vr = (R_VectorRecord*)ev->data[0];
	IC2D* ic = NULL;
	F_C2IL* fc2il = NULL;
	F_C2IT* fc2it = NULL;
	EdtOrient orient;
	IC2D *n_ic = new IC2D();

	auto vitorPosition = vectorList.begin();
	for (vitorPosition = vectorList.begin(); vitorPosition != vectorList.end(); vitorPosition++)
	{
		if (&*vitorPosition == ev)
		{
			break;
		}
	}

	switch (ev->type)
	{
	case 1:
		fc2il = (F_C2IL*)ev->data[1];
		ic = (IC2D*)ev->data[2];
		orient = (EdtOrient)ev->data[3];

		if (ev->data[3] == EdtOrient::E_FORWARD)
		{
			for (auto itor = fc2il->m_arr.begin(); itor != fc2il->m_arr.end(); itor++)
			{
				if (*itor == ic)
				{
					fc2il->m_arr.insert(itor, n_ic);
					break;
				}
			}
		}
		else
		{
			for (auto itor = fc2il->m_arr.begin(); itor != fc2il->m_arr.end(); itor++)
			{
				if (*itor == ic)
				{
					itor++;
					fc2il->m_arr.insert(itor, n_ic);
					break;
				}
			}
		}
		break;
	case 2:
		vr = (R_VectorRecord*)ev->data[0];
		fc2it = (F_C2IT*)ev->data[1];
		EdtTopologyIndicator ei = (EdtTopologyIndicator)ev->data[2];
		if (ei == EdtTopologyIndicator::E_TOPI_BEGNNING)
		{
			auto nvitor = (vitorPosition + 1);
			EdtVector *nv_ev = &*nvitor;
			fc2il = (F_C2IL*)nv_ev->data[1];
			orient = (EdtOrient)nv_ev->data[3];
			auto insertItor = fc2il->m_arr.begin();
			if (nv_ev->data[3] == EdtOrient::E_FORWARD)
			{
				insertItor = fc2il->m_arr.begin();
			}
			else
			{
				insertItor = fc2il->m_arr.end();
				insertItor--;
			}

			fc2il->m_arr.insert(insertItor, n_ic);
		}
		else if (ei == EdtTopologyIndicator::E_TOPI_END)
		{
			auto nvitor = (vitorPosition - 1);
			EdtVector *nv_ev = &*nvitor;
			fc2il = (F_C2IL*)nv_ev->data[1];
			orient = (EdtOrient)nv_ev->data[3];
			auto insertItor = fc2il->m_arr.begin();
			if (nv_ev->data[3] == EdtOrient::E_FORWARD)
			{
				insertItor = fc2il->m_arr.end();
				insertItor--;
			}
			else
			{
				insertItor = fc2il->m_arr.begin();
			}
			fc2il->m_arr.insert(insertItor, n_ic);
		}
		break;
	} 
	EdtVector n_ev;
	n_ev.type = EdtDateType::E_F_C2IL;
	n_ic->m_xcoo = _x;
	n_ic->m_ycoo = _y;

	n_ev.data.push_back((DWORD_PTR)vr);
	n_ev.data.push_back((DWORD_PTR)fc2il);
	n_ev.data.push_back((DWORD_PTR)n_ic);
	n_ev.data.push_back((DWORD_PTR)orient);

	vectorList.insert(vitorPosition, n_ev);

	{
		EdtWorkUnit eu;

		eu.cmd = EdtCommand::E_INSERT;
		eu.data.push_back((DWORD_PTR)curVector);

		workingList.push_back(eu);
		curWorkIterator = workingList.end();
	}
}

void EditingContent::MoveVectorToPoint(int x, int y, bool intoWorkList)
{
	R_VectorRecord* vr = NULL;
	IC2D* ic = NULL;
	F_C2IL* fc2il = NULL;
	F_C2IT* fc2it = NULL;
	int index = 0;

	EdtVector* ev = curVector; 
	switch (ev->type)
	{
	case 1:
		vr = (R_VectorRecord*)ev->data[0];
		fc2il = (F_C2IL*)ev->data[1];
		ic = (IC2D*)ev->data[2]; 
		ic->m_xcoo = x;
		ic->m_ycoo = y;

		break;
	case 2:
		vr = (R_VectorRecord*)ev->data[0];
		fc2it = (F_C2IT*)ev->data[1];

		fc2it->m_xcoo = x;
		fc2it->m_ycoo = y;
		break;
	} 
	if (intoWorkList)
	{
		if (curWorkIterator != workingList.end())
		{
			workingList.erase(curWorkIterator, workingList.end());
		}

		EdtWorkUnit eu;

		eu.cmd = EdtCommand::E_UPDATE;
		eu.data.push_back((DWORD_PTR)curVector);
		eu.data.push_back(x);
		eu.data.push_back(y);
		eu.data.push_back(ex_X);
		eu.data.push_back(ex_Y);

		workingList.push_back(eu); 

		curWorkIterator = workingList.end();
	}         

	return;
}

BOOL EditingContent::Undo()
{
	int cu_x = 0, cu_y = 0;
	int ex_x = 0, ex_y = 0;

	if (curWorkIterator != workingList.begin())
	{
		--curWorkIterator;

		EdtWorkUnit *eu = &*curWorkIterator;
		EdtVector* ev = (EdtVector*)eu->data[0];
		switch (eu->cmd)
		{
		case EdtCommand::E_UPDATE:  
			ex_x = eu->data[3];
			ex_y = eu->data[4];
			SetVectorXY(ev, ex_x, ex_y);
			break;
		case EdtCommand::E_DELETE:
			ev->deleted = false;
			break;
		case EdtCommand::E_INSERT:
			ev->deleted = true;
			break;
		}
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

BOOL EditingContent::Redo()
{
	int cu_x = 0, cu_y = 0;
	int ex_x = 0, ex_y = 0;

	if (curWorkIterator != workingList.end())
	{
		EdtWorkUnit *eu = &*curWorkIterator;
		EdtVector* ev = (EdtVector*)eu->data[0];

		switch (eu->cmd)
		{
		case EdtCommand::E_UPDATE:
			cu_x = eu->data[1];
			cu_y = eu->data[2];
			ex_x = eu->data[3];
			ex_y = eu->data[4];
			SetVectorXY(ev, cu_x, cu_y);
			break;
		case EdtCommand::E_DELETE:
			ev->deleted = true;
			break;
		case EdtCommand::E_INSERT:
			ev->deleted = false;
			break;
		}
		curWorkIterator++;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

void EditingContent::SetVectorXY(EdtVector* ev, int x, int y)
{
	R_VectorRecord* vr = NULL;
	IC2D* ic = NULL;
	F_C2IL* fc2il = NULL;
	F_C2IT* fc2it = NULL;
	int index = 0;

	switch (ev->type)
	{
	case 1:
		vr = (R_VectorRecord*)ev->data[0];
		fc2il = (F_C2IL*)ev->data[1];
		ic = (IC2D*)ev->data[2];

		ic->m_xcoo = x;
		ic->m_ycoo = y;

		break;
	case 2:
		vr = (R_VectorRecord*)ev->data[0];
		fc2it = (F_C2IT*)ev->data[1];

		fc2it->m_xcoo = x;
		fc2it->m_ycoo = y;
		break;
	}


}

BOOL EditingContent::DeleteCurrentVector()
{
	bool intoWorkList = false;
	std::vector<EdtVector>::iterator vitor, next_vitor;
	for (vitor = vectorList.begin(); vitor != vectorList.end(); vitor++)
	{
		if (curVector == &*vitor)
		{
			break;
		}
	}
	EdtWorkUnit eu;

	switch (curVector->type)
	{
	case 1:
		curVector->deleted = true;
		intoWorkList = true;
		break;
	case 2:
		break;
	} 
	if (intoWorkList)
	{
		if (curWorkIterator != workingList.end())
		{
			workingList.erase(curWorkIterator, workingList.end());
		}
		eu.cmd = EdtCommand::E_DELETE;
		eu.data.push_back((DWORD_PTR)curVector);
		workingList.push_back(eu);
		curWorkIterator = workingList.end();
	}
	ReleaseEditVector();
	return TRUE;
}

void EditingContent::ReleaseEditVector()
{
	if (curVector == nullptr)
	{
		return;
	}
	else
	{
		curVector = nullptr;
		return;
	}

}

BOOL EditingContent::AddVectorAfterCurrentVector()
{
	AddVectorToPoint(ex_X, ex_Y, curVector);

	return TRUE;
}

void EditingContent::Apply()
{
	DumpWorkingList();
	pWorkSheet->MakeFullSpatialData();
	ImportFeature(pWorkSheet, pWorkTable);
}

void EditingContent::Cancel()
{
	for (; curWorkIterator != workingList.begin();)
	{
		Undo();
	}
	DumpWorkingList();
	ImportFeature(pWorkSheet, pWorkTable);
}

BOOL EditingContent::DumpWorkingList(bool isAll)
{
	F_C2IL *f_c2il = NULL;
	IC2D* ic2d = NULL;
	if (isAll)
	{
		for (auto itor = vectorList.begin(); itor != vectorList.end(); itor++)
		{
			EdtVector* ev = &*itor;
			if (ev->deleted)
			{
				switch (ev->type)
				{
				case EdtDateType::E_F_C2IL:

					f_c2il = (F_C2IL *)ev->data[1];
					ic2d = (IC2D*)ev->data[2];
					for (auto ic2dItor = f_c2il->m_arr.begin();
						ic2dItor != f_c2il->m_arr.end();
						ic2dItor++)
					{
						if (ic2d == *ic2dItor)
						{
							delete ic2d;
							f_c2il->m_arr.erase(ic2dItor);
							break;
						}
					}

					break;
				case EdtDateType::E_F_C2IT:
					break;
				}
			}
		}
	}                   
	workingList.clear();
	vectorList.clear();

	curWorkIterator = workingList.begin();
	return TRUE;
}