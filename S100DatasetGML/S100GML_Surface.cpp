#include "stdafx.h"
#include "S100GML_Surface.h"
#include "WStringToken.h"


namespace S100DatasetGML
{
	S100GML_Surface::S100GML_Surface()
	{
	}


	S100GML_Surface::~S100GML_Surface()
	{
	}

	int S100GML_Surface::GetType()
	{
		return 3;
	}


	std::list<std::list<GMLPoint>> S100GML_Surface::GetCoordinatesInSurface()
	{
		std::list<std::list<GMLPoint>> ret; 
		
		std::list<GMLPoint> plist;

		std::vector<double> arrX;
		std::vector<double> arrY;

		std::string message_a;

		message_a.assign(posListOfExterior.begin(), posListOfExterior.end());
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

		unsigned size = arrX.size() < arrY.size() ? arrX.size() : arrY.size();

		for (unsigned i = 0; i < size; i++)
		{
			plist.push_back(GMLPoint(arrX[i], arrY[i]));
		}
		ret.push_back(plist);

		for (auto itor = posListOfInteriorList.begin(); itor != posListOfInteriorList.end(); itor++)
		{
			std::list<GMLPoint> plist;

			std::vector<double> arrX;
			std::vector<double> arrY;

			std::wstring posList = *itor;
			std::string message_a;

			message_a.assign(posList.begin(), posList.end());
			printf(message_a.c_str());

			GMLStringTokenizer *pstringTokenizer = new GMLStringTokenizer(message_a, " \t");

			int count = 1;
			while (pstringTokenizer->hasMoreTokens())
			{
				std::string token = pstringTokenizer->nextToken();
		
				double val = atof(token.c_str()) ;
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
				plist.push_back(GMLPoint(arrX[i], arrY[i]));
			}

			ret.push_back(plist);
		}
		return ret;
	}
}                            
