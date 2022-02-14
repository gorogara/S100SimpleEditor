#include "stdafx.h"
#include "ScaleSearchFormat.h"
namespace Dataset
{
	ScaleSearchFormat::ScaleSearchFormat()
	{

	}
	ScaleSearchFormat::~ScaleSearchFormat()
	{

	}

	void ScaleSearchFormat::SetSearchStateForScale(ScaleState value) 
	{
		searchStateForScale = value;
	}
	ScaleState ScaleSearchFormat::GetSearchStateForScale() 
	{
		return searchStateForScale;
	}

	void ScaleSearchFormat::SetData(S100_DatasetDiscoveryMetadata value)
	{
		data = value;
	}

	S100_DatasetDiscoveryMetadata ScaleSearchFormat::GetData() 
	{
		return data; 
	}
}
