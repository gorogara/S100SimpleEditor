#pragma once

#include "S100HDF5File.h"
#include "IrregularGridFeature.h"
#include <vector>

namespace S100HDF5
{

	class S413 :
		public S100HDF5File
	{
	public:
		S413();
		virtual ~S413();

		bool Open(std::string path);

		PickReportResult PickReport(float x, float y, time_t time, const char* featureName);

		void AddIrregularGridFeature(IrregularGridFeature* irregularGridFeature);

		IrregularGridFeature* GetIrregularGridFeature(int index);

		static const char* AvgWavDirGroupName;
		static const char* AvgWavDirInstanceGroupName;


	private:
		void ReadBoundingBox(__int64 fileId);
		void ReadFeatureWithSingleFloatValue(__int64 fileId, const char* FeatureName);
		void ReadFeatureWithDoubleFloatValue(__int64 fileId, const char* FeatureName, const char* columnName1, const char* columnName2);
		IrregularGridInformation* ReadPositioning(__int64 instanceGroupId);
		std::vector<IrregularGridFeature* > _Features;
	};

}