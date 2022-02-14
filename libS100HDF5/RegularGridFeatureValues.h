#pragma once

#include "FloatValues.h"
#include "libS100HDF5.h"

#include <vector>

namespace S100HDF5
{
#ifdef LIBS100HDF5_EXPORTS
	LIBS100HDF5_TEMPLATE template class LIBS100HDF5_API std::vector<FloatValues*>;
#endif

	class LIBS100HDF5_API RegularGridFeatureValues
	{
	public:
		RegularGridFeatureValues();
		virtual ~RegularGridFeatureValues();

		void AddFloatValues(FloatValues* floatValues);
		FloatValues* GetFloatValues(int index);
		int GetFloatValuesCount();

	private:
		std::vector<FloatValues*> _Values;
	};
}