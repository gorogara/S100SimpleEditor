#pragma once 
#include <string>

class Scaler;
class R_FeatureRecord;
class S111Cell;
class S101Cell;
class NewFeatureManager;
class NewInformationManager;
class R_PointRecord;
class R_MultiPointRecord;
class R_CurveRecord;
class R_CompositeRecord;
class R_SurfaceRecord;
class ENCCell;
class ENC_Feature;
class R_InformationRecord;

struct ATTR;

#define CaseEnum(a)    #a 
enum class TOPIC_CATEGORY
{
	farming = 1,
	biota,
	boundaries,
	climatologyMeterologyAtmosphere,
	enonomy,
	elevation,
	environment,
	geoscientificInformation,
	health,
	imageryBaseMapsEarthCover,
	intelligenceMilitary,
	inlandWaters,
	location,
	oceans,
	planningCadastre,
	society,
	structure,
	transportation,
	utilitiesCommunication
}; 
static std::wstring TOPIC_CATEGORY_NAME[] =
{
	L"farming",
	L"biota",
	L"climatologyMeterologyAtmosphere",
	L"enonomy",
	L"elevation",
	L"environment",
	L"geoscientificInformation",
	L"health",
	L"imageryBaseMapsEarthCover",
	L"intelligenceMilitary",
	L"inlandWaters",
	L"location",
	L"oceans",
	L"planningCadastre",
	L"society",
	L"structure",
	L"transportation",
	L"utilitiesCommunication"
};


class ENC_S101_Factory
{
public:
	static S101Cell* CreateEmptyFileByCatalog(Catalog* catalog, std::wstring fileName);
	static S101Cell* CreateUpdateFile(S101Cell* orgCell, unsigned ened = 0);
	static int GetofTopicCategoriesFromAcronym(std::wstring acronym);


	static ENC_Feature* CreateObject(NewFeatureManager *pNewFeatureManager, Scaler* pScaler, bool hasRelation = false);
	static R_FeatureRecord* CreateFeature(NewFeatureManager *pNewFeatureManager, Scaler* pScaler, bool hasRelation = false, bool hasSameGeometry = false);
	static R_FeatureRecord* CreateFeature(NewFeatureManager *pNewFeatureManager);
	static R_InformationRecord* CreateInformation(NewInformationManager *pNewInfmationManager);
	static R_FeatureRecord* CreateDeleteFeature(S101Cell* cell, unsigned featureID);
	static R_FeatureRecord* CreateUpdateFeature(unsigned featureID);
	static R_FeatureRecord* CreateFeatureSameGeometry(R_FeatureRecord* fr, NewFeatureManager *pNewFeatureManager, std::wstring code);

	static R_FeatureRecord* CreateSoundingFeatureByXyzFile(S101Cell* cell, std::wstring xyz_filepath);

	static R_FeatureRecord* CreateInnerCircle(NewFeatureManager *pNewFeatureManager, Scaler* pScaler);
	
	static void SetFeatureToFeatureAssociation(NewFeatureManager *pNewFeatureManager, R_FeatureRecord* objFr);
	static void SetFeatureToFeatureAssociation(S101Cell* cell, R_FeatureRecord* orgFr, R_FeatureRecord* objFr);
	static void SetFeatureToInformationAssociation(S101Cell* cell, R_FeatureRecord* orgFr, R_InformationRecord* objFr);
	static void SetInformationToInformationAssociation(S101Cell* cell, R_InformationRecord* orgIr, R_InformationRecord* objIr);
	
	static void SetUpdateFileInsert(R_FeatureRecord* fr, NewFeatureManager *pNewFeatureManager);
	static void SetUpdateFileInsert(R_PointRecord* r, S101Cell* orgCell);
	static void SetUpdateFileInsert(R_MultiPointRecord* r, S101Cell* orgCell);
	static void SetUpdateFileInsert(R_CurveRecord* r, S101Cell* orgCell);
	static void SetUpdateFileInsert(R_CompositeRecord* r, S101Cell* orgCell);
	static void SetUpdateFileInsert(R_SurfaceRecord* r, S101Cell* orgCell);

	
	static void ProcessCSProcedure(S101Cell* cell, R_FeatureRecord* fr);
	static unsigned GetFeatureID(S101Cell* cell);
	static unsigned GetFeatureID_FOID(S101Cell* cell, __int64 agen, __int64 fids);
	static unsigned GetInformationID(S101Cell* cell);
	static unsigned GetFeatureID(ENCCell* cell);
	static unsigned GetFeatureID_FOID(ENCCell* cell, __int64 agen, __int64 fids);
	static unsigned GetPointID(S101Cell* cell);
	static unsigned GetMultiPointID(S101Cell* cell);
	static unsigned GetCurveID(S101Cell* cell);
	static unsigned GetCompositeCurveID(S101Cell* cell);
	static unsigned GetSurfaceID(S101Cell* cell);
	
	static unsigned GetFeatureID(S111Cell* cell);
	static unsigned GetFeatureID_FOID(S111Cell* cell, __int64 agen, __int64 fids);



	static unsigned GetPointID(ENCCell* cell);
	static unsigned GetPointConnectedID(ENCCell* cell);
	static unsigned GetCurveID(ENCCell* cell);
	static unsigned GetSurfaceID(ENCCell* cell);      
	static unsigned GetATCS(S101Cell* orgCell, std::wstring code);
	static unsigned GetITCS(S101Cell* orgCell, std::wstring code);
	static unsigned GetFTCS(S101Cell* orgCell, std::wstring code);
	static unsigned GetIACS(S101Cell* orgCell, std::wstring code);
	static unsigned GetFACS(S101Cell* orgCell, std::wstring code);
	static unsigned GetARCS(S101Cell* orgCell, std::wstring code);

	static void DeleteAttribute(R_FeatureRecord *fr, ATTR* attr); 
	static void DeleteAttribute(R_InformationRecord* ir, ATTR* attr);
};

