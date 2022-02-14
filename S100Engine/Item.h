#pragma once

#include <string>
#include "SRGB.h"

using namespace std;

namespace libS100Engine
{

	class Item
	{
	public:
		Item();
		virtual ~Item();

	public:
		wstring token;
		SRGB    srgb;
	};

}