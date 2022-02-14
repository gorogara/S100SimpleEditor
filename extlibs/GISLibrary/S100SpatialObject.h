#pragma once

#include "SpatialObject.h"
#include "S100_Members.h"

#include "..\\GeoMetryLibrary\\MBR.h"

class PCOutputSchemaManager;
class S100Layer;

class S100SpatialObject : public SpatialObject
{
public:
	S100SpatialObject();
	virtual ~S100SpatialObject();

public:
	S100::S100_DataProduct S100Product = S100::S100_DataProduct::S_100; 
	PCOutputSchemaManager* pcManager = nullptr;

public:
	void SetS100Product(S100::S100_DataProduct value);
	S100::S100_DataProduct GetS100Product();

	void SetMBR(MBR& value);
	MBR GetMBR();
	void SetPCOutputManager(PCOutputSchemaManager* value);
	PCOutputSchemaManager* GetPCOutputManager();
	S100Layer* GetS100Layer();
};