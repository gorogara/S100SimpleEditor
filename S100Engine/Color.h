#pragma once

#include <string>

using namespace std;

namespace GraphicBasePackage
{
	class Color
	{
	public:
		Color();
		virtual ~Color();

	public:
		std::wstring token;
		double transparency = 0;
	};
}

namespace libS100Engine
{

	class Color
	{
	public:
		Color();
		virtual ~Color();

	public:
		wstring token;
		wstring name;
		wstring desctiption;
	};

}