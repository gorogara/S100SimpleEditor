#pragma once
#include "DrawingPattern.h"

namespace S100_SVG_D2D1_DLL
{
	class BoxLayout : public DrawingPattern
	{
	public:
		BoxLayout();
		virtual ~BoxLayout();

	public:
		std::wstring fill;
		std::wstring x;
		std::wstring y;
		std::wstring height;
		std::wstring width;

	public:
		void SetFill(std::wstring& value);
		std::wstring GetFill();

		void SetX(std::wstring& value);
		std::wstring GetX();

		void SetY(std::wstring& value);
		std::wstring GetY();

		void SetHeight(std::wstring& value);
		std::wstring GetHeight();

		void SetWidth(std::wstring& value);
		std::wstring GetWidth();
	};
}
