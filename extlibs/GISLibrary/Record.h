#pragma once

#include "DRDirectoryInfo.h"
#include "DRReader.h"
#include "DRReaderWriter.h"

class Record
{
public:
	Record();
	virtual ~Record();

public:
	virtual BOOL ReadRecord(DRDirectoryInfo *dir, BYTE*& buf) = 0;
};

