#pragma once

#include <vector>
#include "GraphicBasePackage_PathSegment.h"

namespace GraphicBasePackage
{
	class Path
	{
	public:
		Path();
		virtual ~Path();

	public:
		std::vector<PathSegment*> _segment;

	public:
		void FreeMemory();
		Path& operator=(Path& path);
	};
}