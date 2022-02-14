#pragma once
#include "DRDirectoryInfo.h"
#include "NonPrintableCharacter.h"

#include <atlstr.h>

struct DRDirectoryWriter : public DRDirectory
{
public:
	DRDirectoryWriter();
	DRDirectoryWriter(DRReader leader, DRDirectory& dir)
	{
		this->lengthCipher = leader.m_fieldLength;
		this->posCipher = leader.m_fieldPosition;
		this->tag = dir.tag;
		this->length = dir.length;
		this->pos = dir.pos;

		unsigned i = 0;
		CString str;


		str.Format(TEXT("%09d"), this->length);
		for(i =	0; i < this->lengthCipher; i++)
		{
			b_length[i] = (BYTE)str[9 - this->lengthCipher + i];
		}
		str.Format(TEXT("%09d"), this->pos);
		for(i =	0; i < this->posCipher; i++)
		{
			b_pos[i] = (BYTE)str[9 - this->posCipher + i];
		}
	};
	
public:
	unsigned lengthCipher;
	unsigned posCipher;

	BYTE b_length[9];
	BYTE b_pos[9];
};

class DRDirectoryInfoWriter : public DRDirectoryInfo
{
public:
	DRDirectoryInfoWriter();
	DRDirectoryInfoWriter(int directoryCount);
	virtual ~DRDirectoryInfoWriter();

public:
	BOOL WriteDRDirectory(CFile* file, const DRReader dr);
	void CheckLength(DRReader *dr);
};