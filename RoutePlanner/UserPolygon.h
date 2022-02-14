#pragma once

#include "userobject.h"

namespace RT
{
	class UserPolygon : public UserObject
	{
	public:
		UserPolygon(double       _px[],
			double       _py[],
			int          _cnt,
			std::wstring _name = L"",
			std::wstring _description = L"");
		virtual ~UserPolygon(void);

	public:
		double* px;
		double* py;
		int     cnt;

		double centX;
		double centY;

		double lineWeight;

	public:
		void Set(double _px[], double _py[], int _cnt);
		void Get(double** _px, double** _py, int& _cnt);

		virtual void GetMBR(double& _xmin, double& _ymin, double& _xmax, double& _ymax);


	};
}