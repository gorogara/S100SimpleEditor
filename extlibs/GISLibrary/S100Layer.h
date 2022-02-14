#pragma once

#include "Layer.h"

class Catalog;
class PortrayalCatalogue;
class S100SpatialObject;

class S100Layer : public Layer
{
public:
	S100Layer();
	S100Layer(Catalog *fc, PortrayalCatalogue *pc);
	virtual ~S100Layer();

private:
	Catalog *featureCatalogue = nullptr;
	PortrayalCatalogue *portrayalCatalogue = nullptr;
	bool hasIndividualFC = false;
	bool hasIndividualPC = false;

public:
	void SetFC(Catalog *value);
	Catalog* GetFC();
	void SetPC(PortrayalCatalogue *value);
	PortrayalCatalogue* GetPC();
	void SetIndividualFC(bool value);
	bool GetIndividualFC();
	void SetIndividualPC(bool value);
	bool GetIndividualPC();
	bool OpenFC(CString path);
	bool OpenPC(CString path);
	void DeleteCatalog();
	S100SpatialObject* GetS100SpatialObject();
};