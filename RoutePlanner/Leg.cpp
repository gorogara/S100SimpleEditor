#include "stdafx.h"
#include "Leg.h"
#include "Waypoint.h"
#include "informationAssociation.h"
#include "featureAssociation.h"

#include "LatLonUtility\\LatLonUtility.h"
#include "GeoMetryLibrary\\ENCLine.h"
#include "GeoMetryLibrary\\GeoPoint.h"
#include "GeoMetryLibrary\\GeoCommonFuc.h"

#include <cmath> 
using namespace RT;
using namespace LatLonUtility;

Leg::Leg()
{
	v_speedMin = 10;
	v_speedMax = 10;
	line = NULL;

	leftBufStartPoint.x = 0;
	leftBufStartPoint.y = 0;
	rightBufEndPointX.x = 0;
	rightBufEndPointX.y = 0;
	startOffset = 0;
	endOffset = 0;  
}

Leg::Leg(double _x1, double _y1, double _x2, double _y2)
{
	line = NULL;  
}

Leg::~Leg()
{  
	for (auto i = iaList.begin(); i != iaList.end(); i++) {
		delete *i;
	}

	for (auto i = faList.begin(); i != faList.end(); i++) {
		delete *i;
	}

	delete line;
}                                                                                      

bool Leg::SetSpeed(double _min, double _max)
{
	v_speedMin = _min;
	v_speedMax = _max;

	return true;
}

bool Leg::GetSpeed(double &_min, double &_max)
{
	_min = v_speedMin;
	_max = v_speedMax;
	
	return true;
}


double Leg::GetDistance()
{
	double lat1 = line->Points[0].y;
	double lon1 = line->Points[0].x;
	double lat2 = line->Points[1].y;
	double lon2 = line->Points[1].x;    

	InverseProjectionToRadian(lon1, lat1);
	InverseProjectionToRadian(lon2, lat2);

	return GetDistanceRhumbLineMercator(lat1, lon1, lat2, lon2, true);
}


double Leg::GetHeading()
{
	double lat1 = line->Points[0].y;
	double lon1 = line->Points[0].x;
	double lat2 = line->Points[1].y;
	double lon2 = line->Points[1].x;    

	return GetBearingRhubmLineMercator(lat1, lon1, lat2, lon2, false);
}

double Leg::GetTimeRequired()
{
	double minSpeed, maxSpeed;
	GetSpeed(minSpeed, maxSpeed); 

	if (minSpeed <= 0)
	{
		return 0;
	}
	else
	{
		minSpeed *= KN2MS; 
	}

	double d = GetDistance() * KM2M; 

	return d / minSpeed; 
}

