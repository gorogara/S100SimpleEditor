#include "stdafx.h"
#include "Route.h"
#include "Leg.h"
#include "Waypoint.h" 
#include "VesselStaticInfo.h"
#include "informationAssociation.h"

#include "LatLonUtility\\LatLonUtility.h"
#include "GeoMetryLibrary\\ENCLine.h"
#include "GeoMetryLibrary\\GeoPoint.h"

#include <cwchar>

using namespace RT;
using namespace LatLonUtility;

Route::Route()
{
	vesselStaticInfo = NULL;
	struct tm t;
	curtime = time(NULL);
	localtime_s(&t, &curtime);
	speedStart = 0;
	bufferDistance = 0.2;
}

Route::Route(std::wstring _name)
{
	vesselStaticInfo = NULL;
	struct tm t;
	curtime = time(NULL);
	localtime_s(&t, &curtime);
	name = _name;
	speedStart = 0;
	bufferDistance = 0.2;
}

Route::Route(std::wstring _name, std::time_t _time)
{
	vesselStaticInfo = NULL;
	name = _name;
	curtime = _time;
	speedStart = 0;
	bufferDistance = 0.2;
}

Route::~Route()
{
	for (auto i = waypoints.begin(); i != waypoints.end(); i++) {
		delete *i;
	}

	for (auto i = legs.begin(); i != legs.end(); i++) {
		delete *i;
	}

	for (auto i = iaList.begin(); i != iaList.end(); i++) {
		delete *i;
	}

	delete vesselStaticInfo;
}

bool Route::GetPosSpeedAtTime(std::time_t _time, double& _x, double& _y, double& _speed)
{
	bool res = false;

	for (unsigned int i = 1; i < GetWaypointCount(); i++)
	{
		if (GetArrivalTime(i) == _time)
		{
			_x = waypoints.at(i)->GetX();
			_y = waypoints.at(i)->GetY(); 

			if (waypoints.at(i)->m_asLeg) {
				_speed = waypoints.at(i)->m_asLeg->v_speedMin;
			}

			return true;
		}
		else if (_time > GetArrivalTime(i))
		{
			continue;
		}
		else
		{
			double x1 = waypoints.at(i - 1)->GetX();
			double y1 = waypoints.at(i - 1)->GetY();
			double x2 = waypoints.at(i)->GetX();
			double y2 = waypoints.at(i)->GetY();

			InverseProjectionToRadian(x1, y1);
			InverseProjectionToRadian(x2, y2);

			double brng = GetBearingRhubmLineMercator(
				y1,
				x1,
				y2,
				x2,
				true); 
			double speed = waypoints.at(i - 1)->m_asLeg->v_speedMin * KN2MS; 
			double dist = speed * (_time - GetArrivalTime(i - 1)) * M2KM;

			Pos p = GetDestinationPointRhumbLineMercator(
				y1,
				x1,
				brng,
				dist,
				true);
			_x = p.lon;
			_y = p.lat;

			ProjectionFromRadian(_x, _y);

			_speed = waypoints.at(i - 1)->m_asLeg->v_speedMin;

			return true;
		}
	}

	return res;
}


int Route::GetLegIndexAtTime(std::time_t _time)
{
	int res = 0;

	for (unsigned int i = 1; i < GetWaypointCount(); i++)
	{
		if (_time > GetArrivalTime(i))
		{
			continue;
		}
		else
		{
			res = i - 1;
			break;
		}
	}

	return res;
}


void Route::SetName(std::wstring _name)
{
	name = _name;
}

std::wstring Route::GetName()
{
	return name;
}


