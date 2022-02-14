#pragma once
#include "Layer.h"

class PortrayalCatalogue;
class Catalog;

class S102Layer :
	public Layer
{
public:
	S102Layer();
	virtual ~S102Layer();
public:
	PortrayalCatalogue		*m_pPortrayalCatalogue;
	Catalog					*m_pFeatureCatalogue;

public:
	bool Open(CString _filepath);
	void Draw(HDC &hDC, Scaler *scaler, double offset = 0);
};