#pragma once
#include "libS100HDF5.h"

#include <string>
namespace S100HDF5
{   

	class LIBS100HDF5_API FloatValues
	{
	public:
		FloatValues();
		virtual ~FloatValues();

		const char *GetName();
		float* GetValues();
		int GetValueCount();

		void SetName(const char *name);
		void SetValues(float* values, int count);

	private:
		char *_Name = nullptr;
		float* _Values = nullptr;
		int _ValueCount = 0;
	};
}