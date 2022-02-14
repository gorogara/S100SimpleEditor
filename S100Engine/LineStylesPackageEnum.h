#pragma once

namespace LineStylesPackage
{
	enum SubClassTypeOfAbstractLineStyle
	{
		eAbstractLineStyle = 0,
		eLineStyle = 1,
		eLineStyleReference = 2,
		eCompositeLineStyle = 3
	};

	enum JoinStyle
	{
		eJoinStyle_bevel = 1,
		eJoinStyle_miter = 2,
		eJoinStyle_round = 3
	};
	enum CapStyle
	{
		eCapStyle_butt = 1,
		eCapStyle_square = 2,
		eCapStyle_round = 3
	};
}