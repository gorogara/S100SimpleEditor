#include "stdafx.h"
#include "S100GML_Dataset_PROC.h"
#include "S100GML_Association.h"

#include "../FeatureCatalog/Catalog.h"
#include "../FeatureCatalog/FeatureCatalogue.h"

void DeleteNamespace(std::wstring &value)
{
	int tempi = value.find_last_of(L":");
	if (tempi != -1)
		value = value.substr(tempi + 1);
}

S100GML_Dataset_PROC::S100GML_Dataset_PROC()
{
}
S100GML_Dataset_PROC::~S100GML_Dataset_PROC()
{
}

void S100GML_Dataset_PROC::SetCatalog(Catalog* _catalog)
{
	m_currentCatalog = _catalog;
}

S100DatasetGML::S100GML_FeatureType* S100GML_Dataset_PROC::GetFeatureContents(MSXML2::IXMLDOMNodePtr pNode)
{
	std::wstring nodeName = (LPCTSTR)pNode->GetnodeName();
	S100DatasetGML::S100GML_FeatureType* featureType = NULL;

	featureType = new S100DatasetGML::S100GML_FeatureType();
	featureType->camelCase = nodeName;

	MSXML2::IXMLDOMNamedNodeMapPtr pAttr = pNode->Getattributes();
	MSXML2::IXMLDOMNodePtr pAttrNP;
	VARIANT value;

	pAttrNP = pAttr->getNamedItem(L"gml:id");
	if (pAttrNP)
	{
		pAttrNP->get_nodeValue(&value);
		featureType->id = std::wstring(value.bstrVal).c_str();
	}

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	for (int i = 0; i < pNodeList->Getlength(); i++)
	{
		MSXML2::IXMLDOMNodePtr pSubNode = pNodeList->Getitem(i);

		if (!pSubNode)
			continue;

		std::wstring nodeName = (LPCTSTR)pSubNode->GetnodeName();    
		int nodeType = 0;

		auto cli = m_currentCatalog->m_pCatalogueList.begin();

		FeatureCatalogue* fc = cli->second;
		auto sa = fc->GetSimpleAttribute(nodeName);
		auto ca = fc->GetComplexAttribute(nodeName);
		auto as = fc->GetFeatureAssociation(nodeName);
		auto ro = fc->GetRole(nodeName);

		if (sa)
		{
			nodeType = 1;
		}
		else if (ca)
		{
			nodeType = 2;
		}
		else if (as)
		{
			nodeType = 3;
		}
		else if (ro)
		{
			nodeType = 4;
		}
		else
		{
			nodeType = 0;
		}  
		if (nodeType == 3 || nodeType == 4) 
		{
			S100DatasetGML::S100GML_Association asso;
			asso.tag = nodeName;

			MSXML2::IXMLDOMNamedNodeMapPtr pAttr = pSubNode->Getattributes();

			pAttrNP = pAttr->getNamedItem(L"gml:id");
			if (pAttrNP) {
				pAttrNP->get_nodeValue(&value);
				asso.id = std::wstring(value.bstrVal).c_str();
			}
			pAttrNP = pAttr->getNamedItem(L"xlink:href");
			if (pAttrNP) {
				pAttrNP->get_nodeValue(&value);
				asso.href = std::wstring(value.bstrVal).c_str();
			}
			pAttrNP = pAttr->getNamedItem(L"xlink:role");
			if (pAttrNP) {
				pAttrNP->get_nodeValue(&value);
				asso.role = std::wstring(value.bstrVal).c_str();
			}
			featureType->association.push_back(asso);
		}
		else if (nodeName.compare(L"geometry") == 0)
		{
			S100DatasetGML::S100GML_Geometry* geo = GetGeometryContents(pSubNode);

			if (!geo)
			{
				featureType->geometry = NULL;
			}
			else if (geo->GetType() == 1)
			{
				S100DatasetGML::S100GML_Point* g = (S100DatasetGML::S100GML_Point*)geo;
				if (g->pos.size() < 1)
				{
					featureType->geometry = NULL;
					delete geo;
				}
				else
				{
					featureType->geometry = geo;
				}
			}
			else
				featureType->geometry = geo;
		}
		else
		{
			S100DatasetGML::S100GML_Attribute attr;
			attr.camelCase = nodeName.c_str();

			if (pSubNode->GetchildNodes()->Getlength() == 0)
			{
				MSXML2::IXMLDOMNamedNodeMapPtr pAttr = pNode->Getattributes();

				pAttrNP = pAttr->getNamedItem(L"xlink:href");

				if (pAttrNP) 
				{
					S100DatasetGML::S100GML_Association asso;
					asso.tag = nodeName;
					featureType->association.push_back(asso);
				}
				else
				{
					variant_t variant = pSubNode->Gettext();
					if (SysStringLen(variant.bstrVal) != 0)
					{
						attr.value = (LPCTSTR)variant.bstrVal;
					}
				}
			}
			else if (pSubNode->GetchildNodes()->Getlength() == 1)
			{
				MSXML2::IXMLDOMNodeListPtr tempNodeList = pSubNode->GetchildNodes();
				MSXML2::IXMLDOMNodePtr pTempNode = tempNodeList->Getitem(0);

				std::wstring tempNodeName = (LPCTSTR)pTempNode->GetnodeName();
				if (tempNodeName.compare(L"#text") == 0)
				{
					variant_t variant = pSubNode->Gettext();
					if (SysStringLen(variant.bstrVal) != 0)
						attr.value = (LPCTSTR)variant.bstrVal;
				}
				else
				{
					GetContents(pSubNode, &attr);
				}
			}
			else
			{
				GetContents(pSubNode, &attr);
			}
			featureType->attribute.push_back(attr);
		}
	}
	return featureType;
}
S100DatasetGML::S100GML_InformationType* S100GML_Dataset_PROC::GetInformationContents(MSXML2::IXMLDOMNodePtr pNode)
{
	std::wstring nodeName = (LPCTSTR)pNode->GetnodeName();
	S100DatasetGML::S100GML_InformationType* informationType = NULL;

	informationType = new S100DatasetGML::S100GML_InformationType();
	informationType->camelCase = nodeName;

	MSXML2::IXMLDOMNamedNodeMapPtr pAttr = pNode->Getattributes();
	MSXML2::IXMLDOMNodePtr pAttrNP;
	VARIANT value;

	pAttrNP = pAttr->getNamedItem(L"gml:id");
	if (pAttrNP)
	{
		pAttrNP->get_nodeValue(&value);
		informationType->id = std::wstring(value.bstrVal).c_str();
	}

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	for (int i = 0; i < pNodeList->Getlength(); i++)
	{
		MSXML2::IXMLDOMNodePtr pSubNode = pNodeList->Getitem(i);

		if (!pSubNode)
		{
			continue;
		}

		std::wstring nodeName = (LPCTSTR)pSubNode->GetnodeName();    
		int nodeType = 0;

		auto cli = m_currentCatalog->m_pCatalogueList.begin();

		FeatureCatalogue* fc = cli->second;
		auto sa = fc->GetSimpleAttribute(nodeName);
		auto ca = fc->GetComplexAttribute(nodeName);
		auto as = fc->GetFeatureAssociation(nodeName);
		auto ro = fc->GetRole(nodeName);

		if (sa)
		{
			nodeType = 1;
		}
		else if (ca)
		{
			nodeType = 2;
		}
		else if (as)
		{
			nodeType = 3;
		}
		else if (ro)
		{
			nodeType = 4;
		}
		else
		{
			nodeType = 0;
		} 
		if (nodeName.find(L"#") != std::wstring::npos)
		{
		} 
		if (nodeType == 3 || nodeType == 4)
		{
			S100DatasetGML::S100GML_Association asso;
			asso.tag = nodeName;

			MSXML2::IXMLDOMNamedNodeMapPtr pAttr = pSubNode->Getattributes();

			pAttrNP = pAttr->getNamedItem(L"gml:id");
			if (pAttrNP) {
				pAttrNP->get_nodeValue(&value);
				asso.id = std::wstring(value.bstrVal).c_str();
			}
			pAttrNP = pAttr->getNamedItem(L"xlink:href");
			if (pAttrNP) {
				pAttrNP->get_nodeValue(&value);
				asso.href = std::wstring(value.bstrVal).c_str();
			}
			pAttrNP = pAttr->getNamedItem(L"xlink:role");
			if (pAttrNP) {
				pAttrNP->get_nodeValue(&value);
				asso.role = std::wstring(value.bstrVal).c_str();
			}
			informationType->association.push_back(asso);
		}
		else
		{
			S100DatasetGML::S100GML_Attribute attr;
			attr.camelCase = nodeName.c_str();

			if (pSubNode->GetchildNodes()->Getlength() == 0)
			{
				variant_t variant = pSubNode->Gettext();
				if (SysStringLen(variant.bstrVal) != 0)
					attr.value = (LPCTSTR)variant.bstrVal;
			}
			else if (pSubNode->GetchildNodes()->Getlength() == 1)
			{
				MSXML2::IXMLDOMNodeListPtr tempNodeList = pSubNode->GetchildNodes();
				MSXML2::IXMLDOMNodePtr pTempNode = tempNodeList->Getitem(0);

				std::wstring tempNodeName = (LPCTSTR)pTempNode->GetnodeName();
				if (tempNodeName.compare(L"#text") == 0)
				{
					variant_t variant = pSubNode->Gettext();
					if (SysStringLen(variant.bstrVal) != 0)
						attr.value = (LPCTSTR)variant.bstrVal;
				}
				else
				{
					GetContents(pSubNode, &attr);
				}
			}
			else
			{
				GetContents(pSubNode, &attr);
			}
			informationType->attribute.push_back(attr);
		}
	}
	return informationType;
}

