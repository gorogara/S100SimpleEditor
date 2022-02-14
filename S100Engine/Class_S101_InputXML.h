#pragma once

#include <map>

class CClass_S101_Base;

struct ST_FEATURE_RECORD;
struct ST_INFO_RECORD;
struct ST_POINT_RECORD;
struct ST_MULTI_POINT_RECORD; 
class CClass_S101_InputXML
{
public:
	CClass_S101_InputXML();
	virtual ~CClass_S101_InputXML();      
	MSXML2::IXMLDOMDocument2Ptr GetInputXML(CClass_S101_Base* pBase);       
	bool                        GetInputXML(CClass_S101_Base* pBase, CString pathInputXML);       
	MSXML2::IXMLDOMDocument2Ptr GetOutputXML(CString pathInputXML, CString pathXSL);        
	bool                        GetOutputXML(CString pathInputXML, CString pathXSL, CString pathOutputXML);       
	MSXML2::IXMLDOMDocument2Ptr GetOutputXML(MSXML2::IXMLDOMDocument2Ptr pInputXML, CString pathXSL);      
	bool                        GetOutputXML(MSXML2::IXMLDOMDocument2Ptr pInputXML, CString pathXSL, CString pathOutputXML); 
	CString GetInformationAssociationStringCode(CClass_S101_Base* pBase, int nNumeric);
	CString GetFeatureAssociationStringCode(CClass_S101_Base* pBase, int nNumeric);
	CString GetAssociationRoleStringCode(CClass_S101_Base* pBase, int nNumeric);    
	bool CreateProcessingInstruction(MSXML2::IXMLDOMDocument2Ptr pDoc);    
	MSXML2::IXMLDOMElementPtr CreateDatasetElement(MSXML2::IXMLDOMDocument2Ptr pDoc);      
	MSXML2::IXMLDOMElementPtr CreateFeaturesElement(CClass_S101_Base* pBase, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pDatasetElement);      
	MSXML2::IXMLDOMElementPtr CreateInformationTypesElement(CClass_S101_Base* pBase, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pDatasetElement);      
	MSXML2::IXMLDOMElementPtr CreatePointsElement(CClass_S101_Base* pBase, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pDatasetElement);     
	MSXML2::IXMLDOMElementPtr CreateMultiPointsElement(CClass_S101_Base* pBase, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pDatasetElement);

	MSXML2::IXMLDOMElementPtr CreateCurvesElement(CClass_S101_Base* pBase, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pDatasetElement);
	
	MSXML2::IXMLDOMElementPtr CreateCompositeCurvesElement(CClass_S101_Base* pBase, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pDatasetElement);
	
	MSXML2::IXMLDOMElementPtr CreateSurfacesElement(CClass_S101_Base* pBase, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pDatasetElement);

	bool CreateFeatureTypeStringCodeElement(CClass_S101_Base* pBase, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pFeaturesElement);
	bool CreateAttributeStringCodeElement(CClass_S101_Base* pBase, ST_FEATURE_RECORD* pST_FEATURE_RECORD, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pFeatureTypeElement);
	bool CreateAttributeStringCodeElement(CClass_S101_Base* pBase, ST_INFO_RECORD* pST_INFO_RECORD, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pInformationTypeElement);
	bool CreateInformationTypeStringCodeElement(CClass_S101_Base* pBase, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pInformationTypesElement);
	bool CreatePointElement(CClass_S101_Base* pBase, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pPointsElement);
	bool CreateMultiPointElement(CClass_S101_Base* pBase, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pMultiPointsElement);
	bool CreateCurveElement(CClass_S101_Base* pBase, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pCurvesElement);
	bool CreateCompositeCurveElement(CClass_S101_Base* pBase, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pCompositeCurveElement);
	bool CreateSurfaceElement(CClass_S101_Base* pBase, MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr pSurfacesElement);

	CString GetFeatureTypeID(ST_FEATURE_RECORD* pST_FEATURE_RECORD);
	CString GetFeatureTypePrimitive(ST_FEATURE_RECORD* pST_FEATURE_RECORD);
	CString GetInformationTypeID(ST_INFO_RECORD* pST_INFO_RECORD);
	CString GetPointID(ST_POINT_RECORD* pST_POINT_RECORD);
	CString GetMultiPointID(ST_MULTI_POINT_RECORD* pST_MULTI_POINT_RECORD);
	CString GetInterpolation(int num);

	CString GetSpatialTypeNameFromRRNM(unsigned int nRRNM);
	CString GetOrientationFromORNT(unsigned int nORNT);

	bool AddParameters(MSXML2::IXSLProcessorPtr pProcessor);

	HRESULT hr_Initialize;
};