#include "stdafx.h"
#include "S111Metadata.h"

#include <hdf5.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


S111Metadata::S111Metadata()
	: editionNumber(0),
	horizontalDatumValue(0),
	westBoundLongitude(0),
	eastBoundLongitude(0),
	southBoundLatitude(0),
	northBoundLatitude(0),
	timeRecordInterval(0),
	numberOfTimes(0),
	typeOfCurrentData(HistoricalObservation),
	dataCodingFormat(TimeSeriesAtStations),
	numberOfStations(0),
	depthTypeIndex(LayerAverage),
	surfaceCurrentDepth(0),
	verticalDatum(MeanLowWaterSprings),
	gridOriginLongitude(0),
	gridOriginLatitude(0),
	gridSpacingLongitudinal(0),
	gridSpacingLatitudinal(0),
	numberPointsLong(0),
	numberPointsLat(0),
	minimumGridPointLongitudinal(0),
	minimumGridPointLatitudinal(0),
	numberOfNodes(0),
	gridLandMaskValue(0),
	uncertaintyOfSpeed(0),
	uncertaintyOfDirection(0),
	uncertaintyOfHorizontalPosition(0),
	uncertaintyOfVerticalPosition(0),
	uncertaintyOfTime(0)
{
}


S111Metadata::~S111Metadata()
{
}


bool S111Metadata::WriteMetadata(__int64 file_id)
{
	WriteMetadataStringAttribute(file_id, "nationalOriginator", (char*)nationalOriginator.c_str(), nationalOriginator.size());
	WriteMetadataStringAttribute(file_id, "producingAgency", (char*)producingAgency.c_str(), producingAgency.size());
	WriteMetadataStringAttribute(file_id, "productSpecification", (char*)productSpecification.c_str(), productSpecification.size());
	WriteMetadataStringAttribute(file_id, "dateOfIssue", (char*)dateOfIssue.c_str(), dateOfIssue.size());
	WriteMetadataIntegerAttribute(file_id, "editionNumber", editionNumber);
	WriteMetadataStringAttribute(file_id, "fileName", (char*)fileName.c_str(), fileName.size());
	WriteMetadataStringAttribute(file_id, "dataType", (char*)dataType.c_str(), dataType.size());
	WriteMetadataStringAttribute(file_id, "nameRegion", (char*)nameRegion.c_str(), nameRegion.size());
	WriteMetadataStringAttribute(file_id, "nameSubregion", (char*)nameSubregion.c_str(), nameSubregion.size());
	WriteMetadataStringAttribute(file_id, "horizontalDatumReference", (char*)horizontalDatumReference.c_str(), horizontalDatumReference.size());
	WriteMetadataIntegerAttribute(file_id, "horizontalDatumValue", horizontalDatumValue);
	WriteMetadataFloatAttribute(file_id, "westBoundLongitude", westBoundLongitude);
	WriteMetadataFloatAttribute(file_id, "eastBoundLongitude", eastBoundLongitude);
	WriteMetadataFloatAttribute(file_id, "southBoundLatitude", southBoundLatitude);
	WriteMetadataFloatAttribute(file_id, "northBoundLatitude", northBoundLatitude);
	WriteMetadataStringAttribute(file_id, "dateTimeOfFirstRecord", (char*)dateTimeOfFirstRecord.c_str(), dateTimeOfFirstRecord.size());
	WriteMetadataStringAttribute(file_id, "dateTimeOfLastRecord", (char*)dateTimeOfLastRecord.c_str(), dateTimeOfLastRecord.size());
	WriteMetadataIntegerAttribute(file_id, "timeRecordInterval", timeRecordInterval);
	WriteMetadataIntegerAttribute(file_id, "numberOfTimes", numberOfTimes);
	WriteMetadataIntegerAttribute(file_id, "typeOfCurrentData", typeOfCurrentData);
	WriteMetadataIntegerAttribute(file_id, "dataCodingFormat", dataCodingFormat);
	WriteMetadataIntegerAttribute(file_id, "numberOfStations", numberOfStations);
	WriteMetadataStringAttribute(file_id, "methodOrSource", (char*)methodOrSource.c_str(), methodOrSource.size());
	WriteMetadataIntegerAttribute(file_id, "depthTypeIndex", depthTypeIndex);
	WriteMetadataFloatAttribute(file_id, "surfaceCurrentDepth", surfaceCurrentDepth);
	WriteMetadataIntegerAttribute(file_id, "verticalDatum", verticalDatum);
	WriteMetadataFloatAttribute(file_id, "gridOriginLongitude", gridOriginLongitude);
	WriteMetadataFloatAttribute(file_id, "gridOriginLatitude", gridOriginLatitude);
	WriteMetadataFloatAttribute(file_id, "gridSpacingLongitudinal", gridSpacingLongitudinal);
	WriteMetadataFloatAttribute(file_id, "gridSpacingLatitudinal", gridSpacingLatitudinal);
	WriteMetadataIntegerAttribute(file_id, "numberPointsLong", numberPointsLong);
	WriteMetadataIntegerAttribute(file_id, "numberPointsLat", numberPointsLat);
	WriteMetadataIntegerAttribute(file_id, "minimumGridPointLongitudinal", minimumGridPointLongitudinal);
	WriteMetadataIntegerAttribute(file_id, "minimumGridPointLatitudinal", minimumGridPointLatitudinal);
	WriteMetadataIntegerAttribute(file_id, "numberOfNodes", numberOfNodes);
	WriteMetadataFloatAttribute(file_id, "gridLandMaskValue", gridLandMaskValue);
	WriteMetadataFloatAttribute(file_id, "uncertaintyOfSpeed", uncertaintyOfSpeed);
	WriteMetadataFloatAttribute(file_id, "uncertaintyOfDirection", uncertaintyOfDirection);
	WriteMetadataFloatAttribute(file_id, "uncertaintyOfHorizontalPosition", uncertaintyOfHorizontalPosition);
	WriteMetadataFloatAttribute(file_id, "uncertaintyOfVerticalPosition", uncertaintyOfVerticalPosition);
	WriteMetadataFloatAttribute(file_id, "uncertaintyOfTime", uncertaintyOfTime);

	return true;
}


