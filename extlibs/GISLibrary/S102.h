#pragma once

#include "S100HDF5File.h"
#include "RegularGridFeature.h"

#include <vector>

namespace S100HDF5
{

	class S102 :
		public S100HDF5File
	{
	public:
		S102();
		virtual ~S102();

		bool Open(std::string path);

		PickReportResult PickReport(float x, float y, time_t time, const char* featureName);

		void SetRegularGrid(RegularGridFeature* regularGrid);

		RegularGridFeature* GetRegularGrid(int index);

	private:
		void ReadBoundingBox(__int64 Id);
		RegularGridFeature* _RegularGrids;
	};

}