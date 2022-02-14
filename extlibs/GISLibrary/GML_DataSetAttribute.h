#pragma once
class GML_DataSetAttribute
{
public:
	GML_DataSetAttribute();
	virtual ~GML_DataSetAttribute();

public:
	list<GML_DataSetAttribute*> m_datasetAttributes; 
	wstring m_name;
	wstring m_value;

public:
	void RemoveData();
	void InputGML(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr);
};