S100DatasetGML::S100GML_Geometry* S100GML_Dataset_PROC::GetGeometryContents(MSXML2::IXMLDOMNodePtr pNode)
{
	S100DatasetGML::S100GML_Geometry* geo = NULL;
	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	for (int i = 0; i < pNodeList->Getlength(); i++)
	{
		MSXML2::IXMLDOMNodePtr pNode = pNodeList->Getitem(i);

		if (!pNode)
			continue;

		std::wstring nodeName = (LPCTSTR)pNode->GetnodeName();

		MSXML2::IXMLDOMNodeListPtr pGeoNodeList = pNode->GetchildNodes();

		for (int i = 0; i < pGeoNodeList->Getlength(); i++)
		{
			MSXML2::IXMLDOMNodePtr pGeoNode = pGeoNodeList->Getitem(i);
			if (nodeName.compare(L"S100:pointProperty") == 0)
			{
				geo = new S100DatasetGML::S100GML_Point();
				GetGeometryContents((S100DatasetGML::S100GML_Point*)geo, pGeoNode);
			}
			else if (nodeName.compare(L"S100:curveProperty") == 0)
			{
				geo = new S100DatasetGML::S100GML_Curve();
				GetGeometryContents((S100DatasetGML::S100GML_Curve*)geo, pGeoNode);
			}
			else if (nodeName.compare(L"S100:surfaceProperty") == 0)
			{
				geo = new S100DatasetGML::S100GML_Surface();
				GetGeometryContents((S100DatasetGML::S100GML_Surface*)geo, pGeoNode);
			}
		}
	}

	return geo;
}
void S100GML_Dataset_PROC::GetGeometryContents(S100DatasetGML::S100GML_Point* geo, MSXML2::IXMLDOMNodePtr pNode)
{          
	MSXML2::IXMLDOMNodeListPtr pNodeList;

	if (!pNode) return;
	std::wstring nodeName = (LPCTSTR)pNode->GetnodeName();
	DeleteNamespace(nodeName);
	if (nodeName.compare(L"Point") == 0)
	{
		MSXML2::IXMLDOMNodeListPtr pGeoNodeList = pNode->GetchildNodes();
		for (int i = 0; i < pGeoNodeList->Getlength(); i++)
		{
			MSXML2::IXMLDOMNodePtr pGeoNode = pGeoNodeList->Getitem(i);
			std::wstring nodeName = (LPCTSTR)pGeoNode->GetnodeName();
			DeleteNamespace(nodeName);
			if (nodeName.compare(L"pos") == 0)
			{ 
				variant_t variant = pNode->Gettext();
				if (SysStringLen(variant.bstrVal) != 0) 
					geo->pos = (LPCTSTR)variant.bstrVal;

			}
		}
	}
}
void S100GML_Dataset_PROC::GetGeometryContents(S100DatasetGML::S100GML_Curve* geo, MSXML2::IXMLDOMNodePtr pNode)
{          
	MSXML2::IXMLDOMNodeListPtr pNodeList;

	if (!pNode) return;
	std::wstring nodeName = (LPCTSTR)pNode->GetnodeName();
	DeleteNamespace(nodeName);
	if (nodeName.compare(L"Curve") == 0)
	{
		MSXML2::IXMLDOMNodeListPtr pGeoNodeList = pNode->GetchildNodes();
		for (int i = 0; i < pGeoNodeList->Getlength(); i++)
		{
			MSXML2::IXMLDOMNodePtr pGeoNode = pGeoNodeList->Getitem(i);
			std::wstring nodeName = (LPCTSTR)pGeoNode->GetnodeName();
			DeleteNamespace(nodeName);
			if (nodeName.compare(L"segments") == 0)
			{ 
				variant_t variant = pNode->Gettext();
				if (SysStringLen(variant.bstrVal) != 0) 
					geo->posList = (LPCTSTR)variant.bstrVal;

			}
		}
	}
}
void S100GML_Dataset_PROC::GetGeometryContents(S100DatasetGML::S100GML_Surface* geo, MSXML2::IXMLDOMNodePtr pNode)
{
	std::wstring nodeName = (LPCTSTR)pNode->GetnodeName();
	DeleteNamespace(nodeName);
	if (nodeName.compare(L"Surface") == 0)
	{
		MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

		for (int i = 0; i < pNodeList->Getlength(); i++)
		{
			MSXML2::IXMLDOMNodePtr pNode = pNodeList->Getitem(i);
			if (!pNode) continue;
			std::wstring nodeName = (LPCTSTR)pNode->GetnodeName();
			DeleteNamespace(nodeName);
			MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

			if (nodeName.compare(L"patches") == 0)
			{
				MSXML2::IXMLDOMNodePtr pNode = pNodeList->Getitem(i);
				if (!pNode) continue;
				std::wstring nodeName = (LPCTSTR)pNode->GetnodeName();
				DeleteNamespace(nodeName);
				if (nodeName.compare(L"PolygonPatch") == 0)
				{
					MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();
					for (int i = 0; i < pNodeList->Getlength(); i++)
					{
						MSXML2::IXMLDOMNodePtr pNode = pNodeList->Getitem(i);
						std::wstring nodeName = (LPCTSTR)pNode->GetnodeName();
						DeleteNamespace(nodeName);
						variant_t variant = pNode->Gettext();
						if (SysStringLen(variant.bstrVal) != 0)
						{
							if (nodeName.compare(L"exterior") == 0)
							{
								geo->posListOfExterior = (LPCTSTR)variant.bstrVal;
							}
							else if (nodeName.compare(L"interior") == 0)
							{
								std::wstring posList = (LPCTSTR)variant.bstrVal;
								geo->posListOfInteriorList.push_back(posList);
							}
						}
					}
				}
			}
		}
	}
} 

