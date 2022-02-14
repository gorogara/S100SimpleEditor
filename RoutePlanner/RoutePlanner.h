#pragma once

#include "PointD.h"

#include <unordered_map>
#include <string>
#include <ctime>

namespace RT
{
	class Route;
	class Leg;
	class Waypoint;
	class VesselStaticInfo;
	class VesselVoyageInfo; 
	PointD SimpleRightBufPoint(double _x, double _y, double _heading, double _distance, bool _radian);
	PointD SimpleLeftBufPoint(double _x, double _y, double _heading, double _distance, bool _radian);
	double GetAngleFromLegs(double _heading1, double _heading2, bool _radian);
	bool IsRight(double _x1Leg1, double _y1Leg1, double _x2Leg1, double _y2Leg1,
		double _x1Leg2, double _y1Leg2, double _x2Leg2, double _y2Leg2);

	class RoutePlanner
	{
	public:
		RoutePlanner();
		virtual ~RoutePlanner();
	public:
		std::unordered_map<std::wstring, Route*> routes;
		std::vector<Route*> route;
		std::unordered_map<std::wstring, Leg*> legs;
		std::unordered_map<std::wstring, Waypoint*> waypoints;
		std::unordered_map<std::wstring, VesselStaticInfo*> vesselStaticInfo;
		std::unordered_map<std::wstring, VesselVoyageInfo*> vesselVoyageInfo;
		static int idIndex;
	
	public: 
		void AddRoute(std::wstring _name);
		void AddRoute(std::wstring _name, std::time_t _time);
		bool SetRouteName(unsigned int _routeIndex, std::wstring _name);
		bool DeleteRoute(unsigned int _routeIndex);
		unsigned int GetRouteCount();
		std::wstring GetRouteName(unsigned int _routeIndex);   
		bool GetDepartureTime(unsigned int _routeIndex, std::time_t* _time);
		Route* GetRoute(unsigned int _routeIndex);
		bool SetDepartureTime(unsigned int _routeIndex, std::time_t& _time); 
		Waypoint* AddWaypoint(unsigned int _routeIndex, double _x, double _y, double _minSpeed = 0, double _maxSpeed = 0);
		Waypoint* AddWaypoint(unsigned int _routeIndex, unsigned int _afterIndex, double _x, double _y, double _minSpeed = 0, double _maxSpeed = 0);
		Waypoint* SetWaypoint(unsigned int _routeIndex, unsigned int _waypointIndex, double _x, double _y);
		Waypoint* SetWaypoint(unsigned int _routeIndex, unsigned int _waypointIndex, double _x, double _y, double _minSpeed, double _maxSpeed);
		bool DeleteWaypoint(unsigned int _routeIndex, unsigned int _waypointIndex);
		bool DeleteWaypoint(unsigned int _routeIndex, double _x, double _y);
		unsigned int GetWaypointCount(unsigned int _routeIndex);
		Waypoint*	 GetWaypoint(unsigned int _routeIndex, unsigned waypointNumber);
		double       GetX(unsigned int _routeIndex, unsigned int _waypointIndex);
		double       GetY(unsigned int _routeIndex, unsigned int _waypointIndex);
		time_t GetArrivalTime(unsigned int _routeIndex, unsigned int _wpIndex); 
		Leg* AddLeg(Waypoint* wp1, Waypoint* wp2, double _minSpeed = 0, double _maxSpeed = 0);
		double       GetStartX(unsigned int _routeIndex, unsigned int _legIndex);
		double       GetStartY(unsigned int _routeIndex, unsigned int _legIndex);
		double       GetEndX(unsigned int _routeIndex, unsigned int _legIndex);
		double       GetEndY(unsigned int _routeIndex, unsigned int _legIndex);
		void GetSpeed(unsigned int _routeIndex, unsigned int _legIndex, double& _minSpeed, double& _maxSpeed);
		double GetSpeed(unsigned int _routeIndex, unsigned int _wpIndex);
		double GetDistance(unsigned int _routeIndex, unsigned int _legIndex);
		double GetDistanceAccumulated(unsigned int _routeIndex, unsigned int _legIndex);
		double GetHeading(unsigned int _routeIndex, unsigned int _legIndex);
		double GetLength(int _routeIndex); 
		
		Route* SegRoute(int _routeIndex, int _cnt);  
		time_t GetTimeSpan(int _routeIndex); 
		int GetDangerWaypointIndex(unsigned int _routeIndex, time_t _t); 
		double GetBufferDistance(int _routeIndex); 
		void SetBufferDistance(int _routeIndex, double _distance);

		std::wstring CreateWaypointID();
		std::wstring CreateLegID();    
		int GetWaypointIndex(unsigned int _routeIndex, double _x, double _y);
	
		void AddRouteFromGML(std::wstring _filepath);
		void AddRouteFromGMLByPugi(std::wstring path);
		void GetRouteObject(MSXML2::IXMLDOMNodePtr nodePtr);
		void SetRelation();
		void SetSpatailData();
		void Save(CString _filePathName, unsigned _index = -1);

		bool GetPosSpeedAtTime(int _routeIndex, std::time_t _time, double& x, double& y, double& speed);


	};
}