#pragma once

#include "libS100HDF5.h"
#include "S100HDF5File.h"
#include "PickReportResult.h"

#include <vector>
#include <string>
#include <ctime>

namespace S100HDF5
{

	class LIBS100HDF5_API S100HDF5Manager
	{
	public:
		S100HDF5Manager();
		virtual ~S100HDF5Manager();

		bool OpenExchangeSet(std::string path);
		bool OpenS102(std::string path);
		bool OpenS104(std::string path);
		bool OpenS111(std::string path);
		bool OpenS413(std::string path);

		std::vector<PickReportResult> QueryS102(float x, float y);
		std::vector<PickReportResult> QueryS104RegularGrids(float x, float y, time_t time, int *index);
		std::vector<PickReportResult> QueryS104FixedStations(float x, float y, time_t time, int *index);
		std::vector<PickReportResult> QueryS111RegularGrids(float x, float y, time_t time, int *index);
		std::vector<PickReportResult> QueryS111FixedStations(float x, float y, time_t time, int *index);
		std::vector<PickReportResult> QueryS413(float x, float y, time_t time, int *index);
	};

}