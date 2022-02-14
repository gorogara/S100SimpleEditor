#pragma once
#include "WestBoundLongitude.h"
#include "EastBoundLongitude.h"
#include "SouthBoundLongitude.h"
#include "NorthBoundLongitude.h"

#include <unordered_map>

namespace Dataset
{
	class BoundingBox
	{
	public:
		BoundingBox();
		virtual ~BoundingBox();

	private:
		std::unordered_map<std::wstring, std::wstring> attribute;
		WestBoundLongitude  westBoundLongitude;
		EastBoundLongitude	eastBoundLongitude;
		SouthBoundLongitude	southBoundLongitude;
		NorthBoundLongitude	northBoundLongitude;

	public:
		void SetAttribute(std::unordered_map<std::wstring, std::wstring> value);
		void SetWestBoundLongitude(WestBoundLongitude value);
		void SetEastBoundLongitude(EastBoundLongitude value);
		void SetSouthBoundLongitude(SouthBoundLongitude value);
		void SetNorthBoundLongitude(NorthBoundLongitude value);

		std::unordered_map<std::wstring, std::wstring> GetAttribute();
		WestBoundLongitude GetWestBoundLongitude();
		EastBoundLongitude GetEastBoundLongitude();
		SouthBoundLongitude GetSouthBoundLongitude();
		NorthBoundLongitude GetNorthBoundLongitude();
	};
}