S100DatasetGML::S100GML_FeatureType*  S100GML_Dataset_PROC::GetFeatureContents(pugi::xml_node node)
{                    
	S100DatasetGML::S100GML_FeatureType* featureType = new S100DatasetGML::S100GML_FeatureType();
	featureType->camelCase = pugi::as_wide(node.name());

	for (auto attri = node.first_attribute(); attri; attri = attri.next_attribute())
	{
		auto attriName = attri.name();
		if (strcmp(attriName, "gml:id") == 0)
		{
			featureType->id = pugi::as_wide(attri.value());
			break;
		}
	}


	for (auto instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		if (instruction == nullptr)
		{
			continue;
		}

		auto instructionName = instruction.name();    
		auto instructionNameWString = pugi::as_wide(instructionName);
		int nodeType = 0;

		auto cli = m_currentCatalog->m_pCatalogueList.begin();

		FeatureCatalogue* fc = cli->second;
		auto sa = fc->GetSimpleAttribute(instructionNameWString);
		auto ca = fc->GetComplexAttribute(instructionNameWString);
		auto as = fc->GetFeatureAssociation(instructionNameWString);
		auto ro = fc->GetRole(instructionNameWString);

		if (sa)
		{
			nodeType = 1;
		}
		else if (ca)
		{
			nodeType = 2;
		}
		else if (as)
		{
			nodeType = 3;
		}
		else if (ro)
		{
			nodeType = 4;
		}
		else
		{
			nodeType = 0;
		}   
		if (nodeType == 3 || nodeType == 4)
		{
			S100DatasetGML::S100GML_Association asso;
			asso.tag = pugi::as_wide(instructionName);

			auto attri = instruction.attribute("gml:id");
			if (attri)
			{
				asso.id = pugi::as_wide(attri.value());
			}

			attri = instruction.attribute("xlink:href");
			if (attri)
			{
				asso.href = pugi::as_wide(attri.value());
			}

			attri = instruction.attribute("xlink:role");
			if (attri)
			{
				asso.role = pugi::as_wide(attri.value());
			}
			featureType->association.push_back(asso);
		}

		else if (!strcmp(instructionName, "geometry")) 
		{
			S100DatasetGML::S100GML_Geometry* geo = GetGeometryContents(instruction);
			if (!geo)
			{
				featureType->geometry = nullptr;
			}

			if (geo->GetType() == 1)
			{
				S100DatasetGML::S100GML_Point* g = (S100DatasetGML::S100GML_Point*)geo;
				if (g->pos.size() < 1)
				{
					featureType->geometry = nullptr;
					delete geo;
				}
				else
				{
					featureType->geometry = geo;
				}
			}
			else
			{
				featureType->geometry = geo;
			}
		}

		else
		{
			S100DatasetGML::S100GML_Attribute attr;
			attr.camelCase = pugi::as_wide(instructionName);

			if (instruction.first_child() != nullptr) 
			{

				auto childNodeName = instruction.first_child().name();
				if (strcmp(childNodeName, "") == 0)
				{
					attr.value = pugi::as_wide(instruction.child_value());
				}
				else
				{
					GetContents(instruction, &attr);
				}                 
			}
			else
			{
				GetContents(instruction, &attr);
			}

			featureType->attribute.push_back(attr);
		}
	}
	return featureType;
}
S100DatasetGML::S100GML_InformationType*  S100GML_Dataset_PROC::GetInformationContents(pugi::xml_node node)
{
	S100DatasetGML::S100GML_InformationType* informationType = NULL;

	informationType = new S100DatasetGML::S100GML_InformationType();
	informationType->camelCase = pugi::as_wide(node.name());

	for (auto attri = node.first_attribute(); attri; attri = attri.next_attribute())
	{
		auto attriName = attri.name();
		if (!strcmp(attriName, "gml:id")) 
		{
			auto value = attri.value();
			informationType->id = pugi::as_wide(value);
			break;
		}
	}


	for (auto instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		auto instructionName = instruction.name();    

		auto instructionNameWString = pugi::as_wide(instructionName);
		int nodeType = 0;

		auto cli = m_currentCatalog->m_pCatalogueList.begin();

		FeatureCatalogue* fc = cli->second;
		auto sa = fc->GetSimpleAttribute(instructionNameWString);
		auto ca = fc->GetComplexAttribute(instructionNameWString);
		auto as = fc->GetFeatureAssociation(instructionNameWString);
		auto ro = fc->GetRole(instructionNameWString);

		if (sa)
		{
			nodeType = 1;
		}
		else if (ca)
		{
			nodeType = 2;
		}
		else if (as)
		{
			nodeType = 3;
		}
		else if (ro)
		{
			nodeType = 4;
		}
		else
		{
			nodeType = 0;
		}  
		if (nodeType == 3 || nodeType == 4)
		{
			S100DatasetGML::S100GML_Association asso; 
			for (auto instructionAttri = instruction.first_attribute(); instructionAttri; instructionAttri = instructionAttri.next_attribute())
			{
				auto instructionAttriName = instructionAttri.name();
				if (!strcmp(instructionAttriName, "gml:id"))
				{
					std::wstring value = pugi::as_wide(instructionAttri.value());
					asso.id = value.c_str();
				}
				else if (!strcmp(instructionAttriName, "xlink:href"))
				{
					std::wstring value = pugi::as_wide(instructionAttri.value());
					asso.href = value.c_str();
				}
				else if (!strcmp(instructionAttriName, "xlink:role"))
				{
					std::wstring value = pugi::as_wide(instructionAttri.value());
					asso.role = value.c_str();
				}
				informationType->association.push_back(asso);
			}
		}
		else
		{
			S100DatasetGML::S100GML_Attribute attr;
			attr.camelCase = pugi::as_wide(instructionName);

			auto sdfsf = instruction.child_value();

			if (instruction.first_child() != nullptr) 
			{
				auto childNodeName = instruction.first_child().name();
				if (strcmp(childNodeName, "") == 0)
				{
					attr.value = pugi::as_wide(instruction.child_value());
				}
				else
				{
					GetContents(instruction, &attr);
				}
			}
			else 
			{
				GetContents(instruction, &attr);
			}
			informationType->attribute.push_back(attr);
		}
	}
	return informationType;
}

