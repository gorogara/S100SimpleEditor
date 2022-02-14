#include "stdafx.h"
#include "informationAssociation.h"

namespace RT
{
	informationAssociation::informationAssociation()
	{
	}


	informationAssociation::~informationAssociation()
	{
	}


	void informationAssociation::GetContent(MSXML2::IXMLDOMNodePtr nodePtr)
	{
		USES_CONVERSION;

		MSXML2::IXMLDOMNamedNodeMapPtr pAttr = nodePtr->Getattributes();
		MSXML2::IXMLDOMNodePtr pAttrNP;
		VARIANT value;

		pAttrNP = pAttr->getNamedItem(L"gml:id");
		if (pAttrNP)
		{
			pAttrNP->get_nodeValue(&value);
			id = std::wstring(value.bstrVal);
		}
		pAttrNP = pAttr->getNamedItem(L"xlink:arcrole");
		if (pAttrNP)
		{
			pAttrNP->get_nodeValue(&value);
			arcrole = std::wstring(value.bstrVal);
		}
		pAttrNP = pAttr->getNamedItem(L"xlink:title");
		if (pAttrNP)
		{
			pAttrNP->get_nodeValue(&value);
			title = std::wstring(value.bstrVal);
		}
		pAttrNP = pAttr->getNamedItem(L"xlink:href");
		if (pAttrNP)
		{
			pAttrNP->get_nodeValue(&value);
			href = std::wstring(value.bstrVal);
			href.erase(href.begin(), ++href.begin());
		}
	}

	void informationAssociation::Save(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr
		, std::wstring arcrole, std::wstring title, std::wstring href, std::wstring gml_id)
	{
		MSXML2::IXMLDOMTextPtr pText;
		MSXML2::IXMLDOMElementPtr pElement = NULL;

		pElement = pDoc->createElement(L"S100:informationAssociation");

		ptr->appendChild(pElement);

		pElement->setAttribute((_bstr_t)L"xlink:arcrole", arcrole.c_str());
		pElement->setAttribute((_bstr_t)L"xlink:title", title.c_str());
		pElement->setAttribute((_bstr_t)L"xlink:href", href.c_str());
		pElement->setAttribute((_bstr_t)L"gml:id", gml_id.c_str());
	}
}