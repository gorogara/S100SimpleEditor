#pragma once
#include <vector>
#include "SENC_Element.h"
#include "SENC_VectorPoint.h"
class SENC_TextPoint
{
public:
	SENC_TextPoint();
	~SENC_TextPoint();

public:
	int horizontalAlignment;
	int verticalAlignment;

	std::vector<SENC_Element*> elements;
	SENC_VectorPoint offset;

};

