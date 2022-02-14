#pragma once

#include <pugixml.hpp>

class S101Cell;
class R_CurveRecord;

class CreateInputSchemaS101
{
public:
	CreateInputSchemaS101();
	virtual ~CreateInputSchemaS101();

public:
	static void CreateS101PortrayalInputData(S101Cell* cell);
	static void CreateS101PortrayalInputDataByPugiXML(S101Cell* cell);

	static void SetFeaturesType(S101Cell* cell, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr);
    static void SetFeaturesType(S101Cell* cell, pugi::xml_node node);
	
	static void SetInformationsType(S101Cell* cell, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement);
	static void SetInformationsType(S101Cell* cell, pugi::xml_node node);
	
	static void SetVectorPointsType(S101Cell* cell, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement);
	static void SetVectorPointsType(S101Cell* cell, pugi::xml_node node);

	static void SetVectorMultiPointsType(S101Cell* cell, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement);
	static void SetVectorMultiPointsType(S101Cell* cell, pugi::xml_node node);

	static void SetVectorCurvesType(S101Cell* cell, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement);
	static void SetVectorCurvesType(S101Cell* cell, pugi::xml_node node);

	static void SetVectorCompositeCurvesType(S101Cell* cell, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement);
	static void SetVectorCompositeCurvesType(S101Cell* cell, pugi::xml_node node);
	
	static void SetVectorSurfacesType(S101Cell* cell, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement);
	static void SetVectorSurfacesType(S101Cell* cell, pugi::xml_node node);

	static void SetCurveElement(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement, R_CurveRecord* curveRecord);
	static void SetCurveElement(pugi::xml_node node, R_CurveRecord* curveRecord);

	static void CompositeCurveToCurve(S101Cell* cell, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement, unsigned RCID, unsigned ORNT);
	static void CompositeCurveToCurve(S101Cell* cell,pugi::xml_node node, unsigned RCID, unsigned ORNT);

	static void SurfaceToCurve(S101Cell* cell, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr parentElement, unsigned RCID, unsigned ORNT);
	static void SurfaceToCurve(S101Cell* cell, pugi::xml_node node);
};

