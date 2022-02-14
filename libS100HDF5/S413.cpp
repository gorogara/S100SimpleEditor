#include "stdafx.h"
#include "S413.h"
#include "HDF5Wrapper.h"

#include <hdf5.h>


using namespace S100HDF5;


const char* S413::AvgWavDirGroupName = "AvgWaveDir";
const char* S413::AvgWavDirInstanceGroupName = "AvgWaveDir.01";


S413::S413()
{
}


S413::~S413()
{
	for (auto i = _Features.begin(); i != _Features.end(); i++)
	{
		delete *i;
		*i = nullptr;
	}
}


bool S413::Open(std::string path)
{
	auto fileId = H5Fopen(path.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);

	if (fileId < 0)
	{
		return false;
	}

	ReadBoundingBox(fileId);

	ReadFeatureWithSingleFloatValue(fileId, "AvgWaveDir");
	ReadFeatureWithSingleFloatValue(fileId, "AvgWavePrd");
	ReadFeatureWithSingleFloatValue(fileId, "Humidity");
	ReadFeatureWithSingleFloatValue(fileId, "MaxWaveDir");
	ReadFeatureWithSingleFloatValue(fileId, "MaxWpkPrd");
	ReadFeatureWithSingleFloatValue(fileId, "NewSnowAmout3hr");
	ReadFeatureWithDoubleFloatValue(fileId, "OceanCurrent", "oceanCurrentDirection", "oceanCurrentSpeed");
	ReadFeatureWithSingleFloatValue(fileId, "Pressure");
	ReadFeatureWithSingleFloatValue(fileId, "RainAmount3hr");
	ReadFeatureWithSingleFloatValue(fileId, "SkyStatus");
	ReadFeatureWithSingleFloatValue(fileId, "Temperature3hr");
	ReadFeatureWithSingleFloatValue(fileId, "Visibility");
	ReadFeatureWithSingleFloatValue(fileId, "WaterSalt");
	ReadFeatureWithSingleFloatValue(fileId, "WaterTemperature");
	ReadFeatureWithSingleFloatValue(fileId, "WaveHeightInst");
	ReadFeatureWithSingleFloatValue(fileId, "WaveLength");
	ReadFeatureWithDoubleFloatValue(fileId, "WaveWind", "waveWindDirection", "waveWindSpeed");

	auto result = H5Fclose(fileId);
	if (result < 0)
	{
		return false;
	}

	return true;
}


void S413::AddIrregularGridFeature(IrregularGridFeature* irregularGridFeature)
{
	_Features.push_back(irregularGridFeature);
}


IrregularGridFeature* S413::GetIrregularGridFeature(std::string featureName)
{
	int featureCount = GetIrregularGridFeatureCount();
	for (int i = 0; i < featureCount; i++)
	{
		auto feature = GetIrregularGridFeature(i);
		if (feature)
		{
			if (strcmp(feature->GetName(), featureName.c_str()) == 0)
			{
				return feature;
			}
		}
	}

	return nullptr;
}


IrregularGridFeature* S413::GetIrregularGridFeature(int index)
{
	try
	{
		return _Features.at(index);
	}
	catch (std::out_of_range e)
	{
		return nullptr;
	}

	return nullptr;
}


int S413::GetIrregularGridFeatureCount()
{
	return _Features.size();
}


void S413::ReadBoundingBox(__int64 fileId)
{ 
	float westBoundLongitude = 0;
	HDF5Wrapper::ReadMetadataFloatAttribute(fileId, XMinAttributeName, westBoundLongitude);

	float eastBoundLongitude = 0;
	HDF5Wrapper::ReadMetadataFloatAttribute(fileId, XMaxAttributeName, eastBoundLongitude);

	float southBoundLatitude = 0;
	HDF5Wrapper::ReadMetadataFloatAttribute(fileId, YMinAttributeName, southBoundLatitude);

	float northBoundLatitude = 0;
	HDF5Wrapper::ReadMetadataFloatAttribute(fileId, YMaxAttributeName, northBoundLatitude);

	MBR mbr(westBoundLongitude, southBoundLatitude, eastBoundLongitude, northBoundLatitude);
	SetMBR(&mbr);
}


