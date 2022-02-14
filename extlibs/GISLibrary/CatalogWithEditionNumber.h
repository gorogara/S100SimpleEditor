#pragma once
#include <string>

class Catalog;
class PortrayalCatalogue;

class CatalogWithEditionNumber
{
public:
	CatalogWithEditionNumber();
	virtual ~CatalogWithEditionNumber();

public:
	std::wstring editionNumber;
	int firstNumber;
	int secondNumber;
	int thirdNumber;
	Catalog* catalog;
	PortrayalCatalogue *portrayalCatalog;
};
