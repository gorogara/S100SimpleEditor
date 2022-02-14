#include "stdafx.h"
#include "RoutePlanner.h"
#include "Route.h"
#include "Waypoint.h"
#include "Leg.h"
#include "VesselStaticInfo.h"
#include "VesselVoyageInfo.h"
#include "informationAssociation.h"
#include "featureAssociation.h"

#include "GeoMetryLibrary\\GeoPoint.h"
#include "GeoMetryLibrary\\GeoCommonFuc.h"
#include "GeoMetryLibrary\\ENCLine.h"
#include "LatLonUtility\\LatLonUtility.h"

#include <sstream>
#include <algorithm>
using namespace RT;

int RoutePlanner::idIndex = 1;

RT::PointD RT::SimpleRightBufPoint(double _x, double _y, double _heading, double _distance, bool _radian)
{
	if (_radian) {
		_heading += (M_PI / 2);
	}
	else {
		_heading += 90;
	}

	LatLonUtility::Pos pos = LatLonUtility::GetDestinationPointRhumbLineMercator(_y, _x, _heading, _distance, _radian);
	RT::PointD result;
	result.x = pos.lon;
	result.y = pos.lat;
	return result;
}


RT::PointD RT::SimpleLeftBufPoint(double _x, double _y, double _heading, double _distance, bool _radian)
{
	if (_radian) {
		_heading -= (M_PI / 2);
	}
	else {
		_heading -= 90;
	}

	LatLonUtility::Pos pos = LatLonUtility::GetDestinationPointRhumbLineMercator(_y, _x, _heading, _distance, _radian);
	RT::PointD result;
	result.x = pos.lon;
	result.y = pos.lat;
	return result;
}


double RT::GetAngleFromLegs(double _heading1, double _heading2, bool _radian)
{
	double PI = acos(-1.0);

	if (!_radian) {
		PI *= RAD2DEG;
	}

	if (_heading1 > PI) {
		_heading1 -= PI;
	}

	if (_heading2 > PI) {
		_heading2 -= PI;
	}
	 
	double result = PI - _heading1 + _heading2;   

	if (result > PI) {
		result = (2 * PI) - result;
	}

	return abs(result);
}


bool RT::IsRight(double _x1Leg1, double _y1Leg1, double _x2Leg1, double _y2Leg1,
	double _x1Leg2, double _y1Leg2, double _x2Leg2, double _y2Leg2)
{
	double x1 = _x2Leg1 - _x1Leg1;
	double y1 = _y2Leg1 - _y1Leg1;
	double x2 = _x2Leg2 - _x1Leg2;
	double y2 = _y2Leg2 - _y1Leg2;

	double det = (x1 * y2) - (y1 * x2);

	if (det < 0) {
		return true;
	}

	return false;
}

RoutePlanner::RoutePlanner()
{

}

RoutePlanner::~RoutePlanner()
{
	for (auto iter = route.begin(); iter != route.end(); iter++)
	{
		delete *iter;
	}
	route.clear();

}

void RoutePlanner::AddRouteFromGML(std::wstring _filepath)
{
	time_t departureTime;
	departureTime = time(NULL);

	auto seek = _filepath.find_last_of(L'\\');    
	MSXML2::IXMLDOMDocument2Ptr g_pXMLDoc; 
	MSXML2::IXMLDOMNodeListPtr pNodeList; 

	if (_filepath.size() > 0)
	{
		g_pXMLDoc.CreateInstance(__uuidof(DOMDocument));
		g_pXMLDoc->async = VARIANT_FALSE;
		
		g_pXMLDoc->validateOnParse = VARIANT_TRUE;
		g_pXMLDoc->resolveExternals = VARIANT_TRUE; 
		g_pXMLDoc->load((_variant_t)_filepath.c_str());  
		pNodeList = g_pXMLDoc->selectNodes(L"//RouteInformationBatch");
		{
			for (int i = 0; i < pNodeList->Getlength(); i++) {
				MSXML2::IXMLDOMNodePtr pNodePtr = pNodeList->Getitem(i);
				GetRouteObject(pNodePtr);
			}
		}
		pNodeList.Release();
	}  

} 
void RoutePlanner::AddRouteFromGMLByPugi(std::wstring path) 
{
	time_t departureTime;
	departureTime = time(NULL);

	auto seek = path.find_last_of(L'\\');

	pugi::xml_document xmldoc;
	auto result = xmldoc.load_file(path.c_str());
	
	xmldoc.first_child();

}


