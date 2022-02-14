#pragma once

#include "S100NamedFeature.h"
#include "S57NamedFeature.h"

#include "..\\PLLibrary\\PLCommon.h"
#include <vector>

class R_FeatureRecord;
class ENC_Feature;
class FeatureType;
class ENC_Vector;
class R_PointRecord;
class SpatialObject;
class Catalog;

class NewFeatureManager
{
public:
	NewFeatureManager();
	virtual ~NewFeatureManager();

public:
	FeatureType* m_selectedFeatureType; 
	Catalog* m_selectedCatalog; 
	SpatialObject* m_cell;
	unsigned m_featureType;
	int m_geometryType; 
	std::vector<S100NamedFeature> m_pPickedFeatureRecords; 
	R_FeatureRecord* m_pOrgFeatureRecord; 
	R_FeatureRecord* m_pWorkFeatureRecord; 
	std::vector<S57NamedFeature> m_pPickedObjectRecords;
	ENC_Feature* m_pOrgObjectRecord;
	PointD m_addFeaturePoint;
	std::vector<PointD> m_addFeaturePoints;
	std::list<std::vector<PointD>> m_addFeatureInnerCirclePointsList;

public:
	R_FeatureRecord* SearchFeatureRecordHasVector(R_PointRecord *vr);
	ENC_Feature* SearchFeatureRecordHasVector(ENC_Vector *vr);
	Catalog* GetCatalog();
	FeatureType* GetFeatureType();
	void SetFeatureType(Catalog* _catalog, FeatureType* _ft);
};