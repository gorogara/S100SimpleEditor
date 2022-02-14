#pragma once

#include "libS100HDF5.h"

namespace S100HDF5
{
	enum LIBS100HDF5_API DataCodingFormat
	{
		None = 0,
		FixedStations = 1,
		RegularGird,
		UngeorectifiedGrid,
		MovingFlatform,
		IrregularGrid,
		VariableCellSize,
		TIN
	};
}