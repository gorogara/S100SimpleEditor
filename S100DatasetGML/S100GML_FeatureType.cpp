#include "stdafx.h"
#include "S100GML_FeatureType.h"
#include "S100GML_Geometry.h"

namespace S100DatasetGML
{
	S100GML_FeatureType::S100GML_FeatureType()
	{
	}

	S100GML_FeatureType::~S100GML_FeatureType()
	{
		delete geometry;
	}

	R_FeatureRecord* S100GML_FeatureType::GetFr() 
	{
		return fr;
	}

	void S100GML_FeatureType::SetFr(R_FeatureRecord* value)
	{
		fr = value;
	}

	std::wstring S100GML_FeatureType::GetCamelCase()
	{
		return camelCase;
	}

	void S100GML_FeatureType::SetCamelCase(std::wstring value)
	{
		camelCase = value;
	}
	
	std::wstring S100GML_FeatureType::GetId() 
	{
		return id;
	}

	void S100GML_FeatureType::SetId(std::wstring value)
	{
		id = value;
	}

	S100GML_Geometry* S100GML_FeatureType::GetGeometry()
	{
		return geometry;
	}

	void S100GML_FeatureType::SetGeometry(S100GML_Geometry* value)
	{
		geometry = value;
	}
}
