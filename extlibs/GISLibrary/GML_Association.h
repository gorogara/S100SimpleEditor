#pragma once
#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"
class GML_Information;
class GML_Feature;

enum ASSOC_TYPE {
	INFO_ASSOC = 0,
	INV_INFO_ASSOC = 1,
	FEATURE_ASSOC = 2,
	INV_FEATURE_ASSOC = 3
};

class GML_Association
{
public:
	GML_Association(void);
	virtual ~GML_Association(void);

public:
	static wstring AssociationType[4];
	int m_associationType;
	wstring m_id;
	wstring m_href;
	wstring m_arcrole;

public:
	static GML_Association* CreateAssoc(int assocType, wstring arcrole, wstring href, wstring id);
	static GML_Association* CreateInfoAssoc(int assocType, GML_Information* info, wstring arcrole, int id);
	static GML_Association* CreateFeatureAssoc(int assocType, GML_Feature* feature, wstring arcrole, int id);
	void InputGML(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr);

	void InputGML(pugi::xml_node node);
};