void RoutePlanner::SetRelation()
{
	for (auto itor = routes.begin(); itor != routes.end(); itor++)
	{
		Route *route = itor->second;
		for (auto itor2 = route->iaList.begin(); itor2 != route->iaList.end(); itor2++)
		{
			informationAssociation* fa = *itor2;
			if (fa->title.compare(L"RouteInfoToVesselStaticInfo") == 0)
			{
				auto itorWP = vesselStaticInfo.find(fa->href);
				route->vesselStaticInfo = itorWP->second;
			}
		}
	}

	for (auto itor = waypoints.begin(); itor != waypoints.end(); itor++)
	{
		Waypoint *wp = itor->second;
		for (auto itor2 = wp->iaList.begin(); itor2 != wp->iaList.end(); itor2++)
		{
			informationAssociation* ia = *itor2;
			if (ia->title.compare(L"WaypointToRouteInfo") == 0)
			{
				auto itorRoute = routes.find(ia->href);

				wp->m_asRoute = itorRoute->second;

				itorRoute->second->AddWaypoint(wp);

			}
		}
		for (auto itor2 = wp->faList.begin(); itor2 != wp->faList.end(); itor2++)
		{
			featureAssociation* fa = *itor2;
			if (fa->title.compare(L"WaypointToLeg") == 0)
			{
				auto itorLeg = legs.find(fa->href);

				wp->m_asLeg = itorLeg->second;
			}
			else if (fa->title.compare(L"NextWaypoint") == 0)
			{
				auto itorWP = waypoints.find(fa->href);

				wp->m_asWaypoint = itorWP->second;
			}
		}
	}

	for (auto itor = waypoints.begin(); itor != waypoints.end(); itor++)
	{
		Waypoint *wp = itor->second;

		if (wp->m_asLeg && wp->m_asRoute)
			wp->m_asRoute->AddLeg(wp->m_asLeg);
	}

	for (auto itor = legs.begin(); itor != legs.end(); itor++)
	{
		Leg *leg = itor->second;
		for (auto itor2 = leg->faList.begin(); itor2 != leg->faList.end(); itor2++)
		{
			featureAssociation* fa = *itor2;
			if (fa->title.compare(L"InverseLegToWaypoint") == 0)
			{
				auto itorWP = waypoints.find(fa->href);
				leg->m_asWaypoint = itorWP->second;
			}
		}
	}
	for (auto itor = vesselStaticInfo.begin(); itor != vesselStaticInfo.end(); itor++)
	{
		VesselStaticInfo *vsi = itor->second;
		for (auto itor2 = vsi->iaList.begin(); itor2 != vsi->iaList.end(); itor2++)
		{
			informationAssociation* fa = *itor2;
			if (fa->title.compare(L"VesselStaticInfoToVesselVoyageInfo") == 0)
			{
				auto itorWP = vesselVoyageInfo.find(fa->href);
				vsi->vesselVoyageInfo = itorWP->second;
			}
		}
	}
}

void RoutePlanner::SetSpatailData()
{
	for (auto itor = waypoints.begin(); itor != waypoints.end(); itor++)
	{
		Waypoint *wp = itor->second;

		if (wp->pos.size() > 0)
		{
			wp->p->m_numPoints = 1;
			if (!wp->p->m_pPoints)
				wp->p->m_pPoints = new GeoPoint();
			std::wstring str = wp->pos;
			wstringstream sstr(str);
			wstring item;

			int cnt = 0;
			while (getline(sstr, item, L' ')) {
				if (cnt == 0)
					wp->p->m_pPoints[0].x = _wtof(item.c_str());
				else
					wp->p->m_pPoints[0].y = _wtof(item.c_str());
				cnt++;
			}

			projection(wp->p->m_pPoints[0].x, wp->p->m_pPoints[0].y);
		}
	}

	for (auto itor = legs.begin(); itor != legs.end(); itor++)
	{
		Leg *leg = itor->second;

		if (leg->posList.size() > 0)
		{
			if (leg->line)
				delete leg->line;
			leg->line = new ENCLine();

			std::wstring str = leg->posList;
			wstringstream sstr(str);
			wstring item;

			int cnt = 0;
			while (getline(sstr, item, L' ')) {
				cnt++;
			}

			leg->line->NumPoints = cnt / 2;
			leg->line->NumParts = 1;
			leg->line->Points = new GeoPoint[leg->line->NumPoints];
			leg->line->CPoints = new CPoint[leg->line->NumPoints + 2];
			wstringstream sstr2(str);
			cnt = 0;
			while (getline(sstr2, item, L' ')) {
				if (cnt % 2 == 0)
					leg->line->Points[cnt / 2].x = _wtof(item.c_str());
				else
					leg->line->Points[cnt / 2].y = _wtof(item.c_str());
				cnt++;
			}

			for (int i = 0; i < leg->line->NumPoints; i++)
			{
				projection(leg->line->Points[i].x, leg->line->Points[i].y);
			}
		}
	}
}

