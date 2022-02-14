#pragma once

#include <string>
#include "AbstractLineStyle.h"

namespace LineStylesPackage
{
	class LineStyleReference : public AbstractLineStyle
	{
	public:
		LineStyleReference();
		virtual ~LineStyleReference();
	public:
		std::wstring reference;
	};
}