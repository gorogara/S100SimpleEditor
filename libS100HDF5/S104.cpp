#include "stdafx.h"
#include "S104.h"
#include "HDF5Wrapper.h" 

#include <hdf5.h>


using namespace S100HDF5;


S104::S104()
{
	_FixedStations = nullptr;
	_RegularGrids = nullptr;
}


S104::~S104()
{
	delete _FixedStations;
	_FixedStations = nullptr;

	delete _RegularGrids;
	_RegularGrids = nullptr;
}


bool S104::Open(std::string path)
{
	auto fileId = H5Fopen(path.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);

	if (fileId < 0)
	{
		return false;
	}

	auto featureId = H5Gopen(fileId, "WaterLevel", H5P_DEFAULT);

	auto posId = H5Gopen(featureId, "WaterLevel.01/Positioning", H5P_DEFAULT);

	if (featureId > 0)
	{
		auto instanceId = H5Gopen(fileId, "WaterLevel/WaterLevel.01", H5P_DEFAULT);

		if (instanceId > 0)
		{
			int dataCodingFormat = 0;
			HDF5Wrapper::ReadMetadataIntegerAttribute(featureId, (char*)"dataCodingFormat", dataCodingFormat); 
			if (posId > 0) 
			{
				std::string strDateTimeOfFirstRecord; 
				HDF5Wrapper::ReadMetadataStringAttribute(instanceId, (char*)"dateTimeOfFirstRecord", strDateTimeOfFirstRecord);
				time_t dateTimeOfFirstRecord = TimeInformation::GetTimeTfromISO8601Basic(strDateTimeOfFirstRecord);

				std::string strDateTimeOfLastRecord; 
				HDF5Wrapper::ReadMetadataStringAttribute(instanceId, (char*)"dateTimeOfLastRecord", strDateTimeOfFirstRecord);
				time_t dateTimeOfLastRecord = TimeInformation::GetTimeTfromISO8601Basic(strDateTimeOfLastRecord);

				__int64 timeRecordInterval = 0;
				HDF5Wrapper::ReadMetadataInteger64Attribute(instanceId, (char*)"timeRecordInterval", timeRecordInterval);

				TimeInformation* timeInformation = new TimeInformation();
				timeInformation->SetTimeInformation(dateTimeOfFirstRecord, dateTimeOfLastRecord, (int)timeRecordInterval);

				_FixedStations = new FixedStationFeature();

				FixedStationInformation* fixedStationInformation = new FixedStationInformation();

				int numberOfStations = 0;
				HDF5Wrapper::ReadMetadataIntegerAttribute(instanceId, (char*)"numberOfStations", numberOfStations);

				int numberOfTimes = 0;
				HDF5Wrapper::ReadMetadataIntegerAttribute(instanceId, (char*)"numberOfTimes", numberOfTimes);
				fixedStationInformation->SetNumberOfTimes(numberOfTimes);

				auto positioningDatasetId = H5Dopen(instanceId, "Positioning/geometryValues", H5P_DEFAULT);
				if (positioningDatasetId > 0)
				{
					S100HDF5::Point* positioning = new S100HDF5::Point[numberOfStations];

					H5Dread(positioningDatasetId, H5T_IEEE_F32LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, positioning);
					fixedStationInformation->SetPositioning(positioning, numberOfStations);

					H5Dclose(positioningDatasetId);
				}

				_FixedStations->SetFixedStationInformation(fixedStationInformation);
				_FixedStations->SetTimeInformation(timeInformation);

				for (int i = 0; i < numberOfStations; i++)
				{
					char groupNNN_Name[100] = { 0, };
					sprintf_s(groupNNN_Name, 100, "Group_%03d", i + 1);

					auto groupNNN_Id = H5Gopen(instanceId, groupNNN_Name, H5P_DEFAULT);
					if (groupNNN_Id > 0)
					{
						std::string subregionName;
						HDF5Wrapper::ReadMetadataVariableLengthStringAttribute(groupNNN_Id, (char*)"nameSubregion", subregionName);

						auto valuesDatasetId = H5Dopen(groupNNN_Id, "values", H5P_DEFAULT);
						if (valuesDatasetId > 0)
						{
							FixedStationFeatureValues* fixedStationFeatureValues = new FixedStationFeatureValues();
							fixedStationFeatureValues->SetName(subregionName.c_str());
							_FixedStations->AddFixedStationFeatureValues(fixedStationFeatureValues);


							double *buf = new double[numberOfTimes];
							H5Dread(valuesDatasetId, H5T_IEEE_F64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);

							FloatValues* floatValues = new FloatValues();
							floatValues->SetName("waterLevel");

							float *floatBuf = new float[numberOfTimes];

							for (int j = 0; j < numberOfTimes; j++)
							{
								floatBuf[j] = (float)buf[j];
							}

							floatValues->SetValues(floatBuf, numberOfTimes);

							delete[] floatBuf;
							floatBuf = nullptr;

							fixedStationFeatureValues->AddFloatValues(floatValues);

							delete[] buf;
							buf = nullptr;
							H5Dclose(valuesDatasetId);
						}

						H5Gclose(groupNNN_Id);
					}
				}

				SetBoundingBoxFromPositioning();
			} 
			else 
			{
				std::string strDateTimeOfFirstRecord;
				HDF5Wrapper::ReadMetadataStringAttribute(instanceId, (char*)"dateTimeOfFirstRecord", strDateTimeOfFirstRecord);
				time_t dateTimeOfFirstRecord = TimeInformation::GetTimeTfromISO8601Basic(strDateTimeOfFirstRecord);

				std::string strDateTimeOfLastRecord;
				HDF5Wrapper::ReadMetadataStringAttribute(instanceId, (char*)"dateTimeOfLastRecord", strDateTimeOfLastRecord);
				time_t dateTimeOfLastRecord = TimeInformation::GetTimeTfromISO8601Basic(strDateTimeOfLastRecord);

				__int64 timeRecordInterval = 0;
				HDF5Wrapper::ReadMetadataInteger64Attribute(instanceId, (char*)"timeRecordinterval", timeRecordInterval);

				TimeInformation* timeInformation = new TimeInformation();
				timeInformation->SetTimeInformation(dateTimeOfFirstRecord, dateTimeOfLastRecord, (int)timeRecordInterval);

				_RegularGrids = new RegularGridFeature();
				_RegularGrids->SetDataCodingFormat(S100HDF5::DataCodingFormat::RegularGird);
				_RegularGrids->SetName("WaterLevel");

				RegularGridInformation* regularGridInformation = new RegularGridInformation();

				double gridOriginLongitude = 0;
				HDF5Wrapper::ReadMetadataDoubleAttribute(instanceId, (char*)"gridOriginLongitude", gridOriginLongitude);
				regularGridInformation->SetGridOriginLongitude((float)gridOriginLongitude);

				double gridOriginLatitude = 0;
				HDF5Wrapper::ReadMetadataDoubleAttribute(instanceId, (char*)"gridOriginLatitude", gridOriginLatitude);
				regularGridInformation->SetGridOriginLatitude((float)gridOriginLatitude);

				double gridSpacingLongitudinal = 0;
				HDF5Wrapper::ReadMetadataDoubleAttribute(instanceId, (char*)"gridSpacingLongitudinal", gridSpacingLongitudinal);
				regularGridInformation->SetGridSpacingLongitudinal((float)gridSpacingLongitudinal);

				double gridSpacingLatitudinal = 0;
				HDF5Wrapper::ReadMetadataDoubleAttribute(instanceId, (char*)"gridSpacingLatitudinal", gridSpacingLatitudinal);
				regularGridInformation->SetGridSpacingLatitudinal((float)gridSpacingLatitudinal);

				__int64 numPointsLongitudinal = 0;
				HDF5Wrapper::ReadMetadataInteger64Attribute(instanceId, (char*)"numPointsLongitudinal", numPointsLongitudinal);
				regularGridInformation->SetNumPointLongitudinal((int)numPointsLongitudinal);

				__int64 numPointsLatitudinal = 0;
				HDF5Wrapper::ReadMetadataInteger64Attribute(instanceId, (char*)"numPointsLatitudinal", numPointsLatitudinal);
				regularGridInformation->SetNumPointLatitudinal((int)numPointsLatitudinal);

				MBR boundingBox;
				boundingBox.SetMBR(
					gridOriginLongitude,
					gridOriginLatitude,
					gridOriginLongitude + (numPointsLongitudinal * gridSpacingLongitudinal),
					gridOriginLatitude + (numPointsLatitudinal * gridSpacingLatitudinal));
				SetMBR(&boundingBox);

				_RegularGrids->SetRegularGridInformation(regularGridInformation);
				_RegularGrids->SetTimeInformation(timeInformation);
				int numberOfTimes = timeInformation->GetNumberOfTimes();

				for (int i = 0; i < numberOfTimes; i++)
				{
					char groupNNN_Name[100] = { 0, };
					sprintf_s(groupNNN_Name, 100, "Group_%03d", i + 1);

					auto groupNNN_Id = H5Gopen(instanceId, groupNNN_Name, H5P_DEFAULT);
					if (groupNNN_Id > 0)
					{
						auto valuesDatasetId = H5Dopen(groupNNN_Id, "values", H5P_DEFAULT);
						if (valuesDatasetId > 0)
						{
							RegularGridFeatureValues* regularGridFeatureValues = new RegularGridFeatureValues();
							_RegularGrids->AddRegularGridFeatureValues(regularGridFeatureValues);

							int bufSize = (int)(numPointsLongitudinal * numPointsLatitudinal);
							double *buf = new double[bufSize];

							H5Dread(valuesDatasetId, H5T_IEEE_F64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);

							FloatValues* floatValues = new FloatValues();
							floatValues->SetName("waterLevel");

							float *waterLevel = new float[bufSize];

							for (int j = 0; j < bufSize; j++)
							{
								waterLevel[j] = (float)buf[j];
							}

							floatValues->SetValues(waterLevel, bufSize);

							delete[] waterLevel;
							waterLevel = nullptr;

							regularGridFeatureValues->AddFloatValues(floatValues);

							delete[] buf;
							buf = nullptr;
							H5Dclose(valuesDatasetId);
						}

						H5Gclose(groupNNN_Id);
					}
				}
			} 

			H5Gclose(instanceId);
		}

		H5Gclose(featureId);
	}

	if (H5Fclose(fileId) < 0)
	{
		return false;
	}

	return true;
}