#pragma warning(disable:4996)
void RoutePlanner::GetRouteObject(MSXML2::IXMLDOMNodePtr nodePtr)
{
	USES_CONVERSION;
	MSXML2::IXMLDOMNodeListPtr pNodeList = nodePtr->GetchildNodes();

	Route* newRoute = new Route();
	route.push_back(newRoute);

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr childNode = pNodeList->Getitem(i);
		if (childNode == NULL)
			continue;

		std::string str = std::string(W2A(childNode->baseName));

		if (str.compare("RouteInfo") == 0)
		{
			Route* tRoute = new Route();
			tRoute->GetContent(childNode);
			newRoute->SetName(tRoute->GetName());
			delete tRoute;
		}
		else if (str.compare("Waypoint") == 0)
		{
			Waypoint* waypoint = new Waypoint();
			waypoint->GetContent(childNode);
			std::wstring strLon = std::wcstok((wchar_t*)waypoint->pos.c_str(), L" ");
			std::wstring strLat = std::wcstok(nullptr, L" ");
			AddWaypoint(GetRouteCount() - 1, stod(strLon), stod(strLat), 10, 10);
			delete waypoint;
		}
	}
}
void RoutePlanner::AddRoute(std::wstring _name)
{
	Route* tRoute = new Route(_name);
	route.push_back(tRoute);
}


void RoutePlanner::AddRoute(std::wstring _name, std::time_t _time)
{
	Route* tRoute = new Route(_name, _time);
	route.push_back(tRoute);
}


bool RoutePlanner::SetRouteName(unsigned int _routeIndex, std::wstring _name)
{
	try {
		route.at(_routeIndex)->SetName(_name);
	}
	catch (std::out_of_range) {
		return false;
	}

	return true;
}


bool RoutePlanner::DeleteRoute(unsigned int _routeIndex)
{
	if (_routeIndex >= route.size())
	{
		return false;
	}

	delete *(route.begin() + _routeIndex);
	route.erase(route.begin() + _routeIndex);

	return true;
}

std::wstring RoutePlanner::CreateWaypointID()
{
	int index = 1;

	bool success = false;
	TCHAR buff[100] = { 0 };

	std::wstring id;
	while (!success)
	{
		wsprintf(buff, L"WAYPOINT-%04d", index++);
		id = buff;
		auto itor = waypoints.find(id);

		success = itor == waypoints.end() ? true : false;
	}

	return id;
}

std::wstring RoutePlanner::CreateLegID()
{
	int index = 1;

	bool success = false;
	TCHAR buff[100] = { 0 };

	std::wstring id;
	while (!success)
	{
		wsprintf(buff, L"LEG-%04d", index++);
		id = buff;
		auto itor = legs.find(id);

		success = itor == legs.end() ? true : false;
	}

	return id;
}                              

