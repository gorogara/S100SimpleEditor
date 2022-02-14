#include "stdafx.h"
#include "Waypoint.h"
#include "informationAssociation.h"
#include "featureAssociation.h"
#include "Route.h"
#include "Leg.h"

#include "GeoMetryLibrary\\GeoCommonFuc.h"
#include "GeoMetryLibrary\\GeoPoint.h"

using namespace RT;

Waypoint::Waypoint()
{
	p = new ENCPoint();
	if (!p->m_pPoints)
		p->m_pPoints = new GeoPoint[1];
	p->m_pPoints[0].x = 0;
	p->m_pPoints[0].y = 0;

	speed = 0;

	m_asLeg = NULL;
	m_asRoute = NULL;
	m_asWaypoint = NULL;
}

Waypoint::Waypoint(double _x, double _y)
{
	p = new ENCPoint();
	if (!p->m_pPoints)
		p->m_pPoints = new GeoPoint[1];

	p->m_pPoints[0].x = _x;
	p->m_pPoints[0].y = _y;

	speed = 0;

	m_asLeg = NULL;
	m_asRoute = NULL;
	m_asWaypoint = NULL;
}

Waypoint::~Waypoint()
{
	if (p)
		delete p;

	for (auto i = iaList.begin(); i != iaList.end(); i++) {
		delete *i;
	}

	for (auto i = faList.begin(); i != faList.end(); i++) {
		delete *i;
	}
}

void Waypoint::SetXY(double _x, double _y)
{
	p->m_pPoints[0].x = _x;
	p->m_pPoints[0].y = _y;
}

void Waypoint::SetX(double _x)
{
	p->m_pPoints[0].x = _x;
}

void Waypoint::SetY(double _y)
{
	p->m_pPoints[0].y = _y;
}

void Waypoint::GetXY(double* _x, double* _y)
{
	_x = &p->m_pPoints[0].x;
	_y = &p->m_pPoints[0].y;
}

double Waypoint::GetX()
{
	return p->m_pPoints[0].x;
}


double Waypoint::GetY()
{
	return p->m_pPoints[0].y;
}


void Waypoint::SetSpeed(double _speed)
{
	speed = _speed;
}


double Waypoint::GetSpeed()
{
	return speed;
}

void Waypoint::GetContent(MSXML2::IXMLDOMNodePtr nodePtr)
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
			informationAssociation* ia = new informationAssociation();
			ia->GetContent(childNode);

			iaList.push_back(ia);
		}		
		else if (baseName.compare("featureAssociation") == 0)
		{
			featureAssociation* fa = new featureAssociation();
			fa->GetContent(childNode);

			faList.push_back(fa);
		}
		else if (baseName.compare("pointProperty") == 0)
		{
			MSXML2::IXMLDOMNodeListPtr pChildNodeList = childNode->GetchildNodes();
			int cnt2 = pChildNodeList->Getlength();
			for (int j = 0; j < cnt2; j++) {
				MSXML2::IXMLDOMNodePtr childNode2 = pChildNodeList->Getitem(j);
				if (childNode2 == NULL)
					continue;
				std::string baseName = std::string(W2A(childNode2->baseName));

				if (baseName.compare("Point") == 0)
				{
					MSXML2::IXMLDOMNamedNodeMapPtr pAttr2 = childNode2->Getattributes();
					MSXML2::IXMLDOMNodePtr pAttrNP2;
					pAttrNP2 = pAttr2->getNamedItem(L"gml:id");
					VARIANT value2;
					if (pAttrNP2)
					{
						pAttrNP->get_nodeValue(&value2);
						pointID = std::wstring(value2.bstrVal);
					}

					MSXML2::IXMLDOMNodeListPtr pChildNodeList2 = childNode2->GetchildNodes();
					int cnt2 = pChildNodeList2->Getlength();
					for (int j = 0; j < cnt2; j++) {
						MSXML2::IXMLDOMNodePtr childNode3 = pChildNodeList2->Getitem(j);
						if (childNode3 == NULL)
							continue;
						std::string baseName = std::string(W2A(childNode3->baseName));

						if (baseName.compare("pos") == 0)
						{
							pos = childNode3->Gettext();
						}
					}
				}
			}
		}
		else if (baseName.compare("name") == 0)
		{
			name = childNode->Gettext();
		}
	}
}



