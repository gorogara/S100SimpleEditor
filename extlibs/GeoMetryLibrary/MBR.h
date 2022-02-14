#pragma once

class MBR
{
public:
	MBR();
	MBR(double _xmin, double _ymin, double _xmax, double _ymax);
	virtual ~MBR(void);

public:
	double xmin = 0;
	double ymin = 0;
	double xmax = 0;
	double ymax = 0;

public:
	void SetXMin(double& value);
	double GetXMin();

	void SetYMin(double& value);
	double GetYMin();

	void SetXMax(double& value);
	double GetXMax();

	void SetYMax(double& value);
	double GetYMax();

	void SetMBR(MBR mbr);
	void SetMBR(double _xmin, double _ymin, double _xmax, double _ymax); 
	void ReMBR(MBR newMBR);
	void CalcMBR(double x, double y);
	void CalcMBR(MBR& mbr);
	void InitMBR();

	static bool CheckOverlap(MBR screenMBR, MBR objMBR)
	{
		if ((objMBR.ymin >= screenMBR.ymin && objMBR.ymin <= screenMBR.ymax) ||
			(objMBR.ymax >= screenMBR.ymin && objMBR.ymax <= screenMBR.ymax) ||
			(objMBR.ymin <= screenMBR.ymin && objMBR.ymax >= screenMBR.ymax)
			)
		{
			if ((objMBR.xmin >= screenMBR.xmin && objMBR.xmin <= screenMBR.xmax) ||
				(objMBR.xmax >= screenMBR.xmin && objMBR.xmax <= screenMBR.xmax) ||
				(objMBR.xmin <= screenMBR.xmin && objMBR.xmax >= screenMBR.xmax)
				)
			{
				return true;
			}
		}
		return false;
	}
	bool operator== (MBR& _mbr)
	{
		if ((xmin == _mbr.xmin) && (xmax == _mbr.xmax) && (ymin == _mbr.ymin) && (ymax == _mbr.ymax))
		{
			return true;
		}
		return false;
	}
	static bool IntersectMBR(const MBR& _mbr1, const MBR& _mbr2, MBR& _intersectMBR)
	{
		if (_mbr1.xmin > _mbr2.xmin)
		{
			_intersectMBR.xmin = _mbr1.xmin;
		}
		else
		{
			_intersectMBR.xmin = _mbr2.xmin;
		}

		if (_mbr1.xmax > _mbr2.xmax)
		{
			_intersectMBR.xmax = _mbr2.xmax;
		}
		else
		{
			_intersectMBR.xmax = _mbr1.xmax;
		}

		if (_intersectMBR.xmax < _intersectMBR.xmin)
		{
			return false;
		}

		if (_mbr1.ymin > _mbr2.ymin)
		{
			_intersectMBR.ymin = _mbr1.ymin;
		}
		else
		{
			_intersectMBR.ymin = _mbr2.ymin;
		}

		if (_mbr1.ymax > _mbr2.ymax)
		{
			_intersectMBR.ymax = _mbr2.ymax;
		}
		else
		{
			_intersectMBR.ymax = _mbr1.ymax;
		}

		if (_intersectMBR.ymax < _intersectMBR.ymin)
		{
			return false;
		}

		return true;
	}
	bool PtInMBR(double x, double y)
	{
		if ((xmin <= x) && (x <= xmax) && (ymin <= y) && (y <= ymax))
		{
			return true;
		}

		return false;
	}
};