IrregularGridInformation* S413::ReadPositioning(__int64 instanceGroupId)
{
	int numberOfNodes = 0;
	HDF5Wrapper::ReadMetadataIntegerAttribute(instanceGroupId, (char *)"numberOfNodes", numberOfNodes);

	auto positioningGroupId = H5Gopen(instanceGroupId, "Positioning", H5P_DEFAULT);

	if (positioningGroupId > 0)
	{
		IrregularGridInformation* irregularGridInformation =
			new IrregularGridInformation();

		auto positioningDatasetId = H5Dopen(positioningGroupId, "geometryValues", H5P_DEFAULT);

		if (positioningDatasetId > 0)
		{
			S100HDF5::Point* points = new S100HDF5::Point[numberOfNodes];
			memset(points, 0, sizeof(S100HDF5::Point) * numberOfNodes);

			hid_t xyType = H5Tcreate(H5T_COMPOUND, sizeof(S100HDF5::Point));
			H5Tinsert(xyType, "Longitude", 0, H5T_IEEE_F32LE);
			H5Tinsert(xyType, "Latitude", sizeof(float), H5T_IEEE_F32LE);

			H5Dread(positioningDatasetId, xyType, H5S_ALL, H5S_ALL, H5P_DEFAULT, points);

			irregularGridInformation->SetPositioning(points, numberOfNodes);

			H5Dclose(positioningDatasetId);
		}

		return irregularGridInformation;
	}

	return nullptr;
}


void S413::ReadFeatureWithSingleFloatValue(__int64 fileId, const char* FeatureName)
{
	auto groupId = H5Gopen(fileId, FeatureName, H5P_DEFAULT);
	if (groupId > 0)
	{
		IrregularGridFeature* feature = new IrregularGridFeature();
		feature->SetDataCodingFormat(DataCodingFormat::IrregularGrid);
		feature->SetName(FeatureName);
		AddIrregularGridFeature(feature);

		char instanceGroupName[100] = { 0, };
		sprintf_s(instanceGroupName, "%s.01", FeatureName);

		auto instanceGroupId = H5Gopen(groupId, instanceGroupName, H5P_DEFAULT);

		if (instanceGroupId > 0)
		{
			std::string strDateTimeOfFirstRecord;
			HDF5Wrapper::ReadMetadataStringAttribute(
				instanceGroupId,
				TimeInformation::DateTimeOfFirstRecordAttributeName,
				strDateTimeOfFirstRecord);

			std::string strDateTimeOfLastRecord;
			HDF5Wrapper::ReadMetadataStringAttribute(
				instanceGroupId,
				TimeInformation::DateTimeOfLastRecordAttributeName,
				strDateTimeOfLastRecord);

			TimeInformation* timeInformation = new TimeInformation();

			int timeRecordInterval = 0;
			HDF5Wrapper::ReadMetadataIntegerAttribute(
				instanceGroupId,
				TimeInformation::TimeRecordIntervalAttributeName,
				timeRecordInterval);

			time_t dateTimeOfFirstRecord = TimeInformation::GetTimeTfromISO8601Basic(
				strDateTimeOfFirstRecord);
			time_t dateTimeOfLastRecord = TimeInformation::GetTimeTfromISO8601Basic(
				strDateTimeOfLastRecord);
			timeInformation->SetTimeInformation(
				dateTimeOfFirstRecord,
				dateTimeOfLastRecord,
				timeRecordInterval);

			feature->SetTimeInformation(timeInformation);

			IrregularGridInformation* irregularGridInformation = ReadPositioning(instanceGroupId);
			feature->SetIrregularGridInformation(irregularGridInformation);

			int groupCount = feature->GetTimeInformation()->GetNumberOfTimes();

			for (int i = 0; i < groupCount; i++)
			{
				const int nameSize = 100;
				char groupName_NNN[nameSize] = { 0, };
				sprintf_s(groupName_NNN, nameSize, "Group_%03d", i + 1);

				auto groupNNNId = H5Gopen(instanceGroupId, (const char*)groupName_NNN, H5P_DEFAULT);
				
				
				if (groupNNNId > 0)
				{
					IrregularGridFeatureValues *irregularGridFeatureValues =
						new IrregularGridFeatureValues();

					std::string strTimePoint;
					HDF5Wrapper::ReadMetadataStringAttribute(
						groupNNNId,
						IrregularGridFeatureValues::TimePointAttributeName,
						strTimePoint);

					irregularGridFeatureValues->SetTime(
						TimeInformation::GetTimeTfromISO8601Basic(strTimePoint));					

					auto valueId = H5Dopen(groupNNNId, "value", H5P_DEFAULT);
					if (valueId > 0)
					{
						FloatValues *floatValues = new FloatValues();
						floatValues->SetName("value");

						float *buf = new float[irregularGridInformation->GetNumberOfNodes()];

						H5Dread(valueId, H5T_IEEE_F32LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);

						floatValues->SetValues(buf, irregularGridInformation->GetNumberOfNodes());

						delete[] buf;
						buf = nullptr;

						irregularGridFeatureValues->AddFloatValues(floatValues);

						H5Dclose(valueId);
					}

					feature->AddIrregularGridFeatureValues(irregularGridFeatureValues);

					H5Gclose(groupNNNId);
				}
			}

			H5Gclose(instanceGroupId);
		}

		H5Gclose(groupId);
	}
}


