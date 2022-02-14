#pragma once

#include "S100DatasetGML.h"
#include "S100GML_Point.h"
#include "S100GML_Curve.h"
#include "S100GML_Surface.h"

#include "S100GML_FeatureType.h"
#include "S100GML_InformationType.h"
#include "S100GML_Geometry.h"

#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

class Catalog;

class S100GML_Dataset_PROC
{
private:
	Catalog* m_currentCatalog;

public:
	S100GML_Dataset_PROC();
	virtual ~S100GML_Dataset_PROC();

	void SetCatalog(Catalog* _catalog);


	S100DatasetGML::S100GML_FeatureType* GetFeatureContents(MSXML2::IXMLDOMNodePtr pNode);
	S100DatasetGML::S100GML_InformationType* GetInformationContents(MSXML2::IXMLDOMNodePtr pNode);
	S100DatasetGML::S100GML_Geometry* GetGeometryContents(MSXML2::IXMLDOMNodePtr pNode);

	void GetGeometryContents(S100DatasetGML::S100GML_Point* geo, MSXML2::IXMLDOMNodePtr pNode);
	void GetGeometryContents(S100DatasetGML::S100GML_Curve* geo, MSXML2::IXMLDOMNodePtr pNode);
	void GetGeometryContents(S100DatasetGML::S100GML_Surface* geo, MSXML2::IXMLDOMNodePtr pNode);

	void GetContents(MSXML2::IXMLDOMNodePtr pNode, S100DatasetGML::S100GML_Attribute *parentAttr = NULL); 

	S100DatasetGML::S100GML_FeatureType* GetFeatureContents(pugi::xml_node node);
	S100DatasetGML::S100GML_InformationType* GetInformationContents(pugi::xml_node node);
	S100DatasetGML::S100GML_Geometry* GetGeometryContents(pugi::xml_node node);

	void GetGeometryContents(S100DatasetGML::S100GML_Point* geo, pugi::xml_node node);
	void GetGeometryContents(S100DatasetGML::S100GML_Curve* geo, pugi::xml_node node);
	void GetGeometryContents(S100DatasetGML::S100GML_Surface* geo, pugi::xml_node node);

	void GetContents(pugi::xml_node node, S100DatasetGML::S100GML_Attribute *parentAttr = NULL);

};