void Route::GetContent(MSXML2::IXMLDOMNodePtr nodePtr)
{
	USES_CONVERSION;

	MSXML2::IXMLDOMNamedNodeMapPtr pAttr = nodePtr->Getattributes();
	MSXML2::IXMLDOMNodePtr pAttrNP;
	pAttrNP = pAttr->getNamedItem(L"gml:id");
	VARIANT value;
	if (pAttrNP)
	{
		pAttrNP->get_nodeValue(&value);
		id = std::wstring(value.bstrVal);
	}

	MSXML2::IXMLDOMNodeListPtr pNodeList = nodePtr->GetchildNodes();

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr childNode = pNodeList->Getitem(i);
		if (childNode == NULL)
			continue;

		std::string baseName = std::string(W2A(childNode->baseName));

		std::wstring value;

		if (baseName.compare("informationAssociation") == 0)
		{
			RT::informationAssociation* ia = new RT::informationAssociation();
			ia->GetContent(childNode);

			iaList.push_back(ia);
		}
		else if (baseName.compare("routeName") == 0)
		{
			name = childNode->Gettext();
		}
		else if (baseName.compare("sourceIndication") == 0)
		{
			sourceIndication = childNode->Gettext();
		}
		else if (baseName.compare("routeStatus") == 0)
		{
			routeStatus = childNode->Gettext();
		}
		else if (baseName.compare("optimizationMethod") == 0)
		{
			optimizationMethod = childNode->Gettext();
		}
		else if (baseName.compare("historyOfRouteChanges") == 0)
		{
			historyOfRouteChanges = childNode->Gettext();
		}
	}
}

void Route::AddLeg(Leg *leg)
{
	legs.push_back(leg);
}
void Route::AddWaypoint(Waypoint *wp)
{
	waypoints.push_back(wp);
}                                                                   



Waypoint* Route::SetWaypoint(unsigned int _index, double _x, double _y, double _minSpeed, double _maxSpeed)
{ 
	if ((_index >= GetWaypointCount()) || (_index < 0))
	{
		return nullptr;
	}
	
	waypoints[_index]->SetXY(_x, _y);

	Waypoint* preWP = GetPreWaypoint(waypoints[_index]);

	if (preWP == nullptr)
	{
		waypoints[_index]->m_asLeg->line->Points[0].x = _x;
		waypoints[_index]->m_asLeg->line->Points[0].y = _y;
		waypoints[_index]->m_asLeg->SetSpeed(_minSpeed, _maxSpeed);
	}
	else if (waypoints[_index]->m_asLeg == nullptr)
	{
		preWP->m_asLeg->line->Points[1].x = _x;
		preWP->m_asLeg->line->Points[1].y = _y;
		preWP->m_asLeg->SetSpeed(_minSpeed, _maxSpeed);
	}
	else
	{
		preWP->m_asLeg->line->Points[1].x = _x;
		preWP->m_asLeg->line->Points[1].y = _y;

		waypoints[_index]->m_asLeg->line->Points[0].x = _x;
		waypoints[_index]->m_asLeg->line->Points[0].y = _y;
		waypoints[_index]->m_asLeg->SetSpeed(_minSpeed, _maxSpeed);
	}

	return waypoints[_index];
}


bool Route::DeleteWaypoint(unsigned int _index)
{
	if (_index >= GetWaypointCount())
	{
		return false;
	}
	Waypoint *wp = waypoints[_index];

	Waypoint* preWP = GetPreWaypoint(wp); 
	if (preWP == NULL)
	{
		for (auto it = legs.begin(); it != legs.end(); it++)
		{
			if (*it == wp->m_asLeg)
			{
				delete *it;
				legs.erase(it);
				break;
			}
		}
		delete wp;
		waypoints.erase(waypoints.begin() + _index);
	}
	else
	{ 
		if (wp->m_asLeg)
		{
			preWP->m_asLeg->line->Points[1].x = wp->m_asLeg->line->Points[1].x;
			preWP->m_asLeg->line->Points[1].y = wp->m_asLeg->line->Points[1].y;
			preWP->m_asWaypoint = waypoints.at(_index + 1);
			for (auto it = legs.begin(); it != legs.end(); it++)
			{
				if (*it == wp->m_asLeg)
				{
					delete *it;
					legs.erase(it);
					break;
				}
			}
		} 
		else
		{
			for (auto it = legs.begin(); it != legs.end(); it++)
			{ 
				if (*it == preWP->m_asLeg)
				{
					delete *it;
					legs.erase(it);
					preWP->m_asLeg = nullptr;
					preWP->m_asWaypoint = nullptr;
					break;
				}
			}
		}
		
		delete wp;
		waypoints.erase(waypoints.begin() + _index);
	}

	return true;
}


