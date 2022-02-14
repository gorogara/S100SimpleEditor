#pragma once
#include "TimeInformation.h"
#include "DataCodingFormat.h"
#include "libS100HDF5.h"

#include <string>
namespace S100HDF5
{   

	class LIBS100HDF5_API S100HDF5Feature
	{
	public:
		S100HDF5Feature();
		virtual ~S100HDF5Feature();

		void SetDataCodingFormat(DataCodingFormat dataCodingFormat);
		void SetName(const char *name);
		void SetTimeInformation(TimeInformation* timeInformation);

		DataCodingFormat GetDataCodingFormat();
		const char *GetName();
		TimeInformation* GetTimeInformation();

	private:
		DataCodingFormat _DataCodingFormat = DataCodingFormat::None;
		char *_Name = nullptr;
		TimeInformation* _TimeInformation = nullptr;
	};
}