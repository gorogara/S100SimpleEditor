#pragma once

#include "DRDirectoryInfoWriter.h"
#include "DRReader.h"
#include "DRReaderWriter.h"
#include "NonPrintableCharacter.h"
#include "ISO8211Fuc.h"
#include <list>
#include <vector>

class Field
{
public:
	Field();
	virtual ~Field();

public:
	virtual void ReadField(BYTE *&buf) {};
	virtual BOOL Save(CFile *file) { return TRUE; };
	virtual unsigned GetFieldLength() { return 0; };
};