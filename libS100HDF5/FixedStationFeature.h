#pragma once

#include "S100HDF5Feature.h"
#include "FixedStationInformation.h"
#include "FixedStationFeatureValues.h"
#include "libS100HDF5.h"

#include <vector>

namespace S100HDF5
{
#ifdef LIBS100HDF5_EXPORTS
	LIBS100HDF5_TEMPLATE template class LIBS100HDF5_API std::vector<FixedStationFeatureValues*>;
#endif

	class LIBS100HDF5_API FixedStationFeature :
		public S100HDF5Feature
	{
	public:
		FixedStationFeature();
		virtual ~FixedStationFeature();

		void SetFixedStationInformation(FixedStationInformation* fixedStationInformation);
		FixedStationInformation* GetFixedStationInformation();

		void AddFixedStationFeatureValues(FixedStationFeatureValues* value);
		FixedStationFeatureValues* GetFixedStationFeatureValues(int index);
		FixedStationFeatureValues* GetNearestIrregularGridFeatureValues(time_t time, TimeInformation* timeInformation);

	private:
		FixedStationInformation* _FixedStationInformation = nullptr;
		std::vector<FixedStationFeatureValues* > _Values;
	};

}