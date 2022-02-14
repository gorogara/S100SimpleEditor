#pragma once
#include "S100Layer.h"

class PortrayalCatalogue;
class Catalog;
class S101Cell;

class S101Layer : public S100Layer
{
public:
	S101Layer(Catalog* fc = nullptr, PortrayalCatalogue* pc = nullptr);
	virtual ~S101Layer();

public:
	bool checkedDataCoverageScale = false;

public:
	virtual bool Open(CString _filepath) override;
	void SetSpatialObject(S101Cell* cell);
	void Draw(GISLibrary::D2D1Resources* D2, Scaler* scaler);
};