Leg* RoutePlanner::AddLeg(Waypoint* wp1, Waypoint* wp2, double _minSpeed, double _maxSpeed)
{
	Leg* tLeg = new Leg();
	tLeg->id = CreateLegID();
	tLeg->line = new ENCLine();

	tLeg->line->NumPoints = 2;
	tLeg->line->NumParts = 1;
	tLeg->line->Points = new GeoPoint[tLeg->line->NumPoints];
	tLeg->line->CPoints = new CPoint[tLeg->line->NumPoints + 2];

	tLeg->line->Points[0].x = wp1->GetX();
	tLeg->line->Points[0].y = wp1->GetY();
	tLeg->line->Points[1].x = wp2->GetX();
	tLeg->line->Points[1].y = wp2->GetY();
	tLeg->SetSpeed(_minSpeed, _maxSpeed);
	
	legs.insert(std::unordered_map<std::wstring, Leg*>::value_type(tLeg->id, tLeg));

	wp1->m_asLeg = tLeg;

	tLeg->m_asWaypoint = wp1;

	return tLeg;
}
Waypoint* RoutePlanner::AddWaypoint(unsigned int _routeIndex, double _x, double _y, double _minSpeed, double _maxSpeed)
{
	if (_routeIndex >= route.size())
	{
		return nullptr;
	}
	double px = _x, py = _y;

	projection(px, py);

	Leg* leg = nullptr;
	Waypoint* tWaypoint = new Waypoint(px, py);
	tWaypoint->SetSpeed(_minSpeed);
	tWaypoint->id = CreateWaypointID();

	if (route.at(_routeIndex)->GetWaypointCount() > 0)
	{
		Waypoint* lwp = route[_routeIndex]->GetLastWaypoint();
		leg = AddLeg(lwp, tWaypoint, _minSpeed, _maxSpeed);
		route[_routeIndex]->legs.push_back(leg);
		lwp->m_asWaypoint = tWaypoint;
	}
	else
	{
		route[_routeIndex]->speedStart = _minSpeed;
	}

	tWaypoint->m_asRoute = route[_routeIndex];

	waypoints.insert(std::unordered_map<std::wstring, Waypoint*>::value_type(tWaypoint->id, tWaypoint));
	route[_routeIndex]->waypoints.push_back(tWaypoint);

	return tWaypoint;
}

Waypoint* RoutePlanner::AddWaypoint(unsigned int _routeIndex, unsigned int _afterIndex, double _x, double _y, double _minSpeed, double _maxSpeed)
{
	if ((_afterIndex < 0) || (_afterIndex >= route.at(_routeIndex)->GetWaypointCount())) {
		return nullptr;
	}

	std::vector<Waypoint*> wpBackup;
	int wpCnt = GetWaypointCount(_routeIndex);
	Waypoint* tmpWP;
	for (int i = 0; i < wpCnt; i++) {
		tmpWP = new Waypoint(0, 0);
		tmpWP->SetSpeed(GetSpeed(_routeIndex, i));
		tmpWP->SetXY(GetX(_routeIndex, i), GetY(_routeIndex, i));
		wpBackup.push_back(tmpWP);
	}

	for (unsigned i = 0; i < wpBackup.size(); i++) {
		DeleteWaypoint(_routeIndex, 0);
	}

	double mx = _x;
	double my = _y;
	LatLonUtility::ProjectionFromDegree(mx, my);
	Waypoint* wp = new Waypoint(0, 0);
	wp->SetSpeed(_minSpeed);
	wp->SetXY(mx, my);
	wpBackup.insert(wpBackup.begin() + _afterIndex + 1, wp);

	for (unsigned i = 0; i < wpBackup.size(); i++) {
		double mx = wpBackup.at(i)->GetX();
		double my = wpBackup.at(i)->GetY();
		double speed = wpBackup.at(i)->GetSpeed();
		LatLonUtility::InverseProjectionToDegree(mx, my);
		AddWaypoint(_routeIndex, mx, my, speed, speed);
	}

	for (unsigned i = 0; i < wpBackup.size(); i++) {
		delete wpBackup.at(i);
	}

	wpBackup.clear();

	return GetWaypoint(_routeIndex, _afterIndex + 1);
}


Waypoint* RoutePlanner::SetWaypoint(unsigned int _routeIndex, unsigned int _waypointIndex, double _x, double _y)
{
	if (_routeIndex >= route.size())
	{
		return false;
	}

	return route[_routeIndex]->SetWaypoint(_waypointIndex, _x, _y);
}


