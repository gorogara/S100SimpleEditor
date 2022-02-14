#pragma once
class R_CurveRecord;
class OrientedCurveRecord
{
public:
	OrientedCurveRecord();
	virtual ~OrientedCurveRecord();

public:
	R_CurveRecord *m_pCurveRecord;  
	int m_orient;
};
