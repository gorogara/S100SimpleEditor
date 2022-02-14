#pragma once

#include "S100HDF5File.h"
#include "FixedStationFeature.h"
#include "RegularGridFeature.h"

#include <vector>

namespace S100HDF5
{

	class LIBS100HDF5_API S104 :
		public S100HDF5File
	{
	public:
		S104();
		virtual ~S104();

		bool Open(std::string path);

		PickReportResult PickReport(float x, float y, time_t time, const char* featureName);

		void SetFixedStaion(FixedStationFeature* fixedStation);
		void SetRegularGrid(RegularGridFeature* regularGrid);

		FixedStationFeature* GetFixedStation(int index);
		RegularGridFeature* GetRegularGrid(int index);

	private: 
		void SetBoundingBoxFromPositioning();
		FixedStationFeature* _FixedStations = nullptr;
		RegularGridFeature* _RegularGrids = nullptr;
	};

}