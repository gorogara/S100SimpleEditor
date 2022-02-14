#pragma once
#include "GML_DatasetMetadata.h"

class GML_DatasetMetaDataProperty
{
public:
	GML_DatasetMetaDataProperty();
	virtual ~GML_DatasetMetaDataProperty();
	
public:
	GML_DatasetMetadata m_datasetMetadata;
};