bool S111Metadata::ReadMetadata(__int64 file_id)
{
	ReadMetadataStringAttribute(file_id, "nationalOriginator", nationalOriginator);
	ReadMetadataStringAttribute(file_id, "producingAgency", producingAgency);
	ReadMetadataStringAttribute(file_id, "productSpecification", productSpecification);
	ReadMetadataStringAttribute(file_id, "dateOfIssue", dateOfIssue);


	ReadMetadataIntegerAttribute(file_id, "editionNumber", editionNumber);

	ReadMetadataStringAttribute(file_id, "fileName", fileName);
	ReadMetadataStringAttribute(file_id, "dataType", dataType);  
	ReadMetadataStringAttribute(file_id, "nameRegion", nameRegion);
	ReadMetadataStringAttribute(file_id, "nameSubregion", nameSubregion);
	ReadMetadataStringAttribute(file_id, "horizontalDatumReference", horizontalDatumReference);
	ReadMetadataIntegerAttribute(file_id, "horizontalDatumValue", horizontalDatumValue);
	ReadMetadataFloatAttribute(file_id, "westBoundLongitude", westBoundLongitude);
	ReadMetadataFloatAttribute(file_id, "eastBoundLongitude", eastBoundLongitude);
	ReadMetadataFloatAttribute(file_id, "southBoundLatitude", southBoundLatitude);
	ReadMetadataFloatAttribute(file_id, "northBoundLatitude", northBoundLatitude);
	ReadMetadataStringAttribute(file_id, "dateTimeOfFirstRecord", dateTimeOfFirstRecord);
	ReadMetadataStringAttribute(file_id, "dateTimeOfLastRecord", dateTimeOfLastRecord);
	ReadMetadataIntegerAttribute(file_id, "timeRecordInterval", timeRecordInterval);
	ReadMetadataIntegerAttribute(file_id, "numberOfTimes", numberOfTimes);
	ReadMetadataIntegerAttribute(file_id, "typeOfCurrentData", (int&)typeOfCurrentData);
	ReadMetadataIntegerAttribute(file_id, "dataCodingFormat", (int&)dataCodingFormat);
	ReadMetadataIntegerAttribute(file_id, "numberOfStations", numberOfStations);
	ReadMetadataStringAttribute(file_id, "methodOrSource", methodOrSource);
	ReadMetadataIntegerAttribute(file_id, "depthTypeIndex", (int&)depthTypeIndex);
	ReadMetadataFloatAttribute(file_id, "surfaceCurrentDepth", surfaceCurrentDepth);
	ReadMetadataIntegerAttribute(file_id, "verticalDatum", (int&)verticalDatum);
	ReadMetadataFloatAttribute(file_id, "gridOriginLongitude", gridOriginLongitude);
	ReadMetadataFloatAttribute(file_id, "gridOriginLatitude", gridOriginLatitude);
	ReadMetadataFloatAttribute(file_id, "gridSpacingLongitudinal", gridSpacingLongitudinal);
	ReadMetadataFloatAttribute(file_id, "gridSpacingLatitudinal", gridSpacingLatitudinal);
	ReadMetadataIntegerAttribute(file_id, "numberPointsLong", numberPointsLong);
	ReadMetadataIntegerAttribute(file_id, "numberPointsLat", numberPointsLat);
	ReadMetadataIntegerAttribute(file_id, "minimumGridPointLongitudinal", minimumGridPointLongitudinal);
	ReadMetadataIntegerAttribute(file_id, "minimumGridPointLatitudinal", minimumGridPointLatitudinal);
	ReadMetadataIntegerAttribute(file_id, "numberOfNodes", numberOfNodes);
	ReadMetadataFloatAttribute(file_id, "gridLandMaskValue", gridLandMaskValue);
	ReadMetadataFloatAttribute(file_id, "uncertaintyOfSpeed", uncertaintyOfSpeed);
	ReadMetadataFloatAttribute(file_id, "uncertaintyOfDirection", uncertaintyOfDirection);
	ReadMetadataFloatAttribute(file_id, "uncertaintyOfHorizontalPosition", uncertaintyOfHorizontalPosition);
	ReadMetadataFloatAttribute(file_id, "uncertaintyOfVerticalPosition", uncertaintyOfVerticalPosition);
	ReadMetadataFloatAttribute(file_id, "uncertaintyOfTime", uncertaintyOfTime);

	return true;
}