void Leg::GetContent(MSXML2::IXMLDOMNodePtr nodePtr)
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
		else if (baseName.compare("invFeatureAssociation") == 0)
		{
			featureAssociation* fa = new featureAssociation();
			fa->GetContent(childNode);

			faList.push_back(fa);
		}
		else if (baseName.compare("curveProperty") == 0)
		{
			MSXML2::IXMLDOMNodeListPtr pChildNodeList = childNode->GetchildNodes();
			int cnt2 = pChildNodeList->Getlength();
			for (int j = 0; j < cnt2; j++) {
				MSXML2::IXMLDOMNodePtr childNode2 = pChildNodeList->Getitem(j);
				if (childNode2 == NULL)
					continue;
				std::string baseName = std::string(W2A(childNode2->baseName));

				if (baseName.compare("Curve") == 0)
				{
					MSXML2::IXMLDOMNamedNodeMapPtr pAttr2 = childNode2->Getattributes();
					MSXML2::IXMLDOMNodePtr pAttrNP2;
					pAttrNP2 = pAttr2->getNamedItem(L"gml:id");
					VARIANT value2;
					if (pAttrNP2)
					{
						pAttrNP->get_nodeValue(&value2);
						curveID = std::wstring(value2.bstrVal);
					}

					MSXML2::IXMLDOMNodeListPtr pChildNodeList2 = childNode2->GetchildNodes();
					int cnt2 = pChildNodeList2->Getlength();
					for (int j = 0; j < cnt2; j++) {
						MSXML2::IXMLDOMNodePtr childNode3 = pChildNodeList2->Getitem(j);
						if (childNode3 == NULL)
							continue;
						std::string baseName = std::string(W2A(childNode3->baseName));

						if (baseName.compare("segments") == 0)
						{
							MSXML2::IXMLDOMNodeListPtr pChildNodeList3 = childNode3->GetchildNodes();
							int cnt2 = pChildNodeList3->Getlength();
							for (int j = 0; j < cnt2; j++) {
								MSXML2::IXMLDOMNodePtr childNode4 = pChildNodeList3->Getitem(j);
								if (childNode4 == NULL)
									continue;
								std::string baseName = std::string(W2A(childNode4->baseName));

								if (baseName.compare("LineStringSegment") == 0)
								{
									MSXML2::IXMLDOMNodeListPtr pChildNodeList4 = childNode4->GetchildNodes();
									int cnt2 = pChildNodeList4->Getlength();
									for (int j = 0; j < cnt2; j++) {
										MSXML2::IXMLDOMNodePtr childNode5 = pChildNodeList4->Getitem(j);
										if (childNode5 == NULL)
											continue;
										std::string baseName = std::string(W2A(childNode5->baseName));

										if (baseName.compare("posList") == 0)
										{
											posList = childNode5->Gettext();
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}



void Leg::Save(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr)
{
	TCHAR buff[100] = { 0 };
	std::wstring str;
	MSXML2::IXMLDOMTextPtr pText;
	MSXML2::IXMLDOMElementPtr pParentElement = NULL, pElement;

	pParentElement = pDoc->createElement(L"Leg");
	pParentElement->setAttribute((_bstr_t)L"gml:id", id.c_str());
	ptr->appendChild(pParentElement);

	if (m_asWaypoint)
	{
		pElement = pDoc->createElement(L"S100:invFeatureAssociation");
		wsprintf(buff, L"ifa-%04d", RoutePlanner::idIndex++);
		str = buff;
		pElement->setAttribute((_bstr_t)L"gml:id", str.c_str());
		pElement->setAttribute((_bstr_t)L"xlink:arcrole", L"http://www.kriso.re.kr/RouteInformationSchema");
		pElement->setAttribute((_bstr_t)L"xlink:title", L"InverseLegToWaypoint");
		str = L"#";
		str.append(m_asWaypoint->id.c_str());
		pElement->setAttribute((_bstr_t)L"xlink:href", str.c_str());

		pParentElement->appendChild(pElement);
	}

	if (line)
	{
		MSXML2::IXMLDOMElementPtr pCurvePropElement = pDoc->createElement(L"S100:curveProperty");
		pParentElement->appendChild(pCurvePropElement);

		MSXML2::IXMLDOMElementPtr pCurveElement = pDoc->createElement(L"S100:Curve");
		wsprintf(buff, L"CURVE-%04d", RoutePlanner::idIndex++);
		str = buff;
		pCurveElement->setAttribute((_bstr_t)L"gml:id", str.c_str());
		pCurvePropElement->appendChild(pCurveElement);

		MSXML2::IXMLDOMElementPtr pSegmentsElement = pDoc->createElement(L"gml:segments");
		pCurveElement->appendChild(pSegmentsElement);

		MSXML2::IXMLDOMElementPtr pLineStringSegmentElement = pDoc->createElement(L"gml:LineStringSegment");
		pSegmentsElement->appendChild(pLineStringSegmentElement);

		MSXML2::IXMLDOMElementPtr pPosListElement = pDoc->createElement(L"gml:posList");
		double	x1 = line->Points[0].x, y1 = line->Points[0].y,
			x2 = line->Points[1].x, y2 = line->Points[1].y;

		inverseProjection(x1, y1);
		inverseProjection(x2, y2);
		_stprintf_s(buff, L"%.06f %.06f %.06f %.06f", 
			x1, y1,
			x2, y2			);
		str = buff;
		pText = pDoc->createTextNode((_bstr_t)str.c_str());
		pPosListElement->appendChild(pText);
		pLineStringSegmentElement->appendChild(pPosListElement);
	}
}