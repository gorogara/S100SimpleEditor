#pragma once
#include "S100HDF5Feature.h"
#include "RegularGridInformation.h"
#include "RegularGridFeatureValues.h"
#include "TimeInformation.h"
#include "libS100HDF5.h"

#include <vector>

namespace S100HDF5
{
#ifdef LIBS100HDF5_EXPORTS
	LIBS100HDF5_TEMPLATE template class LIBS100HDF5_API std::vector<RegularGridFeatureValues*>;
#endif

	class LIBS100HDF5_API RegularGridFeature :
		public S100HDF5Feature
	{
	public:
		RegularGridFeature();
		virtual ~RegularGridFeature();

		void SetRegularGridInformation(RegularGridInformation* regularGridInformation);
		RegularGridInformation* GetRegularGridInformation();

		void AddRegularGridFeatureValues(RegularGridFeatureValues* featureValues);
		RegularGridFeatureValues* GetRegularGridFeatureValues(int index);
		RegularGridFeatureValues* GetNearestRegularGridFeatureValues(time_t time, TimeInformation* timeInformation);

	private:
		RegularGridInformation* _RegularGridInformation = nullptr;
		std::vector<RegularGridFeatureValues* > _Values;
	};
}