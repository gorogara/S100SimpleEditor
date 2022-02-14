#pragma once

namespace Dataset
{
	class NorthBoundLongitude
	{
	public:
		NorthBoundLongitude();
		virtual ~NorthBoundLongitude();

	private:
		double Decimal=0;

	public:
		void SetDecimal(double value);
		double GetDecimal();
	};
}