void S413::ReadFeatureWithDoubleFloatValue(__int64 fileId, const char* FeatureName, const char* columnName1, const char* columnName2)
{
	auto groupId = H5Gopen(fileId, FeatureName, H5P_DEFAULT);
	if (groupId > 0)
	{
		IrregularGridFeature* feature = new IrregularGridFeature();
		feature->SetDataCodingFormat(DataCodingFormat::IrregularGrid);
		feature->SetName(FeatureName);
		AddIrregularGridFeature(feature);

		char instanceGroupName[100] = { 0, };
		sprintf_s(instanceGroupName, "%s.01", FeatureName);

		auto instanceGroupId = H5Gopen(groupId, instanceGroupName, H5P_DEFAULT);

		if (instanceGroupId > 0)
		{
			std::string strDateTimeOfFirstRecord;
			HDF5Wrapper::ReadMetadataStringAttribute(
				instanceGroupId,
				TimeInformation::DateTimeOfFirstRecordAttributeName,
				strDateTimeOfFirstRecord);

			std::string strDateTimeOfLastRecord;
			HDF5Wrapper::ReadMetadataStringAttribute(
				instanceGroupId,
				TimeInformation::DateTimeOfLastRecordAttributeName,
				strDateTimeOfLastRecord);

			TimeInformation* timeInformation = new TimeInformation();

			int timeRecordInterval = 0;
			HDF5Wrapper::ReadMetadataIntegerAttribute(
				instanceGroupId,
				TimeInformation::TimeRecordIntervalAttributeName,
				timeRecordInterval);

			time_t dateTimeOfFirstRecord = TimeInformation::GetTimeTfromISO8601Basic(
				strDateTimeOfFirstRecord);
			time_t dateTimeOfLastRecord = TimeInformation::GetTimeTfromISO8601Basic(
				strDateTimeOfLastRecord);
			timeInformation->SetTimeInformation(
				dateTimeOfFirstRecord,
				dateTimeOfLastRecord,
				timeRecordInterval);

			feature->SetTimeInformation(timeInformation);

			IrregularGridInformation* irregularGridInformation = ReadPositioning(instanceGroupId);
			feature->SetIrregularGridInformation(irregularGridInformation);

			int groupCount = feature->GetTimeInformation()->GetNumberOfTimes();

			for (int i = 0; i < groupCount; i++)
			{
				const int nameSize = 100;
				char groupName_NNN[nameSize] = { 0, };
				sprintf_s(groupName_NNN, nameSize, "Group_%03d", i + 1);

				auto groupNNNId = H5Gopen(instanceGroupId, (const char*)groupName_NNN, H5P_DEFAULT);

				if (groupNNNId > 0)
				{
					IrregularGridFeatureValues *irregularGridFeatureValues =
						new IrregularGridFeatureValues();

					std::string strTimePoint;
					HDF5Wrapper::ReadMetadataStringAttribute(
						groupNNNId,
						IrregularGridFeatureValues::TimePointAttributeName,
						strTimePoint);

					irregularGridFeatureValues->SetTime(
						TimeInformation::GetTimeTfromISO8601Basic(strTimePoint));

					auto valueId = H5Dopen(groupNNNId, "values", H5P_DEFAULT);
					if (valueId > 0)
					{
						struct bufStruct
						{
							float value1;
							float value2;
						};

						bufStruct* buf = new bufStruct[irregularGridInformation->GetNumberOfNodes()];

						FloatValues *floatValues1 = new FloatValues();
						floatValues1->SetName(columnName1);

						FloatValues *floatValues2 = new FloatValues();
						floatValues2->SetName(columnName2);

						hid_t compoundType = H5Tcreate(H5T_COMPOUND, sizeof(bufStruct));
						H5Tinsert(compoundType, columnName1, 0, H5T_IEEE_F32LE);
						H5Tinsert(compoundType, columnName2, sizeof(float), H5T_IEEE_F32LE);

						H5Dread(valueId, compoundType, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);

						float* floatBuf1 = new float[irregularGridInformation->GetNumberOfNodes()];
						float* floatBuf2 = new float[irregularGridInformation->GetNumberOfNodes()];

						for (int i = 0; i < irregularGridInformation->GetNumberOfNodes(); i++)
						{
							floatBuf1[i] = buf[i].value1;
							floatBuf2[i] = buf[i].value2;
						}

						floatValues1->SetValues(floatBuf1, irregularGridInformation->GetNumberOfNodes());
						floatValues2->SetValues(floatBuf2, irregularGridInformation->GetNumberOfNodes());

						delete[] floatBuf1;
						delete[] floatBuf2;

						delete[] buf;
						buf = nullptr;

						irregularGridFeatureValues->AddFloatValues(floatValues1);
						irregularGridFeatureValues->AddFloatValues(floatValues2);

						H5Dclose(valueId);
					}

					feature->AddIrregularGridFeatureValues(irregularGridFeatureValues);

					H5Gclose(groupNNNId);
				}
			}

			H5Gclose(instanceGroupId);
		}

		H5Gclose(groupId);
	}
}


