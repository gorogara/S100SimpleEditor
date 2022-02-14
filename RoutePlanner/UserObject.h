#pragma once

#include <string>

namespace RT
{
	class UserObject
	{
	public:
		UserObject(void);
		virtual ~UserObject(void);
	public:
		int type;
		std::wstring name;
		std::wstring description;

		int R;
		int G;
		int B;
		std::wstring font;
		bool on;

	public:
		void SetColor(int _R, int _G, int _B);
		void GetColor(int& _R, int& _G, int& _B);

		virtual void GetMBR(double& _xmin, double& _ymin, double& _xmax, double& _ymax) = 0;

		void SetFont(std::wstring _font);
		std::wstring GetFont();


	protected:
		double AdjustLon(double _lon);
		double AdjustLat(double _lat);
		int AdjustRGB(int _rgb);
	};
}