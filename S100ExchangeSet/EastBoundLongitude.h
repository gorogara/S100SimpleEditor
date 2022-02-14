#pragma once
namespace Dataset
{
	class EastBoundLongitude
	{
	public:
		EastBoundLongitude();
		virtual ~EastBoundLongitude();

	private:
		double Decimal=0;

	public:
		void SetDecimal(double value);
		double GetDecimal();
	};
}