Waypoint* Route::DeleteWaypoint(double _x, double _y)
{
	Waypoint* retWP = NULL;
	if (waypoints.size() <= 0)
	{
		return NULL;
	}

	double distance = GetDistanceLatitudeLongitude(_y, _x, waypoints[0]->GetY(), waypoints[0]->GetX());

	std::vector<Waypoint*>::iterator iter;
	std::vector<Waypoint*>::iterator resultIndex = waypoints.begin();

	for (iter = (waypoints.begin() + 1); iter != waypoints.end(); iter++)
	{
		double currentDistance = GetDistanceLatitudeLongitude(_y, _x, (*iter)->GetY(), (*iter)->GetX());

		if (distance > currentDistance)
		{
			distance = currentDistance;
			resultIndex = iter;
		}
	}

	retWP = *resultIndex;

	waypoints.erase(resultIndex);

	return retWP;
}


unsigned int Route::GetWaypointCount()
{
	return waypoints.size();
}


unsigned int Route::GetLegCount()
{
	return legs.size();
}                           

double Route::GetDistanceLatitudeLongitude(double latitude1, double longitude1, double latitude2, double longitude2)
{ 
	double x1, y1, z1;
	double x2, y2, z2;

	double pi = acos(-1.0);

	latitude1 *= (pi / 180.0);
	longitude1 *= (pi / 180.0);
	latitude2 *= (pi / 180.0);
	longitude2 *= (pi / 180.0);

	x1 = cos(latitude1) * cos(longitude1);
	y1 = cos(latitude1) * sin(longitude1);
	z1 = sin(latitude1);

	x2 = cos(latitude2) * cos(longitude2);
	y2 = cos(latitude2) * sin(longitude2);
	z2 = sin(latitude2); 
	double theta = acos((x1 * x2) + (y1 * y2) + (z1 * z2)); 
	double distance = theta * RADIAN;

	return distance;
}


double Route::GetDistanceLeg(unsigned int _legIndex)
{
	if (legs.size() <= _legIndex)
		return 0;
	return legs[_legIndex]->GetDistance();
}


double Route::GetX(unsigned int _index)
{
	try {
		return waypoints.at(_index)->GetX();
	}
	catch (std::out_of_range) {
		return 0;
	}
}

double Route::GetY(unsigned int _index)
{
	try {
		return waypoints.at(_index)->GetY();
	}
	catch (std::out_of_range) {
		return 0;
	}
}

int Route::GetWaypointIndex(double _x, double _y)
{
	if (waypoints.size() <= 0)
	{
		return -1;
	}

	double distance = GetDistanceLatitudeLongitude(_y, _x, waypoints[0]->GetY(), waypoints[0]->GetX());

	int resultIndex = 0;

	for (unsigned i = 1; i < waypoints.size(); i++)
	{
		double currentDistance = GetDistanceLatitudeLongitude(_y, _x, waypoints[i]->GetY(), waypoints[i]->GetX());

		if (distance > currentDistance)
		{
			distance = currentDistance;
			resultIndex = i;
		}
	}

	return resultIndex;
}


void Route::SetSpeed(int _legIndex, double _minSpeed, double _maxSpeed)
{
	try {
		legs[_legIndex]->SetSpeed(_minSpeed, _maxSpeed);
	}
	catch (std::out_of_range) {

	}
}

void Route::GetSpeed(int _legIndex, double &_minSpeed, double &_maxSpeed)
{
	try {
		legs.at(_legIndex)->GetSpeed(_minSpeed, _maxSpeed);
	}
	catch (std::out_of_range) {
		_minSpeed = speedStart;
		return;
	}
}

std::time_t Route::GetDepartureTime()
{
	return curtime;
}

void Route::SetDepartureTime(time_t& _time)
{
	curtime = _time;
}

double Route::GetDistanceAccumulated(unsigned int _legIndex)
{
	if (_legIndex >= (signed)legs.size())
	{
		return 0;
	}

	double sum = 0;

	for (auto i = legs.begin(); i != (legs.begin() + (_legIndex + 1)); i++)
	{
		sum += (*i)->GetDistance();
	}

	return sum;
}

time_t Route::GetArrivalTime(unsigned int _wpIndex)
{
	if (_wpIndex == 0 || waypoints.size() <= _wpIndex )
		return curtime;

	time_t result = curtime;

	for (auto i = legs.begin(); i != (legs.begin() + _wpIndex); i++)
	{
		result += (time_t)(*i)->GetTimeRequired();
	}

	return result;
}

