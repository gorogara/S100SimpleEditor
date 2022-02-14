#pragma once
#include "S100HDF5File.h"
#include "FixedStationFeature.h"
#include "RegularGridFeature.h"

#include <vector>

namespace S100HDF5
{

	class S111 :
		public S100HDF5File
	{
	public:
		S111();
		virtual ~S111();

		bool Open(std::string path);

		PickReportResult PickReport(float x, float y, time_t time, const char* featureName);

		void SetFixedStaion(FixedStationFeature* fixedStation);
		void SetRegularGrid(RegularGridFeature* regularGrid);

		FixedStationFeature* GetFixedStation(int index);
		RegularGridFeature* GetRegularGrid(int index);

	private:
		void ReadBoundingBox(__int64 Id);
		FixedStationFeature* _FixedStations;
		RegularGridFeature* _RegularGrids;
	};

}