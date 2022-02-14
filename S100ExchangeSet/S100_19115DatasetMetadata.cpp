#include "stdafx.h"
#include "S100_19115DatasetMetadata.h"
namespace Dataset
{
	S100_19115DatasetMetadata::S100_19115DatasetMetadata()
	{

	}

	S100_19115DatasetMetadata::~S100_19115DatasetMetadata() 
	{

	}

	void S100_19115DatasetMetadata::SetfileName(FileName value) 
	{
		fileName = value;
	}

	FileName S100_19115DatasetMetadata::GetfileName() 
	{
		return fileName;
	}
}
