#include "stdafx.h"
#include "S100GML_Point.h"
#include "WStringToken.h"


namespace S100DatasetGML
{
	S100GML_Point::S100GML_Point()
	{ 
	}


	S100GML_Point::~S100GML_Point()
	{
	}

	int S100GML_Point::GetType()
	{
		return 1;
	}

	std::list<GMLPoint> S100GML_Point::GetCoordinates()
	{
		std::list<GMLPoint> list;

		std::vector<double> arrX;
		std::vector<double> arrY;

		std::string message_a;

		message_a.assign(pos.begin(), pos.end());
		printf(message_a.c_str());

		GMLStringTokenizer *pstringTokenizer = new GMLStringTokenizer(message_a, " \t");

		int count = 1;
		while (pstringTokenizer->hasMoreTokens())
		{
			std::string token = pstringTokenizer->nextToken();

			double val = atof(token.c_str());
			if (count % 2 == 1)
			{
				arrX.push_back(val);
			}
			else
			{
				arrY.push_back(val);
			}
			count++;
		}

		delete pstringTokenizer;

		for (unsigned i = 0; i < arrX.size(); i++)
		{
			list.push_back(GMLPoint(arrX[i], arrY[i]));
		}

		return list;
	}
}                             
