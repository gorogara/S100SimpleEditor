#pragma once

#include "Layer.h"
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp" 
class PortrayalCatalogue;
class Catalog;

class S111Layer :
	public Layer
{
public:
	S111Layer();
	virtual ~S111Layer();

public:
	PortrayalCatalogue		*m_pPortrayalCatalogue;
	Catalog					*m_pFeatureCatalogue;

public:
	bool Open(CString filePath);

	void SetCurNumberOfTimes(int _curNumberOfTimes);
	void NextTimeIndex();
	void PrevTimeIndex();

	int GetNumberOfTimes();
	SYSTEMTIME GetSystemTime(int index);

	bool BuildInputXML(int _index);
	bool BuildInputXMLByPugi(int index);
	bool BuildInputXML();
	bool BuildInputXMLByPugi();
	
	void SetVectorPointsType(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement);
	void SetVectorPointsType(pugi::xml_node node);
	
	void SetFeaturesType(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement, int index);
	void SetFeaturesType(pugi::xml_node node,int index);
	
	void SetFeaturesType(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement);
	void SetFeaturesType(pugi::xml_node node);
};