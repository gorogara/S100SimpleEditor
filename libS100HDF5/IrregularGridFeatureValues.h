#pragma once

#include "FloatValues.h"
#include "libS100HDF5.h"

#include <ctime>
#include <vector>
namespace S100HDF5
{
#ifdef LIBS100HDF5_EXPORTS
	LIBS100HDF5_TEMPLATE template class LIBS100HDF5_API std::vector<FloatValues*>;
#endif

	class LIBS100HDF5_API IrregularGridFeatureValues
	{
	public:
		IrregularGridFeatureValues();
		virtual ~IrregularGridFeatureValues();

		void SetTime(time_t TimePoint);
		void AddFloatValues(FloatValues* Values);

		time_t GetTime();
		FloatValues* GetFloatValues(int index);
		int GetFloatValuesCount();

		static char* TimePointAttributeName;

	private:
		time_t _TimePoint = 0;
		std::vector<FloatValues*> _Values;
	};
}