bool S111Metadata::WriteMetadataNationalOriginator(__int64 file_id)
{
	hid_t id_dataspace = H5Screate(H5S_SCALAR);
	hid_t id_type = H5Tcopy(H5T_C_S1);
	H5Tset_size(id_type, 2);
	H5Tset_strpad(id_type, H5T_STR_NULLTERM);
	hid_t id_attribute = H5Acreate2(file_id, "nationalOriginator", id_type, id_dataspace, H5P_DEFAULT, H5P_DEFAULT);

	herr_t ret = H5Awrite(id_attribute, id_type, nationalOriginator.c_str());

	H5Aclose(id_attribute);
	H5Tclose(id_type);
	H5Sclose(id_dataspace);

	return true;
}


bool S111Metadata::WriteMetadataEditionNumber(__int64 file_id)
{
	hsize_t dims = 1;
	hid_t id_dataspace = H5Screate_simple(1, &dims, NULL);
	hid_t id_attribute = H5Acreate2(file_id, "editionNumber", H5T_NATIVE_INT, id_dataspace, H5P_DEFAULT, H5P_DEFAULT);

	H5Awrite(id_attribute, H5T_NATIVE_INT, &editionNumber);

	H5Aclose(id_attribute);
	H5Sclose(id_dataspace);

	return true;
}


bool S111Metadata::WriteMetadataIntegerAttribute(__int64 file_id, char* attributeName, int attributeValue)
{
	hsize_t dims = 1;
	hid_t id_dataspace = H5Screate_simple(1, &dims, NULL);
	hid_t id_attribute = H5Acreate2(file_id, attributeName, H5T_NATIVE_INT64, id_dataspace, H5P_DEFAULT, H5P_DEFAULT);

	H5Awrite(id_attribute, H5T_NATIVE_INT, &attributeValue);

	H5Aclose(id_attribute);
	H5Sclose(id_dataspace);

	return true;
}


