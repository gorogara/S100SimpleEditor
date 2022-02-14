#pragma once 
#include <unordered_map>
#include "..\\GeoMetryLibrary\\MBR.h"

class SENC_DisplayList;
class R_FeatureRecord;
class Layer;

class S101_CoverageLayer
{
public:
	S101_CoverageLayer(int _scaleMinimum, int _scaleMaximum);
	virtual ~S101_CoverageLayer();

	int scaleMinimum;
	int scaleMaximum;

	MBR mbr;

	Layer *layer;
	std::unordered_map<__int64, R_FeatureRecord*> featureMap;

	R_FeatureRecord* dataCoverageFeature;

	SENC_DisplayList* displayList;
};

