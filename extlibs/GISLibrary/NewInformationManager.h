#pragma once
#include "..\\S100DatasetGML\\S100DatasetGML.h"
#include <list> 
class SpatialObject;

class NewInformationManager
{
public :
	NewInformationManager();
	virtual ~NewInformationManager();

public:
	SpatialObject* m_cell;
	unsigned m_informationType; 
};