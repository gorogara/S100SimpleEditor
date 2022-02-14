#pragma once
#include "RecordName.h"

struct RIAS
{
	RecordName m_name;
	unsigned m_ornt;
	unsigned m_usag;
	unsigned m_raui;

	static const int size = 8;
};

