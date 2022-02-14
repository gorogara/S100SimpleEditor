// ExchangeSetDll.cpp : 해당 DLL의 초기화 루틴을 정의합니다. 

#include "stdafx.h"
#include "ExchangeSetXML.h"

#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace Dataset;

ExchangeSetXML::ExchangeSetXML()
{
}
ExchangeSetXML::~ExchangeSetXML()
{

}

void ExchangeSetXML::ChileNodeArrange(MSXML2::IXMLDOMNodeListPtr nodes, Tag* parent, Tag &root)
{
	MSXML2::IXMLDOMNodeListPtr pNodeSelect;
	for (int i = 0; i < nodes->Getlength(); i++)
	{
		pNodeSelect = nodes->Getitem(i)->GetchildNodes();
		MSXML2::IXMLDOMNodePtr pNode = nodes->Getitem(i);
		_bstr_t Name = pNode->nodeName;
		_bstr_t parentName = pNode->parentNode->nodeName;
		Tag* newTag = new Tag(parent); 
		if (strcmp(Name, "#text") == 0)
		{
			parent->Setvalue(std::wstring(pNode->text));
		}

		newTag->Setname(std::wstring(Name)); 
		if (strcmp(parentName, "#document") == 0)
		{ 
			for (int j = 0; j < pNode->attributes->Getlength(); j++)
			{ 
				std::wstring n = pNode->attributes->Getitem(j)->nodeName;
				std::wstring t = pNode->attributes->Getitem(j)->text;
				root.SetAttribute(n, t);
			}
			root.Setname(std::wstring(Name));
		}

		if (strcmp(Name, "#text") == 1 && strcmp(parentName, "#document") == 1)
		{ 
			for (int j = 0; j < pNode->attributes->Getlength(); j++)
			{
				std::wstring n = pNode->attributes->Getitem(j)->nodeName;
				std::wstring t = pNode->attributes->Getitem(j)->text;
				newTag->SetAttribute(n, t);
			} 
			parent->SetChild(newTag);
		}


		if (pNodeSelect->Getlength() > 0)
		{
			if (strcmp(parentName, "#document") == 0)
				ChileNodeArrange(pNodeSelect, &root, root);
			else
				ChileNodeArrange(pNodeSelect, newTag, root);
		}
	}
}

