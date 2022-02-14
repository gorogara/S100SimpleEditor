#pragma once

#import <msxml4.dll>

#include <vector>
#include <map>

#include "AbstractLineStyle.h"
#include "CompositeLineStyle.h"
#include "LineStyle.h"
#include "LineStyleReference.h"
#include "LineSymbol.h"


namespace LineStylesPackage
{
	class LineStyles
	{
	public:
		LineStyles();
		virtual ~LineStyles();

	public:
		std::map<std::wstring, AbstractLineStyle*> mapLineStyle;

	public:
		bool GetRect(CString name, D2D1_RECT_F *pRect);
	};
}