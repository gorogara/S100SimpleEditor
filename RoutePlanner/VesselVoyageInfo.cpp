#include "stdafx.h"
#include "VesselVoyageInfo.h"

namespace RT
{

	VesselVoyageInfo::VesselVoyageInfo()
	{
	}


	VesselVoyageInfo::~VesselVoyageInfo()
	{
	}

	void VesselVoyageInfo::GetContent(MSXML2::IXMLDOMNodePtr nodePtr)
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

			if (baseName.compare("voyageNumber") == 0)
			{
				voyageNumber = childNode->Gettext();
			}
			else if (baseName.compare("vesselMetacentricHeight") == 0)
			{
				vesselMetacentricHeight = childNode->Gettext();
			}
		}
	}

	void VesselVoyageInfo::Save(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr)
	{
		TCHAR buff[100] = { 0 };
		std::wstring str;
		MSXML2::IXMLDOMTextPtr pText;
		MSXML2::IXMLDOMElementPtr pParentElement = NULL, pElement = NULL;

		pParentElement = pDoc->createElement(L"VesselVoyageInfo");
		pParentElement->setAttribute((_bstr_t)L"gml:id", id.c_str());
		ptr->appendChild(pParentElement);

		pElement = pDoc->createElement(L"voyageNumber");
		pText = pDoc->createTextNode((_bstr_t)voyageNumber.c_str());
		pElement->appendChild(pText);
		pParentElement->appendChild(pElement);

		pElement = pDoc->createElement(L"vesselMetacentricHeight");
		pText = pDoc->createTextNode((_bstr_t)vesselMetacentricHeight.c_str());
		pElement->appendChild(pText);
		pParentElement->appendChild(pElement);
	}
}