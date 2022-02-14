#pragma once

#include "userobject.h"

namespace RT
{
	class UserPoint : public UserObject
	{
	public:
		UserPoint(double _x, double _y, std::wstring _name = L"", std::wstring _description = L"");
		virtual ~UserPoint(void);

	public:
		double x;
		double y;
		int size;

	public:
		void Set(double _x, double _y);
		void Get(double& _x, double& _y);
		void SetSize(int _size);
		int GetSize();
		virtual void GetMBR(double& _xmin, double& _ymin, double& _xmax, double& _ymax);
	};
}