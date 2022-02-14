#pragma once 
#include "DRReader.h"

#include <iostream>
#include <fstream>

struct DRDirectory
{  

public:
	unsigned tag = 0;
	unsigned length = 0;
	unsigned pos = 0;
};

class DRDirectoryInfo
{
public:
	DRDirectoryInfo(void);
	DRDirectoryInfo(int directoryCount);
	virtual ~DRDirectoryInfo(void);

public:
	DRDirectory *directories;
	unsigned m_count;

public:
	bool ReadDir(DRReader drReader, BYTE*& buf); 
	DRDirectory* GetDirectory(int count);
	void ReAllocateDirectory(int count);
};