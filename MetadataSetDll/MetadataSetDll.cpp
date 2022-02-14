// S100ExchangeSet.cpp : 해당 DLL의 초기화 루틴을 정의합니다. 

#include "stdafx.h"
#include "MetadataSetDll.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


namespace gco
{
	NilReason::NilReason(){}
	ObjectIdentification::ObjectIdentification(){}
	AbstractObject_Type::AbstractObject_Type(){}
	ObjectReference::ObjectReference(){}
	ObjectReference_PropertyType::ObjectReference_PropertyType(){}
	CodeListValue_Type::CodeListValue_Type(){}
	TypeName::TypeName()
	{
		documentation = L"A TypeName is a LocalName that references either a recordType or object type in some form of schema. The stored value 'aName' is the returned value for the 'aName()' operation. This is the types name. - For parsing from types (or objects) the parsible name normally uses a '.' navigation separator, so that it is of the form [class].[member].[memberOfMember]. ...)";
	}
	TypeName_PropertyType::TypeName_PropertyType(){}
	MemberName::MemberName()
	{
		documentation = L"A MemberName is a LocalName that references either an attribute slot in a record or recordType or an attribute, operation, or association role in an object instance or type description in some form of schema. The stored value 'aName' is the returned value for the 'aName()' operation.";
	}
	MemberName_PropertyType::MemberName_PropertyType(){}
	Multiplicity::Multiplicity()
	{
		documentation = L"Use to represent the possible cardinality of a relation. Represented by a set of simple multiplicity ranges.";
	}
	Multiplicity_PropertyType::Multiplicity_PropertyType(){}
	MultiplicityRange::MultiplicityRange()
	{
		documentation = L"A component of a multiplicity, consisting of an non-negative lower bound, and a potentially infinite upper bound.";
	}
	MultiplicityRange_PropertyType::MultiplicityRange_PropertyType(){}
	Measure_PropertyType::Measure_PropertyType(){}
	Length_PropertyType::Length_PropertyType(){}
	Angle_PropertyType::Angle_PropertyType(){}
	Scale_PropertyType::Scale_PropertyType(){}
	Distance_PropertyType::Distance_PropertyType(){}
	CharacterString_PropertyType::CharacterString_PropertyType(){}
	Boolean_PropertyType::Boolean_PropertyType(){}
	GenericName_PropertyType::GenericName_PropertyType(){}
	LocalName_PropertyType::LocalName_PropertyType(){}
	ScopedName_PropertyType::ScopedName_PropertyType(){}
	UomAngle_PropertyType::UomAngle_PropertyType(){}
	UomLength_PropertyType::UomLength_PropertyType(){}
	UomScale_PropertyType::UomScale_PropertyType(){}
	UnitOfMeasure_PropertyType::UnitOfMeasure_PropertyType(){}
	UomArea_PropertyType::UomArea_PropertyType(){}
	UomVelocity_PropertyType::UomVelocity_PropertyType(){}
	UomTime_PropertyType::UomTime_PropertyType(){}
	UomVolume_PropertyType::UomVolume_PropertyType(){}
	Date::Date(){}
	Date_PropertyType::Date_PropertyType(){}
	DateTime::DateTime(){}
	DateTime_PropertyType::DateTime_PropertyType(){}
	Decimal::Decimal(){}
	Decimal_PropertyType::Decimal_PropertyType(){}
	Binary::Binary(){}
	Binary_PropertyType::Binary_PropertyType(){}
	Real::Real(){}
	Real_PropertyType::Real_PropertyType(){}
	Integer::Integer(){}
	Integer_PropertyType::Integer_PropertyType(){}
	UnlimitedInteger::UnlimitedInteger(){}
	UnlimitedInteger_PropertyType::UnlimitedInteger_PropertyType(){}
	Record::Record(){}
	Record_PropertyType::Record_PropertyType(){}
	RecordType::RecordType(){}
	RecordType_PropertyType::RecordType_PropertyType(){}
}
namespace gts
{
	TM_PeriodDuration::TM_PeriodDuration(){}
	TM_PeriodDuration_PropertyType::TM_PeriodDuration_PropertyType(){}
}
namespace gss
{
	GM_Point_PropertyType::GM_Point_PropertyType(){}
	GM_Object_PropertyType::GM_Object_PropertyType(){}

}
namespace gsr
{
	SC_CRS_PropertyType::SC_CRS_PropertyType(){}
}
namespace gmd
{
	MD_ApplicationSchemaInformation::MD_ApplicationSchemaInformation()
	{
		documentation = L"Information about the application schema used to build the dataset";
	}
	MD_ApplicationSchemaInformation_PropertyType::MD_ApplicationSchemaInformation_PropertyType(){}
	URL_PropertyType::URL_PropertyType(){}
	CI_RoleCode_PropertyType::CI_RoleCode_PropertyType(){}
	CI_PresentationFormCode_PropertyType::CI_PresentationFormCode_PropertyType(){}
	CI_OnLineFunctionCode_PropertyType::CI_OnLineFunctionCode_PropertyType(){}
	CI_Series::CI_Series(){}
	CI_Series_PropertyType::CI_Series_PropertyType(){}
	CI_Telephone::CI_Telephone()
	{
		documentation = L"Telephone numbers for contacting the responsible individual or organisation";
	}
	CI_Telephone_PropertyType::CI_Telephone_PropertyType(){}
	CI_Address::CI_Address()
	{
		documentation = L"Location of the responsible individual or organisation";
	}
	CI_Address_PropertyType::CI_Address_PropertyType(){}
	CI_Contact::CI_Contact()
	{
		documentation = L"Information required enabling contact with the responsible person and/or organisation";
	}
	CI_Contact_PropertyType::CI_Contact_PropertyType(){}
	CI_Date::CI_Date(){}
	CI_DateTypeCode_PropertyType::CI_DateTypeCode_PropertyType(){}
	CI_Citation::CI_Citation()
	{
		documentation = L"Standardized resource reference";
	}
	CI_Citation_PropertyType::CI_Citation_PropertyType(){}
	CI_OnlineResource::CI_OnlineResource()
	{
		documentation = L"Information about online sources from which the dataset, specification, or community profile name and extended metadata elements can be obtained.";
	}
	CI_OnlineResource_PropertyType::CI_OnlineResource_PropertyType(){}
	CI_ResponsibleParty::CI_ResponsibleParty()
	{
		documentation = L"Identification of, and means of communication with, person(s) and organisations associated with the dataset";
	}
	CI_ResponsibleParty_PropertyType::CI_ResponsibleParty_PropertyType(){}
	MD_ClassificationCode_PropertyType::MD_ClassificationCode_PropertyType(){}
	MD_RestrictionCode_PropertyType::MD_RestrictionCode_PropertyType(){}
	MD_Constraints::MD_Constraints()
	{
		documentation = L"Restrictions on the access and use of a dataset or metadata";
	}
	MD_Constraints_PropertyType::MD_Constraints_PropertyType(){}
	MD_LegalConstraints::MD_LegalConstraints()
	{
		documentation = L"Restrictions and legal prerequisites for accessing and using the dataset.";
	}
	MD_LegalConstraints_PropertyType::MD_LegalConstraints_PropertyType(){}
	MD_SecurityConstraints::MD_SecurityConstraints()
	{
		documentation = L"Restrictions and legal prerequisites for accessing and using the dataset.";
	}
	MD_SecurityConstraints_PropertyType::MD_SecurityConstraints_PropertyType(){}
	RS_Identifier::RS_Identifier(){}
	RS_Identifier_PropertyType::RS_Identifier_PropertyType(){}
	MD_ReferenceSystem::MD_ReferenceSystem(){}
	MD_ReferenceSystem_PropertyType::MD_ReferenceSystem_PropertyType(){}
	MD_Identifier::MD_Identifier(){}
	MD_Identifier_PropertyType::MD_Identifier_PropertyType(){}
	AbstractRS_ReferenceSystem::AbstractRS_ReferenceSystem()
	{
		documentation = L"Description of the spatial and temporal reference systems used in the dataset";
	}
	RS_ReferenceSystem_PropertyType::RS_ReferenceSystem_PropertyType(){}
	MD_CoverageContentTypeCode_PropertyType::MD_CoverageContentTypeCode_PropertyType(){}
	MD_ImagingConditionCode_PropertyType::MD_ImagingConditionCode_PropertyType(){}
	MD_FeatureCatalogueDescription::MD_FeatureCatalogueDescription()
	{
		documentation = L"Information identifing the feature catalogue";
	}
	MD_FeatureCatalogueDescription_PropertyType::MD_FeatureCatalogueDescription_PropertyType(){}
	MD_CoverageDescription::MD_CoverageDescription()
	{
		documentation = L"Information about the domain of the raster cell";
	}
	MD_CoverageDescription_PropertyType::MD_CoverageDescription_PropertyType(){}
	MD_ImageDescription::MD_ImageDescription()
	{
		documentation = L"Information about an image's suitability for use";
	}
	MD_ImageDescription_PropertyType::MD_ImageDescription_PropertyType(){}
	AbstractMD_ContentInformation::AbstractMD_ContentInformation(){}
	MD_ContentInformation_PropertyType::MD_ContentInformation_PropertyType(){}
	MD_RangeDimension::MD_RangeDimension()
	{
		documentation = L"Set of adjacent wavelengths in the electro-magnetic spectrum with a common characteristic, such as the visible band";
	}
	MD_RangeDimension_PropertyType::MD_RangeDimension_PropertyType(){}
	MD_Band::MD_Band()
	{
		documentation = L"Set of adjacent wavelengths in the electro-magnetic spectrum with a common characteristic, such as the visible band";
	}
	MD_Band_PropertyType::MD_Band_PropertyType(){}
	DQ_EvaluationMethodTypeCode_PropertyType::DQ_EvaluationMethodTypeCode_PropertyType(){}
	LI_ProcessStep::LI_ProcessStep(){}
	LI_ProcessStep_PropertyType::LI_ProcessStep_PropertyType(){}
	LI_Source::LI_Source(){}
	LI_Source_PropertyType::LI_Source_PropertyType(){}
	LI_Lineage::LI_Lineage(){}
	LI_Lineage_PropertyType::LI_Lineage_PropertyType(){}
	DQ_ConformanceResult::DQ_ConformanceResult()
	{
		documentation = L"quantitative_result from Quality Procedures - - renamed to remove implied use limitiation.";
	}
	DQ_ConformanceResult_PropertyType::DQ_ConformanceResult_PropertyType(){}
	DQ_QuantitativeResult::DQ_QuantitativeResult(){}
	DQ_QuantitativeResult_PropertyType::DQ_QuantitativeResult_PropertyType(){}
	AbstractDQ_Result::AbstractDQ_Result(){}
	DQ_Result_PropertyType::DQ_Result_PropertyType(){}
	DQ_TemporalValidity::DQ_TemporalValidity(){}
	DQ_TemporalValidity_PropertyType::DQ_TemporalValidity_PropertyType(){}
	DQ_TemporalConsistency::DQ_TemporalConsistency(){}
	DQ_TemporalConsistency_PropertyType::DQ_TemporalConsistency_PropertyType(){}
	DQ_AccuracyOfATimeMeasurement::DQ_AccuracyOfATimeMeasurement(){}
	DQ_AccuracyOfATimeMeasurement_PropertyType::DQ_AccuracyOfATimeMeasurement_PropertyType(){}
	DQ_QuantitativeAttributeAccuracy::DQ_QuantitativeAttributeAccuracy(){}
	DQ_QuantitativeAttributeAccuracy_PropertyType::DQ_QuantitativeAttributeAccuracy_PropertyType(){}
	DQ_NonQuantitativeAttributeAccuracy::DQ_NonQuantitativeAttributeAccuracy(){}
	DQ_NonQuantitativeAttributeAccuracy_PropertyType::DQ_NonQuantitativeAttributeAccuracy_PropertyType(){}
	DQ_ThematicClassificationCorrectness::DQ_ThematicClassificationCorrectness(){}
	DQ_ThematicClassificationCorrectness_PropertyType::DQ_ThematicClassificationCorrectness_PropertyType(){}
	DQ_RelativeInternalPositionalAccuracy::DQ_RelativeInternalPositionalAccuracy(){}
	DQ_RelativeInternalPositionalAccuracy_PropertyType::DQ_RelativeInternalPositionalAccuracy_PropertyType(){}
	DQ_GriddedDataPositionalAccuracy::DQ_GriddedDataPositionalAccuracy(){}
	DQ_GriddedDataPositionalAccuracy_PropertyType::DQ_GriddedDataPositionalAccuracy_PropertyType(){}
	DQ_AbsoluteExternalPositionalAccuracy::DQ_AbsoluteExternalPositionalAccuracy(){}
	DQ_AbsoluteExternalPositionalAccuracy_PropertyType::DQ_AbsoluteExternalPositionalAccuracy_PropertyType(){}
	DQ_TopologicalConsistency::DQ_TopologicalConsistency(){}
	DQ_TopologicalConsistency_PropertyType::DQ_TopologicalConsistency_PropertyType(){}
	DQ_FormatConsistency::DQ_FormatConsistency(){}
	DQ_FormatConsistency_PropertyType::DQ_FormatConsistency_PropertyType(){}
	DQ_DomainConsistency::DQ_DomainConsistency(){}
	DQ_DomainConsistency_PropertyType::DQ_DomainConsistency_PropertyType(){}
	DQ_ConceptualConsistency::DQ_ConceptualConsistency(){}
	DQ_ConceptualConsistency_PropertyType::DQ_ConceptualConsistency_PropertyType(){}
	DQ_CompletenessOmission::DQ_CompletenessOmission(){}
	DQ_CompletenessOmission_PropertyType::DQ_CompletenessOmission_PropertyType(){}
	DQ_CompletenessCommission::DQ_CompletenessCommission(){}
	DQ_CompletenessCommission_PropertyType::DQ_CompletenessCommission_PropertyType(){}
	AbstractDQ_TemporalAccuracy::AbstractDQ_TemporalAccuracy(){}
	DQ_TemporalAccuracy_PropertyType::DQ_TemporalAccuracy_PropertyType(){}
	AbstractDQ_ThematicAccuracy::AbstractDQ_ThematicAccuracy(){}
	DQ_ThematicAccuracy_PropertyType::DQ_ThematicAccuracy_PropertyType(){}
	AbstractDQ_PositionalAccuracy::AbstractDQ_PositionalAccuracy(){}
	DQ_PositionalAccuracy_PropertyType::DQ_PositionalAccuracy_PropertyType(){}
	AbstractDQ_LogicalConsistency::AbstractDQ_LogicalConsistency(){}
	DQ_LogicalConsistency_PropertyType::DQ_LogicalConsistency_PropertyType(){}
	AbstractDQ_Completeness::AbstractDQ_Completeness(){}
	DQ_Completeness_PropertyType::DQ_Completeness_PropertyType(){}
	AbstractDQ_Element::AbstractDQ_Element(){}
	DQ_Element_PropertyType::DQ_Element_PropertyType(){}
	DQ_DataQuality::DQ_DataQuality(){}
	DQ_DataQuality_PropertyType::DQ_DataQuality_PropertyType(){}
	DQ_Scope::DQ_Scope(){}
	DQ_Scope_PropertyType::DQ_Scope_PropertyType(){}
	MD_DistributionUnits_PropertyType::MD_DistributionUnits_PropertyType(){}
	MD_MediumFormatCode_PropertyType::MD_MediumFormatCode_PropertyType(){}
	MD_MediumNameCode_PropertyType::MD_MediumNameCode_PropertyType(){}
	MD_Medium::MD_Medium()
	{
		documentation = L"Information about the media on which the data can be distributed";
	}
	MD_Medium_PropertyType::MD_Medium_PropertyType(){}
	MD_DigitalTransferOptions::MD_DigitalTransferOptions()
	{
		documentation = L"Technical means and media by which a dataset is obtained from the distributor";
	}
	MD_DigitalTransferOptions_PropertyType::MD_DigitalTransferOptions_PropertyType(){}
	MD_StandardOrderProcess::MD_StandardOrderProcess()
	{
		documentation = L"Common ways in which the dataset may be obtained or received, and related instructions and fee information";
	}
	MD_StandardOrderProcess_PropertyType::MD_StandardOrderProcess_PropertyType(){}
	MD_Distributor::MD_Distributor()
	{
		documentation = L"Information about the distributor";
	}
	MD_Distributor_PropertyType::MD_Distributor_PropertyType(){}
	MD_Distribution::MD_Distribution()
	{
		documentation = L"Information about the distributor of and options for obtaining the dataset";
	}
	MD_Distribution_PropertyType::MD_Distribution_PropertyType(){}
	MD_Format::MD_Format()
	{
		documentation = L"Description of the form of the data to be distributed";
	}
	MD_Format_PropertyType::MD_Format_PropertyType(){}
	EX_TemporalExtent::EX_TemporalExtent()
	{
		documentation = L"Time period covered by the content of the dataset";
	}
	EX_TemporalExtent_PropertyType::EX_TemporalExtent_PropertyType(){}
	EX_VerticalExtent::EX_VerticalExtent()
	{
		documentation = L"Vertical domain of dataset";
	}
	EX_VerticalExtent_PropertyType::EX_VerticalExtent_PropertyType(){}
	EX_BoundingPolygon::EX_BoundingPolygon()
	{
		documentation = L"Boundary enclosing the dataset expressed as the closed set of (x,y) coordinates of the polygon (last poconst int replicates first point)";
	}
	EX_BoundingPolygon_PropertyType::EX_BoundingPolygon_PropertyType(){}
	EX_Extent::EX_Extent()
	{
		documentation = L"Information about spatial, vertical, and temporal extent";
	}
	EX_Extent_PropertyType::EX_Extent_PropertyType(){}
	AbstractEX_GeographicExtent::AbstractEX_GeographicExtent()
	{
		documentation = L"Geographic area of the dataset";
	}
	EX_GeographicExtent_PropertyType::EX_GeographicExtent_PropertyType(){}
	EX_GeographicBoundingBox::EX_GeographicBoundingBox()
	{
		documentation = L"Geographic area of the entire dataset referenced to WGS 84";
	}
	EX_GeographicBoundingBox_PropertyType::EX_GeographicBoundingBox_PropertyType(){}
	EX_SpatialTemporalExtent::EX_SpatialTemporalExtent()
	{
		documentation = L"Extent with respect to date and time";
	}
	EX_SpatialTemporalExtent_PropertyType::EX_SpatialTemporalExtent_PropertyType(){}
	EX_GeographicDescription::EX_GeographicDescription()
	{
		documentation = L"Extent with respect to date and time";
	}
	EX_GeographicDescription_PropertyType::EX_GeographicDescription_PropertyType(){}
	LanguageCode_PropertyType::LanguageCode_PropertyType(){}
	Country_PropertyType::Country_PropertyType(){}
	PT_FreeText::PT_FreeText(){}
	PT_FreeText_PropertyType::PT_FreeText_PropertyType(){}
	PT_Locale::PT_Locale(){}
	PT_Locale_PropertyType::PT_Locale_PropertyType(){}
	LocalisedCharacterString::LocalisedCharacterString(){}
	LocalisedCharacterString_PropertyType::LocalisedCharacterString_PropertyType(){}
	PT_LocaleContainer::PT_LocaleContainer(){}
	PT_LocaleContainer_PropertyType::PT_LocaleContainer_PropertyType(){}
	MD_CharacterSetCode_PropertyType::MD_CharacterSetCode_PropertyType(){}
	MD_SpatialRepresentationTypeCode_PropertyType::MD_SpatialRepresentationTypeCode_PropertyType(){}
	MD_ProgressCode_PropertyType::MD_ProgressCode_PropertyType(){}
	MD_KeywordTypeCode_PropertyType::MD_KeywordTypeCode_PropertyType(){}
	DS_AssociationTypeCode_PropertyType::DS_AssociationTypeCode_PropertyType(){}
	DS_InitiativeTypeCode_PropertyType::DS_InitiativeTypeCode_PropertyType(){}
	AbstractMD_Identification::AbstractMD_Identification()
	{
		documentation = L"Basic information about data";
	}
	MD_Identification_PropertyType::MD_Identification_PropertyType(){}
	MD_BrowseGraphic::MD_BrowseGraphic()
	{
		documentation = L"Graphic that provides an illustration of the dataset (should include a legend for the graphic)";
	}
	MD_BrowseGraphic_PropertyType::MD_BrowseGraphic_PropertyType(){}
	MD_DataIdentification::MD_DataIdentification(){}
	MD_DataIdentification_PropertyType::MD_DataIdentification_PropertyType(){}
	MD_ServiceIdentification::MD_ServiceIdentification()
	{
		documentation = L"See 19119 for further info";
	}
	MD_ServiceIdentification_PropertyType::MD_ServiceIdentification_PropertyType(){}
	MD_RepresentativeFraction::MD_RepresentativeFraction(){}
	MD_RepresentativeFraction_PropertyType::MD_RepresentativeFraction_PropertyType(){}
	MD_Usage::MD_Usage()
	{
		documentation = L"Brief description of ways in which the dataset is currently used";
	}
	MD_Usage_PropertyType::MD_Usage_PropertyType(){}
	MD_Keywords::MD_Keywords()
	{
		documentation = L"Keywords, their type and reference source";
	}
	MD_Keywords_PropertyType::MD_Keywords_PropertyType(){}
	DS_Association::DS_Association(){}
	DS_Association_PropertyType::DS_Association_PropertyType(){}
	MD_AggregateInformation::MD_AggregateInformation()
	{
		documentation = L"Encapsulates the dataset aggregation information";
	}
	MD_AggregateInformation_PropertyType::MD_AggregateInformation_PropertyType(){}
	MD_Resolution::MD_Resolution(){}
	MD_Resolution_PropertyType::MD_Resolution_PropertyType(){}
	MD_TopicCategoryCode::MD_TopicCategoryCode()
	{
		documentation = L"High-level geospatial data thematic classification to assist in the grouping and search of available geospatial datasets";

		base.push_back(L"farming");
		base.push_back(L"biota");
		base.push_back(L"boundaries");
		base.push_back(L"climatologyMeteorologyAtmosphere");
		base.push_back(L"economy");
		base.push_back(L"elevation");
		base.push_back(L"environment");
		base.push_back(L"geoscientificInformation");
		base.push_back(L"health");
		base.push_back(L"imageryBaseMapsEarthCover");
		base.push_back(L"intelligenceMilitary");
		base.push_back(L"inlandWaters");
		base.push_back(L"location");
		base.push_back(L"oceans");
		base.push_back(L"planningCadastre");
		base.push_back(L"society");
		base.push_back(L"structure");
		base.push_back(L"transportation");
		base.push_back(L"utilitiesCommunication");
	}
	MD_TopicCategoryCode_PropertyType::MD_TopicCategoryCode_PropertyType(){}
	MD_MaintenanceFrequencyCode_PropertyType::MD_MaintenanceFrequencyCode_PropertyType(){}
	MD_ScopeCode_PropertyType::MD_ScopeCode_PropertyType(){}
	MD_MaintenanceInformation::MD_MaintenanceInformation()
	{
		documentation = L"Information about the scope and frequency of updating";
	}
	MD_MaintenanceInformation_PropertyType::MD_MaintenanceInformation_PropertyType(){}
	MD_ScopeDescription::MD_ScopeDescription()
	{
		documentation = L"Description of the class of information covered by the information";
	}
	MD_ScopeDescription_PropertyType::MD_ScopeDescription_PropertyType(){}
	AbstractDS_Aggregate::AbstractDS_Aggregate()
	{
		documentation = L"Identifiable collection of datasets";
	}
	DS_Aggregate_PropertyType::DS_Aggregate_PropertyType(){}
	DS_DataSet::DS_DataSet()
	{
		documentation = L"Identifiable collection of data";
	}
	DS_DataSet_PropertyType::DS_DataSet_PropertyType(){}
	DS_OtherAggregate::DS_OtherAggregate(){}
	DS_OtherAggregate_PropertyType::DS_OtherAggregate_PropertyType(){}
	DS_Series::DS_Series(){}
	DS_Series_PropertyType::DS_Series_PropertyType(){}
	DS_Initiative::DS_Initiative(){}
	DS_Initiative_PropertyType::DS_Initiative_PropertyType(){}
	DS_Platform::DS_Platform(){}
	DS_Platform_PropertyType::DS_Platform_PropertyType(){}
	DS_Sensor::DS_Sensor(){}
	DS_Sensor_PropertyType::DS_Sensor_PropertyType(){}
	DS_ProductionSeries::DS_ProductionSeries(){}
	DS_ProductionSeries_PropertyType::DS_ProductionSeries_PropertyType(){}
	DS_StereoMate::DS_StereoMate(){}
	DS_StereoMate_PropertyType::DS_StereoMate_PropertyType(){}
	MD_Metadata::MD_Metadata()
	{
		documentation = L"Information about the metadata";
	}
	MD_Metadata_PropertyType::MD_Metadata_PropertyType(){}
	MD_ObligationCode::MD_ObligationCode()
	{
		base.push_back(L"mandatory");
		base.push_back(L"optional");
		base.push_back(L"conditional");
	}
	MD_ObligationCode_PropertyType::MD_ObligationCode_PropertyType(){}
	MD_DatatypeCode_PropertyType::MD_DatatypeCode_PropertyType(){}
	MD_ExtendedElementInformation::MD_ExtendedElementInformation()
	{
		documentation = L"New metadata element, not found in ISO 19115, which is required to describe geographic data";
	}
	MD_ExtendedElementInformation_PropertyType::MD_ExtendedElementInformation_PropertyType(){}
	MD_MetadataExtensionInformation::MD_MetadataExtensionInformation()
	{
		documentation = L"Information describing metadata extensions.";
	}
	MD_MetadataExtensionInformation_PropertyType::MD_MetadataExtensionInformation_PropertyType(){}
	MD_PortrayalCatalogueReference::MD_PortrayalCatalogueReference()
	{
		documentation = L"Information identifing the portrayal catalogue used";
	}
	MD_PortrayalCatalogueReference_PropertyType::MD_PortrayalCatalogueReference_PropertyType(){}
	MD_TopologyLevelCode_PropertyType::MD_TopologyLevelCode_PropertyType(){}
	MD_GeometricObjectTypeCode_PropertyType::MD_GeometricObjectTypeCode_PropertyType(){}
	MD_CellGeometryCode_PropertyType::MD_CellGeometryCode_PropertyType(){}
	MD_DimensionNameTypeCode_PropertyType::MD_DimensionNameTypeCode_PropertyType(){}
	MD_GridSpatialRepresentation::MD_GridSpatialRepresentation()
	{
		documentation = L"Types and numbers of raster spatial objects in the dataset";
	}
	MD_GridSpatialRepresentation_PropertyType::MD_GridSpatialRepresentation_PropertyType(){}
	MD_VectorSpatialRepresentation::MD_VectorSpatialRepresentation()
	{
		documentation = L"Information about the vector spatial objects in the dataset";
	}
	MD_VectorSpatialRepresentation_PropertyType::MD_VectorSpatialRepresentation_PropertyType(){}
	AbstractMD_SpatialRepresentation::AbstractMD_SpatialRepresentation()
	{
		documentation = L"Digital mechanism used to represent spatial information";
	}
	MD_SpatialRepresentation_PropertyType::MD_SpatialRepresentation_PropertyType(){}
	MD_Georeferenceable::MD_Georeferenceable(){}
	MD_Georeferenceable_PropertyType::MD_Georeferenceable_PropertyType(){}
	MD_Dimension::MD_Dimension(){}
	MD_Dimension_PropertyType::MD_Dimension_PropertyType(){}
	MD_Georectified::MD_Georectified(){}
	MD_Georectified_PropertyType::MD_Georectified_PropertyType(){}
	MD_GeometricObjects::MD_GeometricObjects(){}
	MD_GeometricObjects_PropertyType::MD_GeometricObjects_PropertyType(){}
	MD_PixelOrientationCode::MD_PixelOrientationCode()
	{
		base.push_back(L"center");
		base.push_back(L"lowerLeft");
		base.push_back(L"lowerRight");
		base.push_back(L"upperRight");
		base.push_back(L"upperLeft");
	}
	MD_PixelOrientationCode_PropertyType::MD_PixelOrientationCode_PropertyType(){}

}


