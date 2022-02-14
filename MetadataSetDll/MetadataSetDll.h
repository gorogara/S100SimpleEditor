
#import <msxml4.dll>
#include "msxml.h"

#include <list>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;


namespace xs
{
	class data_size
	{
	public:
		int min;
		int max;
		void SizeSet(int mi, int ma)
		{
			min = mi;
			max = ma;
		}
	};
	enum limit
	{
		zero = 0,
		one = 1,
		two = 2,
		unbounded = 999999999
	};
}
namespace gco
{ 
	class NilReason;
	class ObjectIdentification;
	class AbstractObject_Type;
	class ObjectReference;
	class ObjectReference_PropertyType;
	class CodeListValue_Type;  
	class TypeName;
	class TypeName_PropertyType;
	class MemberName;
	class MemberName_PropertyType;
	class Multiplicity;
	class Multiplicity_PropertyType;
	class MultiplicityRange;
	class MultiplicityRange_PropertyType;
	class Measure_PropertyType;
	class Length_PropertyType;
	class Angle_PropertyType;
	class Scale_PropertyType;
	class Distance_PropertyType;
	class CharacterString_PropertyType;
	class Boolean_PropertyType;
	class GenericName_PropertyType;
	class LocalName_PropertyType;
	class ScopedName_PropertyType;
	class UomAngle_PropertyType;
	class UomLength_PropertyType;
	class UomScale_PropertyType;
	class UnitOfMeasure_PropertyType;
	class UomArea_PropertyType;
	class UomVelocity_PropertyType;
	class UomTime_PropertyType;
	class UomVolume_PropertyType;
	class Date;
	class Date_PropertyType;
	class DateTime;
	class DateTime_PropertyType; 
	class Decimal;
	class Decimal_PropertyType;
	class Binary;
	class Binary_PropertyType;
	class Real;
	class Real_PropertyType;
	class Integer;
	class Integer_PropertyType;
	class UnlimitedInteger;
	class UnlimitedInteger_PropertyType;
	class Record;
	class Record_PropertyType;
	class RecordType;
	class RecordType_PropertyType;  
	class NilReason
	{
	public:
		AFX_EXT_CLASS NilReason();
	};
	class ObjectIdentification
	{
	public:
		AFX_EXT_CLASS ObjectIdentification();
		wstring id;
		wstring uuid;
	};
	class AbstractObject_Type
	{
	public:
		AFX_EXT_CLASS AbstractObject_Type();
		gco::ObjectIdentification objectIdentification;
	};
	class ObjectReference
	{
	public:
		AFX_EXT_CLASS ObjectReference();
		wstring uuidref;
	};
	class ObjectReference_PropertyType
	{
	public:
		AFX_EXT_CLASS ObjectReference_PropertyType();
		gco::ObjectReference m_ObjectReference;
		gco::NilReason m_nilReason;
	};
	class CodeListValue_Type
	{
	public:
		AFX_EXT_CLASS CodeListValue_Type();
		wstring codeList;
		wstring codeListValue;
		wstring codeSpace;
	};
	class TypeName
	{
	public:
		AFX_EXT_CLASS TypeName();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> aName;
		int aName_minOccurs = xs::one;
		int aName_maxOccurs = xs::one;
	};
	class TypeName_PropertyType
	{
	public:
		AFX_EXT_CLASS TypeName_PropertyType();
		gco::TypeName m_TypeName;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MemberName
	{
	public:
		AFX_EXT_CLASS MemberName();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> aName;
		int aName_minOccurs = xs::one;
		int aName_maxOccurs = xs::one;
		list<gco::TypeName_PropertyType> attributeType;
		int attributeType_minOccurs = xs::one;
		int attributeType_maxOccurs = xs::one;
	};
	class MemberName_PropertyType
	{
	public:
		AFX_EXT_CLASS MemberName_PropertyType();
		gco::MemberName m_TypeName;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class Multiplicity
	{
	public:
		AFX_EXT_CLASS Multiplicity();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::MultiplicityRange_PropertyType> range;
		int range_minOccurs = xs::one;
		int range_maxOccurs = xs::unbounded;
	};
	class Multiplicity_PropertyType
	{
	public:
		AFX_EXT_CLASS Multiplicity_PropertyType();
		gco::Multiplicity m_Multiplicity;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MultiplicityRange
	{
	public:
		AFX_EXT_CLASS MultiplicityRange();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::Integer_PropertyType> lower;
		int lower_minOccurs = xs::one;
		int lower_maxOccurs = xs::one;
		list<gco::UnlimitedInteger_PropertyType> upper;
		int upper_minOccurs = xs::one;
		int upper_maxOccurs = xs::one;
	};
	class MultiplicityRange_PropertyType
	{
	public:
		AFX_EXT_CLASS MultiplicityRange_PropertyType();
		gco::MultiplicityRange m_MultiplicityRange;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class Measure_PropertyType
	{
	public:
		AFX_EXT_CLASS Measure_PropertyType();
		wstring m_MeasureType;//gml::MeasureType
		gco::NilReason m_nilReason;
	};
	class Length_PropertyType
	{
	public:
		AFX_EXT_CLASS Length_PropertyType();
		wstring m_LengthType;//gml::LengthType
		gco::NilReason m_nilReason;
	};
	class Angle_PropertyType
	{
	public:
		AFX_EXT_CLASS Angle_PropertyType();
		wstring m_AngleType;//gml::AngleType
		gco::NilReason m_nilReason;
	};
	class Scale_PropertyType
	{
	public:
		AFX_EXT_CLASS Scale_PropertyType();
		wstring m_ScaleType;//gml::ScaleType
		gco::NilReason m_nilReason;
	};
	class Distance_PropertyType
	{
	public:
		AFX_EXT_CLASS Distance_PropertyType();
		wstring m_DistanceType;//gml::LengthType
		gco::NilReason m_nilReason;
	};
	class CharacterString_PropertyType
	{
	public:
		AFX_EXT_CLASS CharacterString_PropertyType();
		wstring m_CharacterString;
		CharacterString_PropertyType(wstring str)
		{
			m_CharacterString = str;
		}
		gco::NilReason m_nilReason;
	};
	class Boolean_PropertyType
	{
	public:
		AFX_EXT_CLASS Boolean_PropertyType();
		bool boolean;
		gco::NilReason m_nilReason;
	};
	class GenericName_PropertyType
	{
	public:
		AFX_EXT_CLASS GenericName_PropertyType();
		bool abstract = true;
		wstring m_AbstractGenericName; 
		gco::NilReason m_nilReason;
	};
	class LocalName_PropertyType
	{
	public:
		AFX_EXT_CLASS LocalName_PropertyType();
		bool abstract = true;
		wstring m_LocalName; 
		gco::NilReason m_nilReason;
	};
	class ScopedName_PropertyType
	{
	public:
		AFX_EXT_CLASS ScopedName_PropertyType();
		bool abstract = true;
		wstring m_ScopedName; 
		gco::NilReason m_nilReason;
	};
	class UomAngle_PropertyType
	{
	public:
		AFX_EXT_CLASS UomAngle_PropertyType();
		wstring m_UnitDefinition;//gml:UnitDefinition
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class UomLength_PropertyType
	{
	public:
		AFX_EXT_CLASS UomLength_PropertyType();
		wstring m_UnitDefinition;//gml:UnitDefinition
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class UomScale_PropertyType
	{
	public:
		AFX_EXT_CLASS UomScale_PropertyType();
		wstring m_UnitDefinition;//gml:UnitDefinition
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class UnitOfMeasure_PropertyType
	{
	public:
		AFX_EXT_CLASS UnitOfMeasure_PropertyType();
		wstring m_UnitDefinition;//gml:UnitDefinition
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class UomArea_PropertyType
	{
	public:
		AFX_EXT_CLASS UomArea_PropertyType();
		wstring m_UnitDefinition;//gml:UnitDefinition
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class UomVelocity_PropertyType
	{
	public:
		AFX_EXT_CLASS UomVelocity_PropertyType();
		wstring m_UnitDefinition;//gml:UnitDefinition
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class UomTime_PropertyType
	{
	public:
		AFX_EXT_CLASS UomTime_PropertyType();
		wstring m_UnitDefinition;//gml:UnitDefinition
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class UomVolume_PropertyType
	{
	public:
		AFX_EXT_CLASS UomVolume_PropertyType();
		wstring m_UnitDefinition;//gml:UnitDefinition
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class Date
	{
	public:
		AFX_EXT_CLASS Date();
		wstring day;
		wstring month;
		wstring year;
	};
	class DateTime
	{
	public:
		AFX_EXT_CLASS DateTime();
		Date date;
		wstring h;
		wstring m;
		wstring s;
	};
	class Date_PropertyType
	{
	public:
		AFX_EXT_CLASS Date_PropertyType();
		Date date;
		DateTime dataTime;
	};
	class DateTime_PropertyType
	{
	public:
		AFX_EXT_CLASS DateTime_PropertyType();
		DateTime m_DateTime;
		gco::NilReason m_nilReason;
	};
	class Real
	{
	public:
		AFX_EXT_CLASS Real();
		double real;
	};
	class Real_PropertyType
	{
	public:
		AFX_EXT_CLASS Real_PropertyType();
		Real m_Real;
		gco::NilReason m_nilReason;
	};
	class Decimal
	{
	public:
		AFX_EXT_CLASS Decimal();
		double decimal;
	};
	class Decimal_PropertyType
	{
	public:
		AFX_EXT_CLASS Decimal_PropertyType();
		Decimal m_Decimal;
		gco::NilReason m_nilReason;
	};
	class Integer
	{
	public:
		AFX_EXT_CLASS Integer();
		int integer;
	};
	class Integer_PropertyType
	{
	public:
		AFX_EXT_CLASS Integer_PropertyType();
		Integer m_Integer;
		gco::NilReason m_nilReason;
	};
	class Number_PropertyType
	{
	public:
		AFX_EXT_CLASS Number_PropertyType();
		gco::Real m_Real;
		gco::Decimal m_Decimal;
		gco::Integer m_Integer;
		gco::NilReason m_nilReason;
	};
	class Binary
	{
	public:
		AFX_EXT_CLASS Binary();
		wstring binary;
	};
	class Binary_PropertyType
	{
	public:
		AFX_EXT_CLASS Binary_PropertyType();
		Binary m_Binary;
		gco::NilReason m_nilReason;
	};
	class UnlimitedInteger
	{
	public:
		AFX_EXT_CLASS UnlimitedInteger();

	};
	class UnlimitedInteger_PropertyType
	{
	public:
		AFX_EXT_CLASS UnlimitedInteger_PropertyType();

	};
	class Record
	{
	public:
		AFX_EXT_CLASS Record();
	};
	class Record_PropertyType
	{
	public:
		AFX_EXT_CLASS Record_PropertyType();
		Record m_Record;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class RecordType
	{
	public:
		AFX_EXT_CLASS RecordType();
		wstring base;
	};
	class RecordType_PropertyType
	{
	public:
		AFX_EXT_CLASS RecordType_PropertyType();
		RecordType m_RecordType;
		gco::NilReason m_nilReason;
	};
}
namespace gts
{
	class TM_PeriodDuration
	{
	public:
		AFX_EXT_CLASS TM_PeriodDuration();
		wstring value;
	};
	class TM_PeriodDuration_PropertyType
	{
	public:
		AFX_EXT_CLASS TM_PeriodDuration_PropertyType();
		gts::TM_PeriodDuration  tm_PeriodDuration;
	};
}
namespace gss
{
	class GM_Point_PropertyType
	{
	public:
		AFX_EXT_CLASS GM_Point_PropertyType();
		wstring m_Point;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class GM_Object_PropertyType
	{
	public:
		AFX_EXT_CLASS GM_Object_PropertyType();
		wstring m_AbstractGeometry;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
}
namespace gsr
{
	class SC_CRS_PropertyType
	{
	public:
		AFX_EXT_CLASS SC_CRS_PropertyType();
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
}
namespace gmd
{ 
	class MD_ApplicationSchemaInformation;
	class MD_ApplicationSchemaInformation_PropertyType;  
	class URL_PropertyType;

	class CI_RoleCode_PropertyType;
	class CI_PresentationFormCode_PropertyType;
	class CI_OnLineFunctionCode_PropertyType;
	class CI_DateTypeCode_PropertyType;

	class CI_Series;
	class CI_Series_PropertyType;
	class CI_Telephone;
	class CI_Telephone_PropertyType;
	class CI_Address;
	class CI_Address_PropertyType;
	class CI_Contact;
	class CI_Contact_PropertyType;
	class CI_Date;
	class CI_DateTypeCode_PropertyType;
	class CI_Citation;
	class CI_Citation_PropertyType;
	class CI_OnlineResource;
	class CI_OnlineResource_PropertyType;
	class CI_ResponsibleParty;
	class CI_ResponsibleParty_PropertyType;  
	class MD_ClassificationCode_PropertyType;
	class MD_RestrictionCode_PropertyType;

	class MD_Constraints;
	class MD_Constraints_PropertyType;
	class MD_LegalConstraints;
	class MD_LegalConstraints_PropertyType;
	class MD_SecurityConstraints;
	class MD_SecurityConstraints_PropertyType;  
	class RS_Identifier;
	class RS_Identifier_PropertyType;
	class MD_ReferenceSystem;
	class MD_ReferenceSystem_PropertyType;
	class MD_Identifier;
	class MD_Identifier_PropertyType;
	class AbstractRS_ReferenceSystem;
	class RS_ReferenceSystem_PropertyType;  
	class MD_CoverageContentTypeCode_PropertyType;
	class MD_ImagingConditionCode_PropertyType;

	class MD_FeatureCatalogueDescription;
	class MD_FeatureCatalogueDescription_PropertyType;
	class MD_CoverageDescription;
	class MD_CoverageDescription_PropertyType;
	class MD_ImageDescription;
	class MD_ImageDescription_PropertyType;
	class AbstractMD_ContentInformation;
	class MD_ContentInformation_PropertyType;
	class MD_RangeDimension;
	class MD_RangeDimension_PropertyType;
	class MD_Band;
	class MD_Band_PropertyType;  
	class DQ_EvaluationMethodTypeCode_PropertyType;

	class LI_ProcessStep;
	class LI_ProcessStep_PropertyType;
	class LI_Source;
	class LI_Source_PropertyType;
	class LI_Lineage;
	class LI_Lineage_PropertyType;
	class DQ_ConformanceResult;
	class DQ_ConformanceResult_PropertyType;
	class DQ_QuantitativeResult;
	class DQ_QuantitativeResult_PropertyType;
	class AbstractDQ_Result;
	class DQ_Result_PropertyType;
	class DQ_TemporalValidity;
	class DQ_TemporalValidity_PropertyType;
	class DQ_TemporalConsistency;
	class DQ_TemporalConsistency_PropertyType;
	class DQ_AccuracyOfATimeMeasurement;
	class DQ_AccuracyOfATimeMeasurement_PropertyType;
	class DQ_QuantitativeAttributeAccuracy;
	class DQ_QuantitativeAttributeAccuracy_PropertyType;
	class DQ_NonQuantitativeAttributeAccuracy;
	class DQ_NonQuantitativeAttributeAccuracy_PropertyType;
	class DQ_ThematicClassificationCorrectness;
	class DQ_ThematicClassificationCorrectness_PropertyType;
	class DQ_RelativeInternalPositionalAccuracy;
	class DQ_RelativeInternalPositionalAccuracy_PropertyType;
	class DQ_GriddedDataPositionalAccuracy;
	class DQ_GriddedDataPositionalAccuracy_PropertyType;
	class DQ_AbsoluteExternalPositionalAccuracy;
	class DQ_AbsoluteExternalPositionalAccuracy_PropertyType;
	class DQ_TopologicalConsistency;
	class DQ_TopologicalConsistency_PropertyType;
	class DQ_FormatConsistency;
	class DQ_FormatConsistency_PropertyType;
	class DQ_DomainConsistency;
	class DQ_DomainConsistency_PropertyType;
	class DQ_ConceptualConsistency;
	class DQ_ConceptualConsistency_PropertyType;
	class DQ_CompletenessOmission;
	class DQ_CompletenessOmission_PropertyType;
	class DQ_CompletenessCommission;
	class DQ_CompletenessCommission_PropertyType;
	class AbstractDQ_TemporalAccuracy;
	class DQ_TemporalAccuracy_PropertyType;
	class AbstractDQ_ThematicAccuracy;
	class DQ_ThematicAccuracy_PropertyType;
	class AbstractDQ_PositionalAccuracy;
	class DQ_PositionalAccuracy_PropertyType;
	class AbstractDQ_LogicalConsistency;
	class DQ_LogicalConsistency_PropertyType;
	class AbstractDQ_Completeness;
	class DQ_Completeness_PropertyType;
	class AbstractDQ_Element;
	class DQ_Element_PropertyType;
	class DQ_DataQuality;
	class DQ_DataQuality_PropertyType;
	class DQ_Scope;
	class DQ_Scope_PropertyType;  
	class MD_DistributionUnits_PropertyType;
	class MD_MediumFormatCode_PropertyType;
	class MD_MediumNameCode_PropertyType;

	class MD_Medium;
	class MD_Medium_PropertyType;
	class MD_DigitalTransferOptions;
	class MD_DigitalTransferOptions_PropertyType;
	class MD_StandardOrderProcess;
	class MD_StandardOrderProcess_PropertyType;
	class MD_Distributor;
	class MD_Distributor_PropertyType;
	class MD_Distribution;
	class MD_Distribution_PropertyType;
	class MD_Format;
	class MD_Format_PropertyType;  
	class EX_TemporalExtent;
	class EX_TemporalExtent_PropertyType;
	class EX_VerticalExtent;
	class EX_VerticalExtent_PropertyType;
	class EX_BoundingPolygon;
	class EX_BoundingPolygon_PropertyType;
	class EX_Extent;
	class EX_Extent_PropertyType;
	class AbstractEX_GeographicExtent;
	class EX_GeographicExtent_PropertyType;
	class EX_GeographicBoundingBox;
	class EX_GeographicBoundingBox_PropertyType;
	class EX_SpatialTemporalExtent;
	class EX_SpatialTemporalExtent_PropertyType;
	class EX_GeographicDescription;
	class EX_GeographicDescription_PropertyType;  
	class LanguageCode_PropertyType;
	class Country_PropertyType;

	class PT_FreeText;
	class PT_FreeText_PropertyType;
	class PT_Locale;
	class PT_Locale_PropertyType;
	class LocalisedCharacterString;
	class LocalisedCharacterString_PropertyType;
	class PT_LocaleContainer;
	class PT_LocaleContainer_PropertyType;  
	class MD_CharacterSetCode_PropertyType;
	class MD_SpatialRepresentationTypeCode_PropertyType;
	class MD_ProgressCode_PropertyType;
	class MD_KeywordTypeCode_PropertyType;
	class DS_AssociationTypeCode_PropertyType;
	class DS_InitiativeTypeCode_PropertyType;

	class AbstractMD_Identification;
	class MD_Identification_PropertyType;
	class MD_BrowseGraphic;
	class MD_BrowseGraphic_PropertyType;
	class MD_DataIdentification;
	class MD_DataIdentification_PropertyType;
	class MD_ServiceIdentification;
	class MD_ServiceIdentification_PropertyType;
	class MD_RepresentativeFraction;
	class MD_RepresentativeFraction_PropertyType;
	class MD_Usage;
	class MD_Usage_PropertyType;
	class MD_Keywords;
	class MD_Keywords_PropertyType;
	class DS_Association;
	class DS_Association_PropertyType;
	class MD_AggregateInformation;
	class MD_AggregateInformation_PropertyType;
	class MD_Resolution;
	class MD_Resolution_PropertyType;
	class MD_TopicCategoryCode;
	class MD_TopicCategoryCode_PropertyType;  
	class MD_MaintenanceFrequencyCode_PropertyType;
	class MD_ScopeCode_PropertyType;

	class MD_MaintenanceInformation;
	class MD_MaintenanceInformation_PropertyType;
	class MD_ScopeDescription;
	class MD_ScopeDescription_PropertyType;  
	class AbstractDS_Aggregate;
	class DS_Aggregate_PropertyType;
	class DS_DataSet;
	class DS_DataSet_PropertyType;
	class DS_OtherAggregate;
	class DS_OtherAggregate_PropertyType;
	class DS_Series;
	class DS_Series_PropertyType;
	class DS_Initiative;
	class DS_Initiative_PropertyType;
	class DS_Platform;
	class DS_Platform_PropertyType;
	class DS_Sensor;
	class DS_Sensor_PropertyType;
	class DS_ProductionSeries;
	class DS_ProductionSeries_PropertyType;
	class DS_StereoMate;
	class DS_StereoMate_PropertyType;  
	class MD_Metadata;
	class MD_Metadata_PropertyType;  
	class MD_ObligationCode;
	class MD_ObligationCode_PropertyType;

	class MD_DatatypeCode_PropertyType;

	class MD_ExtendedElementInformation;
	class MD_ExtendedElementInformation_PropertyType;
	class MD_MetadataExtensionInformation;
	class MD_MetadataExtensionInformation_PropertyType;  
	class MD_PortrayalCatalogueReference;
	class MD_PortrayalCatalogueReference_PropertyType;  
	class MD_TopologyLevelCode_PropertyType;
	class MD_GeometricObjectTypeCode_PropertyType;
	class MD_CellGeometryCode_PropertyType;
	class MD_DimensionNameTypeCode_PropertyType;

	class MD_GridSpatialRepresentation;
	class MD_GridSpatialRepresentation_PropertyType;
	class MD_VectorSpatialRepresentation;
	class MD_VectorSpatialRepresentation_PropertyType;
	class AbstractMD_SpatialRepresentation;
	class MD_SpatialRepresentation_PropertyType;
	class MD_Georeferenceable;
	class MD_Georeferenceable_PropertyType;
	class MD_Dimension;
	class MD_Dimension_PropertyType;
	class MD_Georectified;
	class MD_Georectified_PropertyType;
	class MD_GeometricObjects;
	class MD_GeometricObjects_PropertyType;
	class MD_PixelOrientationCode;
	class MD_PixelOrientationCode_PropertyType;  
	class MD_ApplicationSchemaInformation
	{
	public:
		AFX_EXT_CLASS MD_ApplicationSchemaInformation();
		wstring documentation;
		gco::AbstractObject_Type base;

		list<gmd::CI_Citation_PropertyType> name;
		const int name_minOccurs = xs::one;
		const int name_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> schemaLanguage;
		const int schemaLanguage_minOccurs = xs::one;
		const int schemaLanguage_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> constraintLanguage;
		const int constraintLanguage_minOccurs = xs::one;
		const int constraintLanguage_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> schemaAscii;
		const int schemaAscii_minOccurs = xs::zero;
		const int schemaAscii_maxOccurs = xs::one;
		list<gco::Binary_PropertyType> graphicsFile;
		const int graphicsFile_minOccurs = xs::zero;
		const int graphicsFile_maxOccurs = xs::one;
		list<gco::Binary_PropertyType> softwareDevelopmentFile;
		const int softwareDevelopmentFile_minOccurs = xs::zero;
		const int softwareDevelopmentFile_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> softwareDevelopmentFileFormat;
		const int softwareDevelopmentFileFormat_minOccurs = xs::zero;
		const int softwareDevelopmentFileFormat_maxOccurs = xs::one;
	};
	class MD_ApplicationSchemaInformation_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_ApplicationSchemaInformation_PropertyType();
		gmd::MD_ApplicationSchemaInformation m_MD_ApplicationSchemaInformation;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class URL_PropertyType
	{
	public:
		AFX_EXT_CLASS URL_PropertyType();
		wstring URL;
		gco::NilReason m_nilReason;
	};
	class CI_RoleCode_PropertyType
	{
	public:
		AFX_EXT_CLASS CI_RoleCode_PropertyType();
		gco::CodeListValue_Type m_CI_RoleCode_PropertyType;
		gco::NilReason m_nilReason;
	};
	class CI_PresentationFormCode_PropertyType
	{
	public:
		AFX_EXT_CLASS CI_PresentationFormCode_PropertyType();
		gco::CodeListValue_Type CI_PresentationFormCode;
		gco::NilReason m_nilReason;
	};
	class CI_OnLineFunctionCode_PropertyType
	{
	public:
		AFX_EXT_CLASS CI_OnLineFunctionCode_PropertyType();
		gco::CodeListValue_Type m_CI_OnLineFunctionCode;
		gco::NilReason m_nilReason;
	};
	class CI_DateTypeCode_PropertyType
	{
	public:
		AFX_EXT_CLASS CI_DateTypeCode_PropertyType();
		gco::CodeListValue_Type CI_DateTypeCode;
		gco::NilReason m_nilReason;
	};
	class CI_Series
	{
	public:
		AFX_EXT_CLASS CI_Series();
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> name;
		const int name_minOccurs = xs::zero;
		const int name_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> issueIdentification;
		const int issueIdentification_minOccurs = xs::zero;
		const int issueIdentification_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> page;
		const int page_minOccurs = xs::zero;
		const int page_maxOccurs = xs::one;
	};
	class CI_Series_PropertyType
	{
	public:
		AFX_EXT_CLASS CI_Series_PropertyType();
		gmd::CI_Series m_CI_Series;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class CI_Telephone
	{
	public:
		AFX_EXT_CLASS CI_Telephone();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> voice;
		const int voice_minOccurs = xs::zero;
		const int voice_maxOccurs = xs::unbounded;
		list<gco::CharacterString_PropertyType> facsimile;
		const int facsimile_minOccurs = xs::zero;
		const int facsimile_maxOccurs = xs::unbounded;
	};
	class CI_Telephone_PropertyType
	{
	public:
		AFX_EXT_CLASS CI_Telephone_PropertyType();
		gmd::CI_Telephone m_CI_Telephone;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class CI_Address
	{
	public:
		AFX_EXT_CLASS CI_Address();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> deliveryPoint;
		const int deliveryPoint_minOccurs = xs::zero;
		const int deliveryPoint_maxOccurs = xs::unbounded;
		list<gco::CharacterString_PropertyType> city;
		const int city_minOccurs = xs::zero;
		const int city_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> administrativeArea;
		const int administrativeArea_minOccurs = xs::zero;
		const int administrativeArea_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> postalCode;
		const int postalCode_minOccurs = xs::zero;
		const int postalCode_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> country;
		const int country_minOccurs = xs::zero;
		const int country_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> electronicMailAddress;
		const int electronicMailAddress_minOccurs = xs::zero;
		const int electronicMailAddress_maxOccurs = xs::unbounded;
	};
	class CI_Address_PropertyType
	{
	public:
		AFX_EXT_CLASS CI_Address_PropertyType();
		gmd::CI_Address m_CI_Address;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class CI_Contact
	{
	public:
		AFX_EXT_CLASS CI_Contact();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gmd::CI_Telephone_PropertyType> phone;
		const int phone_minOccurs = xs::zero;
		const int phone_maxOccurs = xs::one;
		list<gmd::CI_Address_PropertyType> address;
		const int address_minOccurs = xs::zero;
		const int address_maxOccurs = xs::one;
		list<gmd::CI_OnlineResource_PropertyType> onlineResource;
		const int onlineResource_minOccurs = xs::zero;
		const int onlineResource_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> hoursOfService;
		const int hoursOfService_minOccurs = xs::zero;
		const int hoursOfService_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> contactInstructions;
		const int contactInstructions_minOccurs = xs::zero;
		const int contactInstructions_maxOccurs = xs::one;
	};
	class CI_Contact_PropertyType
	{
	public:
		AFX_EXT_CLASS CI_Contact_PropertyType();
		gmd::CI_Contact m_CI_Contact;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class CI_Date
	{
	public:
		AFX_EXT_CLASS CI_Date();
		gco::AbstractObject_Type base;
		list<gco::Date_PropertyType> date;
		const int date_minOccurs = xs::one;
		const int date_maxOccurs = xs::one;
		list<gmd::CI_DateTypeCode_PropertyType> dateType;
		const int dateType_minOccurs = xs::one;
		const int dateType_maxOccurs = xs::one;
	};
	class CI_Date_PropertyType
	{
	public:
		AFX_EXT_CLASS CI_Date_PropertyType();
		gmd::CI_Date m_CI_Date;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class CI_Citation
	{
	public:
		AFX_EXT_CLASS CI_Citation();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> title;
		const int title_minOccurs = xs::one;
		const int title_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> alternateTitle;
		const int alternateTitle_minOccurs = xs::zero;
		const int alternateTitle_maxOccurs = xs::unbounded;
		list<gmd::CI_Date_PropertyType> date;
		const int date_minOccurs = xs::one;
		const int date_maxOccurs = xs::unbounded;
		list<gco::CharacterString_PropertyType> edition;
		const int edition_minOccurs = xs::zero;
		const int edition_maxOccurs = xs::one;
		list<gco::Date_PropertyType> editionDate;
		const int editionDate_minOccurs = xs::zero;
		const int editionDate_maxOccurs = xs::one;
		list<gmd::MD_Identifier_PropertyType> identifier;
		const int identifier_minOccurs = xs::zero;
		const int identifier_maxOccurs = xs::unbounded;
		list<gmd::CI_ResponsibleParty_PropertyType> citedResponsibleParty;
		const int citedResponsibleParty_minOccurs = xs::zero;
		const int citedResponsibleParty_maxOccurs = xs::unbounded;
		list<gmd::CI_PresentationFormCode_PropertyType> presentationForm;
		const int presentationForm_minOccurs = xs::zero;
		const int presentationForm_maxOccurs = xs::unbounded;
		list<gmd::CI_Series_PropertyType> series;
		const int series_minOccurs = xs::zero;
		const int series_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> otherCitationDetails;
		const int otherCitationDetails_minOccurs = xs::zero;
		const int otherCitationDetails_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> collectiveTitle;
		const int collectiveTitle_minOccurs = xs::zero;
		const int collectiveTitle_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> ISBN;
		const int ISBN_minOccurs = xs::zero;
		const int ISBN_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> ISSN;
		const int ISSN_minOccurs = xs::zero;
		const int ISSN_maxOccurs = xs::one;

	};
	class CI_Citation_PropertyType
	{
	public:
		AFX_EXT_CLASS CI_Citation_PropertyType();
		gmd::CI_Citation m_CI_Citation;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class CI_OnlineResource
	{
	public:
		AFX_EXT_CLASS CI_OnlineResource();
		wstring documentation;
		gco::AbstractObject_Type base;

		list<gmd::URL_PropertyType> linkage;
		const int linkage_minOccurs = xs::one;
		const int linkage_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> protocol;
		const int protocol_minOccurs = xs::zero;
		const int protocol_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> applicationProfile;
		const int applicationProfile_minOccurs = xs::zero;
		const int applicationProfile_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> name;
		const int name_minOccurs = xs::zero;
		const int name_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> description;
		const int description_minOccurs = xs::zero;
		const int description_maxOccurs = xs::one;
		list<gmd::CI_OnLineFunctionCode_PropertyType> function;
		const int function_minOccurs = xs::zero;
		const int function_maxOccurs = xs::one;
	};
	class CI_OnlineResource_PropertyType
	{
	public:
		AFX_EXT_CLASS CI_OnlineResource_PropertyType();
		CI_OnlineResource m_CI_OnlineResource;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class CI_ResponsibleParty
	{
	public:
		AFX_EXT_CLASS CI_ResponsibleParty();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> individualName;
		const int individualName_minOccurs = xs::zero;
		const int individualName_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> organisationName;
		const int organisationName_minOccurs = xs::zero;
		const int organisationName_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> positionName;
		const int positionName_minOccurs = xs::zero;
		const int positionName_maxOccurs = xs::one;
		list<gmd::CI_Contact_PropertyType> contactInfo;
		const int contactInfo_minOccurs = xs::zero;
		const int contactInfo_maxOccurs = xs::one;
		list<gmd::CI_RoleCode_PropertyType> role;
		const int role_minOccurs = xs::one;
		const int role_maxOccurs = xs::one;
	};
	class CI_ResponsibleParty_PropertyType
	{
	public:
		AFX_EXT_CLASS CI_ResponsibleParty_PropertyType();
		gmd::CI_ResponsibleParty m_CI_ResponsibleParty;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_ClassificationCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_ClassificationCode_PropertyType();
		gco::CodeListValue_Type m_MD_ClassificationCode;
		gco::NilReason m_nilReason;
	};
	class MD_RestrictionCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_RestrictionCode_PropertyType();
		gco::CodeListValue_Type m_MD_RestrictionCode;
		gco::NilReason m_nilReason;
	};
	class MD_Constraints
	{
	public:
		AFX_EXT_CLASS MD_Constraints();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> usexsation;
		const int schemaAscii_minOccurs = xs::zero;
		const int schemaAscii_maxOccurs = xs::unbounded;

	};
	class MD_Constraints_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_Constraints_PropertyType();
		gmd::MD_Constraints m_MD_Constraints;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_LegalConstraints
	{
	public:
		AFX_EXT_CLASS MD_LegalConstraints();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gmd::MD_RestrictionCode_PropertyType> accessConstraints;
		const int accessConstraints_minOccurs = xs::zero;
		const int accessConstraints_maxOccurs = xs::unbounded;
		list<gmd::MD_RestrictionCode_PropertyType> useConstraints;
		const int useConstraints_minOccurs = xs::zero;
		const int useConstraints_maxOccurs = xs::unbounded;
		list<gco::CharacterString_PropertyType> otherConstraints;
		const int otherConstraints_minOccurs = xs::zero;
		const int otherConstraints_maxOccurs = xs::unbounded;

	};
	class MD_LegalConstraints_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_LegalConstraints_PropertyType();
		gmd::MD_LegalConstraints m_MD_LegalConstraints;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_SecurityConstraints
	{
	public:
		AFX_EXT_CLASS MD_SecurityConstraints();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gmd::MD_ClassificationCode_PropertyType> classification;
		const int classification_minOccurs = xs::one;
		const int classification_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> useConstraints;
		const int useConstraints_minOccurs = xs::zero;
		const int useConstraints_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> classificationSystem;
		const int classificationSystem_minOccurs = xs::zero;
		const int classificationSystem_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> handlingDescription;
		const int handlingDescription_minOccurs = xs::one;
		const int handlingDescription_maxOccurs = xs::unbounded;

	};
	class MD_SecurityConstraints_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_SecurityConstraints_PropertyType();
		gmd::MD_SecurityConstraints m_MD_SecurityConstraints;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class RS_Identifier
	{
	public:
		AFX_EXT_CLASS RS_Identifier();
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> codeSpace;
		const int codeSpace_minOccurs = xs::zero;
		const int codeSpace_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> version;
		const int version_minOccurs = xs::zero;
		const int version_maxOccurs = xs::one;
	};
	class RS_Identifier_PropertyType
	{
	public:
		AFX_EXT_CLASS RS_Identifier_PropertyType();
		gmd::RS_Identifier m_RS_Identifier;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_ReferenceSystem
	{
	public:
		AFX_EXT_CLASS MD_ReferenceSystem();
		gco::AbstractObject_Type base;
		list<gmd::RS_Identifier_PropertyType> referenceSystemIdentifier;
		const int extensionOnLineResource_minOccurs = xs::zero;
		const int extensionOnLineResource_maxOccurs = xs::one;
	};
	class MD_ReferenceSystem_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_ReferenceSystem_PropertyType();
		gmd::MD_ReferenceSystem m_MD_ReferenceSystem;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_Identifier
	{
	public:
		AFX_EXT_CLASS MD_Identifier();
		gco::AbstractObject_Type base;
		list<gmd::CI_Citation_PropertyType> authority;
		const int authority_minOccurs = xs::one;
		const int authority_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> code;
		const int code_minOccurs = xs::one;
		const int code_maxOccurs = xs::one;
	};
	class MD_Identifier_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_Identifier_PropertyType();
		gmd::MD_Identifier m_MD_Identifier;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class AbstractRS_ReferenceSystem
	{
	public:
		AFX_EXT_CLASS AbstractRS_ReferenceSystem();
		bool abstract = true;
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gmd::RS_Identifier_PropertyType> name;
		const int name_minOccurs = xs::one;
		const int name_maxOccurs = xs::one;
		list<gmd::EX_Extent_PropertyType> domainOfValidity;
		const int domainOfValidity_minOccurs = xs::zero;
		const int domainOfValidity_maxOccurs = xs::unbounded;

	};
	class RS_ReferenceSystem_PropertyType
	{
	public:
		AFX_EXT_CLASS RS_ReferenceSystem_PropertyType();
		gmd::AbstractRS_ReferenceSystem m_AbstractRS_ReferenceSystem;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_CoverageContentTypeCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_CoverageContentTypeCode_PropertyType();
		gco::CodeListValue_Type m_MD_CoverageContentTypeCode;
		gco::NilReason m_nilReason;
	};
	class MD_ImagingConditionCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_ImagingConditionCode_PropertyType();
		gco::CodeListValue_Type m_MD_ImagingConditionCode;
		gco::NilReason m_nilReason;
	};
	class MD_FeatureCatalogueDescription
	{
	public:
		AFX_EXT_CLASS MD_FeatureCatalogueDescription();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::Boolean_PropertyType> complianceCode;
		const int complianceCode_minOccurs = xs::zero;
		const int complianceCode_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> language;
		const int language_minOccurs = xs::zero;
		const int language_maxOccurs = xs::unbounded;
		list<gco::Boolean_PropertyType> includedWithDataset;
		const int includedWithDataset_minOccurs = xs::one;
		const int includedWithDataset_maxOccurs = xs::one;
		list<gco::GenericName_PropertyType> featureTypes;
		const int featureTypes_minOccurs = xs::zero;
		const int featureTypes_maxOccurs = xs::unbounded;
		list<gco::CharacterString_PropertyType> featureCatalogueCitation;
		const int featureCatalogueCitation_minOccurs = xs::one;
		const int featureCatalogueCitation_maxOccurs = xs::unbounded;

	};
	class MD_FeatureCatalogueDescription_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_FeatureCatalogueDescription_PropertyType();
		gmd::MD_FeatureCatalogueDescription m_MD_FeatureCatalogueDescription;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class AbstractMD_ContentInformation
	{
	public:
		AFX_EXT_CLASS AbstractMD_ContentInformation();
		bool abstract = true;
		gco::AbstractObject_Type base;
	};
	class MD_ContentInformation_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_ContentInformation_PropertyType();
		gmd::AbstractMD_ContentInformation m_AbstractMD_ContentInformation;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_CoverageDescription
	{
	public:
		AFX_EXT_CLASS MD_CoverageDescription();
		wstring documentation;
		gmd::AbstractMD_ContentInformation base;
		list<gco::RecordType_PropertyType> attributeDescription;
		const int attributeDescription_minOccurs = xs::one;
		const int attributeDescription_maxOccurs = xs::one;
		list<gmd::MD_CoverageContentTypeCode_PropertyType> contentType;
		const int contentType_minOccurs = xs::one;
		const int contentType_maxOccurs = xs::one;
		list<gmd::MD_RangeDimension_PropertyType> dimension;
		const int dimension_minOccurs = xs::zero;
		const int dimension_maxOccurs = xs::one;
		;

	};
	class MD_CoverageDescription_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_CoverageDescription_PropertyType();
		gmd::MD_CoverageDescription m_MD_CoverageDescription;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_ImageDescription
	{
	public:
		AFX_EXT_CLASS MD_ImageDescription();
		wstring documentation;
		gmd::MD_CoverageDescription base;
		list<gco::Real_PropertyType> illuminationElevationAngle;
		const int illuminationElevationAngle_minOccurs = xs::zero;
		const int illuminationElevationAngle_maxOccurs = xs::one;
		list<gco::Real_PropertyType> illuminationAzimuthAngle;
		const int illuminationAzimuthAngle_minOccurs = xs::zero;
		const int illuminationAzimuthAngle_maxOccurs = xs::one;
		list<gmd::MD_ImagingConditionCode_PropertyType> imagingCondition;
		const int imagingCondition_minOccurs = xs::zero;
		const int imagingCondition_maxOccurs = xs::one;
		list<gmd::MD_Identifier_PropertyType> imageQualityCode;
		const int imageQualityCode_minOccurs = xs::zero;
		const int imageQualityCode_maxOccurs = xs::one;
		list<gco::Real_PropertyType> cloudCoverPercentage;
		const int cloudCoverPercentage_minOccurs = xs::zero;
		const int cloudCoverPercentage_maxOccurs = xs::one;
		list<gmd::MD_Identifier_PropertyType> processingLevelCode;
		const int processingLevelCode_minOccurs = xs::zero;
		const int processingLevelCode_maxOccurs = xs::one;
		list<gco::Integer_PropertyType> compressionGenerationQuantity;
		const int compressionGenerationQuantity_minOccurs = xs::zero;
		const int compressionGenerationQuantity_maxOccurs = xs::one;
		list<gco::Boolean_PropertyType> triangulationIndicator;
		const int triangulationIndicator_minOccurs = xs::zero;
		const int triangulationIndicator_maxOccurs = xs::one;
		list<gco::Boolean_PropertyType> radiometricCalibrationDataAvailability;
		const int radiometricCalibrationDataAvailability_minOccurs = xs::zero;
		const int radiometricCalibrationDataAvailability_maxOccurs = xs::one;
		list<gco::Boolean_PropertyType> cameraCalibrationInformationAvailability;
		const int cameraCalibrationInformationAvailability_minOccurs = xs::zero;
		const int cameraCalibrationInformationAvailability_maxOccurs = xs::one;
		list<gco::Boolean_PropertyType> filmDistortionInformationAvailability;
		const int filmDistortionInformationAvailability_minOccurs = xs::zero;
		const int filmDistortionInformationAvailability_maxOccurs = xs::one;
		list<gco::Boolean_PropertyType> lensDistortionInformationAvailability;
		const int _minOccurs = xs::zero;
		const int _maxOccurs = xs::one;
	};
	class MD_ImageDescription_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_ImageDescription_PropertyType();
		gmd::MD_ImageDescription m_MD_ImageDescription;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_RangeDimension
	{
	public:
		AFX_EXT_CLASS MD_RangeDimension();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::MemberName_PropertyType> sequenceIdentifier;
		const int sequenceIdentifier_minOccurs = xs::zero;
		const int sequenceIdentifier_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> descriptor;
		const int descriptor_minOccurs = xs::zero;
		const int descriptor_maxOccurs = xs::one;

	};
	class MD_RangeDimension_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_RangeDimension_PropertyType();
		gmd::MD_RangeDimension m_MD_RangeDimension;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_Band
	{
	public:
		AFX_EXT_CLASS MD_Band();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::Real_PropertyType> maxValue;
		const int maxValue_minOccurs = xs::zero;
		const int maxValue_maxOccurs = xs::one;
		list<gco::Real_PropertyType> minValue;
		const int minValue_minOccurs = xs::zero;
		const int minValue_maxOccurs = xs::one;
		list<gco::UomLength_PropertyType> units;
		const int units_minOccurs = xs::zero;
		const int units_maxOccurs = xs::one;
		list<gco::Real_PropertyType> peakResponse;
		const int peakResponse_minOccurs = xs::zero;
		const int peakResponse_maxOccurs = xs::one;
		list<gco::Integer_PropertyType> bitsPerValue;
		const int bitsPerValue_minOccurs = xs::zero;
		const int bitsPerValue_maxOccurs = xs::one;
		list<gco::Integer_PropertyType> toneGradation;
		const int toneGradation_minOccurs = xs::zero;
		const int toneGradation_maxOccurs = xs::one;
		list<gco::Real_PropertyType> scaleFactor;
		const int scaleFactor_minOccurs = xs::zero;
		const int scaleFactor_maxOccurs = xs::one;
		list<gco::Real_PropertyType> offset;
		const int offset_minOccurs = xs::zero;
		const int offset_maxOccurs = xs::one;
	};
	class MD_Band_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_Band_PropertyType();
		gmd::MD_Band m_MD_Band;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_EvaluationMethodTypeCode_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_EvaluationMethodTypeCode_PropertyType();
		gco::CodeListValue_Type DQ_EvaluationMethodTypeCode;
		gco::NilReason m_nilReason;
	};
	class LI_ProcessStep
	{
	public:
		AFX_EXT_CLASS LI_ProcessStep();
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> description;
		const int description_minOccurs = xs::one;
		const int description_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> rationale;
		const int rationale_minOccurs = xs::zero;
		const int rationale_maxOccurs = xs::one;
		list<gco::DateTime_PropertyType> dateTime;
		const int dateTime_minOccurs = xs::one;
		const int dateTime_maxOccurs = xs::one;
		list<gmd::CI_ResponsibleParty_PropertyType> processor;
		const int processor_minOccurs = xs::zero;
		const int processor_maxOccurs = xs::unbounded;
		list<gmd::LI_Source_PropertyType> source;
		const int source_minOccurs = xs::zero;
		const int source_maxOccurs = xs::unbounded;
	};
	class LI_ProcessStep_PropertyType
	{
	public:
		AFX_EXT_CLASS LI_ProcessStep_PropertyType();
		gmd::LI_ProcessStep m_LI_ProcessStep;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class LI_Source
	{
	public:
		AFX_EXT_CLASS LI_Source();
		gco::AbstractObject_Type base;
		list<gco::DateTime_PropertyType> description;
		const int description_minOccurs = xs::zero;
		const int description_maxOccurs = xs::one;
		list<gmd::MD_RepresentativeFraction_PropertyType> scaleDenominator;
		const int scaleDenominator_minOccurs = xs::zero;
		const int scaleDenominator_maxOccurs = xs::one;
		list<gmd::MD_ReferenceSystem_PropertyType> sourceReferenceSystem;
		const int sourceReferenceSystem_minOccurs = xs::zero;
		const int sourceReferenceSystem_maxOccurs = xs::one;
		list<gmd::CI_Citation_PropertyType> sourceCitation;
		const int sourceCitation_minOccurs = xs::zero;
		const int sourceCitation_maxOccurs = xs::one;
		list<gmd::EX_Extent_PropertyType> sourceExtent;
		const int sourceExtent_minOccurs = xs::zero;
		const int sourceExtent_maxOccurs = xs::unbounded;
		list<gmd::LI_ProcessStep_PropertyType> sourceStep;
		const int sourceStep_minOccurs = xs::zero;
		const int sourceStep_maxOccurs = xs::unbounded;
	};
	class LI_Source_PropertyType
	{
	public:
		AFX_EXT_CLASS LI_Source_PropertyType();
		gmd::LI_Source m_LI_Source;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class LI_Lineage
	{
	public:
		AFX_EXT_CLASS LI_Lineage();
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> statement;
		const int statement_minOccurs = xs::zero;
		const int statement_maxOccurs = xs::one;
		list<gmd::LI_ProcessStep_PropertyType> processStep;
		const int processStep_minOccurs = xs::zero;
		const int processStep_maxOccurs = xs::unbounded;
		list<gmd::LI_Source_PropertyType> source;
		const int source_minOccurs = xs::zero;
		const int source_maxOccurs = xs::unbounded;
	};
	class LI_Lineage_PropertyType
	{
	public:
		AFX_EXT_CLASS LI_Lineage_PropertyType();
		gmd::LI_Lineage m_LI_Lineage;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class AbstractDQ_Result
	{
	public:
		AFX_EXT_CLASS AbstractDQ_Result();
		bool abstract = true;
		gco::AbstractObject_Type base;
	};
	class DQ_Result_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_Result_PropertyType();
		gmd::AbstractDQ_Result m_AbstractDQ_Result;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_ConformanceResult
	{
	public:
		AFX_EXT_CLASS DQ_ConformanceResult();
		wstring documentation;
		gmd::AbstractDQ_Result base;
		list<gmd::CI_Citation_PropertyType> specification;
		const int specification_minOccurs = xs::one;
		const int specification_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> explanation;
		const int explanation_minOccurs = xs::one;
		const int explanation_maxOccurs = xs::one;
		list<gco::Boolean_PropertyType> pass;
		const int pass_minOccurs = xs::one;
		const int pass_maxOccurs = xs::one;
	};
	class DQ_ConformanceResult_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_ConformanceResult_PropertyType();
		gmd::DQ_ConformanceResult m_DQ_ConformanceResult;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_QuantitativeResult
	{
	public:
		AFX_EXT_CLASS DQ_QuantitativeResult();
		gmd::AbstractDQ_Result base;
		list<gco::RecordType_PropertyType> valueType;
		const int valueType_minOccurs = xs::one;
		const int valueType_maxOccurs = xs::one;
		list<gco::UnitOfMeasure_PropertyType> valueUnit;
		const int valueUnit_minOccurs = xs::one;
		const int valueUnit_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> errorStatistic;
		const int errorStatistic_minOccurs = xs::one;
		const int errorStatistic_maxOccurs = xs::one;
		list<gco::Record_PropertyType> value;
		const int value_minOccurs = xs::one;
		const int value_maxOccurs = xs::one;
	};
	class DQ_QuantitativeResult_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_QuantitativeResult_PropertyType();
		gmd::DQ_ConformanceResult m_DQ_ConformanceResult;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class AbstractDQ_Element
	{
	public:
		AFX_EXT_CLASS AbstractDQ_Element();
		bool absrtact = true;
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> nameOfMeasure;
		const int nameOfMeasure_minOccurs = xs::zero;
		const int nameOfMeasure_maxOccurs = xs::unbounded;
		list<gmd::MD_Identifier_PropertyType> measureIdentification;
		const int measureIdentification_minOccurs = xs::zero;
		const int measureIdentification_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> measureDescription;
		const int measureDescription_minOccurs = xs::zero;
		const int measureDescription_maxOccurs = xs::one;
		list<gmd::DQ_EvaluationMethodTypeCode_PropertyType> evaluationMethodType;
		const int evaluationMethodType_minOccurs = xs::zero;
		const int evaluationMethodType_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> evaluationMethodDescription;
		const int evaluationMethodDescription_minOccurs = xs::zero;
		const int evaluationMethodDescription_maxOccurs = xs::one;
		list<gmd::CI_Citation_PropertyType> evaluationProcedure;
		const int evaluationProcedure_minOccurs = xs::zero;
		const int evaluationProcedure_maxOccurs = xs::one;
		list<gco::DateTime_PropertyType> dateTime;
		const int dateTime_minOccurs = xs::zero;
		const int dateTime_maxOccurs = xs::unbounded;
		list<gmd::DQ_Result_PropertyType> result;
		const int result_minOccurs = xs::one;
		const int result_maxOccurs = xs::two;
	};
	class DQ_Element_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_Element_PropertyType();
		gmd::AbstractDQ_Element m_AbstractDQ_Element;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class AbstractDQ_TemporalAccuracy
	{
	public:
		AFX_EXT_CLASS AbstractDQ_TemporalAccuracy();
		bool abstract = true;
		gmd::AbstractDQ_Element base;
	};
	class DQ_TemporalAccuracy_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_TemporalAccuracy_PropertyType();
		gmd::AbstractDQ_TemporalAccuracy m_AbstractDQ_TemporalAccuracy;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_TemporalValidity
	{
	public:
		AFX_EXT_CLASS DQ_TemporalValidity();
		gmd::AbstractDQ_TemporalAccuracy base;
	};
	class DQ_TemporalValidity_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_TemporalValidity_PropertyType();
		gmd::DQ_TemporalValidity m_DQ_TemporalValidity;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_TemporalConsistency
	{
	public:
		AFX_EXT_CLASS DQ_TemporalConsistency();
		gmd::AbstractDQ_TemporalAccuracy base;
	};
	class DQ_TemporalConsistency_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_TemporalConsistency_PropertyType();
		gmd::DQ_TemporalConsistency m_DQ_TemporalConsistency;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_AccuracyOfATimeMeasurement
	{
	public:
		AFX_EXT_CLASS DQ_AccuracyOfATimeMeasurement();
		gmd::AbstractDQ_TemporalAccuracy base;
	};
	class DQ_AccuracyOfATimeMeasurement_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_AccuracyOfATimeMeasurement_PropertyType();
		gmd::DQ_AccuracyOfATimeMeasurement m_DQ_AccuracyOfATimeMeasurement;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class AbstractDQ_PositionalAccuracy
	{
	public:
		AFX_EXT_CLASS AbstractDQ_PositionalAccuracy();
		bool abstract = true;
		gmd::AbstractDQ_Element base;
	};
	class DQ_PositionalAccuracy_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_PositionalAccuracy_PropertyType();
		gmd::AbstractDQ_PositionalAccuracy m_AbstractDQ_PositionalAccuracy;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class AbstractDQ_LogicalConsistency
	{
	public:
		AFX_EXT_CLASS AbstractDQ_LogicalConsistency();
		bool abstract = true;
		gmd::AbstractDQ_Element base;
	};
	class DQ_LogicalConsistency_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_LogicalConsistency_PropertyType();
		gmd::AbstractDQ_LogicalConsistency m_AbstractDQ_LogicalConsistency;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class AbstractDQ_Completeness
	{
	public:
		AFX_EXT_CLASS AbstractDQ_Completeness();
		bool abstract = true;
		gmd::AbstractDQ_Element base;
	};
	class DQ_Completeness_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_Completeness_PropertyType();
		gmd::AbstractDQ_Completeness m_AbstractDQ_Completeness;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class AbstractDQ_ThematicAccuracy
	{
	public:
		AFX_EXT_CLASS AbstractDQ_ThematicAccuracy();
		bool abstract = true;
		gmd::AbstractDQ_Element base;
	};
	class DQ_ThematicAccuracy_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_ThematicAccuracy_PropertyType();
		gmd::AbstractDQ_ThematicAccuracy m_AbstractDQ_ThematicAccuracy;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_QuantitativeAttributeAccuracy
	{
	public:
		AFX_EXT_CLASS DQ_QuantitativeAttributeAccuracy();
		gmd::AbstractDQ_ThematicAccuracy base;
	};
	class DQ_QuantitativeAttributeAccuracy_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_QuantitativeAttributeAccuracy_PropertyType();
		gmd::DQ_QuantitativeAttributeAccuracy m_DQ_QuantitativeAttributeAccuracy;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_NonQuantitativeAttributeAccuracy
	{
	public:
		AFX_EXT_CLASS DQ_NonQuantitativeAttributeAccuracy();
		gmd::AbstractDQ_ThematicAccuracy base;
	};
	class DQ_NonQuantitativeAttributeAccuracy_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_NonQuantitativeAttributeAccuracy_PropertyType();
		gmd::DQ_NonQuantitativeAttributeAccuracy m_DQ_NonQuantitativeAttributeAccuracy;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_ThematicClassificationCorrectness
	{
	public:
		AFX_EXT_CLASS DQ_ThematicClassificationCorrectness();
		gmd::AbstractDQ_ThematicAccuracy base;
	};
	class DQ_ThematicClassificationCorrectness_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_ThematicClassificationCorrectness_PropertyType();
		gmd::DQ_ThematicClassificationCorrectness m_DQ_ThematicClassificationCorrectness;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_RelativeInternalPositionalAccuracy
	{
	public:
		AFX_EXT_CLASS DQ_RelativeInternalPositionalAccuracy();
		gmd::AbstractDQ_PositionalAccuracy base;
	};
	class DQ_RelativeInternalPositionalAccuracy_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_RelativeInternalPositionalAccuracy_PropertyType();
		gmd::DQ_RelativeInternalPositionalAccuracy m_DQ_RelativeInternalPositionalAccuracy;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_GriddedDataPositionalAccuracy
	{
	public:
		AFX_EXT_CLASS DQ_GriddedDataPositionalAccuracy();
		gmd::AbstractDQ_PositionalAccuracy base;
	};
	class DQ_GriddedDataPositionalAccuracy_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_GriddedDataPositionalAccuracy_PropertyType();
		gmd::DQ_GriddedDataPositionalAccuracy m_DQ_GriddedDataPositionalAccuracy;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_AbsoluteExternalPositionalAccuracy
	{
	public:
		AFX_EXT_CLASS DQ_AbsoluteExternalPositionalAccuracy();
		gmd::AbstractDQ_PositionalAccuracy base;
	};
	class DQ_AbsoluteExternalPositionalAccuracy_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_AbsoluteExternalPositionalAccuracy_PropertyType();
		gmd::DQ_AbsoluteExternalPositionalAccuracy m_DQ_AbsoluteExternalPositionalAccuracy;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_TopologicalConsistency
	{
	public:
		AFX_EXT_CLASS DQ_TopologicalConsistency();
		gmd::AbstractDQ_LogicalConsistency base;
	};
	class DQ_TopologicalConsistency_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_TopologicalConsistency_PropertyType();
		gmd::DQ_TopologicalConsistency m_DQ_TopologicalConsistency;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_FormatConsistency
	{
	public:
		AFX_EXT_CLASS DQ_FormatConsistency();
		gmd::AbstractDQ_LogicalConsistency base;
	};
	class DQ_FormatConsistency_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_FormatConsistency_PropertyType();
		gmd::DQ_FormatConsistency m_DQ_FormatConsistency;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_DomainConsistency
	{
	public:
		AFX_EXT_CLASS DQ_DomainConsistency();
		gmd::AbstractDQ_LogicalConsistency base;
	};
	class DQ_DomainConsistency_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_DomainConsistency_PropertyType();
		gmd::DQ_DomainConsistency m_DQ_DomainConsistency;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_ConceptualConsistency
	{
	public:
		AFX_EXT_CLASS DQ_ConceptualConsistency();
		gmd::AbstractDQ_LogicalConsistency base;
	};
	class DQ_ConceptualConsistency_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_ConceptualConsistency_PropertyType();
		gmd::DQ_ConceptualConsistency m_DQ_ConceptualConsistency;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_CompletenessOmission
	{
	public:
		AFX_EXT_CLASS DQ_CompletenessOmission();
		gmd::AbstractDQ_Completeness base;
	};
	class DQ_CompletenessOmission_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_CompletenessOmission_PropertyType();
		gmd::DQ_CompletenessOmission m_DQ_CompletenessOmission;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_CompletenessCommission
	{
	public:
		AFX_EXT_CLASS DQ_CompletenessCommission();
		gmd::AbstractDQ_Completeness base;
	};
	class DQ_CompletenessCommission_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_CompletenessCommission_PropertyType();
		gmd::DQ_CompletenessCommission m_DQ_CompletenessCommission;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_DataQuality
	{
	public:
		AFX_EXT_CLASS DQ_DataQuality();
		gco::AbstractObject_Type base;

		list<gmd::DQ_Scope_PropertyType> scope;
		const int scope_minOccurs = xs::one;
		const int scope_maxOccurs = xs::one;
		list<gmd::DQ_Element_PropertyType> report;
		const int report_minOccurs = xs::zero;
		const int report_maxOccurs = xs::unbounded;
		list<gmd::LI_Lineage_PropertyType> lineage;
		const int lineage_minOccurs = xs::zero;
		const int lineage_maxOccurs = xs::one;
	};
	class DQ_DataQuality_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_DataQuality_PropertyType();
		gmd::DQ_DataQuality m_DQ_DataQuality;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DQ_Scope
	{
	public:
		AFX_EXT_CLASS DQ_Scope();
		gco::AbstractObject_Type base;
		list<gmd::MD_ScopeCode_PropertyType> level;
		const int level_minOccurs = xs::one;
		const int level_maxOccurs = xs::one;
		list<gmd::EX_Extent_PropertyType> extent;
		const int extent_minOccurs = xs::zero;
		const int extent_maxOccurs = xs::one;
		list<gmd::MD_ScopeDescription_PropertyType> levelDescription;
		const int levelDescription_minOccurs = xs::zero;
		const int levelDescription_maxOccurs = xs::unbounded;
	};
	class DQ_Scope_PropertyType
	{
	public:
		AFX_EXT_CLASS DQ_Scope_PropertyType();
		gmd::DQ_Scope m_DQ_Scope;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_DistributionUnits_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_DistributionUnits_PropertyType();
		gco::CodeListValue_Type m_MD_DistributionUnits;
		gco::NilReason m_nilReason;
	};
	class MD_MediumFormatCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_MediumFormatCode_PropertyType();
		gco::CodeListValue_Type m_MD_MediumFormatCode;
		gco::NilReason m_nilReason;
	};
	class MD_MediumNameCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_MediumNameCode_PropertyType();
		gco::CodeListValue_Type m_MD_MediumNameCode;
		gco::NilReason m_nilReason;
	};
	class MD_Medium
	{
	public:
		AFX_EXT_CLASS MD_Medium();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gmd::MD_MediumNameCode_PropertyType> name;
		const int name_minOccurs = xs::zero;
		const int name_maxOccurs = xs::one;
		list<gco::Real_PropertyType> density;
		const int density_minOccurs = xs::zero;
		const int density_maxOccurs = xs::unbounded;
		list<gco::CharacterString_PropertyType> densityUnits;
		const int densityUnits_minOccurs = xs::zero;
		const int densityUnits_maxOccurs = xs::one;
		list<gco::Integer_PropertyType> volumes;
		const int volumes_minOccurs = xs::zero;
		const int volumes_maxOccurs = xs::one;
		list<gmd::MD_MediumFormatCode_PropertyType> mediumFormat;
		const int mediumFormat_minOccurs = xs::zero;
		const int mediumFormat_maxOccurs = xs::unbounded;
		list<gco::CharacterString_PropertyType> mediumNote;
		const int mediumNote_minOccurs = xs::zero;
		const int mediumNote_maxOccurs = xs::one;
	};
	class MD_Medium_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_Medium_PropertyType();
		MD_Medium m_MD_Medium;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_DigitalTransferOptions
	{
	public:
		AFX_EXT_CLASS MD_DigitalTransferOptions();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> unitsOfDistribution;
		const int unitsOfDistribution_minOccurs = xs::zero;
		const int unitsOfDistribution_maxOccurs = xs::one;
		list<gco::Real_PropertyType> transferSize;
		const int transferSize_minOccurs = xs::zero;
		const int transferSize_maxOccurs = xs::one;
		list<gmd::CI_OnlineResource_PropertyType> onLine;
		const int onLine_minOccurs = xs::zero;
		const int onLine_maxOccurs = xs::unbounded;
		list<gmd::MD_Medium_PropertyType> offLine;
		const int offLine_minOccurs = xs::zero;
		const int offLine_maxOccurs = xs::one;
	};
	class MD_DigitalTransferOptions_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_DigitalTransferOptions_PropertyType();
		gmd::MD_DigitalTransferOptions m_MD_DigitalTransferOptions;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_StandardOrderProcess
	{
	public:
		AFX_EXT_CLASS MD_StandardOrderProcess();
		wstring documentation;
		gco::AbstractObject_Type base;

		list<gco::CharacterString_PropertyType> fees;
		const int fees_minOccurs = xs::zero;
		const int fees_maxOccurs = xs::one;
		list<gco::DateTime_PropertyType> plannedAvailableDateTime;
		const int plannedAvailableDateTime_minOccurs = xs::zero;
		const int plannedAvailableDateTime_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> orderingInstructions;
		const int orderingInstructions_minOccurs = xs::zero;
		const int orderingInstructions_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> turnaround;
		const int turnaround_minOccurs = xs::zero;
		const int turnaround_maxOccurs = xs::one;
	};
	class MD_StandardOrderProcess_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_StandardOrderProcess_PropertyType();
		gmd::MD_StandardOrderProcess m_MD_StandardOrderProcess;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_Distributor
	{
	public:
		AFX_EXT_CLASS MD_Distributor();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gmd::CI_ResponsibleParty_PropertyType> distributorContact;
		const int distributorContact_minOccurs = xs::one;
		const int distributorContact_maxOccurs = xs::one;
		list<gmd::MD_StandardOrderProcess_PropertyType> distributionOrderProcess;
		const int distributionOrderProcess_minOccurs = xs::zero;
		const int distributionOrderProcess_maxOccurs = xs::unbounded;
		list<gmd::MD_Format_PropertyType> distributorFormat;
		const int distributorFormat_minOccurs = xs::zero;
		const int distributorFormat_maxOccurs = xs::unbounded;
		list<gmd::MD_DigitalTransferOptions_PropertyType> distributorTransferOptions;
		const int distributorTransferOptions_minOccurs = xs::zero;
		const int distributorTransferOptions_maxOccurs = xs::unbounded;
	};
	class MD_Distributor_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_Distributor_PropertyType();
		gmd::MD_Distributor m_MD_Distributor;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_Distribution
	{
	public:
		AFX_EXT_CLASS MD_Distribution();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gmd::MD_Format_PropertyType> distributionFormat;
		const int distributionFormat_minOccurs = xs::zero;
		const int distributionFormat_maxOccurs = xs::unbounded;
		list<gmd::MD_Distributor_PropertyType> distributor;
		const int distributor_minOccurs = xs::zero;
		const int distributor_maxOccurs = xs::unbounded;
		list<gmd::MD_DigitalTransferOptions_PropertyType> transferOptions;
		const int transferOptions_minOccurs = xs::zero;
		const int transferOptions_maxOccurs = xs::unbounded;
	};
	class MD_Distribution_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_Distribution_PropertyType();
		gmd::MD_Distribution m_MD_Distribution;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_Format
	{
	public:
		AFX_EXT_CLASS MD_Format();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> name;
		const int name_minOccurs = xs::one;
		const int name_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> version;
		const int version_minOccurs = xs::one;
		const int version_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> amendmentNumber;
		const int amendmentNumber_minOccurs = xs::zero;
		const int amendmentNumber_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> specification;
		const int specification_minOccurs = xs::zero;
		const int specification_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> fileDecompressionTechnique;
		const int fileDecompressionTechnique_minOccurs = xs::zero;
		const int fileDecompressionTechnique_maxOccurs = xs::one;
		list<gmd::MD_Distributor_PropertyType> formatDistributor;
		const int formatDistributor_minOccurs = xs::zero;
		const int formatDistributor_maxOccurs = xs::unbounded;
	};
	class MD_Format_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_Format_PropertyType();
		gmd::MD_Format m_MD_Format;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class EX_TemporalExtent
	{
	public:
		AFX_EXT_CLASS EX_TemporalExtent();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gts::TM_PeriodDuration_PropertyType> extent;
		const int extent_minOccurs = xs::one;
		const int extent_maxOccurs = xs::one;
	};
	class EX_TemporalExtent_PropertyType
	{
	public:
		AFX_EXT_CLASS EX_TemporalExtent_PropertyType();
		gmd::EX_TemporalExtent m_EX_TemporalExtent;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class EX_VerticalExtent
	{
	public:
		AFX_EXT_CLASS EX_VerticalExtent();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::Real_PropertyType> minimumValue;
		const int minimumValue_minOccurs = xs::one;
		const int minimumValue_maxOccurs = xs::one;
		list<gco::Real_PropertyType> maximumValue;
		const int maximumValue_minOccurs = xs::one;
		const int maximumValue_maxOccurs = xs::one;
		list<gsr::SC_CRS_PropertyType> verticalCRS;
		const int verticalCRS_minOccurs = xs::one;
		const int verticalCRS_maxOccurs = xs::one;

	};
	class EX_VerticalExtent_PropertyType
	{
	public:
		AFX_EXT_CLASS EX_VerticalExtent_PropertyType();
		gmd::EX_VerticalExtent m_EX_VerticalExtent;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class AbstractEX_GeographicExtent
	{
	public:
		AFX_EXT_CLASS AbstractEX_GeographicExtent();
		bool abstract = true;
		wstring documentation;
		gco::AbstractObject_Type base;

		list<gco::Boolean_PropertyType> extentTypeCode;
		const int extentTypeCode_minOccurs = xs::zero;
		const int extentTypeCode_maxOccurs = xs::one;
	};
	class EX_GeographicExtent_PropertyType
	{
	public:
		AFX_EXT_CLASS EX_GeographicExtent_PropertyType();
		gmd::AbstractEX_GeographicExtent m_AbstractEX_GeographicExtent;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class EX_BoundingPolygon
	{
	public:
		AFX_EXT_CLASS EX_BoundingPolygon();
		wstring documentation;
		gmd::AbstractEX_GeographicExtent base;
		list<gss::GM_Object_PropertyType> polygon;
		const int polygon_minOccurs = xs::one;
		const int polygon_maxOccurs = xs::unbounded;
	};
	class EX_BoundingPolygon_PropertyType
	{
	public:
		AFX_EXT_CLASS EX_BoundingPolygon_PropertyType();
		gmd::EX_BoundingPolygon m_EX_BoundingPolygon;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class EX_Extent
	{
	public:
		AFX_EXT_CLASS EX_Extent();
		wstring documentation;
		gco::AbstractObject_Type base;

		list<gco::CharacterString_PropertyType> description;
		const int description_minOccurs = xs::zero;
		const int description_maxOccurs = xs::one;
		list<gmd::EX_GeographicExtent_PropertyType> geographicElement;
		const int geographicElement_minOccurs = xs::zero;
		const int geographicElement_maxOccurs = xs::unbounded;
		list<gmd::EX_TemporalExtent_PropertyType> temporalElement;
		const int temporalElement_minOccurs = xs::zero;
		const int temporalElement_maxOccurs = xs::unbounded;
		list<gmd::EX_VerticalExtent_PropertyType> verticalElement;
		const int verticalElement_minOccurs = xs::zero;
		const int verticalElement_maxOccurs = xs::unbounded;
	};
	class EX_Extent_PropertyType
	{
	public:
		AFX_EXT_CLASS EX_Extent_PropertyType();
		gmd::EX_Extent m_EX_Extent;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class EX_GeographicBoundingBox
	{
	public:
		AFX_EXT_CLASS EX_GeographicBoundingBox();
		wstring documentation;
		gmd::AbstractEX_GeographicExtent base;

		list<gco::Decimal_PropertyType> westBoundLongitude;
		const int westBoundLongitude_minOccurs = xs::zero;
		const int westBoundLongitude_maxOccurs = xs::one;
		list<gco::Decimal_PropertyType> eastBoundLongitude;
		const int eastBoundLongitude_minOccurs = xs::zero;
		const int eastBoundLongitude_maxOccurs = xs::one;
		list<gco::Decimal_PropertyType> southBoundLatitude;
		const int southBoundLatitude_minOccurs = xs::zero;
		const int southBoundLatitude_maxOccurs = xs::one;
		list<gco::Decimal_PropertyType> northBoundLatitude;
		const int northBoundLatitude_minOccurs = xs::zero;
		const int northBoundLatitude_maxOccurs = xs::one;
	};
	class EX_GeographicBoundingBox_PropertyType
	{
	public:
		AFX_EXT_CLASS EX_GeographicBoundingBox_PropertyType();
		gmd::EX_GeographicBoundingBox m_EX_GeographicBoundingBox;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class EX_SpatialTemporalExtent
	{
	public:
		AFX_EXT_CLASS EX_SpatialTemporalExtent();
		wstring documentation;
		gmd::EX_TemporalExtent base;

		list<gmd::EX_GeographicExtent_PropertyType> spatialExtent;
		const int spatialExtent_minOccurs = xs::one;
		const int spatialExtent_maxOccurs = xs::unbounded;
	};
	class EX_SpatialTemporalExtent_PropertyType
	{
	public:
		AFX_EXT_CLASS EX_SpatialTemporalExtent_PropertyType();
		gmd::EX_SpatialTemporalExtent m_EX_SpatialTemporalExtent;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class EX_GeographicDescription
	{
	public:
		AFX_EXT_CLASS EX_GeographicDescription();
		wstring documentation;
		gmd::EX_TemporalExtent base;

		list<gmd::EX_GeographicExtent_PropertyType> geographicIdentifier;
		const int geographicIdentifier_minOccurs = xs::one;
		const int geographicIdentifier_maxOccurs = xs::one;
	};
	class EX_GeographicDescription_PropertyType
	{
	public:
		AFX_EXT_CLASS EX_GeographicDescription_PropertyType();
		gmd::EX_GeographicDescription m_EX_GeographicDescription;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class LanguageCode_PropertyType
	{
	public:
		AFX_EXT_CLASS LanguageCode_PropertyType();
		gco::CodeListValue_Type m_LanguageCode;
		gco::NilReason m_nilReason;
	};
	class Country_PropertyType
	{
	public:
		AFX_EXT_CLASS Country_PropertyType();
		gco::CodeListValue_Type m_Country;
		gco::NilReason m_nilReason;
	};
	class PT_FreeText
	{
	public:
		AFX_EXT_CLASS PT_FreeText();
		gco::AbstractObject_Type base;
	};
	class PT_FreeText_PropertyType
	{
	public:
		AFX_EXT_CLASS PT_FreeText_PropertyType();
		gco::CharacterString_PropertyType base;
		gmd::PT_FreeText m_PT_FreeText;
	};
	class PT_Locale
	{
	public:
		AFX_EXT_CLASS PT_Locale();
		gco::AbstractObject_Type base;
		list<gmd::LanguageCode_PropertyType> languageCode;
		const int languageCode_minOccurs = xs::one;
		const int languageCode_maxOccurs = xs::one;
		list<gmd::Country_PropertyType> country;
		const int country_minOccurs = xs::zero;
		const int country_maxOccurs = xs::one;
		list<gmd::MD_CharacterSetCode_PropertyType> characterEncoding;
		const int characterEncoding_minOccurs = xs::one;
		const int characterEncoding_maxOccurs = xs::one;
	};
	class PT_Locale_PropertyType
	{
	public:
		AFX_EXT_CLASS PT_Locale_PropertyType();
		gmd::PT_Locale m_PT_Locale;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class LocalisedCharacterString
	{
	public:
		AFX_EXT_CLASS LocalisedCharacterString();
		wstring base;
		list<wstring> id;
		const int id_minOccurs = xs::one;
		const int id_maxOccurs = xs::one;
		list<wstring> locale;
		const int locale_minOccurs = xs::one;
		const int locale_maxOccurs = xs::one;
	};
	class LocalisedCharacterString_PropertyType
	{
	public:
		AFX_EXT_CLASS LocalisedCharacterString_PropertyType();
		gmd::LocalisedCharacterString m_LocalisedCharacterString;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class PT_LocaleContainer
	{
	public:
		AFX_EXT_CLASS PT_LocaleContainer();
		wstring base;
		list<gco::CharacterString_PropertyType> description;
		const int description_minOccurs = xs::one;
		const int description_maxOccurs = xs::one;
		list<gmd::PT_Locale_PropertyType> locale;
		const int locale_minOccurs = xs::one;
		const int locale_maxOccurs = xs::one;
		list<gmd::CI_Date_PropertyType> date;
		const int date_minOccurs = xs::one;
		const int date_maxOccurs = xs::unbounded;
		list<gmd::CI_ResponsibleParty_PropertyType> responsibleParty;
		const int responsibleParty_minOccurs = xs::one;
		const int responsibleParty_maxOccurs = xs::unbounded;
		list<gmd::LocalisedCharacterString_PropertyType> localisedString;
		const int localisedString_minOccurs = xs::one;
		const int localisedString_maxOccurs = xs::unbounded;
	};
	class PT_LocaleContainer_PropertyType
	{
	public:
		AFX_EXT_CLASS PT_LocaleContainer_PropertyType();
		gmd::PT_LocaleContainer m_PT_LocaleContainer;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_CharacterSetCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_CharacterSetCode_PropertyType();
		gco::CodeListValue_Type m_MD_CharacterSetCode;
		gco::NilReason m_nilReason;
	};
	class MD_SpatialRepresentationTypeCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_SpatialRepresentationTypeCode_PropertyType();
		gco::CodeListValue_Type m_MD_SpatialRepresentationTypeCode;
		gco::NilReason m_nilReason;
	};
	class MD_ProgressCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_ProgressCode_PropertyType();
		gco::CodeListValue_Type m_MD_ProgressCode;
		gco::NilReason m_nilReason;
	};
	class MD_KeywordTypeCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_KeywordTypeCode_PropertyType();
		gco::CodeListValue_Type m_MD_KeywordTypeCode;
		gco::NilReason m_nilReason;
	};
	class DS_AssociationTypeCode_PropertyType
	{
	public:
		AFX_EXT_CLASS DS_AssociationTypeCode_PropertyType();
		gco::CodeListValue_Type m_DS_AssociationTypeCode;
		gco::NilReason m_nilReason;
	};
	class DS_InitiativeTypeCode_PropertyType
	{
	public:
		AFX_EXT_CLASS DS_InitiativeTypeCode_PropertyType();
		gco::CodeListValue_Type m_DS_InitiativeTypeCode;
		gco::NilReason m_nilReason;
	};
	class AbstractMD_Identification
	{
	public:
		AFX_EXT_CLASS AbstractMD_Identification();
		bool abstract = true;
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gmd::CI_Citation_PropertyType> citation;
		const int citation_minOccurs = xs::one;
		const int citation_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> purpose;
		const int purpose_minOccurs = xs::zero;
		const int purpose_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> credit;
		const int credit_minOccurs = xs::zero;
		const int credit_maxOccurs = xs::unbounded;
		list<gmd::MD_ProgressCode_PropertyType> status;
		const int status_minOccurs = xs::zero;
		const int status_maxOccurs = xs::unbounded;
		list<gmd::CI_ResponsibleParty_PropertyType> pointOfContact;
		const int pointOfContact_minOccurs = xs::zero;
		const int pointOfContact_maxOccurs = xs::unbounded;
		list<gmd::MD_BrowseGraphic_PropertyType> graphicOverview;
		const int graphicOverview_minOccurs = xs::zero;
		const int graphicOverview_maxOccurs = xs::unbounded;
		list<gmd::MD_Format_PropertyType> resourceFormat;
		const int resourceFormat_minOccurs = xs::zero;
		const int resourceFormat_maxOccurs = xs::unbounded;
		list<gmd::MD_Keywords_PropertyType> descriptiveKeywords;
		const int _minOccurs = xs::zero;
		const int _maxOccurs = xs::unbounded;
		list<gmd::MD_Usage_PropertyType> resourceSpecificUsage;
		const int resourceSpecificUsage_minOccurs = xs::zero;
		const int resourceSpecificUsage_maxOccurs = xs::unbounded;
		list<gmd::MD_Constraints_PropertyType> resourceConstraints;
		const int resourceConstraints_minOccurs = xs::zero;
		const int resourceConstraints_maxOccurs = xs::unbounded;
		list<gmd::MD_AggregateInformation_PropertyType> aggregationInfo;
		const int aggregationInfo_minOccurs = xs::zero;
		const int aggregationInfo_maxOccurs = xs::unbounded;
	};
	class MD_Identification_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_Identification_PropertyType();
		gmd::AbstractMD_Identification m_AbstractMD_Identification;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_BrowseGraphic
	{
	public:
		AFX_EXT_CLASS MD_BrowseGraphic();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> fileName;
		const int fileName_minOccurs = xs::one;
		const int fileName_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> fileDescription;
		const int fileDescription_minOccurs = xs::zero;
		const int fileDescription_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> fileType;
		const int fileType_minOccurs = xs::zero;
		const int fileType_maxOccurs = xs::one;
	};
	class MD_BrowseGraphic_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_BrowseGraphic_PropertyType();
		gmd::MD_BrowseGraphic m_MD_BrowseGraphic;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_DataIdentification
	{
	public:
		AFX_EXT_CLASS MD_DataIdentification();
		gmd::AbstractMD_Identification base;
		list<gmd::MD_SpatialRepresentationTypeCode_PropertyType> spatialRepresentationType;
		const int spatialRepresentationType_minOccurs = xs::one;
		const int spatialRepresentationType_maxOccurs = xs::unbounded;
		list<gmd::MD_Resolution_PropertyType> spatialResolution;
		const int spatialResolution_minOccurs = xs::one;
		const int spatialResolution_maxOccurs = xs::unbounded;
		list<gco::CharacterString_PropertyType> language;
		const int language_minOccurs = xs::one;
		const int language_maxOccurs = xs::unbounded;
		list<gmd::MD_CharacterSetCode_PropertyType> characterSet;
		const int characterSet_minOccurs = xs::zero;
		const int characterSet_maxOccurs = xs::unbounded;
		list<gmd::MD_TopicCategoryCode_PropertyType> topicCategory;
		const int topicCategory_minOccurs = xs::one;
		const int topicCategory_maxOccurs = xs::unbounded;
		list<gco::CharacterString_PropertyType> environmentDescription;
		const int environmentDescription_minOccurs = xs::zero;
		const int environmentDescription_maxOccurs = xs::one;
		list<gmd::EX_Extent_PropertyType> extent;
		const int extent_minOccurs = xs::one;
		const int extent_maxOccurs = xs::unbounded;
		list<gco::CharacterString_PropertyType> supplementalInformation;
		const int supplementalInformation_minOccurs = xs::zero;
		const int supplementalInformation_maxOccurs = xs::one;
	};
	class MD_DataIdentification_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_DataIdentification_PropertyType();
		gmd::MD_DataIdentification m_MD_DataIdentification;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_ServiceIdentification
	{
	public:
		AFX_EXT_CLASS MD_ServiceIdentification();
		wstring documentation;
		gmd::AbstractMD_Identification base;
	};
	class MD_ServiceIdentification_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_ServiceIdentification_PropertyType();
		gmd::MD_ServiceIdentification m_MD_ServiceIdentification;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_RepresentativeFraction
	{
	public:
		AFX_EXT_CLASS MD_RepresentativeFraction();
		gco::AbstractObject_Type base;
		list<gco::Integer_PropertyType> denominator;
		const int denominator_minOccurs = xs::one;
		const int denominator_maxOccurs = xs::one;
	};
	class MD_RepresentativeFraction_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_RepresentativeFraction_PropertyType();
		gmd::MD_RepresentativeFraction m_MD_RepresentativeFraction;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_Usage
	{
	public:
		AFX_EXT_CLASS MD_Usage();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> SpecificUsage;
		const int SpecificUsage_minOccurs = xs::one;
		const int SpecificUsage_maxOccurs = xs::one;
		list<gco::DateTime> usageDateTime;
		const int usageDateTime_minOccurs = xs::zero;
		const int usageDateTime_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> userDeterminedxsations;
		const int userDeterminedxsations_minOccurs = xs::zero;
		const int userDeterminedxsations_maxOccurs = xs::one;
		list<gmd::CI_ResponsibleParty_PropertyType> userContactInfo;
		const int userContactInfo_minOccurs = xs::one;
		const int userContactInfo_maxOccurs = xs::unbounded;
	};
	class MD_Usage_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_Usage_PropertyType();
		gmd::MD_Usage m_MD_Usage;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_Keywords
	{
	public:
		AFX_EXT_CLASS MD_Keywords();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> keyword;
		const int userDeterminedxsations_minOccurs = xs::one;
		const int userDeterminedxsations_maxOccurs = xs::unbounded;
		list<gmd::MD_KeywordTypeCode_PropertyType> type;
		const int type_minOccurs = xs::zero;
		const int type_maxOccurs = xs::one;
		list<gmd::CI_Citation_PropertyType> thesaurusName;
		const int thesaurusName_minOccurs = xs::zero;
		const int thesaurusName_maxOccurs = xs::one;

	};
	class MD_Keywords_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_Keywords_PropertyType();
		gmd::MD_Keywords m_MD_Keywords;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DS_Association
	{
	public:
		AFX_EXT_CLASS DS_Association();
		gco::AbstractObject_Type base;
	};
	class DS_Association_PropertyType
	{
	public:
		AFX_EXT_CLASS DS_Association_PropertyType();
		gmd::DS_Association m_DS_Association;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_AggregateInformation
	{
	public:
		AFX_EXT_CLASS MD_AggregateInformation();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gmd::CI_Citation_PropertyType> aggregateDataSetName;
		const int aggregateDataSetName_minOccurs = xs::zero;
		const int aggregateDataSetName_maxOccurs = xs::one;
		list<gmd::MD_Identifier_PropertyType> aggregateDataSetIdentifier;
		const int aggregateDataSetIdentifier_minOccurs = xs::zero;
		const int aggregateDataSetIdentifier_maxOccurs = xs::one;
		list<gmd::DS_AssociationTypeCode_PropertyType> associationType;
		const int associationType_minOccurs = xs::one;
		const int associationType_maxOccurs = xs::one;
		list<gmd::DS_InitiativeTypeCode_PropertyType> initiativeType;
		const int initiativeType_minOccurs = xs::zero;
		const int initiativeType_maxOccurs = xs::one;
	};
	class MD_AggregateInformation_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_AggregateInformation_PropertyType();
		gmd::MD_AggregateInformation m_MD_AggregateInformation;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_Resolution
	{
	public:
		AFX_EXT_CLASS MD_Resolution();

		list<gmd::MD_RepresentativeFraction_PropertyType> equivalentScale;
		const int equivalentScale_minOccurs = xs::one;
		const int equivalentScale_maxOccurs = xs::one;
		list<gco::Distance_PropertyType> distance;
		const int distance_minOccurs = xs::one;
		const int distance_maxOccurs = xs::one;
	};
	class MD_Resolution_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_Resolution_PropertyType();
		gmd::MD_Resolution m_MD_Resolution;
		gco::NilReason m_nilReason;
	};
	class MD_TopicCategoryCode
	{
	public:
		wstring documentation;
		list<wstring> base;

		AFX_EXT_CLASS MD_TopicCategoryCode();
	};
	class MD_TopicCategoryCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_TopicCategoryCode_PropertyType();
		gmd::MD_TopicCategoryCode m_MD_TopicCategoryCode;
		gco::NilReason m_nilReason;
	};
	class MD_MaintenanceFrequencyCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_MaintenanceFrequencyCode_PropertyType();
		gco::CodeListValue_Type MD_MaintenanceFrequencyCode;
		gco::NilReason m_nilReason;
	};
	class MD_ScopeCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_ScopeCode_PropertyType();
		gco::CodeListValue_Type m_MD_ScopeCode;
		gco::NilReason m_nilReason;
	};
	class MD_MaintenanceInformation
	{
	public:
		AFX_EXT_CLASS MD_MaintenanceInformation();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gmd::MD_MaintenanceFrequencyCode_PropertyType> maintenanceAndUpdateFrequency;
		const int maintenanceAndUpdateFrequency_minOccurs = xs::one;
		const int maintenanceAndUpdateFrequency_maxOccurs = xs::one;
		list<gco::Date_PropertyType> dateOfNextUpdate;
		const int dateOfNextUpdate_minOccurs = xs::zero;
		const int dateOfNextUpdate_maxOccurs = xs::one;
		list<gts::TM_PeriodDuration_PropertyType> userDefinedMaintenanceFrequency;
		const int userDefinedMaintenanceFrequency_minOccurs = xs::zero;
		const int userDefinedMaintenanceFrequency_maxOccurs = xs::one;
		list<gmd::MD_ScopeCode_PropertyType> updateScope;
		const int updateScope_minOccurs = xs::zero;
		const int updateScope_maxOccurs = xs::unbounded;
		list<gmd::MD_ScopeDescription_PropertyType> updateScopeDescription;
		const int updateScopeDescription_minOccurs = xs::zero;
		const int updateScopeDescription_maxOccurs = xs::unbounded;
		list<gco::CharacterString_PropertyType> maintenanceNote;
		const int maintenanceNote_minOccurs = xs::zero;
		const int maintenanceNote_maxOccurs = xs::unbounded;
		list<gmd::CI_ResponsibleParty_PropertyType> contact;
		const int contact_minOccurs = xs::zero;
		const int contact_maxOccurs = xs::unbounded;
	};
	class MD_MaintenanceInformation_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_MaintenanceInformation_PropertyType();
		gmd::MD_MaintenanceInformation m_MD_MaintenanceInformation;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_ScopeDescription
	{
	public:
		AFX_EXT_CLASS MD_ScopeDescription();
		wstring documentation;
		list<gco::ObjectReference_PropertyType> attributes;
		const int attributes_minOccurs = xs::one;
		const int attributes_maxOccurs = xs::unbounded;
		list<gco::ObjectReference_PropertyType> features;
		const int features_minOccurs = xs::one;
		const int features_maxOccurs = xs::unbounded;
		list<gco::ObjectReference_PropertyType> featureInstances;
		const int featureInstances_minOccurs = xs::one;
		const int featureInstances_maxOccurs = xs::unbounded;
		list<gco::ObjectReference_PropertyType> attributeInstances;
		const int attributeInstances_minOccurs = xs::one;
		const int attributeInstances_maxOccurs = xs::unbounded;
		list<gco::CharacterString_PropertyType> dataset;
		const int dataset_minOccurs = xs::one;
		const int dataset_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> other;
		const int other_minOccurs = xs::one;
		const int other_maxOccurs = xs::one;
	};
	class MD_ScopeDescription_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_ScopeDescription_PropertyType();
		gmd::MD_ScopeDescription m_MD_ScopeDescription;
		gco::NilReason m_nilReason;
	};
	class AbstractDS_Aggregate
	{
	public:
		AFX_EXT_CLASS AbstractDS_Aggregate();
		bool abstract = true;
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gmd::DS_DataSet_PropertyType> composedOf;
		const int composedOf_minOccurs = xs::one;
		const int composedOf_maxOccurs = xs::unbounded;
		list<gmd::MD_Metadata_PropertyType> seriesMetadata;
		const int seriesMetadata_minOccurs = xs::one;
		const int seriesMetadata_maxOccurs = xs::unbounded;
		list<gmd::DS_Aggregate_PropertyType> subset;
		const int subset_minOccurs = xs::zero;
		const int subset_maxOccurs = xs::unbounded;
		list<gmd::DS_Aggregate_PropertyType> superset;
		const int superset_minOccurs = xs::zero;
		const int superset_maxOccurs = xs::unbounded;
	};
	class DS_Aggregate_PropertyType
	{
	public:
		AFX_EXT_CLASS DS_Aggregate_PropertyType();
		gmd::AbstractDS_Aggregate m_AbstractDS_Aggregate;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DS_DataSet
	{
	public:
		AFX_EXT_CLASS DS_DataSet();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gmd::MD_Metadata_PropertyType> has;
		const int has_minOccurs = xs::one;
		const int has_maxOccurs = xs::unbounded;
		list<gmd::DS_Aggregate_PropertyType> partOf;
		const int partOf_minOccurs = xs::zero;
		const int partOf_maxOccurs = xs::unbounded;
	};
	class DS_DataSet_PropertyType
	{
	public:
		AFX_EXT_CLASS DS_DataSet_PropertyType();
		gmd::DS_DataSet m_DS_DataSet;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DS_OtherAggregate
	{
	public:
		AFX_EXT_CLASS DS_OtherAggregate();
		gmd::AbstractDS_Aggregate base;
	};
	class DS_OtherAggregate_PropertyType
	{
	public:
		AFX_EXT_CLASS DS_OtherAggregate_PropertyType();
		gmd::DS_OtherAggregate m_DS_OtherAggregate;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DS_Series
	{
	public:
		AFX_EXT_CLASS DS_Series();
		gmd::AbstractDS_Aggregate base;
	};
	class DS_Series_PropertyType
	{
	public:
		AFX_EXT_CLASS DS_Series_PropertyType();
		gmd::DS_Series m_DS_Series;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DS_Initiative
	{
	public:
		AFX_EXT_CLASS DS_Initiative();
		gmd::AbstractDS_Aggregate base;
	};
	class DS_Initiative_PropertyType
	{
	public:
		AFX_EXT_CLASS DS_Initiative_PropertyType();
		gmd::DS_Initiative m_DS_Initiative;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DS_Platform
	{
	public:
		AFX_EXT_CLASS DS_Platform();
		gmd::DS_Series base;
	};
	class DS_Platform_PropertyType
	{
	public:
		AFX_EXT_CLASS DS_Platform_PropertyType();
		gmd::DS_Platform m_DS_Platform;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DS_Sensor
	{
	public:
		AFX_EXT_CLASS DS_Sensor();
		gmd::DS_Series base;
	};
	class DS_Sensor_PropertyType
	{
	public:
		AFX_EXT_CLASS DS_Sensor_PropertyType();
		gmd::DS_Sensor m_DS_Sensor;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DS_ProductionSeries
	{
	public:
		AFX_EXT_CLASS DS_ProductionSeries();
		gmd::DS_Series base;
	};
	class DS_ProductionSeries_PropertyType
	{
	public:
		AFX_EXT_CLASS DS_ProductionSeries_PropertyType();
		gmd::DS_ProductionSeries m_DS_ProductionSeries;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class DS_StereoMate
	{
	public:
		AFX_EXT_CLASS DS_StereoMate();
		gmd::DS_OtherAggregate base;
	};
	class DS_StereoMate_PropertyType
	{
	public:
		AFX_EXT_CLASS DS_StereoMate_PropertyType();
		gmd::DS_StereoMate m_DS_StereoMate;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_Metadata
	{
	public:
		AFX_EXT_CLASS MD_Metadata();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> fileIdentifier;
		const int fileIdentifier_minOccurs = xs::zero;
		const int fileIdentifier_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> language;
		const int language_minOccurs = xs::zero;
		const int language_maxOccurs = xs::one;
		list<gmd::MD_CharacterSetCode_PropertyType> characterSet;
		const int characterSet_minOccurs = xs::zero;
		const int characterSet_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> parentIdentifier;
		const int parentIdentifier_minOccurs = xs::zero;
		const int parentIdentifier_maxOccurs = xs::one;
		list<gmd::MD_ScopeCode_PropertyType> hierarchyLevel;
		const int hierarchyLevel_minOccurs = xs::zero;
		const int hierarchyLevel_maxOccurs = xs::unbounded;
		list<gco::CharacterString_PropertyType> hierarchyLevelName;
		const int hierarchyLevelName_minOccurs = xs::zero;
		const int hierarchyLevelName_maxOccurs = xs::unbounded;
		list<gmd::CI_ResponsibleParty_PropertyType> contact;
		const int contact_minOccurs = xs::zero;
		const int contact_maxOccurs = xs::unbounded;
		list<gco::Date_PropertyType> dateStamp;
		const int dateStamp_minOccurs = xs::zero;
		const int dateStamp_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> metadataStandardName;
		const int metadataStandardName_minOccurs = xs::zero;
		const int metadataStandardName_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> metadataStandardVersion;
		const int metadataStandardVersion_minOccurs = xs::zero;
		const int metadataStandardVersion_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> dataSetURI;
		const int dataSetURI_minOccurs = xs::zero;
		const int dataSetURI_maxOccurs = xs::one;
		list<gmd::PT_Locale_PropertyType> locale;
		const int locale_minOccurs = xs::zero;
		const int locale_maxOccurs = xs::unbounded;
		list<gmd::MD_SpatialRepresentation_PropertyType> spatialRepresentationInfo;
		const int spatialRepresentationInfo_minOccurs = xs::zero;
		const int spatialRepresentationInfo_maxOccurs = xs::unbounded;
		list<gmd::MD_ReferenceSystem_PropertyType> referenceSystemInfo;
		const int referenceSystemInfo_minOccurs = xs::zero;
		const int referenceSystemInfo_maxOccurs = xs::unbounded;
		list<gmd::MD_MetadataExtensionInformation_PropertyType> metadataExtensionInfo;
		const int metadataExtensionInfo_minOccurs = xs::zero;
		const int metadataExtensionInfo_maxOccurs = xs::unbounded;
		list<gmd::MD_Identification_PropertyType> identificationInfo;
		const int identificationInfo_minOccurs = xs::zero;
		const int identificationInfo_maxOccurs = xs::unbounded;
		list<gmd::MD_ContentInformation_PropertyType> contentInfo;
		const int contentInfo_minOccurs = xs::zero;
		const int contentInfo_maxOccurs = xs::unbounded;
		list<gmd::MD_Distribution_PropertyType> distributionInfo;
		const int distributionInfo_minOccurs = xs::zero;
		const int distributionInfo_maxOccurs = xs::one;
		list<gmd::DQ_DataQuality_PropertyType> dataQualityInfo;
		const int dataQualityInfo_minOccurs = xs::zero;
		const int dataQualityInfo_maxOccurs = xs::unbounded;
		list<gmd::MD_PortrayalCatalogueReference_PropertyType> portrayalCatalogueInfo;
		const int portrayalCatalogueInfo_minOccurs = xs::zero;
		const int portrayalCatalogueInfo_maxOccurs = xs::unbounded;
		list<gmd::MD_Constraints_PropertyType> metadataConstraints;
		const int metadataConstraints_minOccurs = xs::zero;
		const int metadataConstraints_maxOccurs = xs::unbounded;
		list<gmd::MD_ApplicationSchemaInformation_PropertyType> applicationSchemaInfo;
		const int applicationSchemaInfo_minOccurs = xs::zero;
		const int applicationSchemaInfo_maxOccurs = xs::unbounded;
		list<gmd::MD_MaintenanceInformation_PropertyType> metadataMaintenance;
		const int metadataMaintenance_minOccurs = xs::zero;
		const int metadataMaintenance_maxOccurs = xs::one;
		list<gmd::DS_Aggregate_PropertyType> series;
		const int series_minOccurs = xs::zero;
		const int series_maxOccurs = xs::unbounded;
		list<gmd::DS_DataSet_PropertyType> describes;
		const int describes_minOccurs = xs::zero;
		const int describes_maxOccurs = xs::unbounded;
		list<gco::ObjectReference> propertyType;
		const int propertyType_minOccurs = xs::zero;
		const int propertyType_maxOccurs = xs::unbounded;
		list<gco::ObjectReference> featureType;
		const int featureType_minOccurs = xs::zero;
		const int featureType_maxOccurs = xs::unbounded;
		list<gco::ObjectReference> featureAttribute;
		const int featureAttribute_minOccurs = xs::zero;
		const int featureAttribute_maxOccurs = xs::unbounded;
	};
	class MD_Metadata_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_Metadata_PropertyType();
		gmd::MD_Metadata m_MD_Metadata;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
	};
	class MD_ObligationCode
	{
	public:
		list<wstring> base;
		AFX_EXT_CLASS MD_ObligationCode();
	};
	class MD_ObligationCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_ObligationCode_PropertyType();
		gmd::MD_ObligationCode m_MD_ObligationCode;
		gco::NilReason m_nilReason;
	};
	class MD_DatatypeCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_DatatypeCode_PropertyType();
		gco::CodeListValue_Type m_MD_DatatypeCode;
		gco::NilReason m_nilReason;
	};
	class MD_ExtendedElementInformation
	{
	public:
		AFX_EXT_CLASS MD_ExtendedElementInformation();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gco::CharacterString_PropertyType> name;
		const int name_minOccurs = xs::one;
		const int name_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> shortName;
		const int shortName_minOccurs = xs::zero;
		const int shortName_maxOccurs = xs::one;
		list<gco::Integer_PropertyType> domainCode;
		const int domainCode_minOccurs = xs::zero;
		const int domainCode_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> definition;
		const int definition_minOccurs = xs::one;
		const int definition_maxOccurs = xs::one;
		list<gmd::MD_ObligationCode_PropertyType> obligation;
		const int obligation_minOccurs = xs::zero;
		const int obligation_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> condition;
		const int condition_minOccurs = xs::zero;
		const int condition_maxOccurs = xs::one;
		list<gmd::MD_DatatypeCode_PropertyType> dataType;
		const int dataType_minOccurs = xs::one;
		const int dataType_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> maximumOccurrence;
		const int maximumOccurrence_minOccurs = xs::zero;
		const int maximumOccurrence_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> domainValue;
		const int domainValue_minOccurs = xs::zero;
		const int domainValue_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> parentEntity;
		const int parentEntity_minOccurs = xs::one;
		const int parentEntity_maxOccurs = xs::unbounded;
		list<gco::CharacterString_PropertyType> rule;
		const int rule_minOccurs = xs::one;
		const int rule_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> rationale;
		const int rationale_minOccurs = xs::zero;
		const int rationale_maxOccurs = xs::unbounded;
		list<gmd::CI_ResponsibleParty_PropertyType> source;
		const int source_minOccurs = xs::one;
		const int source_maxOccurs = xs::unbounded;
	};
	class MD_ExtendedElementInformation_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_ExtendedElementInformation_PropertyType();
		gmd::MD_ExtendedElementInformation m_MD_ExtendedElementInformation;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_MetadataExtensionInformation
	{
	public:
		AFX_EXT_CLASS MD_MetadataExtensionInformation();
		wstring documentation;
		gco::AbstractObject_Type base;
		list<gmd::CI_OnlineResource_PropertyType> extensionOnLineResource;
		const int extensionOnLineResource_minOccurs = xs::zero;
		const int extensionOnLineResource_maxOccurs = xs::one;
		list<gmd::MD_ExtendedElementInformation_PropertyType> extendedElementInformation;
		const int extendedElementInformation_minOccurs = xs::zero;
		const int extendedElementInformation_maxOccurs = xs::unbounded;

	};
	class MD_MetadataExtensionInformation_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_MetadataExtensionInformation_PropertyType();
		gmd::MD_MetadataExtensionInformation m_MD_MetadataExtensionInformation;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_PortrayalCatalogueReference
	{
	public:
		AFX_EXT_CLASS MD_PortrayalCatalogueReference();
		wstring documentation;
		gco::AbstractObject_Type base;

		list<gmd::CI_Citation_PropertyType> portrayalCatalogueCitation;
		const int portrayalCatalogueCitation_minOccurs = xs::one;
		const int portrayalCatalogueCitation_maxOccurs = xs::unbounded;
	};
	class MD_PortrayalCatalogueReference_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_PortrayalCatalogueReference_PropertyType();
		gmd::MD_PortrayalCatalogueReference m_MD_PortrayalCatalogueReference;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_TopologyLevelCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_TopologyLevelCode_PropertyType();
		gco::CodeListValue_Type m_MD_TopologyLevelCode;
		gco::NilReason m_nilReason;
	};
	class MD_GeometricObjectTypeCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_GeometricObjectTypeCode_PropertyType();
		gco::CodeListValue_Type m_MD_GeometricObjectTypeCode;
		gco::NilReason m_nilReason;
	};
	class MD_CellGeometryCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_CellGeometryCode_PropertyType();
		gco::CodeListValue_Type m_MD_CellGeometryCode;
		gco::NilReason m_nilReason;
	};
	class MD_DimensionNameTypeCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_DimensionNameTypeCode_PropertyType();
		gco::CodeListValue_Type m_MD_DimensionNameTypeCode;
		gco::NilReason m_nilReason;
	};
	class AbstractMD_SpatialRepresentation
	{
	public:
		AFX_EXT_CLASS AbstractMD_SpatialRepresentation();
		bool abstract = true;
		wstring documentation;
		gco::AbstractObject_Type base;
	};
	class MD_SpatialRepresentation_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_SpatialRepresentation_PropertyType();
		gmd::AbstractMD_SpatialRepresentation m_AbstractMD_SpatialRepresentation;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_GridSpatialRepresentation
	{
	public:
		AFX_EXT_CLASS MD_GridSpatialRepresentation();
		wstring documentation;
		gmd::AbstractMD_SpatialRepresentation base;
		list<gco::Integer_PropertyType> numberOfDimensions;
		const int numberOfDimensions_minOccurs = xs::one;
		const int numberOfDimensions_maxOccurs = xs::one;
		list<gmd::MD_Dimension_PropertyType> axisDimensionProperties;
		const int axisDimensionProperties_minOccurs = xs::zero;
		const int axisDimensionProperties_maxOccurs = xs::unbounded;
		list<gmd::MD_CellGeometryCode_PropertyType> cellGeometry;
		const int cellGeometry_minOccurs = xs::one;
		const int cellGeometry_maxOccurs = xs::one;
		list<gco::Boolean_PropertyType> transformationParameterAvailability;
		const int transformationParameterAvailability_minOccurs = xs::one;
		const int transformationParameterAvailability_maxOccurs = xs::one;

	};
	class MD_GridSpatialRepresentation_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_GridSpatialRepresentation_PropertyType();
		gmd::MD_GridSpatialRepresentation m_MD_GridSpatialRepresentation;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_VectorSpatialRepresentation
	{
	public:
		AFX_EXT_CLASS MD_VectorSpatialRepresentation();
		wstring documentation;
		gmd::AbstractMD_SpatialRepresentation base;
		list<gmd::MD_TopologyLevelCode_PropertyType> topologyLevel;
		const int topologyLevel_minOccurs = xs::zero;
		const int topologyLevel_maxOccurs = xs::one;
		list<gmd::MD_GeometricObjects_PropertyType> geometricObjects;
		const int geometricObjects_minOccurs = xs::zero;
		const int geometricObjects_maxOccurs = xs::unbounded;
	};
	class MD_VectorSpatialRepresentation_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_VectorSpatialRepresentation_PropertyType();
		gmd::MD_VectorSpatialRepresentation m_MD_VectorSpatialRepresentation;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_Georeferenceable
	{
	public:
		AFX_EXT_CLASS MD_Georeferenceable();
		gmd::MD_GridSpatialRepresentation base;
		list<gco::Boolean_PropertyType> controlPointAvailability;
		const int controlPointAvailability_minOccurs = xs::one;
		const int controlPointAvailability_maxOccurs = xs::one;
		list<gco::Boolean_PropertyType> orientationParameterAvailability;
		const int orientationParameterAvailability_minOccurs = xs::one;
		const int orientationParameterAvailability_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> orientationParameterDescription;
		const int orientationParameterDescription_minOccurs = xs::zero;
		const int orientationParameterDescription_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> georeferencedParameters;
		const int georeferencedParameters_minOccurs = xs::one;
		const int georeferencedParameters_maxOccurs = xs::one;
		list<gmd::CI_Citation_PropertyType> parameterCitation;
		const int parameterCitation_minOccurs = xs::zero;
		const int parameterCitation_maxOccurs = xs::unbounded;
	};
	class MD_Georeferenceable_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_Georeferenceable_PropertyType();
		gmd::MD_Georeferenceable m_MD_Georeferenceable;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_Dimension
	{
	public:
		AFX_EXT_CLASS MD_Dimension();
		gco::AbstractObject_Type base;
		list<gmd::MD_DimensionNameTypeCode_PropertyType> dimensionName;
		const int dimensionName_minOccurs = xs::one;
		const int dimensionName_maxOccurs = xs::one;
		list<gco::Integer_PropertyType> dimensionSize;
		const int dimensionSize_minOccurs = xs::one;
		const int dimensionSize_maxOccurs = xs::one;
		list<gco::Measure_PropertyType> resolution;
		const int resolution_minOccurs = xs::zero;
		const int resolution_maxOccurs = xs::one;
	};
	class MD_Dimension_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_Dimension_PropertyType();
		gmd::MD_Dimension m_MD_Dimension;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_Georectified
	{
	public:
		AFX_EXT_CLASS MD_Georectified();
		gmd::MD_GridSpatialRepresentation base;
		list<gco::Boolean_PropertyType> checkPointAvailability;
		const int checkPointAvailability_minOccurs = xs::one;
		const int checkPointAvailability_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> checkPointDescription;
		const int checkPointDescription_minOccurs = xs::zero;
		const int checkPointDescription_maxOccurs = xs::one;
		list<gss::GM_Point_PropertyType> cornerPoints;
		const int cornerPoints_minOccurs = xs::zero;
		const int cornerPoints_maxOccurs = xs::unbounded;
		list<gss::GM_Point_PropertyType> centerPoint;
		const int centerPoint_minOccurs = xs::zero;
		const int centerPoint_maxOccurs = xs::one;
		list<gmd::MD_PixelOrientationCode_PropertyType> pointInPixel;
		const int pointInPixel_minOccurs = xs::one;
		const int pointInPixel_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> transformationDimensionDescription;
		const int transformationDimensionDescription_minOccurs = xs::zero;
		const int transformationDimensionDescription_maxOccurs = xs::one;
		list<gco::CharacterString_PropertyType> transformationDimensionMapping;
		const int transformationDimensionMapping_minOccurs = xs::zero;
		const int transformationDimensionMapping_maxOccurs = xs::two;
	};
	class MD_Georectified_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_Georectified_PropertyType();
		gmd::MD_Georectified m_MD_Georectified;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_GeometricObjects
	{
	public:
		AFX_EXT_CLASS MD_GeometricObjects();
		gco::AbstractObject_Type base;
		list<gmd::MD_GeometricObjectTypeCode_PropertyType> geometricObjectType;
		const int geometricObjectType_minOccurs = xs::one;
		const int geometricObjectType_maxOccurs = xs::one;
		list<gco::Integer_PropertyType> geometricObjectCount;
		const int geometricObjectCount_minOccurs = xs::zero;
		const int geometricObjectCount_maxOccurs = xs::one;
	};
	class MD_GeometricObjects_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_GeometricObjects_PropertyType();
		gmd::MD_GeometricObjects m_MD_GeometricObjects;
		gco::ObjectReference_PropertyType m_ObjectReference_PropertyType;
		gco::NilReason m_nilReason;
	};
	class MD_PixelOrientationCode
	{
	public:
		list<wstring> base;
		MD_PixelOrientationCode();
	};
	class MD_PixelOrientationCode_PropertyType
	{
	public:
		AFX_EXT_CLASS MD_PixelOrientationCode_PropertyType();
		gmd::MD_PixelOrientationCode m_MD_PixelOrientationCode;
		gco::NilReason m_nilReason;
	};
}


namespace MetadataSet
{
	class MetadataSetXML
	{
	public:
		AFX_EXT_CLASS MetadataSetXML();

		static gmd::MD_Metadata g_metadata;

		static AFX_EXT_CLASS void XmlOpen(std::wstring path, gmd::MD_Metadata &metadata);
		static AFX_EXT_CLASS void ChileNodeArrange(MSXML2::IXMLDOMNodeListPtr nodes, DWORD_PTR variableSpace, gmd::MD_Metadata &metadata);
	};
}