void S104::SetBoundingBoxFromPositioning()
{
	if (_FixedStations)
	{
		FixedStationInformation* fixedStationInformation = _FixedStations->GetFixedStationInformation();
		if (fixedStationInformation)
		{
			S100HDF5::Point* points = fixedStationInformation->GetPositioning();
			int numPoint = fixedStationInformation->GetNumberOfNode();

			MBR boundingBox;

			for (int i = 0; i < numPoint; i++)
			{
				if (i == 0)
				{
					boundingBox.xmin = points[i].X;
					boundingBox.xmax = points[i].X;
					boundingBox.ymin = points[i].Y;
					boundingBox.ymax = points[i].Y;
				}
				else
				{
					if (boundingBox.xmin > points[i].X)
					{
						boundingBox.xmin = points[i].X;
					}
					else if (boundingBox.xmax < points[i].X)
					{
						boundingBox.xmax = points[i].X;
					}

					if (boundingBox.ymin > points[i].Y)
					{
						boundingBox.ymin = points[i].Y;
					}
					else if (boundingBox.ymax < points[i].Y)
					{
						boundingBox.ymax = points[i].Y;
					}
				}
			}

			SetMBR(&boundingBox);
		}
	}
}                 


PickReportResult S104::PickReport(float x, float y, time_t time, const char* featureName)
{
	PickReportResult result;

	if (_FixedStations)
	{
		int timeIndex = _FixedStations->GetTimeInformation()->GetNearestTimeIndex(time);
		time_t findTime = _FixedStations->GetTimeInformation()->GetTime(timeIndex);
		result.SetTime(findTime);
		FixedStationInformation* fixedStationInfo = _FixedStations->GetFixedStationInformation();
		if (fixedStationInfo)
		{
			int numNode = fixedStationInfo->GetNumberOfNode();
			S100HDF5::Point* positioning = fixedStationInfo->GetPositioning();

			int findIndex = 0;
			float shortestDistance = 0;
			for (int i = 0; i < numNode; i++)
			{
				float dx = x - positioning[i].X;
				float dy = y - positioning[i].Y;

				float currentDistance = dx * dx + dy * dy;
				if (i == 0)
				{
					shortestDistance = currentDistance;
				}
				else if (shortestDistance > currentDistance)
				{
					shortestDistance = currentDistance;
					findIndex = i;
				}
			}

			result.SetX(positioning[findIndex].X);
			result.SetY(positioning[findIndex].Y);

			FixedStationFeatureValues* featureValues = _FixedStations->GetFixedStationFeatureValues(findIndex);
			if (featureValues)
			{
				FloatValues *speedValues = featureValues->GetFloatValues(0);
				if (speedValues)
				{
					float *speed = speedValues->GetValues();
					if (speed)
					{
						result.AddValue(speed[timeIndex]);
					}
				}

				FloatValues *directionValues = featureValues->GetFloatValues(1);
				if (directionValues)
				{
					float *direction = directionValues->GetValues();
					if (direction)
					{
						result.AddValue(direction[timeIndex]);
					}
				}
			}
		}
	}
	else if (_RegularGrids)
	{
		int timeIndex = _RegularGrids->GetTimeInformation()->GetNearestTimeIndex(time);
		time_t findTime = _RegularGrids->GetTimeInformation()->GetTime(timeIndex);
		result.SetTime(findTime);
		RegularGridInformation* regularGridInfo = _RegularGrids->GetRegularGridInformation();
		if (regularGridInfo)
		{
			int numX = regularGridInfo->GetNumPointLongitudinal();
			int numY = regularGridInfo->GetNumPointLatitudinal();
			float gridOriginX = regularGridInfo->GetGridOgirinLongitude();
			float gridOriginY = regularGridInfo->GetGridOriginLatitude();
			float gridSpacingX = regularGridInfo->GetGridSpacingLongitudinal();
			float gridSpacingY = regularGridInfo->GetGridSpacingLatitudinal();
			float maxX = gridOriginX + (gridSpacingX * numX - 1);
			float maxY = gridOriginY + (gridSpacingY * numY - 1);

			int xIndex = 0;
			int yIndex = 0;

			if (gridOriginX > x)
			{
				xIndex = 0;
			}
			else if (gridOriginX < x && maxX > x)
			{
				float offset = x - gridOriginX;
				xIndex = (int)(offset / gridSpacingX);

				float d1 = x - (xIndex * gridSpacingX);
				float d2 = x - ((xIndex + 1) * gridSpacingX);
				if (d1 > d2)
				{
					xIndex++;
				}
			}
			else if (x > maxX)
			{
				xIndex = numX - 1;
			}

			if (gridOriginY > y)
			{
				yIndex = 0;
			}
			else if (gridOriginY < x && maxY > y)
			{
				float offset = y - gridOriginY;
				yIndex = (int)(offset / gridSpacingY);

				float d1 = y - (yIndex * gridSpacingY);
				float d2 = y - ((yIndex + 1) * gridSpacingY);
				if (d1 > d2)
				{
					yIndex++;
				}
			}
			else if (y > maxY)
			{
				yIndex = numY - 1;
			}

			result.SetX(gridOriginX + (xIndex * gridSpacingX));
			result.SetY(gridOriginY + (yIndex * gridSpacingY));

			RegularGridFeatureValues* featureValues = _RegularGrids->GetRegularGridFeatureValues(timeIndex);
			if (featureValues)
			{
				FloatValues *speedValues = featureValues->GetFloatValues(0);
				if (speedValues)
				{
					float *speed = speedValues->GetValues();
					if (speed)
					{
						result.AddValue(speed[numX * yIndex + xIndex]);
					}
				}

				FloatValues *directionValues = featureValues->GetFloatValues(1);
				if (directionValues)
				{
					float *direction = directionValues->GetValues();
					if (direction)
					{
						result.AddValue(direction[numX * yIndex + xIndex]);
					}
				}
			}
		}
	}

	return result;
}


void S104::SetFixedStaion(FixedStationFeature* fixedStation)
{
	_FixedStations = fixedStation;
}


void S104::SetRegularGrid(RegularGridFeature* regularGrid)
{
	_RegularGrids = regularGrid;
}


FixedStationFeature* S104::GetFixedStation(int index)
{
	return _FixedStations;
}


RegularGridFeature* S104::GetRegularGrid(int index)
{
	return _RegularGrids;
}