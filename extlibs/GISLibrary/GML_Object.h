#pragma once
#include "GML_Attribute.h"
#include "GML_Association.h"

class GML_Object
{
public:
	GML_Object();
	virtual ~GML_Object();

public: 
	int m_objlCode;
	int m_iid;
	wstring m_name;
	wstring m_id;
	list<GML_Attribute*> m_attributes;
	list<GML_Association*> m_associations;

public:
	void ResetAttributes();
	virtual void InputGML(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr){};
};