#pragma once

#include "EnumTypeOfDrawingInstruction.h"
#include "FeatureReference.h"
#include "SpatialReference.h"

class DrawingInstruction
{
public:
	DrawingInstruction();
	virtual ~DrawingInstruction();

public:
	CString m_strViewingGroup;
	CString m_strDisplayPlane;
	int     m_nDrawingPriority;
	int     m_nScaleMinimum; 
	int     m_nScaleMaximum; 
	FeatureReference *m_pFeatureReference;
	SpatialReference *m_pSpatialReference;
	TypeOfDrawingInstruction m_nTypeOfDrawingInstruction;
	int m_nRefGeometryType;
	int m_nRefGeometryID;
};