Waypoint* RoutePlanner::SetWaypoint(unsigned int _routeIndex, unsigned int _waypointIndex, double _x, double _y, double _minSpeed, double _maxSpeed)
{
	if (_routeIndex >= route.size())
	{
		return false;
	}

	route[_routeIndex]->SetSpeed(_waypointIndex, _minSpeed);
	return route[_routeIndex]->SetWaypoint(_waypointIndex, _x, _y, _minSpeed, _maxSpeed);
}


bool RoutePlanner::SetDepartureTime(unsigned int _routeIndex, std::time_t& _time)
{
	if (_routeIndex >= route.size())
	{
		return false;
	}

	route[_routeIndex]->SetDepartureTime(_time);

	return true;
}


bool RoutePlanner::DeleteWaypoint(unsigned int _routeIndex, unsigned int _waypointIndex)
{
	if (_routeIndex >= route.size())
	{
		return false;
	}

	return route[_routeIndex]->DeleteWaypoint(_waypointIndex);
}


bool RoutePlanner::DeleteWaypoint(unsigned int _routeIndex, double _x, double _y)
{
	if (_routeIndex >= route.size())
	{
		return false;
	}
	Waypoint* wp = route[_routeIndex]->DeleteWaypoint(_x, _y);

	for (auto itor = waypoints.begin(); itor != waypoints.end(); itor++)
	{
		if (itor->second == wp)
		{
			delete wp;
			waypoints.erase(itor);
		}
	}
	if (wp)
		return true;
	else
		return false;
}


unsigned int RoutePlanner::GetRouteCount()
{
	return route.size();
}


std::wstring RoutePlanner::GetRouteName(unsigned int _routeIndex)
{
	std::wstring ret = L"";

	try {
		ret = route.at(_routeIndex)->GetName();
	}
	catch (std::out_of_range) {
		return ret;
	}

	return ret;
}


unsigned int RoutePlanner::GetWaypointCount(unsigned int _routeIndex)
{
	if (_routeIndex >= route.size())
	{
		return -1;
	}

	return route[_routeIndex]->GetWaypointCount();
}


Waypoint* RoutePlanner::GetWaypoint(unsigned int _routeIndex, unsigned waypointNumber)
{
	if (_routeIndex >= route.size())
	{
		return NULL;
	}

	return route[_routeIndex]->GetWaypoint(waypointNumber);
}         


double RoutePlanner::GetStartX(unsigned int _routeIndex, unsigned int _legIndex)
{
	if (_routeIndex >= route.size())
	{
		return 0;
	}

	return route[_routeIndex]->GetX(_legIndex);
}


double RoutePlanner::GetStartY(unsigned int _routeIndex, unsigned int _legIndex)
{
	if (_routeIndex >= route.size())
	{
		return 0;
	}

	return route[_routeIndex]->GetY(_legIndex);
}


double RoutePlanner::GetEndX(unsigned int _routeIndex, unsigned int _legIndex)
{
	if (_routeIndex >= route.size())
	{
		return 0;
	}

	return route[_routeIndex]->GetX(_legIndex + 1);
}


double RoutePlanner::GetEndY(unsigned int _routeIndex, unsigned int _legIndex)
{
	if (_routeIndex >= route.size())
	{
		return 0;
	}

	return route[_routeIndex]->GetY(_legIndex + 1);
}


double RoutePlanner::GetX(unsigned int _routeIndex, unsigned int _waypointIndex)
{
	return route[_routeIndex]->GetX(_waypointIndex);
}


double RoutePlanner::GetY(unsigned int _routeIndex, unsigned int _waypointIndex)
{
	return route[_routeIndex]->GetY(_waypointIndex);
}


int RoutePlanner::GetWaypointIndex(unsigned int _routeIndex, double _x, double _y)
{
	if (_routeIndex >= route.size())
	{
		return -1;
	}

	return route[_routeIndex]->GetWaypointIndex(_x, _y);
}


void RoutePlanner::GetSpeed(unsigned int _routeIndex, unsigned int _legIndex, double& _minSpeed, double& _maxSpeed)
{
	if (_routeIndex >= route.size() ||
		route[_routeIndex]->legs.size() <= _legIndex
	)
	{
		_minSpeed = -1;
		_maxSpeed = -1;
		return;
	}
	route[_routeIndex]->GetSpeed(_legIndex, _minSpeed, _maxSpeed);
}


