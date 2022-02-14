#ifndef LEG_H
#define LEG_H

#include "RoutePlanner.h"

#include <string>
#include <list>
#include <unordered_map>
#include <ctime> 
#define KN2MS 0.514444; 
#define KM2M 1000;

class ENCLine;

namespace RT
{

	class Waypoint;
	class informationAssociation;
	class featureAssociation;
	class Leg
	{
	public:
		Leg();
		Leg(double _x1, double _y1, double _x2, double _y2);
		virtual ~Leg();

	public:
		std::wstring id;
		std::wstring curveID;
		std::wstring speedMin;
		std::wstring speedMax;
		std::list<informationAssociation*> iaList;
		std::list<featureAssociation*> faList;
		std::wstring posList;
		ENCLine *line;
		double v_speedMin;
		double v_speedMax;
		Waypoint* m_asWaypoint; 
		RT::PointD leftBufStartPoint;
		RT::PointD leftBufEndPoint;
		RT::PointD rightBufStartPoint;
		RT::PointD rightBufEndPointX;
		double startOffset; 
		double endOffset; 

	public:            
		bool SetSpeed(double _min, double _max); 
		bool GetSpeed(double &_min, double &_max);
		double GetDistance();
		double GetHeading();
		double GetTimeRequired();   
		void GetContent(MSXML2::IXMLDOMNodePtr nodePtr);
		void Save(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr);
	};

} 
#endif