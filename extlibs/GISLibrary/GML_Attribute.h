#pragma once
class GML_Attribute
{
public:
	GML_Attribute(void);
	virtual ~GML_Attribute(void);

public:
	wstring m_name;
	wstring m_value;
	
public:
	list<GML_Attribute*> m_attributes;
	void InputGML(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr);
};

