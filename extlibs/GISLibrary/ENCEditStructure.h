#pragma once  

class ENC_Vector;
class R_PointRecord;
class F_C2IT;
class F_C3IT;
class SG2D;

class EditPoint
{
public:
	EditPoint()
	{
		m_pPR = NULL;
		m_pC2IT = NULL;
		m_pC3IT = NULL;
	};

public:
	R_PointRecord* m_pPR;
	F_C2IT* m_pC2IT;
	F_C3IT* m_pC3IT;

	ENC_Vector* m_pVec;
	SG2D* m_pSG2D;

	double x;
	double y;
};