S100DatasetGML::S100GML_Geometry*  S100GML_Dataset_PROC::GetGeometryContents(pugi::xml_node node)
{
	S100DatasetGML::S100GML_Geometry* geo = nullptr;
	for (auto instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		auto instructionName = instruction.name();
		if (!strcmp(instructionName, "S100:pointProperty"))
		{
			geo = new S100DatasetGML::S100GML_Point();
			GetGeometryContents((S100DatasetGML::S100GML_Point*)geo, instruction);
		}
		else if (!strcmp(instructionName, "S100:curveProperty"))
		{
			geo = new S100DatasetGML::S100GML_Curve();
			GetGeometryContents((S100DatasetGML::S100GML_Curve*)geo, instruction);
		}
		else if (!strcmp(instructionName, "S100:surfaceProperty"))
		{
			geo = new S100DatasetGML::S100GML_Surface();
			GetGeometryContents((S100DatasetGML::S100GML_Surface*)geo, instruction);
		}
	}
	return geo;
}

void S100GML_Dataset_PROC::GetGeometryContents(S100DatasetGML::S100GML_Point* geo, pugi::xml_node node)
{
	auto  pointNode = node.first_child();
	auto pointNodeName = pointNode.name();
	if (!strcmp(pointNodeName, "S100:Point"))
	{
		auto posNode = pointNode.first_child();
		auto posNodeName = posNode.name();
		if (!strcmp(posNodeName, "gml:pos"))
		{
			geo->pos = pugi::as_wide(posNode.child_value());
		}
	}
}
void S100GML_Dataset_PROC::GetGeometryContents(S100DatasetGML::S100GML_Curve* geo, pugi::xml_node node)
{
	if (!node)
	{
		return;
	}
	auto curveNode = node.first_child();
	auto curveNodeName = curveNode.name();

	if (!strcmp(curveNodeName, "gml:Curve"))
	{ 
		auto segmentNode = curveNode.first_child();
		auto posNodeName = segmentNode.name();
		
		if (!strcmp(posNodeName, "gml:segments"))
		{
			auto valueNode = segmentNode.first_child();
			auto value=valueNode.first_child().child_value();
			geo->posList = pugi::as_wide(value);
		}
	}
}
void S100GML_Dataset_PROC::GetGeometryContents(S100DatasetGML::S100GML_Surface* geo, pugi::xml_node node)
{
	pugi::xml_node surfaceNode = node.first_child();
	auto surfaceNodeName = surfaceNode.name();
	
	auto attribute = surfaceNode.first_attribute();
	if (attribute!=nullptr)
	{
		const char* value = attribute.value(); 

		if (!strcmp(value, "unknown"))
		{
			return;
		}
	}
	
	
	if (!strcmp(surfaceNodeName, "S100:Surface"))
	{ 
		auto pathNode = surfaceNode.first_child();
		auto pathNodeName = pathNode.name();
		if (!strcmp(pathNodeName, "gml:patches"))
		{
			auto PolygonPatchNode = pathNode.first_child();
			auto PolygonPatchNodeName = PolygonPatchNode.name();
			if (!strcmp(PolygonPatchNodeName, "gml:PolygonPatch"))
			{
				auto exteriorNode = PolygonPatchNode.first_child();
				auto exteriorNodeName = exteriorNode.name();

				if (!strcmp(exteriorNodeName, "gml:exterior"))
				{
					pugi::xml_node LinerRing = exteriorNode.first_child();
					pugi::xml_node Poslist = LinerRing.first_child();

					const char* dfsff = Poslist.child_value();
					const char* fsfsf=Poslist.name();

					std::wstring value = pugi::as_wide(Poslist.child_value());
					
					geo->posListOfExterior = value;   
					int i = 0;
				
				}
				else if (!strcmp(exteriorNodeName, "gml:interior"))
				{
					auto valueNode = exteriorNode.first_child();
					auto value = valueNode.first_child().child_value();
					geo->posListOfInteriorList.push_back(pugi::as_wide(value));
				}

			}
		}
	}


}

