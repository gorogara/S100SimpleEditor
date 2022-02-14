#pragma once
#include "Layer.h"
class PortrayalCatalogue;
class Catalog;

class S413Layer :
	public Layer
{
public:
	S413Layer();
	virtual ~S413Layer();

public:
	PortrayalCatalogue		*m_pPortrayalCatalogue = nullptr;
	Catalog					*m_pFeatureCatalogue = nullptr;

public:
	bool Open(CString filePath);
};