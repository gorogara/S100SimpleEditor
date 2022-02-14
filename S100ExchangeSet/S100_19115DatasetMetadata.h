#pragma once
#include "FileName.h"
namespace Dataset
{
	class S100_19115DatasetMetadata
	{
	public:
		S100_19115DatasetMetadata();
		virtual ~S100_19115DatasetMetadata();

	private:
		FileName fileName;

	public :
		void SetfileName(FileName value);
		FileName GetfileName();
	};
}