double Route::GetHeading(unsigned int _legIndex)
{
	try {
		return legs.at(_legIndex)->GetHeading();
	}
	catch (std::out_of_range) {
		return 0;
	}
}

Waypoint* Route::GetWaypoint(unsigned _index)
{
	if (waypoints.size() <= _index)
		return NULL;
	
	return waypoints[_index];
}

Waypoint* Route::GetPreWaypoint(Waypoint* curWP)
{
	for (auto itor = waypoints.begin(); itor != waypoints.end(); itor++)
	{
		Waypoint* wp = *itor;

		if (wp->m_asWaypoint == curWP)
		{
			return wp;
		}
	}
	return NULL;
}

Waypoint* Route::GetLastWaypoint()
{
	for (auto itor = waypoints.begin(); itor != waypoints.end(); itor++)
	{
		Waypoint* wp = *itor;

		if (wp->m_asWaypoint == NULL)
		{
			return wp;
		}
	}
	return NULL;
}


void Route::Save(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr)
{
	TCHAR buff[100] = { 0 };
	std::wstring str;
	MSXML2::IXMLDOMTextPtr pText;
	MSXML2::IXMLDOMElementPtr pParentElement = NULL, pElement = NULL;

	pParentElement = pDoc->createElement(L"RouteInfo");
	pParentElement->setAttribute((_bstr_t)L"gml:id", id.c_str());
	ptr->appendChild(pParentElement);

	
	pElement = pDoc->createElement(L"routeName");
	pText = pDoc->createTextNode((_bstr_t)name.c_str());
	pElement->appendChild(pText);
	pParentElement->appendChild(pElement);


	if (vesselStaticInfo)
	{
		pElement = pDoc->createElement(L"S100:informationAssociation");
		wsprintf(buff, L"ia-%04d", RoutePlanner::idIndex++);
		str = buff;
		pElement->setAttribute((_bstr_t)L"gml:id", str.c_str());
		pElement->setAttribute((_bstr_t)L"xlink:arcrole", L"http://www.kriso.re.kr/RouteInformationSchema");
		pElement->setAttribute((_bstr_t)L"xlink:title", L"RouteInfoToVesselStaticInfo");
		str = L"#";
		str.append(vesselStaticInfo->id.c_str());
		pElement->setAttribute((_bstr_t)L"xlink:href", str.c_str());

		pParentElement->appendChild(pElement);
	}

	pElement = pDoc->createElement(L"sourceIndication");
	pText = pDoc->createTextNode((_bstr_t)sourceIndication.c_str());
	pElement->appendChild(pText);
	pParentElement->appendChild(pElement);

	pElement = pDoc->createElement(L"routeStatus");
	pText = pDoc->createTextNode((_bstr_t)routeStatus.c_str());
	pElement->appendChild(pText);
	pParentElement->appendChild(pElement);

	pElement = pDoc->createElement(L"optimizationMethod");
	pText = pDoc->createTextNode((_bstr_t)optimizationMethod.c_str());
	pElement->appendChild(pText);
	pParentElement->appendChild(pElement);

	pElement = pDoc->createElement(L"historyOfRouteChanges");
	pText = pDoc->createTextNode((_bstr_t)historyOfRouteChanges.c_str());
	pElement->appendChild(pText);
	pParentElement->appendChild(pElement);       
}


void Route::SetSpeed(int _wpIndex, double _speed)
{
	try {
		waypoints.at(_wpIndex)->SetSpeed(_speed);
	}
	catch (std::out_of_range) {
		OutputDebugString(_T("Exception : Route::SetSpeed()\n"));
	}
}


double Route::GetSpeed(int _wpIndex)
{
	double ret = 0;

	try {
		ret = waypoints.at(_wpIndex)->GetSpeed();
	}
	catch (std::out_of_range) {
		OutputDebugString(_T("Exception : Route::GetSpeed()\n"));
	}

	return ret;
}


double Route::GetBufferDistance()
{
	return bufferDistance;
}


void Route::SetBufferDistance(double _distance)
{
	bufferDistance = _distance;
}


