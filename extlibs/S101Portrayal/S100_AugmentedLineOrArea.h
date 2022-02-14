#pragma once
#include "S100_AugmentedGeometry.h"
#include "S100_LineStyleReference.h"
#include "S100_CompositeLineStyle.h"

class S100_AugmentedLineOrArea :
	public S100_AugmentedGeometry
{
public:
	S100_AugmentedLineOrArea();
	virtual ~S100_AugmentedLineOrArea();

public:
	S100_LineStyleReference* lineStyleReference;
	S100_CompositeLineStyle* compositeLineStyle;
	S100_LineStyle *lineStyle;
};