PickReportResult S413::PickReport(float x, float y, time_t time, const char* featureName)
{
	PickReportResult result;

	for (auto i = _Features.begin(); i != _Features.end(); i++)
	{
		std::string currentFeatureName = (*i)->GetName();

		if (0 == strcmp(currentFeatureName.c_str(), featureName))
		{
			IrregularGridInformation* gridInfo = (*i)->GetIrregularGridInformation();

			if (gridInfo)
			{
				S100HDF5::Point* points = gridInfo->GetPositioning();
				int numOfPoint = gridInfo->GetNumberOfNodes();

				if (points)
				{
					if (numOfPoint > 0)
					{
						int findIndex = -1;
						if (numOfPoint == 1)
						{
							findIndex = 0;
						}
						else
						{
							float shortestDistance = 0;
							for (int j = 0; j < numOfPoint; j++)
							{
								float dx = points[j].X - x;
								float dy = points[j].Y - y;
								float currentDistance = dx * dx + dy * dy;
								if (j == 0)
								{
									shortestDistance = currentDistance;
									findIndex = 0;
								}
								else if (currentDistance < shortestDistance)
								{
									shortestDistance = currentDistance;
									findIndex = j;
								}
							}
						}

						result.SetX(points[findIndex].X);
						result.SetY(points[findIndex].Y);

						IrregularGridFeatureValues* featureValues = (*i)->GetNearestIrregularGridFeatureValues(time);
						if (featureValues)
						{
							result.SetTime(featureValues->GetTime());
							int valueNum = featureValues->GetFloatValuesCount();
							try
							{
								for (int j = 0; j < valueNum; j++)
								{
									FloatValues* floatValues = featureValues->GetFloatValues(j);
									if (floatValues)
									{
										float* values = floatValues->GetValues();
										if (values)
										{
											result.AddValue(values[findIndex]);
										}
									}
								}
							}
							catch (std::out_of_range)
							{

							}
						}

						if (findIndex >= 0)
						{
							return result;
						}
					}
				}
			}
		}
	}

	return result;
}