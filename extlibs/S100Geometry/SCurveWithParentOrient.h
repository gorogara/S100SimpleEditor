#pragma once

class SCurve;
class SCurveWithParentOrient
{
public:
	SCurveWithParentOrient(bool _parentOrient, SCurve* _curve)
	{
		parentOrient = _parentOrient;
		curve = _curve;
	}

private:
	bool parentOrient = true;
	bool m_masking = false;
	SCurve* curve = nullptr;

public:
	bool GetParentOrient()
	{
		return parentOrient;
	}

	SCurve* GetCurve()
	{
		return curve;
	}
	void SetMasking(bool value);
	bool GetMasking();
};