bool S111Metadata::WriteMetadataFloatAttribute(__int64 file_id, char* attributeName, float attributeValue)
{
	hid_t id_dataspace = H5Screate(H5S_SCALAR);
	hid_t id_attribute = H5Acreate2(file_id, attributeName, H5T_IEEE_F32LE, id_dataspace, H5P_DEFAULT, H5P_DEFAULT);

	H5Awrite(id_attribute, H5T_IEEE_F32LE, &attributeValue);

	H5Aclose(id_attribute);
	H5Sclose(id_dataspace);

	return true;
}


bool S111Metadata::WriteMetadataStringAttribute(__int64 file_id,
	char* attributeName, char* attributeValue, int sizeValue)
{
	hid_t id_dataspace = H5Screate(H5S_SCALAR);
	hid_t id_type = H5Tcopy(H5T_C_S1);
	H5Tset_size(id_type, sizeValue);
	H5Tset_strpad(id_type, H5T_STR_NULLTERM);
	hid_t id_attribute = H5Acreate2(file_id, attributeName, id_type, id_dataspace, H5P_DEFAULT, H5P_DEFAULT);

	herr_t ret = H5Awrite(id_attribute, id_type, attributeValue);

	H5Aclose(id_attribute);
	H5Tclose(id_type);
	H5Sclose(id_dataspace);

	return true;
}


bool S111Metadata::ReadMetadataIntegerAttribute(__int64 file_id, char* attributeName, int& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(file_id, attributeName);

	if (id_attribute < 0)
	{
		CString str;
		str.Format(_T("Failed to read attribute : %S\n"), attributeName); 
		return false;
	}

	status = H5Aread(id_attribute, H5T_NATIVE_INT, &attributeValue); 

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aread() : %S\n"), attributeName); 

		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aclose() : %S\n"), attributeName); 
		return false;
	}

	return true;
}


bool S111Metadata::ReadMetadataFloatAttribute(__int64 file_id, char* attributeName, float& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(file_id, attributeName);

	if (id_attribute < 0)
	{
		CString str;
		str.Format(_T("Failed to read attribute : %S\n"), attributeName); 
		return false;
	}

	status = H5Aread(id_attribute, H5T_IEEE_F32LE, &attributeValue);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aread() : %S\n"), attributeName); 

		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aclose() : %S\n"), attributeName); 
		return false;
	}

	return true;
}


bool S111Metadata::ReadMetadataStringAttribute(__int64 file_id, char* attributeName, std::string& attributeValue)
{
	herr_t status = 0;

	hid_t id_attribute = H5Aopen_name(file_id, attributeName);

	if (id_attribute < 0)
	{
		CString str;
		str.Format(_T("Failed to read attribute : %S\n"), attributeName); 
		return false;
	}

	hid_t type = H5Aget_type(id_attribute);

	if (type < 0)
	{
		CString str;
		str.Format(_T("Failed to get attribute type : %S"), attributeName); 

		H5Aclose(id_attribute);
		return false;
	}

	int size = H5Aget_storage_size(id_attribute);

	char* buf = new char[size + 1];
	memset(buf, 0, sizeof(char) * (size + 1));

	hid_t type_class = H5Tget_class(type);

	if (type_class != H5T_STRING)
	{
		CString str;
		str.Format(_T("Attribute type is not H5T_STRING : %S\n"), attributeName); 

		H5Tclose(type);
		H5Aclose(id_attribute);
		return false;
	}

	hid_t type_mem = H5Tget_native_type(type, H5T_DIR_ASCEND);

	if (type_mem < 0)
	{
		CString str;
		str.Format(_T("Fail to get native type : %S\n"), attributeName); 

		H5Tclose(type);
		H5Aclose(id_attribute);
		return false;
	}

	status = H5Aread(id_attribute, type_mem, buf);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to read attribute : %S\n"), attributeName); 

		H5Tclose(type);
		H5Aclose(id_attribute);
		return false;
	}

	status = H5Tclose(type);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Faield to close type : %S\n"), attributeName); 

		H5Aclose(id_attribute);
		return false;
	}

	attributeValue = buf;
	delete[] buf;

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aread() : %S\n"), attributeName); 

		H5Aclose(id_attribute);

		return false;
	}

	status = H5Aclose(id_attribute);

	if (status != 0)
	{
		CString str;
		str.Format(_T("Failed to H5Aclose() : %S\n"), attributeName); 
		return false;
	}

	return true;
}