double RoutePlanner::GetSpeed(unsigned int _routeIndex, unsigned int _wpIndex)
{
	double ret = 0;

	try {
		ret = route.at(_routeIndex)->GetSpeed(_wpIndex);
	}
	catch (std::out_of_range) {
		OutputDebugString(_T("Exception : RoutePlanner::GetSpeed()\n"));
	}

	return ret;
}


bool RoutePlanner::GetDepartureTime(unsigned int _routeIndex, std::time_t* _time)
{
	if (_routeIndex >= route.size())
	{
		return false;
	}

	*_time = route[_routeIndex]->GetDepartureTime();

	return true;
}


double RoutePlanner::GetDistance(unsigned int _routeIndex, unsigned int _legIndex)
{
	if (_routeIndex >= route.size())
	{
		return 0;
	}

	return route[_routeIndex]->GetDistanceLeg(_legIndex);
}


double RoutePlanner::GetDistanceAccumulated(unsigned int _routeIndex, unsigned int _legIndex)
{
	if (_routeIndex >= route.size())
	{
		return 0;
	}

	return route[_routeIndex]->GetDistanceAccumulated(_legIndex);
}


time_t RoutePlanner::GetArrivalTime(unsigned int _routeIndex, unsigned int _wpIndex)
{
	time_t returnTime = 0;

	if (_routeIndex >= route.size())
	{
		return returnTime;
	}

	return route[_routeIndex]->GetArrivalTime(_wpIndex);
}


double RoutePlanner::GetHeading(unsigned int _routeIndex, unsigned int _legIndex)
{
	if (_routeIndex >= route.size())
	{
		return -1000;
	}

	return route[_routeIndex]->GetHeading(_legIndex);
}


int RoutePlanner::GetDangerWaypointIndex(unsigned int _routeIndex, time_t _t)
{
	try {
		if (_t == route.at(_routeIndex)->GetArrivalTime(0)) return 0;

		for (unsigned i = 0; i < route.at(_routeIndex)->GetWaypointCount(); i++) {
			time_t arrivalTime = route.at(_routeIndex)->GetArrivalTime(i);

			if (arrivalTime > _t) {
				return i;
			}
		}
	}
	catch (std::out_of_range) {
		return -1;
	}

	return 0;
}


Route* RoutePlanner::GetRoute(unsigned int _routeIndex)
{
	try {
		return route.at(_routeIndex);
	}
	catch (std::out_of_range) {
		return nullptr;
	}
}
void RoutePlanner::Save(CString _filePathName, unsigned _index)
{
	RoutePlanner::idIndex = 1;
	if (_index == -1)
	{

	}
	else
	{
		MSXML2::IXMLDOMDocument2Ptr				pDoc;
		pDoc.CreateInstance(__uuidof(DOMDocument));
		
		MSXML2::IXMLDOMProcessingInstructionPtr pPI;
		pPI = pDoc->createProcessingInstruction(L"xml", L"version=\"1.0\" encoding=\"UTF-8\"");
		pDoc->appendChild(pPI);

		MSXML2::IXMLDOMElementPtr pRootElement = pDoc->createElement(L"RouteInformationBatch"); 
		pRootElement->setAttribute(L"xmlns", L"http://www.kriso.re.kr/RouteInformationSchema");
		pRootElement->setAttribute(L"xmlns:S100", L"http://www.iho.int/s100gml/1.0");
		pRootElement->setAttribute(L"xmlns:gml", L"http://www.opengis.net/gml/3.2");
		pRootElement->setAttribute(L"xmlns:xlink", L"http://www.w3.org/1999/xlink");
		pRootElement->setAttribute(L"xmlns:xsi", L"http://www.w3.org/2001/XMLSchema-instance");
		pRootElement->setAttribute(L"xsi:schemaLocation", L"http://www.kriso.re.kr/RouteInformationSchema Route_Information_GML_Schema.xsd");
		
		pDoc->appendChild(pRootElement);

		Route *route = GetRoute(_index);

		for (auto itor = route->legs.begin(); itor != route->legs.end(); itor++) {
			Leg* leg = *itor;
			leg->Save(pDoc, pRootElement);
		}

		for (auto itor = route->waypoints.begin(); itor != route->waypoints.end(); itor++) {
			Waypoint* wp = *itor;
			wp->Save(pDoc, pRootElement);
		}                 

		route->Save(pDoc, pRootElement);

		if (route->vesselStaticInfo) {
			route->vesselStaticInfo->Save(pDoc, pRootElement);
			route->vesselStaticInfo->vesselVoyageInfo->Save(pDoc, pRootElement);
		}

		pDoc->save((_variant_t)(_filePathName + _T(".gml")));
	}
}


