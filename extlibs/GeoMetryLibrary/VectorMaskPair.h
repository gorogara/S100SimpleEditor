#pragma once

struct VectorMaskPair
{
public:
	VectorMaskPair(); 
	VectorMaskPair(unsigned startIndex, unsigned size, bool isMask); 
	virtual ~VectorMaskPair();

public:
	unsigned m_startIndex;
	unsigned m_size;
	bool m_bMask;
};
