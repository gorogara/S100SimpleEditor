#pragma once

#define DR_LENGTH			24
#define RECORD_LENGTH		5
#define FIELD_LENGTH		1
#define FIELD_POSITION		1

#include <iostream>
#include <fstream>

using namespace std;

class DRReader
{
public:
	DRReader(void);
	virtual ~DRReader(void);

public:
	static const unsigned size = 24;
	unsigned m_recordLength;
	unsigned m_fieldAreaLoc;
	unsigned m_fieldLength;
	unsigned m_fieldPosition;

public:
	bool ReadReader(BYTE*& buf); 
};