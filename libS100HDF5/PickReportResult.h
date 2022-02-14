#pragma once

#include "libS100HDF5.h"

#include <ctime>
#include <vector>

namespace S100HDF5
{
#ifdef LIBS100HDF5_EXPORTS
	LIBS100HDF5_TEMPLATE template class LIBS100HDF5_API std::vector<float> ;
#endif

	class LIBS100HDF5_API PickReportResult
	{
	public:
		PickReportResult();
		virtual ~PickReportResult();

		void SetX(float x);
		void SetY(float y);
		void AddValue(float value);
		void SetTime(time_t time);

		float GetX();
		float GetY();
		float GetValue(int index);
		time_t GetTime();

	private:
		float _X = 0;
		float _Y = 0;
		std::vector<float> _Values;
		time_t _Time = 0;
	};
}