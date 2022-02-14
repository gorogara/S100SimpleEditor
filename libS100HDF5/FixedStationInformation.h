#pragma once

#include "FloatPoint.h"
#include "libS100HDF5.h"

namespace S100HDF5
{

	class LIBS100HDF5_API FixedStationInformation
	{
	public:
		FixedStationInformation();
		virtual ~FixedStationInformation();

		int GetNumberOfTimes();
		void SetNumberOfTimes(int num);

		void SetPositioning(S100HDF5::Point* positioning, int numberOfNodes);
		S100HDF5::Point* GetPositioning();
		int GetNumberOfNode();

	private:
		int _NumberOfTimes = 0;
		int _NumberOfNode = 0;
		S100HDF5::Point* _Positioning = nullptr;
	};

}