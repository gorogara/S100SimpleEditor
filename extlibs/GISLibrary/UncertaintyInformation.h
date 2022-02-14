#pragma once
class UncertaintyInformation
{
public:
	UncertaintyInformation(double _lon, double _lat, double _miter);
	virtual ~UncertaintyInformation();
public:
	double lon = 0;
	double lat = 0;
	double miter = 0;

public:
	void SetLon(double value);
	double GetLon();

	void SetLat(double value);
	double GetLat();

	void SetMiter(double value);
	double GetMiter();
};