void Route::MakeBuf()
{
	int wpCnt = GetWaypointCount();

	if (wpCnt < 1) {
		return;
	} 
	PointD* ptWp = new PointD[wpCnt];
	for (int i = 0; i < wpCnt; i++) {
		ptWp[i].x = GetX(i);
		ptWp[i].y = GetY(i);
		LatLonUtility::InverseProjectionToDegree(ptWp[i].x, ptWp[i].y);
	}

	int legCnt = GetLegCount();

	for (int i = 0; i < legCnt; i++) {
		if ((i == 0) && (i == (legCnt - 1))) {  
			PointD ptTMP = SimpleLeftBufPoint(ptWp[i].x, ptWp[i].y, 
				GetHeading(i), bufferDistance, false);
			LatLonUtility::ProjectionFromDegree(ptTMP.x, ptTMP.y);
			legs.at(i)->leftBufStartPoint = ptTMP; 
			ptTMP = SimpleRightBufPoint(ptWp[i].x, ptWp[i].y,
				GetHeading(i), bufferDistance, false);
			LatLonUtility::ProjectionFromDegree(ptTMP.x, ptTMP.y);
			legs.at(i)->rightBufStartPoint = ptTMP;  
			ptTMP = SimpleLeftBufPoint(ptWp[i + 1].x, ptWp[i + 1].y,
				GetHeading(i), bufferDistance, false);
			LatLonUtility::ProjectionFromDegree(ptTMP.x, ptTMP.y);
			legs.at(i)->leftBufEndPoint = ptTMP; 
			ptTMP = SimpleRightBufPoint(ptWp[i + 1].x, ptWp[i + 1].y,
				GetHeading(i), bufferDistance, false);
			LatLonUtility::ProjectionFromDegree(ptTMP.x, ptTMP.y);
			legs.at(i)->rightBufEndPointX = ptTMP;
		}
		else if (i == 0) {  
			PointD ptTMP = SimpleLeftBufPoint(ptWp[i].x, ptWp[i].y,
				GetHeading(i), bufferDistance, false);
			LatLonUtility::ProjectionFromDegree(ptTMP.x, ptTMP.y);
			legs.at(i)->leftBufStartPoint = ptTMP; 
			ptTMP = SimpleRightBufPoint(ptWp[i].x, ptWp[i].y,
				GetHeading(i), bufferDistance, false);
			LatLonUtility::ProjectionFromDegree(ptTMP.x, ptTMP.y);
			legs.at(i)->rightBufStartPoint = ptTMP; 
			double currentHeading = GetHeading(i);
			double nextHeading = GetHeading(i + 1);

			double theta = GetAngleFromLegs(currentHeading, nextHeading, false) * DEG2RAD;

			double offset = 0;

			if (theta != M_PI) {
				offset = bufferDistance / tan(theta / 2.0);
			}

			LatLonUtility::Pos pos = GetDestinationPointRhumbLineMercator(
				ptWp[i + 1].y, ptWp[i + 1].x, GetHeading(i) + 180, offset, false); 
			ptTMP = SimpleLeftBufPoint(pos.lon, pos.lat, GetHeading(i), bufferDistance, false);
			LatLonUtility::ProjectionFromDegree(ptTMP.x, ptTMP.y);
			legs.at(i)->leftBufEndPoint = ptTMP; 
			ptTMP = SimpleRightBufPoint(pos.lon, pos.lat, GetHeading(i), bufferDistance, false);
			LatLonUtility::ProjectionFromDegree(ptTMP.x, ptTMP.y);
			legs.at(i)->rightBufEndPointX = ptTMP;

			legs.at(i)->endOffset = LatLonUtility::GetDistanceRhumbLineMercator(pos.lat, pos.lon, ptWp[i + 1].y, ptWp[i + 1].x, false);
		}
		else if (i == (legCnt - 1)) {

		}
		else {

		}
	}

	delete[] ptWp;
}


double Route::GetLength()
{
	double sumLength = 0;

	for (int i = 0, cnt = legs.size(); i < cnt; i++) {
		sumLength += legs[i]->GetDistance();
	}

	return sumLength;
}


time_t Route::GetTimeSpan()
{
	return GetArrivalTime(waypoints.size() - 1) - curtime;
}