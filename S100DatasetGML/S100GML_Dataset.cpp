#include "stdafx.h"
#include "S100DatasetGML.h"
#include "S100GML_Dataset.h"
#include "S100GML_FeatureType.h"
#include "S100GML_InformationType.h"
#include "S100GML_Dataset_PROC.h"

#include "GISLibrary\\S101Cell.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\R_InformationRecord.h"

#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

#include <algorithm>

#import <msxml4.dll>

namespace S100DatasetGML
{
	S100GML_Dataset::S100GML_Dataset()
	{
	}

	S100GML_Dataset::~S100GML_Dataset()
	{
		for (auto i = features.begin(); i != features.end(); i++)
		{
			delete i->second;
		}
		for (auto i = informations.begin(); i != informations.end(); i++)
		{
			delete i->second;
		}
	}  

	void S100GML_Dataset::SetFeatureToFeatureAssociation(S101Cell* cell, R_FeatureRecord* orgFr, R_FeatureRecord* objFr)
	{

	}
	void S100GML_Dataset::SetFeatureToInformationAssociation(S101Cell* cell, R_FeatureRecord* orgFr, R_InformationRecord* objIr)
	{

	}
	void S100GML_Dataset::SetInformationToInformationAssociation(S101Cell* cell, R_InformationRecord* orgIr, R_InformationRecord* objIr)
	{

	}

	void S100GML_DELETE(S100GML_Dataset* dataset)
	{
		delete dataset;
	}

	S100GML_Dataset* S100GML_OPEN(std::wstring filepath, Catalog* catalog)
	{
		S100GML_Dataset_PROC proc;
		proc.SetCatalog(catalog);
		MSXML2::IXMLDOMDocument2Ptr g_pXMLDoc; 
		MSXML2::IXMLDOMNodeListPtr pNodeList; 

		S100GML_Dataset* dataset = new S100GML_Dataset();
		if (filepath.size() > 0)
		{
			g_pXMLDoc.CreateInstance(__uuidof(DOMDocument));
			g_pXMLDoc->async = VARIANT_FALSE;

			g_pXMLDoc->validateOnParse = VARIANT_TRUE;
			g_pXMLDoc->resolveExternals = VARIANT_TRUE; 
			if (g_pXMLDoc->load((_variant_t)filepath.c_str()))
			{
				pNodeList = g_pXMLDoc->GetchildNodes();

				for (int k = 0; k < pNodeList->Getlength(); k++)
				{
					MSXML2::IXMLDOMNodePtr pNodePtr = pNodeList->Getitem(k);
					std::wstring nodeName = (LPCTSTR)pNodePtr->GetnodeName();
					std::transform(nodeName.begin(), nodeName.end(), nodeName.begin(), tolower);
					if (nodeName.find(L"dataset") == std::wstring::npos)
					{
						continue;
					}

					MSXML2::IXMLDOMNodeListPtr pDSNodeList = pNodePtr->GetchildNodes();
					for (int i = 0; i < pDSNodeList->Getlength(); i++)
					{
						MSXML2::IXMLDOMNodePtr pDSNode = pDSNodeList->Getitem(i);
						std::wstring dsNodeName = (LPCTSTR)pDSNode->GetnodeName();

						if (dsNodeName.compare(L"imember") == 0)
						{
							MSXML2::IXMLDOMNodeListPtr pObjNodeList = pDSNode->GetchildNodes();
							for (int i = 0; i < pObjNodeList->Getlength(); i++)
							{
								MSXML2::IXMLDOMNodePtr pObjNodePtr = pObjNodeList->Getitem(i);
								std::wstring nodeName = (LPCTSTR)pObjNodePtr->GetnodeName();

								if (nodeName.compare(L"#comment") == 0)
								{
									continue;
								}
								S100GML_InformationType* data = proc.GetInformationContents(pObjNodePtr);
								dataset->informations.insert(std::unordered_map<std::wstring, S100GML_InformationType*>::value_type(data->id, data));
							}
						}
						else if (dsNodeName.compare(L"member") == 0)
						{
							MSXML2::IXMLDOMNodeListPtr pObjNodeList = pDSNode->GetchildNodes();
							for (int i = 0; i < pObjNodeList->Getlength(); i++)
							{
								MSXML2::IXMLDOMNodePtr pObjNodePtr = pObjNodeList->Getitem(i);
								std::wstring nodeName = (LPCTSTR)pObjNodePtr->GetnodeName();

								if (nodeName.compare(L"#comment") == 0)
								{
									continue;
								}

								S100GML_FeatureType* data = proc.GetFeatureContents(pObjNodePtr);
								dataset->features.insert(std::unordered_map<std::wstring, S100GML_FeatureType*>::value_type(data->id, data));
							}
						}
						else
						{
							S100DatasetGML::S100GML_Attribute attr;
							attr.camelCase = dsNodeName.c_str();


							auto what = pDSNode->GetchildNodes()->Getlength();
							if (pDSNode->GetchildNodes()->Getlength() == 0)
							{
								variant_t variant = pDSNode->Gettext();

								if (SysStringLen(variant.bstrVal) != 0)
								{
									attr.value = (LPCTSTR)variant.bstrVal;
								}
							}

							else if (pDSNode->GetchildNodes()->Getlength() == 1)
							{
								MSXML2::IXMLDOMNodeListPtr tempNodeList = pDSNode->GetchildNodes();
								MSXML2::IXMLDOMNodePtr pTempNode = tempNodeList->Getitem(0);

								std::wstring tempNodeName = (LPCTSTR)pTempNode->GetnodeName();
								if (tempNodeName.compare(L"#text") == 0)
								{
									variant_t variant = pDSNode->Gettext();
									if (SysStringLen(variant.bstrVal) != 0)
									{
										attr.value = (LPCTSTR)variant.bstrVal;
									}
								}
								else
								{
									proc.GetContents(pDSNode, &attr);
								}
							}
							else
							{
								proc.GetContents(pDSNode, &attr);
							}
							dataset->attribute.insert(std::unordered_map<std::wstring, S100GML_Attribute>::value_type(attr.camelCase, attr));
						}
					}
				}
			}
		}
		return dataset;
	}

