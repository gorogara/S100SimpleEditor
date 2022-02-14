#pragma once
namespace Dataset
{
	class SouthBoundLongitude
	{
	public:
		SouthBoundLongitude();
		virtual ~SouthBoundLongitude();

	private:
		double Decimal=0;

	public:
		void SetDecimal(double value);
		double GetDecimal();
	};
}