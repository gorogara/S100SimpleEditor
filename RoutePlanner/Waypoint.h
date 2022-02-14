#ifndef WAYPOINT_H
#define WAYPOINT_H
#include <string>
#include <list>

#include "GeoMetryLibrary\\ENCPoint.h"


namespace RT
{
	class informationAssociation;
	class featureAssociation;
	class Leg;
	class ENC_Feature;
	class Route;
	class Waypoint
	{
	public:
		Waypoint();
		Waypoint(double _x, double _y);
		virtual ~Waypoint();

	public:
		double speed; 
		ENC_Feature* m_feature;
		void GetContent(MSXML2::IXMLDOMNodePtr nodePtr);
		std::wstring id;
		std::wstring pointID;
		std::wstring name;

		std::list<informationAssociation*> iaList;
		std::wstring pos;
		ENCPoint *p;
		std::list<featureAssociation*> faList;

		Leg* m_asLeg; 
		Route* m_asRoute; 
		Waypoint* m_asWaypoint; 

	public:
		void SetXY(double _x, double _y);
		void SetX(double _x);
		void SetY(double _y);

		void GetXY(double* _x, double* _y);
		double GetX();
		double GetY();

		void SetSpeed(double _speed);
		double GetSpeed();  
		void Save(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr);
	};
}
#endif 