void ExchangeSetXML::ChileNodeArrange(pugi::xml_node node, Tag* parent, Tag &root)
{
	Tag* newTag = new Tag(parent);
	auto NodeName = node.name();
	if (!strcmp(NodeName, "S100XC:S100_ExchangeCatalogue")) 
	{ 
		for (auto attri = node.first_attribute(); attri; attri=attri.next_attribute())
		{
			std::wstring n = pugi::as_wide(attri.name());
			std::wstring t = pugi::as_wide(attri.value()); 
			root.SetAttribute(n, t);
		}

		root.Setname(pugi::as_wide(NodeName));
		for (auto instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
		{
			ChileNodeArrange(instruction, &root, root);
		}
	}
	else
	{ 
		if (!strcmp(NodeName,""))
		{
			parent->Setvalue(pugi::as_wide(node.value()));
			int i = 0;
		}
		else 
		{
			newTag->Setname(pugi::as_wide(NodeName));
			for (auto attri = node.first_attribute(); attri; attri = attri.next_attribute())
			{
				std::wstring n = pugi::as_wide(attri.name());
				std::wstring t = pugi::as_wide(attri.value());
				newTag->SetAttribute(n, t);
			}
			parent->SetChild(newTag);
		}
		

		for (auto instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
		{
			ChileNodeArrange(instruction, newTag, root);
		}
	}
}

void ExchangeSetXML::SetRoot(Tag value)
{
	m_root = value;
}

Tag ExchangeSetXML::GetRoot()
{
	return m_root;
}

void ExchangeSetXML::SetSearchData(list<Dataset::S100_DatasetDiscoveryMetadata> value)
{
	m_searchData = value;
}

list<Dataset::S100_DatasetDiscoveryMetadata> ExchangeSetXML::GetSearchData()
{
	return m_searchData;
}

void ExchangeSetXML::SetCatalogues(list<Dataset::S100_CatalogueMetadata> value)
{
	m_catalogues = value;
}

list<Dataset::S100_CatalogueMetadata> ExchangeSetXML::GetCatalogues()
{
	return m_catalogues;
}

void ExchangeSetXML::XmlOpen(std::wstring path)
{
	MSXML2::IXMLDOMDocument2Ptr pDoc;
	MSXML2::IXMLDOMNodeListPtr pNodeObject;

	pDoc.CreateInstance(__uuidof(DOMDocument)); 
	pDoc->load((_variant_t)path.c_str());

	pNodeObject = pDoc->selectNodes(L"S100XC:S100_ExchangeCatalogue");

	ChileNodeArrange(pNodeObject, NULL, m_root);

	m_searchData = SearchDataExtract(m_root);
}

void ExchangeSetXML::XmlOpenByPugi(std::wstring path)
{
	pugi::xml_document doc;
	auto result = doc.load_file(path.c_str()); 
	pugi::xml_node rootNode = doc.first_child();

	auto rootNodeName = rootNode.name();
	if (!strcmp(rootNodeName, "S100XC:S100_ExchangeCatalogue"))
	{
		ChileNodeArrange(rootNode, NULL, m_root);
	}
	m_searchData = SearchDataExtract(m_root);

	KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"ExchangeSet Read Clear", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::None);
}

list<Dataset::S100_DatasetDiscoveryMetadata> ExchangeSetXML::SearchDataExtract(Tag root)
{
	list<Dataset::S100_DatasetDiscoveryMetadata> result;
	if (root.GetChild().size() > 0)
	{

		for each (Tag* T in root.GetChild())
		{
			std::wstring str = T->Getname().c_str();

			if (!StrCmp(L"S100XC:datasetDiscoveryMetadata", str.c_str()))
			{
				for each(auto child in T->GetChild())
				{

					str = child->Getname().c_str();
					if (!StrCmp(L"S100XC:S100_DatasetDiscoveryMetadata", str.c_str()))
					{
						S100_DatasetDiscoveryMetadata s100; 
						s100.SetFileName(str.c_str());

						for each (Tag* C in child->GetChild())
						{
							str = C->Getname().c_str();
							if (!StrCmp(L"S100XC:fileName", str.c_str()))
								s100.SetFileName(C->Getvalue());
							else if (!StrCmp(L"S100XC:filePath", str.c_str()))
								s100.SetFilePath(C->Getvalue());
							else if (!StrCmp(L"S100XC:description", str.c_str()))
								s100.SetDescrition(C->Getvalue());
							else if (!StrCmp(L"S100XC:dataProtection", str.c_str()))
								s100.SetDataProtection(_ttoi(C->Getvalue().c_str()));
							else if (!StrCmp(L"S100XC:purpose", str.c_str()))
								s100.SetPurpose(C->Getvalue());
							else if (!StrCmp(L"S100XC:specificUsage", str.c_str()))
								s100.SetSpecificUsage(C->Getvalue());
							else if (!StrCmp(L"S100XC:editionNumber", str.c_str()))
								s100.SetEditionNumber(_ttoi(C->Getvalue().c_str()));
							else if (!StrCmp(L"S100XC:updateNumber", str.c_str()))
								s100.SetUpdateNumber(_ttoi(C->Getvalue().c_str()));
							else if (!StrCmp(L"S100XC:updateApplicationDate", str.c_str()))
								s100.SetUpdateApplicationDate(C->Getvalue());
							else if (!StrCmp(L"S100XC:issueDate", str.c_str()))
								s100.SetIssueDate(C->Getvalue());
							else if (!StrCmp(L"S100XC:productSpecification", str.c_str()))
							{
								for each (Tag* productSpecification in C->GetChild())
								{
									str = productSpecification->Getname().c_str();
									if (!StrCmp(L"S100XC:name", str.c_str()))
									{
										s100.GetProductSpecification().SetName(productSpecification->Getvalue());
									}
									else if (!StrCmp(L"S100XC:version", str.c_str()))
									{
										s100.GetProductSpecification().SetVersion(productSpecification->Getvalue());
									}
									if (!StrCmp(L"S100XC:date", str.c_str()))
									{
										s100.GetProductSpecification().SetData(productSpecification->Getvalue());
									}
								}
							}
							else if (!StrCmp(L"S100XC:producingAgency", str.c_str()))
							{
								for each (std::pair<std::wstring, std::wstring> attribute  in C->GetAttribute())
								{ 
									s100.GetProducingAgendataProtectioncy().GetAttribute().insert(unordered_map<std::wstring, std::wstring>::value_type(attribute.first, attribute.second));
								}
								for each (Tag* producingAgency in C->GetChild())
								{

									str = producingAgency->Getname().c_str();
									if (!StrCmp(L"gmd:organisationName", str.c_str()))
									{
										for each (Tag* CharacterString in producingAgency->GetChild())
										{
											str = CharacterString->Getname().c_str();
											if (!StrCmp(L"gco:CharacterString", str.c_str()))
												s100.GetProducingAgendataProtectioncy().GetOrganisagtionName().SetCharacterString(CharacterString->Getvalue()); 
										}
									}
									else if (!StrCmp(L"gmd:contactInfo", str.c_str()))
									{
										for each (Tag* CI_Contact in producingAgency->GetChild())
										{
											str = CI_Contact->Getname().c_str();
											if (!StrCmp(L"gmd:CI_Contact", str.c_str()))
												for each (Tag* phone in CI_Contact->GetChild())
												{
													str = phone->Getname().c_str();
													if (!StrCmp(L"gmd:phone", str.c_str()))
														for each (Tag* CI_Telephone in phone->GetChild())
														{
															str = CI_Telephone->Getname().c_str();
															if (!StrCmp(L"gmd:CI_Telephone", str.c_str()))
																for each (Tag* voice in CI_Telephone->GetChild())
																{
																	str = voice->Getname().c_str();
																	if (!StrCmp(L"gmd:voice", str.c_str()))
																		for each (Tag* CharacterString in voice->GetChild())
																		{
																			str = CharacterString->Getname().c_str();
																			if (!StrCmp(L"gco:CharacterString", str.c_str()))
																				s100.GetProducingAgendataProtectioncy().GetContactInfo().GetCi_Contact().GetPhone().GetCi_Telephone().GetVoice().SetCharacterString(CharacterString->Getvalue()); 
																		}
																}
														}
													else if (!StrCmp(L"gmd:address", str.c_str()))
														for each (Tag* CI_Address in phone->GetChild())
														{
															str = CI_Address->Getname().c_str();
															if (!StrCmp(L"gmd:CI_Address", str.c_str()))
																for each (Tag* deliveryPoint in CI_Address->GetChild())
																{
																	str = deliveryPoint->Getname().c_str();
																	if (!StrCmp(L"gmd:deliveryPoint", str.c_str()))
																		for each (Tag* CharacterString in deliveryPoint->GetChild())
																		{
																			str = CharacterString->Getname().c_str();
																			if (!StrCmp(L"gco:CharacterString", str.c_str()))
																				s100.GetProducingAgendataProtectioncy().GetContactInfo().GetCi_Contact().GetAddress().GetCi_TelePhone().GetDeliveryPoint().SetCharacterString(CharacterString->Getvalue()); 
																		}
																	else if (!StrCmp(L"gmd:city", str.c_str()))
																		for each (Tag* CharacterString in deliveryPoint->GetChild())
																		{
																			str = CharacterString->Getname().c_str();
																			if (!StrCmp(L"gco:CharacterString", str.c_str()))
																				s100.GetProducingAgendataProtectioncy().GetContactInfo().GetCi_Contact().GetAddress().GetCi_TelePhone().GetCity().SetCharacterString(CharacterString->Getvalue()); 
																		}
																	else if (!StrCmp(L"gmd:postalCode", str.c_str()))
																		for each (Tag* CharacterString in deliveryPoint->GetChild())
																		{
																			str = CharacterString->Getname().c_str();
																			if (!StrCmp(L"gco:CharacterString", str.c_str()))
																				s100.GetProducingAgendataProtectioncy().GetContactInfo().GetCi_Contact().GetAddress().GetCi_TelePhone().GetPostalCode().SetCharacterString(CharacterString->Getvalue()); 
																		}
																}
														}
												}
										}
									}
									else if (!StrCmp(L"gmd:role", str.c_str()))
									{
										for each (Tag* CI_RoleCode in producingAgency->GetChild())
										{
											str = CI_RoleCode->Getname().c_str();
											if (!StrCmp(L"gmd:CI_RoleCode", str.c_str()))
											{
												for each (std::pair<std::wstring, std::wstring> attribute  in CI_RoleCode->GetAttribute())
												{
													s100.GetProducingAgendataProtectioncy().GetRole().GetCi_roleCode().GetAttribute().insert(unordered_map<std::wstring, std::wstring>::value_type(attribute.first, attribute.second)); 
												}
											}
										}
									}
								}
							}
							else if (!StrCmp(L"S100XC:optimumDisplayScale", str.c_str()))
								s100.SetOptimumDisplayScale(_ttoi(C->Getvalue().c_str())); 
							else if (!StrCmp(L"S100XC:maximumDisplayScale", str.c_str()))
								s100.SetMaximumDisplayScale(_ttoi(C->Getvalue().c_str())); 
							else if (!StrCmp(L"S100XC:minimumDisplayScale", str.c_str()))
								s100.SetMinimumDisplayScale(_ttoi(C->Getvalue().c_str())); 
							else if (!StrCmp(L"S100XC:horizontalDatumReference", str.c_str()))
								s100.SetHorizontalDatumReference(C->Getvalue()); 
							else if (!StrCmp(L"S100XC:horizontalDatumValue", str.c_str()))
								s100.SetHorizontalDatumValue(_ttoi(C->Getvalue().c_str()));
							else if (!StrCmp(L"S100XC:verticalDatum", str.c_str()))
								s100.SetVerticalDatum(C->Getvalue());
							else if (!StrCmp(L"S100XC:soundingDatum", str.c_str()))
								s100.SetSoundingDatum(C->Getvalue());
							else if (!StrCmp(L"S100XC:dataType", str.c_str()))
								s100.SetDataType(C->Getvalue());
							else if (!StrCmp(L"S100XC:dataTypeVersion", str.c_str()))
								s100.SetDataTypeVersion(C->Getvalue());
							else if (!StrCmp(L"S100XC:dataCoverage", str.c_str())) 
							{
								for each (auto child in C->GetChild())
								{
									str = child->Getname(); 
									if (!StrCmp(L"S100XC:boundingBox", str.c_str()))
									{
										for each (std::pair<std::wstring, std::wstring> attribute  in C->GetAttribute())
										{
											s100.GetBoundingBox().GetAttribute().insert(unordered_map<std::wstring, std::wstring>::value_type(attribute.first, attribute.second)); 
										}
										for each (Tag* boundingBox in child->GetChild())
										{
											str = boundingBox->Getname().c_str();
											if (!StrCmp(L"gex:westBoundLongitude", str.c_str()))
											{
												for each (Tag* decimal in boundingBox->GetChild())
												{
													str = decimal->Getname().c_str();
													if (!StrCmp(L"gco:Decimal", str.c_str()))
														s100.GetBoundingBox().GetWestBoundLongitude().SetDecimal(_wtof(decimal->Getvalue().c_str())); 
												}
											}
											else if (!StrCmp(L"gex:eastBoundLongitude", str.c_str()))
											{
												for each (Tag* decimal in boundingBox->GetChild())
												{
													str = decimal->Getname().c_str();
													if (!StrCmp(L"gco:Decimal", str.c_str()))
														s100.GetBoundingBox().GetEastBoundLongitude().SetDecimal(_wtof(decimal->Getvalue().c_str()));
												}
											}
											else if (!StrCmp(L"gex:southBoundLatitude", str.c_str()))
											{
												for each (Tag* decimal in boundingBox->GetChild())
												{
													str = decimal->Getname().c_str();
													if (!StrCmp(L"gco:Decimal", str.c_str()))
														s100.GetBoundingBox().GetSouthBoundLongitude().SetDecimal(_wtof(decimal->Getvalue().c_str()));
												}
											}
											else if (!StrCmp(L"gex:northBoundLatitude", str.c_str()))
											{
												for each (Tag* decimal in boundingBox->GetChild())
												{
													str = decimal->Getname().c_str();
													if (!StrCmp(L"gco:Decimal", str.c_str()))
														s100.GetBoundingBox().GetNorthBoundLongitude().SetDecimal(_wtof(decimal->Getvalue().c_str()));
												}
											}
										}
										OutputDebugString(L"");

									}
									else if (!StrCmp(L"S100XC:optimumDisplayScale", str.c_str()))
									{ 
									}
								}
							}
							else if (!StrCmp(L"S100XC:comment", str.c_str()))
								s100.SetComment(C->Getvalue());
							else if (!StrCmp(L"S100XC:checkSum", str.c_str()))
								s100.SetCheckSum(C->Getvalue());
							else if (!StrCmp(L"S100XC:S100_19115DatasetMetadata", str.c_str()))
							{
								for each (Tag* FileName in C->GetChild())
								{
									str = FileName->Getname().c_str();
									if (!StrCmp(L"gmx:FileName", str.c_str()))
									{
										S100_19115DatasetMetadata temp;
										temp.GetfileName().Setvalue(FileName->Getvalue().c_str());
										s100.GetS100_19115DatasetMetadata().push_back(temp); 
									}
								}
							}
							else if (!StrCmp(L"S100XC:S100_SupportFileDiscoveryMetadata", str.c_str()))
							{
								S100_SupportFileDiscoveryMetadata temp;
								for each (Tag* SupportFileDiscoveryMetadata in C->GetChild())
								{
									str = SupportFileDiscoveryMetadata->Getname().c_str();
									if (!StrCmp(L"S100XC:fileName", str.c_str()))
									{
										temp.SetFileName(SupportFileDiscoveryMetadata->Getvalue());
									}
									else if (!StrCmp(L"S100XC:fileLocation", str.c_str()))
									{
										temp.SetFileLoaction(SupportFileDiscoveryMetadata->Getvalue());
									}
									else if (!StrCmp(L"S100XC:purpose", str.c_str()))
									{
										temp.SetPurPose(SupportFileDiscoveryMetadata->Getvalue());
									}
									else if (!StrCmp(L"S100XC:editionNumber", str.c_str()))
									{
										temp.SetEditionNumber(SupportFileDiscoveryMetadata->Getvalue());
									}
									else if (!StrCmp(L"S100XC:issueDate", str.c_str()))
									{
										temp.SetIssueDate(SupportFileDiscoveryMetadata->Getvalue());
									}
									else if (!StrCmp(L"S100XC:dataType", str.c_str()))
									{
										temp.SetDataType(SupportFileDiscoveryMetadata->Getvalue());
									}
									else if (!StrCmp(L"S100XC:comment", str.c_str()))
									{
										temp.SetComment(SupportFileDiscoveryMetadata->Getvalue());
									}
									else if (!StrCmp(L"S100XC:checkSum", str.c_str()))
									{
										temp.SetCheckSum(SupportFileDiscoveryMetadata->Getvalue());
									}
								}
								s100.GetS100_SupportFileDiscoveryMetadata().push_back(temp); 
							}
						}
						result.push_back(s100);

					}
				}
			}

			if (!StrCmp(L"S100XC:S100_CatalogueMetadata", str.c_str()))
			{
				S100_CatalogueMetadata s100catalog; 

				for each (Tag* C in T->GetChild())
				{
					str = C->Getname().c_str();
					if (!StrCmp(L"S100XC:catalogType", str.c_str()))
						s100catalog.SetCatalogType(C->Getvalue());
					else if (!StrCmp(L"S100XC:name", str.c_str()))
						s100catalog.SetName(C->Getvalue());
					else if (!StrCmp(L"S100XC:fileName", str.c_str()))
						s100catalog.SetFileName(C->Getvalue());
					else if (!StrCmp(L"S100XC:fileLocation", str.c_str()))
						s100catalog.SetFileLocation(C->Getvalue());
					else if (!StrCmp(L"S100XC:purpose", str.c_str()))
						s100catalog.SetPurpose(C->Getvalue()); 
					else if (!StrCmp(L"S100XC:editionNumber", str.c_str()))
						s100catalog.SetEditionNumber(C->Getvalue().c_str()); 
					else if (!StrCmp(L"S100XC:issueDate", str.c_str()))
						s100catalog.SetIssueDate(C->Getvalue());
					else if (!StrCmp(L"S100XC:productSpecification", str.c_str()))
					{
						for each (Tag* productSpecification in C->GetChild())
						{
							str = productSpecification->Getname().c_str();
							if (!StrCmp(L"S100XC:name", str.c_str()))
							{
								s100catalog.GetProductSpecification().SetName(productSpecification->Getvalue()); 
							}
							else if (!StrCmp(L"S100XC:version", str.c_str()))
							{
								s100catalog.GetProductSpecification().SetVersion(productSpecification->Getvalue());
							}
							if (!StrCmp(L"S100XC:date", str.c_str()))
							{
								s100catalog.GetProductSpecification().SetData(productSpecification->Getvalue());
							}
						}
					}
					else if (!StrCmp(L"S100XC:dataType", str.c_str()))
						s100catalog.SetDataType(C->Getvalue()); 
					else if (!StrCmp(L"S100XC:comment", str.c_str())) 
						s100catalog.SetComment(C->Getvalue().c_str());
					else if (!StrCmp(L"S100XC:checkSum", str.c_str()))
						s100catalog.SetCheckSum(C->Getvalue());
				}
				m_catalogues.push_back(s100catalog);
			}
		}
	}
	return result;
}
  
list<Dataset::S100_DatasetDiscoveryMetadata> ExchangeSetXML::GetAllDataset()
{
	list<S100_DatasetDiscoveryMetadata> result;
	for each (S100_DatasetDiscoveryMetadata s100 in m_searchData)
	{
		result.push_back(s100);
	}
	return result;
}

list<S100_DatasetDiscoveryMetadata> ExchangeSetXML::SearchForFilename(std::wstring filename)
{
	list<S100_DatasetDiscoveryMetadata> result;
	for each (S100_DatasetDiscoveryMetadata s100 in m_searchData)
	{
		if (!StrCmp(filename.c_str(), s100.GetFileName().c_str()))
		{
			result.push_back(s100);
		}
	}
	return result;
}

list<S100_DatasetDiscoveryMetadata> ExchangeSetXML::SearchForSpecificUsage(std::wstring specificUsage)
{
	list<S100_DatasetDiscoveryMetadata> result;
	for each (S100_DatasetDiscoveryMetadata s100 in m_searchData)
	{
		if (!StrCmp(specificUsage.c_str(), s100.GetSpecificUsage().c_str()))
		{
			result.push_back(s100);
		}
	}
	return result;
}

list<ScaleSearchFormat> ExchangeSetXML::SearchForScale(int Scale)
{
	list<ScaleSearchFormat> result;
	for each (S100_DatasetDiscoveryMetadata s100 in m_searchData)
	{
		ScaleSearchFormat temp;
		temp.SetData(s100);

		if (s100.GetMaximumDisplayScale() > Scale)
		{
			temp.SetSearchStateForScale(ScaleState::ScaleForSmall);
		}
		else if (s100.GetMinimumDisplayScale() < Scale)
		{
			temp.SetSearchStateForScale(ScaleState::ScaleForLarge);
		}
		else
		{
			temp.SetSearchStateForScale(ScaleState::SearchScope);
		}
		result.push_back(temp);
	}
	return result;
}    

std::wstring ExchangeSetXML::GetFeatureCatalog() 
{
	for each (S100_CatalogueMetadata s100 in m_catalogues)
	{
		if (s100.GetCatalogType().compare(L"Feature Catalog") == 0)
		{
			return s100.GetProductSpecification().GetName();
		}
	}

	return L"";
}

std::wstring ExchangeSetXML::GetPortrayalCatalog()
{
	for each (S100_CatalogueMetadata s100 in m_catalogues)
	{
		if (s100.GetCatalogType().compare(L"Portrayal Catalog") == 0)
		{
			return s100.GetProductSpecification().GetName();
		}
	}
	return L"";
}