#pragma once

#include "libS100HDF5.h"
#include "PickReportResult.h"

#include "GeoMetryLibrary\\MBR.h"

#ifdef LIBS100HDF5_EXPORTS
class LIBS100HDF5_API MBR;
#endif

namespace S100HDF5
{
	
	class LIBS100HDF5_API S100HDF5File
	{
	public:
		S100HDF5File();
		virtual ~S100HDF5File();
		
		virtual bool Open(std::string path) { return true; }
		virtual PickReportResult PickReport(float x, float y, time_t time, const char* featureName) { return PickReportResult(); }

		MBR GetMBR();
		void SetMBR(MBR* mbr);

		static char* XMinAttributeName;
		static char* XMaxAttributeName;
		static char* YMinAttributeName;
		static char* YMaxAttributeName;

	private: 
		MBR _BoundingBox;
	};
}