void Waypoint::Save(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr)
{
	TCHAR buff[100] = { 0 };
	std::wstring str;
	MSXML2::IXMLDOMTextPtr pText;
	MSXML2::IXMLDOMElementPtr pParentElement = NULL, pElement = NULL;

	pParentElement = pDoc->createElement(L"Waypoint");
	pParentElement->setAttribute((_bstr_t)L"gml:id", id.c_str());
	ptr->appendChild(pParentElement);

	if (m_asRoute)
	{
		pElement = pDoc->createElement(L"S100:informationAssociation");
		wsprintf(buff, L"ia-%04d", RoutePlanner::idIndex++);
		str = buff;
		pElement->setAttribute((_bstr_t)L"gml:id", str.c_str());
		pElement->setAttribute((_bstr_t)L"xlink:arcrole", L"http://www.kriso.re.kr/RouteInformationSchema");
		pElement->setAttribute((_bstr_t)L"xlink:title", L"WaypointToRouteInfo");
		str = L"#";
		str.append(m_asRoute->id.c_str());
		pElement->setAttribute((_bstr_t)L"xlink:href", str.c_str());

		pParentElement->appendChild(pElement);
	}
	if (m_asLeg)
	{
		pElement = pDoc->createElement(L"S100:featureAssociation");
		wsprintf(buff, L"fa-%04d", RoutePlanner::idIndex++);
		str = buff;
		pElement->setAttribute((_bstr_t)L"gml:id", str.c_str());
		pElement->setAttribute((_bstr_t)L"xlink:arcrole", L"http://www.kriso.re.kr/RouteInformationSchema");
		pElement->setAttribute((_bstr_t)L"xlink:title", L"WaypointToLeg");
		str = L"#";
		str.append(m_asLeg->id.c_str());
		pElement->setAttribute((_bstr_t)L"xlink:href", str.c_str());

		pParentElement->appendChild(pElement);
	}
	if (m_asWaypoint)
	{
		pElement = pDoc->createElement(L"S100:featureAssociation");
		wsprintf(buff, L"fa-%04d", RoutePlanner::idIndex++);
		str = buff;
		pElement->setAttribute((_bstr_t)L"gml:id", str.c_str());
		pElement->setAttribute((_bstr_t)L"xlink:arcrole", L"http://www.kriso.re.kr/RouteInformationSchema");
		pElement->setAttribute((_bstr_t)L"xlink:title", L"NextWaypoint");
		str = L"#";
		str.append(m_asWaypoint->id.c_str());
		pElement->setAttribute((_bstr_t)L"xlink:href", str.c_str());

		pParentElement->appendChild(pElement);
	}

	if (p)
	{
		MSXML2::IXMLDOMElementPtr pPointPropElement = pDoc->createElement(L"S100:pointProperty");
		pParentElement->appendChild(pPointPropElement);

		MSXML2::IXMLDOMElementPtr pPointElement = pDoc->createElement(L"S100:Point");
		wsprintf(buff, L"POINT-%04d", RoutePlanner::idIndex++);
		str = buff;
		pPointElement->setAttribute((_bstr_t)L"gml:id", str.c_str());
		pPointPropElement->appendChild(pPointElement);

		MSXML2::IXMLDOMElementPtr pPosElement = pDoc->createElement(L"gml:pos");
		double	x = p->m_pPoints[0].x, y = p->m_pPoints[0].y;
		inverseProjection(x, y);
		_stprintf_s(buff, L"%.06f %.06f",
			x, y);
		str = buff;
		pText = pDoc->createTextNode((_bstr_t)str.c_str());
		pPosElement->appendChild(pText);
		pPointElement->appendChild(pPosElement);
	}


	pElement = pDoc->createElement(L"name");
	pText = pDoc->createTextNode((_bstr_t)name.c_str());
	pElement->appendChild(pText);
	pParentElement->appendChild(pElement);
}