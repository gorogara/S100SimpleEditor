#include "stdafx.h"
#include "S102.h"
#include "HDF5Wrapper.h"
#include "..\\LibMFCUtil\\LibMFCUtil.h"

#include <hdf5.h>

using namespace S100HDF5;
S102::S102()
{
}


S102::~S102()
{
	delete _RegularGrids;
	_RegularGrids = nullptr;
}

bool S102::Open(std::string path)
{
	auto fileId = H5Fopen(path.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);

	if (fileId < 0)
	{
		auto fapl = H5Pcreate(H5P_FILE_ACCESS);
		auto status = H5Pset_fapl_family(fapl, 0, H5P_DEFAULT);
		auto newPath = LibMFCUtil::GetHDF5SplittedFilePath(path);
		fileId = H5Fopen(newPath.c_str(), H5F_ACC_RDONLY, fapl);

		if (fileId < 0)
		{
			return false;
		}
	}

	ReadBoundingBox(fileId);

	auto featureId = H5Gopen(fileId, "BathymetryCoverage", H5P_DEFAULT);

	if (featureId > 0)
	{
		auto instanceId = H5Gopen(fileId, "BathymetryCoverage/BathymetryCoverage_01", H5P_DEFAULT);

		if (instanceId < 0)
		{
			instanceId = H5Gopen(fileId, "BathymetryCoverage/BathymetryCoverage.01", H5P_DEFAULT);
		}

		if (instanceId > 0)
		{
			int dataCodingFormat = 0;
			HDF5Wrapper::ReadMetadataIntegerAttribute(featureId, (char*)"dataCodingFormat", dataCodingFormat);
			
			if (dataCodingFormat == 2)
			{
				_RegularGrids = new RegularGridFeature();
				_RegularGrids->SetDataCodingFormat(DataCodingFormat::RegularGird);
				_RegularGrids->SetName("BathymetryCoverage");

				RegularGridInformation* regularGridInformation = new RegularGridInformation();

				float gridOriginLongitude = 0;
				HDF5Wrapper::ReadMetadataFloatAttribute(instanceId, (char*)"gridOriginLongitude", gridOriginLongitude);
				regularGridInformation->SetGridOriginLongitude(gridOriginLongitude);

				float gridOriginLatitude = 0;
				HDF5Wrapper::ReadMetadataFloatAttribute(instanceId, (char*)"gridOriginLatitude", gridOriginLatitude);
				regularGridInformation->SetGridOriginLatitude(gridOriginLatitude);

				float gridSpacingLongitudinal = 0;
				HDF5Wrapper::ReadMetadataFloatAttribute(instanceId, (char*)"gridSpacingLongitudinal", gridSpacingLongitudinal);
				regularGridInformation->SetGridSpacingLongitudinal(gridSpacingLongitudinal);

				float gridSpacingLatitudinal = 0;
				HDF5Wrapper::ReadMetadataFloatAttribute(instanceId, (char*)"gridSpacingLatitudinal", gridSpacingLatitudinal);
				regularGridInformation->SetGridSpacingLatitudinal(gridSpacingLatitudinal);

				int numPointsLongitudinal = 0;
				HDF5Wrapper::ReadMetadataIntegerAttribute(instanceId, (char*)"numPointsLongitudinal", numPointsLongitudinal);
				regularGridInformation->SetNumPointLongitudinal(numPointsLongitudinal);

				int numPointsLatitudinal = 0;
				HDF5Wrapper::ReadMetadataIntegerAttribute(instanceId, (char*)"numPointsLatitudinal", numPointsLatitudinal);
				regularGridInformation->SetNumPointLatitudinal(numPointsLatitudinal);

				_RegularGrids->SetRegularGridInformation(regularGridInformation);

				auto groupNNN_Id = H5Gopen(instanceId, "Group_001", H5P_DEFAULT);
				if (groupNNN_Id > 0)
				{
					auto valuesDatasetId = H5Dopen(groupNNN_Id, "values", H5P_DEFAULT);
					if (valuesDatasetId > 0)
					{
						RegularGridFeatureValues* regularGridFeatureValues = new RegularGridFeatureValues();
						_RegularGrids->AddRegularGridFeatureValues(regularGridFeatureValues);

						struct bufStruct
						{
							float depth;
							float uncertainty;
						};

						int bufSize = numPointsLongitudinal * numPointsLatitudinal;
						bufStruct *buf = new bufStruct[bufSize];

						hid_t compounType = H5Tcreate(H5T_COMPOUND, sizeof(bufStruct));
						H5Tinsert(compounType, "depth", 0, H5T_IEEE_F32LE);
						H5Tinsert(compounType, "uncertainty", sizeof(float), H5T_IEEE_F32LE);

						H5Dread(valuesDatasetId, compounType, H5S_ALL, H5S_ALL, H5P_DEFAULT, buf);

						FloatValues* floatValues[1] = { new FloatValues()/*, new FloatValues() */};
						floatValues[0]->SetName("depth"); 

						float *depth = new float[bufSize]; 

						for (int j = 0; j < bufSize; j++)
						{
							depth[j] = buf[j].depth; 
						}

						floatValues[0]->SetValues(depth, bufSize); 

						delete[] depth;
						depth = nullptr;  

						regularGridFeatureValues->AddFloatValues(floatValues[0]); 

						delete[] buf;
						buf = nullptr;
						H5Dclose(valuesDatasetId);
					}

					H5Gclose(groupNNN_Id);
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


PickReportResult S102::PickReport(float x, float y, time_t time, const char* featureName)
{
	PickReportResult result;

	RegularGridInformation *gridInfo = _RegularGrids->GetRegularGridInformation();
	MBR mbr = GetMBR();

	if (gridInfo)
	{
		if (x < mbr.xmin || x > mbr.xmax ||
			y < mbr.ymin || y > mbr.ymax)
		{
			return result;
		}

		float offsetX = (float)(x - mbr.xmin);
		float offsetY = (float)(y - mbr.ymin);

		int divX = (int)(offsetX / gridInfo->GetGridSpacingLongitudinal());
		int divY = (int)(offsetY / gridInfo->GetGridSpacingLatitudinal());

		int index = divX + (divY * gridInfo->GetNumPointLongitudinal());

		RegularGridFeatureValues *featureValue = _RegularGrids->GetRegularGridFeatureValues(0);
		if (featureValue)
		{
			FloatValues *depth = featureValue->GetFloatValues(0);
			if (depth)
			{
				float *depthValues = depth->GetValues();
				int depthValuesSize = depth->GetValueCount();

				if (index < depthValuesSize)
				{
					result.AddValue(depthValues[index]);
					float dx = gridInfo->GetGridSpacingLongitudinal();
					float dy = gridInfo->GetGridSpacingLatitudinal();
					result.SetX((float)(mbr.xmin + (dx * divX) + (dx / 2)));
					result.SetY((float)(mbr.ymin + (dy * divY) + (dy / 2)));
					return result;
				}
			}
		}
	}
	
	return result;
}

void S102::SetRegularGrid(RegularGridFeature* regularGrid)
{
	_RegularGrids = regularGrid;
}

RegularGridFeature* S102::GetRegularGrid(int index)
{
	return _RegularGrids;
}

void S102::ReadBoundingBox(__int64 Id)
{
	float westBoundLongitude = 0;
	HDF5Wrapper::ReadMetadataFloatAttribute(Id, XMinAttributeName, westBoundLongitude);

	float eastBoundLongitude = 0;
	HDF5Wrapper::ReadMetadataFloatAttribute(Id, XMaxAttributeName, eastBoundLongitude);

	float southBoundLatitude = 0;
	HDF5Wrapper::ReadMetadataFloatAttribute(Id, YMinAttributeName, southBoundLatitude);

	float northBoundLatitude = 0;
	HDF5Wrapper::ReadMetadataFloatAttribute(Id, YMaxAttributeName, northBoundLatitude);

	MBR mbr(westBoundLongitude, southBoundLatitude, eastBoundLongitude, northBoundLatitude);
	SetMBR(&mbr);
}