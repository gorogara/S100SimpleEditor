#pragma once

#include "libS100HDF5.h"
#include "S100HDF5Feature.h"
#include "IrregularGridInformation.h"
#include "IrregularGridFeatureValues.h"

namespace S100HDF5
{
#ifdef LIBS100HDF5_EXPORTS
	LIBS100HDF5_TEMPLATE template class LIBS100HDF5_API std::vector<IrregularGridFeatureValues* >;
#endif

	class LIBS100HDF5_API IrregularGridFeature :
		public S100HDF5Feature
	{
	public:
		IrregularGridFeature();
		virtual ~IrregularGridFeature();

		void SetIrregularGridInformation(IrregularGridInformation* irregularGridInformation);
		void AddIrregularGridFeatureValues(IrregularGridFeatureValues* irregularGridFeatureValues);

		IrregularGridInformation* GetIrregularGridInformation();
		IrregularGridFeatureValues* GetIrregularGridFeatureValues(int index);
		IrregularGridFeatureValues* GetNearestIrregularGridFeatureValues(time_t time);

	private:
		IrregularGridInformation* _IrregularGridInformation = nullptr;
		std::vector<IrregularGridFeatureValues* > _Values;
	};

}