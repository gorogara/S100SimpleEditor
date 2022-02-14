#pragma once

#include "afxdialogex.h"

#include "..\\S101Portrayal\\PortrayalCatalogue.h"

class Catalogue
{
public:
	Catalogue();
	virtual ~Catalogue();

public:
	Catalog Featurecatalog;
	PortrayalCatalogue portrayalCatalogue;

public:
	void Set_Catalogue(Catalog _Featurecatalog, PortrayalCatalogue _portrayalCatalogue);
};