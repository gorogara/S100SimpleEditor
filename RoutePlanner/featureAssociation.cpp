#include "stdafx.h"
#include "featureAssociation.h"

namespace RT
{

	featureAssociation::featureAssociation()
	{
	}


	featureAssociation::~featureAssociation()
	{
	}


	void featureAssociation::GetContent(MSXML2::IXMLDOMNodePtr nodePtr)
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

}