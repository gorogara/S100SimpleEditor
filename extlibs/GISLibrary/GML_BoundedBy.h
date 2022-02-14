#pragma once
class GML_BoundedBy
{
public:
	GML_BoundedBy(void);
	virtual ~GML_BoundedBy(void);

public:
	wstring m_srsName;
	double m_minX, m_minY, m_maxX, m_maxY;
	MBR m_mbr;

public:
	void GetDataFromXML(MSXML2::IXMLDOMNodePtr ptr);
	void InputGML(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr);
};

