#pragma once
#include <Windows.h>

namespace kv
{
	struct VIEW_ARROW
	{
		int width;
		float angle;
		bool fill;
	};

	void arrow_to(HDC dc, int x0, int y0, int x, int y, VIEW_ARROW& va);
};