#pragma once

namespace Dataset
{
	class WestBoundLongitude
	{
	public:
		WestBoundLongitude();
		~WestBoundLongitude();

	private:
		double Decimal=0;

	public:
		void SetDecimal(double value);
		double GetDecimal();
	};
}