double RoutePlanner::GetBufferDistance(int _routeIndex)
{
	try {
		return route.at(_routeIndex)->GetBufferDistance();
	} 
	catch (std::out_of_range) {
		OutputDebugString(_T("Error : RoutePlanner::GetBufferDistance()\n"));
	}

	return 0;
}


void RoutePlanner::SetBufferDistance(int _routeIndex, double _distance)
{
	try {
		route.at(_routeIndex)->SetBufferDistance(_distance);
	}
	catch (std::out_of_range) {
		OutputDebugString(_T("Error : RoutePlanner::SetBufferDistance()\n"));
	}
}


double RoutePlanner::GetLength(int _index) 
{
	try {
		return route.at(_index)->GetLength();
	}
	catch (std::out_of_range) {
		return 0;
	}
}


time_t RoutePlanner::GetTimeSpan(int _index)
{
	try {
		return route.at(_index)->GetTimeSpan();
	}	
	catch (std::out_of_range) {
		return 0;
	}
}


bool RoutePlanner::GetPosSpeedAtTime(int _routeIndex, std::time_t _time, double& x, double& y, double& speed)
{
	try {
		return route.at(_routeIndex)->GetPosSpeedAtTime(_time, x, y, speed);
	}
	catch (std::out_of_range) {
		return false;
	}
}


Route* RoutePlanner::SegRoute(int _routeIndex, int _cnt)
{
	try {
		if (route.at(_routeIndex)->GetWaypointCount() <= 1) {
			return nullptr;
		}

		AddRoute(route.at(_routeIndex)->GetName(), route.at(_routeIndex)->GetDepartureTime());

		int rIndex = GetRouteCount() - 1;
		time_t departTime = 0;
		GetDepartureTime(_routeIndex, &departTime);
		time_t arrivalTime = GetArrivalTime(_routeIndex, GetWaypointCount(_routeIndex) - 1);
		time_t timeSpan = arrivalTime - departTime;
		time_t segTime = timeSpan / (_cnt - GetWaypointCount(_routeIndex) + 1 + 1);

		if (timeSpan <= 0) {
			return nullptr;
		}

		if (segTime <= 0) {
			return nullptr;
		}

		struct data {
			time_t x;
			double lon;
			double lat;
			double speed;

			bool operator < (const data& _val) const {
				return x < _val.x;
			}
		};

		data tmpData;

		std::vector<data> routeData;      

		for (unsigned i = 1; i <= (_cnt - GetWaypointCount(_routeIndex) + 1); i++) {
			tmpData.x = departTime + (segTime * i);
			route.at(_routeIndex)->GetPosSpeedAtTime(tmpData.x, tmpData.lon, tmpData.lat, tmpData.speed);
			LatLonUtility::InverseProjectionToDegree(tmpData.lon, tmpData.lat);
			routeData.push_back(tmpData);
		}     

		for (unsigned i = 0; i < GetWaypointCount(_routeIndex); i++) {
			tmpData.lon = GetX(_routeIndex, i);
			tmpData.lat = GetY(_routeIndex, i);
			tmpData.speed = GetSpeed(_routeIndex, i);
			tmpData.x = GetArrivalTime(_routeIndex, i);
			LatLonUtility::InverseProjectionToDegree(tmpData.lon, tmpData.lat);
			routeData.push_back(tmpData);
		}

		sort(routeData.begin(), routeData.end());

		for (unsigned i = 0; i < routeData.size(); i++) {
			AddWaypoint(rIndex, routeData.at(i).lon, routeData.at(i).lat, routeData.at(i).speed, routeData.at(i).speed);
		}

		Route* ret = GetRoute(rIndex);
		route.pop_back();
		return ret;
	}
	catch (std::out_of_range) {
		return nullptr;
	}
}