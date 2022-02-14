#include "stdafx.h"
#include "VesselStaticInfo.h"
#include "informationAssociation.h"
#include "RoutePlanner.h"

namespace RT
{
	VesselStaticInfo::VesselStaticInfo()
	{
		vesselVoyageInfo = NULL;
	}


	VesselStaticInfo::~VesselStaticInfo()
	{
		for (auto i = iaList.begin(); i != iaList.end(); i++) {
			delete *i;
		}

		delete vesselVoyageInfo;
	}

	void VesselStaticInfo::GetContent(MSXML2::IXMLDOMNodePtr nodePtr)
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

			std::wstring routeName;
			std::wstring sourceIndication;
			std::wstring routeStatus;
			std::wstring optimizationMethod;
			std::wstring historyOfRouteChanges;
			if (baseName.compare("informationAssociation") == 0)
			{
				RT::informationAssociation* ia = new RT::informationAssociation();
				ia->GetContent(childNode);

				iaList.push_back(ia);
			}
			else if (baseName.compare("routeName") == 0)
			{
				routeName = childNode->Gettext();
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
	void VesselStaticInfo::Save(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr)
	{
		TCHAR buff[100] = { 0 };
		std::wstring str;
		MSXML2::IXMLDOMTextPtr pText;
		MSXML2::IXMLDOMElementPtr pParentElement = NULL, pElement = NULL;

		pParentElement = pDoc->createElement(L"VesselStaticInfo");
		pParentElement->setAttribute((_bstr_t)L"gml:id", id.c_str());
		ptr->appendChild(pParentElement);

		if (vesselVoyageInfo)
		{
			pElement = pDoc->createElement(L"S100:informationAssociation");
			wsprintf(buff, L"ia-%04d", RoutePlanner::idIndex++);
			str = buff;
			pElement->setAttribute((_bstr_t)L"gml:id", str.c_str());
			pElement->setAttribute((_bstr_t)L"xlink:arcrole", L"http://www.kriso.re.kr/RouteInformationSchema");
			pElement->setAttribute((_bstr_t)L"xlink:title", L"VesselStaticInfoToVesselVoyageInfo");
			str = L"#";
			str.append(vesselVoyageInfo->id.c_str());
			pElement->setAttribute((_bstr_t)L"xlink:href", str.c_str());

			pParentElement->appendChild(pElement);
		}

		pElement = pDoc->createElement(L"vesselName");
		pText = pDoc->createTextNode((_bstr_t)vesselName.c_str());
		pElement->appendChild(pText);
		pParentElement->appendChild(pElement);

		pElement = pDoc->createElement(L"vesselType");
		pText = pDoc->createTextNode((_bstr_t)vesselType.c_str());
		pElement->appendChild(pText);
		pParentElement->appendChild(pElement);
	}
}