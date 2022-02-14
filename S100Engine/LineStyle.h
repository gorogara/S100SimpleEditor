#pragma once
#include <string>
#include <vector>

using namespace std;

#include "AbstractLineStyle.h"
#include "Dash.h"
#include "GraphicBasePackage.h"

namespace LineStylesPackage
{
	class LineSymbol;

	class LineStyle : public AbstractLineStyle
	{
	public:
		LineStyle();
		virtual ~LineStyle();
	
	public:
		double intervalLength;
		double offset;
		std::vector<LineStylesPackage::Dash *> dash;
		std::vector<LineStylesPackage::LineSymbol *> symbol;
		GraphicBasePackage::Pen* pen;
		LineStylesPackage::CapStyle _capStyle = LineStylesPackage::eCapStyle_butt;
		LineStylesPackage::JoinStyle _joinStyle = LineStylesPackage::eJoinStyle_miter;
	};
}