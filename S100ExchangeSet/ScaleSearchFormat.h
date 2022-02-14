#pragma once
#include "ScaleState.h"
#include "S100_DatasetDiscoveryMetadata.h"

namespace Dataset
{
	class ScaleSearchFormat
	{
	public:
		ScaleSearchFormat();
		virtual ~ScaleSearchFormat();

	private:
		ScaleState searchStateForScale;
		S100_DatasetDiscoveryMetadata data;

	public:
		void SetSearchStateForScale(ScaleState value);
		ScaleState GetSearchStateForScale();

		void SetData(S100_DatasetDiscoveryMetadata value);
		S100_DatasetDiscoveryMetadata GetData();
	};
}