	S100GML_Dataset* S100GML_OPENByPugi(std::wstring filepath, Catalog* catalog)
	{
		S100GML_Dataset_PROC proc;
		proc.SetCatalog(catalog);
		S100GML_Dataset* dataset = new S100GML_Dataset();

		if (filepath.size() <= 0)
		{
			return nullptr;
		}

		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(filepath.c_str()); 
		pugi::xml_node  datasetNode = doc.first_child();  

		std::wstring DataName = pugi::as_wide(datasetNode.name());
		dataset->gml_namespace.insert({ DataName, DataName });

		for (auto namespaceNode = datasetNode.first_attribute(); namespaceNode; namespaceNode = namespaceNode.next_attribute())
		{
			const pugi::char_t* namespaceNodeName = namespaceNode.name();
			const pugi::char_t* namespaceNodeValue = namespaceNode.value();
			dataset->gml_namespace.insert({ pugi::as_wide(namespaceNodeName),pugi::as_wide(namespaceNodeValue) });
		}

		for (pugi::xml_node instruction = datasetNode.first_child(); instruction; instruction = instruction.next_sibling())
		{
			auto instuctionName = instruction.name();

			if (!strcmp(instuctionName, "imember"))
			{
				auto node = instruction.first_child();
				S100GML_InformationType* data = proc.GetInformationContents(node);
				dataset->informations.insert(std::unordered_map<std::wstring, S100GML_InformationType*>::value_type(data->id, data));
			}
			else if (!strcmp(instuctionName, "member"))
			{
				auto node = instruction.first_child();
				S100GML_FeatureType* data = proc.GetFeatureContents(node);
				dataset->features.insert(std::unordered_map<std::wstring, S100GML_FeatureType*>::value_type(data->id, data));
			}
			else
			{
				S100DatasetGML::S100GML_Attribute attr;
				attr.camelCase = pugi::as_wide(instuctionName);

				if (strcmp(instruction.child_value(), "")) 
				{
					attr.value = pugi::as_wide(instruction.value());
				}

				auto firstchild = instruction.first_child();
				if (firstchild != nullptr)
				{
					auto firstchiildname = firstchild.name();
					if (!strcmp(firstchiildname, "")) 
					{
						attr.value = pugi::as_wide(firstchild.value());
					}
					else
					{
						proc.GetContents(instruction, &attr);
					}
				}
				else
				{ 
					proc.GetContents(instruction, &attr);
				}
				dataset->attribute.insert(std::unordered_map<std::wstring, S100GML_Attribute>::value_type(attr.camelCase, attr));
			}
		}

		return dataset;
	}
}