void S100GML_Dataset_PROC::GetContents(MSXML2::IXMLDOMNodePtr pNode, S100DatasetGML::S100GML_Attribute *parentAttr)
{
	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();
	for (int i = 0; i < pNodeList->Getlength(); i++)
	{
		MSXML2::IXMLDOMNodePtr pNode = pNodeList->Getitem(i);
		if (!pNode)
			continue;
		std::wstring nodeName = (LPCTSTR)pNode->GetnodeName();

		S100DatasetGML::S100GML_Attribute attr;
		attr.camelCase = nodeName.c_str();

		if (pNode->GetchildNodes()->Getlength() == 1)
		{
			MSXML2::IXMLDOMNodeListPtr tempNodeList = pNode->GetchildNodes();
			MSXML2::IXMLDOMNodePtr pTempNode = tempNodeList->Getitem(0);

			std::wstring tempNodeName = (LPCTSTR)pTempNode->GetnodeName();
			if (tempNodeName.compare(L"#text") == 0)
			{
				variant_t variant = pNode->Gettext();
				if (SysStringLen(variant.bstrVal) != 0)
					attr.value = (LPCTSTR)variant.bstrVal;
			}
			else
			{
				GetContents(pNode, &attr);
			}
		}
		else if (pNode->GetchildNodes()->Getlength() > 1)
		{
			GetContents(pNode, &attr);
		}
		else
		{
			variant_t variant = pNode->Gettext();
			if (SysStringLen(variant.bstrVal) != 0)
				attr.value = (LPCTSTR)variant.bstrVal;
		}
		parentAttr->childAttr.push_back(attr);
	}
}

void S100GML_Dataset_PROC::GetContents(pugi::xml_node node, S100DatasetGML::S100GML_Attribute *parentAttr)
{
	auto ndms = node.name();
	for (auto instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		if (instruction == nullptr)
		{
			continue;
		}

		S100DatasetGML::S100GML_Attribute attr;

		auto instructionName = instruction.name();
		attr.camelCase = pugi::as_wide(instructionName);

		auto SimpleValue = instruction.child_value();

		if (!strcmp(SimpleValue, ""))
		{
			GetContents(instruction, &attr);
		}
		else
		{
			attr.value = pugi::as_wide(SimpleValue);
		}
		parentAttr->childAttr.push_back(attr);
	}
}

