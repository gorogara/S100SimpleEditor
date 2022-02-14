#pragma once

#include "libS111Decl.h"

enum TypeOfCurrentData {
	HistoricalObservation = 1,
	RealtimeObservation,
	AstronomicalPrediction,
	Analysis,
	ModelBasedHindcast,
	ModelBasedForecast
};

enum DataCodingFormat {
	TimeSeriesAtStations = 1,
	RegularlyGriddedArrays,
	IrregularlyGriddedArrays,
	LagrangianDrifters
};

enum DepthTypeIndex {
	LayerAverage = 1,
	SeaSurface,
	VerticalDatum,
	SeaBottom
};

enum VerticalDatumReference {
	MeanLowWaterSprings = 1,
	MeanLowerLowWaterSprings,
	MeanSeaLevel,
	LowestLowWater,
	MeanLowWater,
	LowestLowWaterSprings,
	ApproximateMeanLowWaterSprings,
	IndianSpringLowWater,
	LowWaterSprings,
	ApproximateLowestAstronomicalTide,
	NearlyLowestLowWater,
	MeanLowerLowWater,
	LowWater,
	ApproximateMeanLowWater,
	ApproximateMeanLowerLowWater,
	MeanHighWater,
	MeanHighWaterSprings,
	HighWater,
	ApproximateMeanSeaLevel,
	HighWaterSprings,
	MeanHigherHighWater,
	EquinocticalSpringLowWater,
	LowestAstronomicalTide,
	LocalDatum,
	InternationalGreatLakesDatum1985,
	MeanWaterLevel,
	LowerLowWaterLargeTide,
	HigherHighWaterLargeTide,
	NearylyHighestHighWater,
	HighestAstronomicalTide
};

class LIBS111_API S111Metadata
{
public:
	S111Metadata();
	virtual ~S111Metadata();

	bool WriteMetadata(__int64 file_id);
	bool ReadMetadata(__int64 file_id); 
	std::string nationalOriginator;
	std::string producingAgency;
	std::string productSpecification;
	std::string dateOfIssue;
	int         editionNumber;
	std::string fileName;
	std::string dataType;
	std::string nameRegion;
	std::string nameSubregion;
	std::string horizontalDatumReference;
	int         horizontalDatumValue; 
	float       westBoundLongitude;
	float       eastBoundLongitude;
	float       southBoundLatitude;
	float       northBoundLatitude;
	std::string dateTimeOfFirstRecord;
	std::string dateTimeOfLastRecord;
	int         timeRecordInterval;
	int         numberOfTimes; 
	TypeOfCurrentData      typeOfCurrentData;
	DataCodingFormat       dataCodingFormat;
	int                    numberOfStations;
	std::string            methodOrSource;
	DepthTypeIndex         depthTypeIndex;
	float                  surfaceCurrentDepth;
	VerticalDatumReference verticalDatum; 
	float gridOriginLongitude;
	float gridOriginLatitude;
	float gridSpacingLongitudinal;
	float gridSpacingLatitudinal;
	int   numberPointsLong;
	int   numberPointsLat;
	int   minimumGridPointLongitudinal;
	int   minimumGridPointLatitudinal;
	int   numberOfNodes;
	float gridLandMaskValue; 
	float uncertaintyOfSpeed;
	float uncertaintyOfDirection;
	float uncertaintyOfHorizontalPosition;
	float uncertaintyOfVerticalPosition;
	float uncertaintyOfTime;

private:
	bool WriteMetadataNationalOriginator(__int64 file_id);
	bool WriteMetadataEditionNumber(__int64 file_id);

	bool WriteMetadataIntegerAttribute(__int64 file_id, char* attributeName, int attributeValue);
	bool WriteMetadataFloatAttribute(__int64 file_id, char* attributeName, float attributeValue);
	bool WriteMetadataStringAttribute(__int64 file_id,
		char* attributeName, char* attributeValue, int sizeValue);

	bool ReadMetadataIntegerAttribute(__int64 file_id, char* attributeName, int& attributeValue);
	bool ReadMetadataFloatAttribute(__int64 file_id, char* attributeName, float& attributeValue);
	bool ReadMetadataStringAttribute(__int64 file_id, char* attributeName, std::string& attributeValue);
};