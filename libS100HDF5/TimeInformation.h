#pragma once
#include "libS100HDF5.h"

#include <ctime>
#include <string>
namespace S100HDF5
{

	class LIBS100HDF5_API TimeInformation
	{
	public:
		TimeInformation();
		virtual ~TimeInformation();

		void SetTimeInformation(
			time_t DateTimeOfFirstRecord,
			time_t DateTimeOfLastRecord,
			int TimeRecordInterval);

		int GetNumberOfTimes();
		int GetTimeRecordInterval();
		time_t GetDateTimeOfFirstRecord();
		time_t GetDateTimeOfLastRecord();

		int GetNearestTimeIndex(time_t time);
		time_t GetTime(int index);

		static time_t GetTimeTfromISO8601Basic(std::string text);

		static char* DateTimeOfFirstRecordAttributeName;
		static char* DateTimeOfLastRecordAttributeName;
		static char* TimeRecordIntervalAttributeName;

	private:
		time_t _DateTimeOfFirstRecord = 0;
		time_t _DateTimeOfLastRecord = 0;
		int _TimeRecordInterval = 0;
		int _NumberOfTimes = 0;
	};

}