#include "stdafx.h"
#include "BoundingBox.h"

namespace Dataset
{
	BoundingBox::BoundingBox()
	{

	}

	BoundingBox::~BoundingBox()
	{

	}

	void BoundingBox::SetAttribute(std::unordered_map<std::wstring, std::wstring> value)
	{
		attribute = value;
	}
	void BoundingBox::SetWestBoundLongitude(WestBoundLongitude value)
	{
		westBoundLongitude = value;
	}
	void BoundingBox::SetEastBoundLongitude(EastBoundLongitude value)
	{
		eastBoundLongitude = value;
	}
	void BoundingBox::SetSouthBoundLongitude(SouthBoundLongitude value)
	{
		southBoundLongitude = value;
	}
	void BoundingBox::SetNorthBoundLongitude(NorthBoundLongitude value)
	{
		northBoundLongitude = value;
	}

	std::unordered_map<std::wstring, std::wstring> BoundingBox::GetAttribute()
	{
		return attribute;
	}

	WestBoundLongitude BoundingBox::GetWestBoundLongitude()
	{
		return westBoundLongitude;
	}

	EastBoundLongitude BoundingBox::GetEastBoundLongitude()
	{
		return eastBoundLongitude;
	}

	SouthBoundLongitude BoundingBox::GetSouthBoundLongitude()
	{
		return southBoundLongitude;
	}

	NorthBoundLongitude BoundingBox::GetNorthBoundLongitude()
	{
		return northBoundLongitude;
	}
}

