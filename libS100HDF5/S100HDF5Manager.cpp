#include "stdafx.h"
#include "S100HDF5Manager.h"

namespace S100HDF5
{

	S100HDF5Manager::S100HDF5Manager()
	{
	}


	S100HDF5Manager::~S100HDF5Manager()
	{
	}


	bool S100HDF5Manager::OpenExchangeSet(std::string path)
	{
		return true;
	}


	bool S100HDF5Manager::OpenS102(std::string path)
	{
		return true;
	}


	bool S100HDF5Manager::OpenS104(std::string path)
	{
		return true;
	}


	bool S100HDF5Manager::OpenS111(std::string path)
	{
		return true;
	}


	bool S100HDF5Manager::OpenS413(std::string path)
	{
		return true;
	}


	std::vector<PickReportResult> S100HDF5Manager::QueryS102(float x, float y)
	{
		std::vector<PickReportResult> result;

		return result;
	}


	std::vector<PickReportResult> S100HDF5Manager::QueryS104RegularGrids(float x, float y, time_t time, int *index)
	{
		std::vector<PickReportResult> result;

		return result;
	}


	std::vector<PickReportResult> S100HDF5Manager::QueryS104FixedStations(float x, float y, time_t time, int *index)
	{
		std::vector<PickReportResult> result;

		return result;
	}


	std::vector<PickReportResult> S100HDF5Manager::QueryS111RegularGrids(float x, float y, time_t time, int *index)
	{
		std::vector<PickReportResult> result;

		return result;
	}


	std::vector<PickReportResult> S100HDF5Manager::QueryS111FixedStations(float x, float y, time_t time, int *index)
	{
		std::vector<PickReportResult> result;

		return result;
	}


	std::vector<PickReportResult> S100HDF5Manager::QueryS413(float x, float y, time_t time, int *index)
	{
		std::vector<PickReportResult> result;

		return result;
	}
}