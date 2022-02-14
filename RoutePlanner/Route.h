#ifndef ROUTE_H
#define ROUTE_H

#ifndef RADIAN
#define RADIAN 6378.1
#endif

#include <vector>
#include <string>
#include <ctime>
#include <list> 
#define KN2MS 0.514444; 
#define KM2M 1000; 
#define M2KM 0.001;


namespace RT
{
	class Leg;
	class Waypoint;
	class informationAssociation;
	class VesselStaticInfo;

	class Route
	{
	public:
		Route();
		Route(std::wstring _name);
		Route(std::wstring _name, std::time_t _time);
		virtual ~Route();
	public:
		std::wstring id;
		std::list<informationAssociation*> iaList;

		std::vector<Leg*> legs;
		std::vector<Waypoint*> waypoints;
		VesselStaticInfo*  vesselStaticInfo;
		std::wstring name;
		std::time_t curtime;
		std::wstring sourceIndication;
		std::wstring routeStatus;
		std::wstring optimizationMethod;
		std::wstring historyOfRouteChanges;

		Waypoint* GetWaypoint(unsigned _index);

		Waypoint* GetPreWaypoint(Waypoint* curWP);
		Waypoint* GetLastWaypoint();

		double speedStart;
		double bufferDistance; 

	public:
		void GetContent(MSXML2::IXMLDOMNodePtr nodePtr); 
		void AddWaypoint(Waypoint* wp); 
		void AddLeg(Leg* wp); 
		void AddWaypoint(Waypoint*& wp, Leg*& leg, double _x, double _y, double _minSpeed = 0, double _maxSpeed = 0);                  

		Waypoint* SetWaypoint(unsigned int _index, double _x, double _y, double _minSpeed = 0, double _maxSpeed = 0);
		bool DeleteWaypoint(unsigned int _index);        
		Waypoint* DeleteWaypoint(double _x, double _y);
		double GetX(unsigned int _index);
		double GetY(unsigned int _index);
		unsigned int GetWaypointCount();
		unsigned int GetLegCount();
		void SetName(std::wstring _name);
		std::wstring GetName(); 
		double GetDistanceLatitudeLongitude(double latitude1, double longitude1, double latitude2, double longitude2);
		double GetDistanceLeg(unsigned int _legIndex);
		double GetDistanceAccumulated(unsigned int _legIndex);
		time_t GetArrivalTime(unsigned int _wpIndex);
		int GetWaypointIndex(double _x, double _y);
		void SetSpeed(int _legIndex, double _minSpeed, double _maxSpeed);
		void GetSpeed(int _legIndex, double &_minSpeed, double &_maxSpeed);
		void SetSpeed(int _wpIndex, double _speed);
		double GetSpeed(int _wpIndex);
		void SetDepartureTime(time_t& _time);
		time_t GetDepartureTime(); 
		double GetHeading(unsigned int _legIndex);
		bool GetPosSpeedAtTime(std::time_t _time, double& x, double& y, double& speed); 
		double GetBufferDistance(); 
		void SetBufferDistance(double _distance); 
		double GetLength();  
		time_t GetTimeSpan();
		int GetLegIndexAtTime(std::time_t _time);
		void MakeBuf();
		double GetLeftBufLegStartPointX(int _legIndex);
		double GetLeftBUfLegStartPointY(int _legIndex);
		double GetLeftBufLegEndPointX(int _legIndex);
		double GetLeftBufLegEndPointY(int _legIndex);
		double GetRightBufLegStartPointX(int _legIndex);
		double GetRightBUfLegStartPointY(int _legIndex);
		double GetRightBufLegEndPointX(int _legIndex);
		double GetRightBufLegEndPointY(int _legIndex);
		double GetStartOffset(int _legIndex);
		double GetEndOffset(int _legIndex);
		void Save(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr);
	};
}

#endif 