namespace MetadataSet
{

	MetadataSetXML::MetadataSetXML()
	{
	}

	void MetadataSetXML::XmlOpen(std::wstring path, gmd::MD_Metadata &metadata)
	{
		MSXML2::IXMLDOMDocument2Ptr pDoc;
		MSXML2::IXMLDOMNodeListPtr pNodeObject;

		pDoc.CreateInstance(__uuidof(DOMDocument)); 
		pDoc->load((_variant_t)path.c_str());

		pNodeObject = pDoc->selectNodes(L"gmd:MD_Metadata");
		ChileNodeArrange(pNodeObject, DWORD_PTR_ERROR, metadata);

	}

	void MetadataSetXML::ChileNodeArrange(MSXML2::IXMLDOMNodeListPtr nodes, DWORD_PTR variableSpace, gmd::MD_Metadata &metadata)
	{
		MSXML2::IXMLDOMNodeListPtr pNodeSelect;
		for (int i = 0; i < nodes->Getlength(); i++)
		{
			pNodeSelect = nodes->Getitem(i)->GetchildNodes();
			MSXML2::IXMLDOMNodePtr pNode = nodes->Getitem(i);
			_bstr_t Name = pNode->nodeName;
			if (!StrCmpA(Name, "#comment") || !StrCmpA(Name, "#text") || !StrCmpA(Name, "gco:CharacterString"))		continue;
			_bstr_t parentName = pNode->parentNode->nodeName;

			try
			{
				if (pNode->childNodes->length > 0)
				{
					if (!StrCmpA(pNode->firstChild->nodeName, "gco:CharacterString"))
					{
						if (!StrCmpA(pNode->parentNode->nodeName, "gmd:MD_Metadata") &&
							!StrCmpA(Name, "gmd:fileIdentifier"))
						{
							metadata.fileIdentifier.emplace_back(gco::CharacterString_PropertyType((wstring)(pNode->firstChild->text)));
						}
						else if (!StrCmpA(pNode->parentNode->nodeName, "gmd:MD_Metadata") &&
							!StrCmpA(Name, "gmd:language"))
						{
							metadata.language.emplace_back(gco::CharacterString_PropertyType((wstring)(pNode->firstChild->text)));
						}
						else if (!StrCmpA(pNode->parentNode->nodeName, "gmd:MD_Metadata") &&
							!StrCmpA(Name, "gmd:metadataStandardName"))
						{
							metadata.metadataStandardName.emplace_back(gco::CharacterString_PropertyType((wstring)(pNode->firstChild->text)));
						}
						else if (!StrCmpA(pNode->parentNode->nodeName, "gmd:MD_Metadata") &&
							!StrCmpA(Name, "gmd:metadataStandardVersion"))
						{
							metadata.metadataStandardVersion.emplace_back(gco::CharacterString_PropertyType((wstring)(pNode->firstChild->text)));
						} 
						else if (!StrCmpA(pNode->parentNode->parentNode->nodeName, "gmd:contact") &&
							!StrCmpA(pNode->parentNode->nodeName, "gmd:CI_ResponsibleParty"))
						{
							if (!StrCmpA(Name, "gmd:individualName"))
							{
								std::list<gmd::CI_ResponsibleParty_PropertyType>::iterator t = metadata.contact.begin();
								std::advance(t, metadata.contact.size() - 1);
								t->m_CI_ResponsibleParty.individualName.emplace_back(gco::CharacterString_PropertyType((wstring)(pNode->firstChild->text)));
							}
							else if (!StrCmpA(Name, "gmd:organisationName"))
							{
								std::list<gmd::CI_ResponsibleParty_PropertyType>::iterator t = metadata.contact.begin();
								std::advance(t, metadata.contact.size() - 1);
								t->m_CI_ResponsibleParty.organisationName.emplace_back(gco::CharacterString_PropertyType((wstring)(pNode->firstChild->text)));
							}
							else if (!StrCmpA(pNode->parentNode->parentNode->parentNode->parentNode->parentNode->parentNode->nodeName, "gmd:contactInfo") &&
								!StrCmpA(Name, "gmd:contactInfo"))
							{
							}

						}
					}
					else if (!StrCmpA(pNode->firstChild->nodeName, "gmd:MD_CharacterSetCode"))
					{
						gmd::MD_CharacterSetCode_PropertyType t;
						for (int i = 0; i < pNode->firstChild->attributes->Getlength(); i++)
						{
							_bstr_t name = pNode->firstChild->attributes->Getitem(i)->nodeName;
							_bstr_t text = pNode->firstChild->attributes->Getitem(i)->text;
							if (!StrCmpA(name, "codeList"))			t.m_MD_CharacterSetCode.codeList = text;
							if (!StrCmpA(name, "codeListValue"))	t.m_MD_CharacterSetCode.codeListValue = text;
							if (!StrCmpA(name, "codeSpace"))		t.m_MD_CharacterSetCode.codeSpace = text;
						}
						metadata.characterSet.emplace_back(t);
					}
					else if (!StrCmpA(pNode->parentNode->nodeName, "gmd:contact") &&
						!StrCmpA(Name, "gmd:CI_ResponsibleParty"))
					{ 
						gmd::CI_ResponsibleParty_PropertyType t;
						metadata.contact.emplace_back(t);
					}
				}
				if (!StrCmpA(Name, "gmd:role"))
				{
					if (!StrCmpA(pNode->parentNode->parentNode->nodeName, "gmd:contact") &&
						!StrCmpA(pNode->firstChild->nodeName, "gmd:CI_RoleCode"))
					{
						std::list<gmd::CI_ResponsibleParty_PropertyType>::iterator t;
						t = metadata.contact.begin();
						std::advance(t, metadata.contact.size() - 1);
						gmd::CI_RoleCode_PropertyType temp;
						for (int i = 0; i < pNode->firstChild->attributes->Getlength(); i++)
						{
							_bstr_t name = pNode->firstChild->attributes->Getitem(i)->nodeName;
							_bstr_t text = pNode->firstChild->attributes->Getitem(i)->text;
							if (!StrCmpA(name, "codeList"))			temp.m_CI_RoleCode_PropertyType.codeList = text;
							if (!StrCmpA(name, "codeListValue"))	temp.m_CI_RoleCode_PropertyType.codeListValue = text;
							if (!StrCmpA(name, "codeSpace"))		temp.m_CI_RoleCode_PropertyType.codeSpace = text;
						}
						t->m_CI_ResponsibleParty.role.emplace_back(temp);
					}
				}
			}
			catch (exception ex)
			{
			}

			if (pNodeSelect->Getlength() > 0)
			{
				ChileNodeArrange(pNodeSelect, variableSpace, metadata);
			}
		}
	}
}