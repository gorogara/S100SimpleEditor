#pragma once
#include "RecordName.h"

struct SPAS {
	RecordName m_name;
	unsigned m_ornt;
	unsigned m_smin = 1;
	unsigned m_smax = 15;
	unsigned m_saui;

	static const int size = 15;
};

