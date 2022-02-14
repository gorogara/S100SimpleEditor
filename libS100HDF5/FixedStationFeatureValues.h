#pragma once

#include "FloatValues.h"
#include "libS100HDF5.h"

#include <vector>
#include <string>

namespace S100HDF5
{   

	class LIBS100HDF5_API FixedStationFeatureValues
	{
	public:
		FixedStationFeatureValues();
		virtual ~FixedStationFeatureValues();

		void SetName(const char *subregionName);
		const char * GetName();

		void AddFloatValues(FloatValues* floatValues);
		FloatValues* GetFloatValues(int index);
		int GetFloatValuesCount();

	private:
		std::vector<FloatValues*> _Values; 
		char *_SubregionName = nullptr;
	};

}