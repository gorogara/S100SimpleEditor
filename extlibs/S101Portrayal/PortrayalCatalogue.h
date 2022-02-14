#pragma once

#include "S100_Rules.h"
#include "S100_LineStyles.h"
#include "S100_AreaFills.h"
#include "S100_Transform.h"
#include "S100_SymbolFill.h"
#include "S100_ColorProfile.h"
#include "EnumPortrayalRuleType.h"

#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

#include "..\\S100_SVG_D2D1_DLL\\SVGManager.h"

#include "..\\S100Engine\\S100PCManager.h"
#include "..\\S100Engine\\S100Render.h"

#include "..\\GeoMetryLibrary\\ENCCommon.h"

#include <unordered_map>
#include <string>


class S100_ColorProfiles;
class S100PCManager;

class PortrayalCatalogue
{
public:
	PortrayalCatalogue();
	PortrayalCatalogue(std::wstring path);
	virtual ~PortrayalCatalogue();

public:
	std::wstring rootPath;
	std::wstring product;
	PortrayalRuleType portrayalRuleType = XSLT; 
	S100_ColorProfiles* colorProfiles = nullptr; 
	S100_Rules *rules = nullptr;
	S100_LineStyles *lineStyles = nullptr;
	S100_AreaFills *areaFills = nullptr; 
	S100_ColorProfile s100_colorProfile;
	std::unordered_map<std::wstring, S100_LineStyleBase*> s100_lineStyles;

	std::unordered_map<std::wstring, S100_SymbolFill*> s100_symbolFill;
	std::vector<S100_Transform*> s100_transform; 
	std::unordered_map<std::wstring, S100_RuleFile*> mainRules;
	SENC_Rule* sencRules = nullptr;

	S100_SVG_D2D1_DLL::SVGManager *m_svgSymbolManager = nullptr; 
	std::wstring currentPalette = L"Day";
	S100PCManager *s100PCManager = new S100PCManager();
	S100Render s100Render;

public:
	void Open(std::wstring path);
	void Init();
	void Delete();

	bool ReadPortrayalCatalogue(std::wstring path);
	bool ReadPortrayalCatalogueByPugiXML(std::wstring path); 

	void GetContents(MSXML2::IXMLDOMNodeListPtr pNodeList);
	void GetContents(pugi::xml_node& node);

	S100_ColorProfile* GetColorProfile();
	S100_ColorProfile* GetColorProfile(std::wstring id);

	void GetLineStyles();
	void GetLineStylesByPugiXml();
	void GetAreaFills();
	void GetRules(std::wstring path);
	void ProcessTemplate();
	void GetMainRuleFile();

	void CreateSENCRuleFile();
	SENC_Template* S1002SENC_Template(S100_Template* tp);

	void S1002SENC_TemplateCommon(S100_Instruction* tp, SENC_Instruction* si);
	SENC_Instruction* S1002SENC_TemplatePoint(S100_Instruction* tp);
	SENC_Instruction* S1002SENC_TemplateLine(S100_Instruction* tp);
	SENC_Instruction* S1002SENC_TemplateArea(S100_Instruction* tp);
	SENC_Instruction* S1002SENC_TemplateText(S100_Instruction* tp);

	void SetCurrentPaletteName(std::wstring paletteName);
	void SetCurrentPalette(ENCCommon::ColorTable value);
	std::wstring GetCurrentPaletteName();

	S100PCManager* GetS100PCManager();

	void SetRuleType(PortrayalRuleType value);
	PortrayalRuleType GetRuleType();

	void SetSVGManager(S100_SVG_D2D1_DLL::SVGManager* value);
	S100_SVG_D2D1_DLL::SVGManager* GetSVGManager();

	void CreatePatternImages(ID2D1Factory1* d2Factory, IWICImagingFactory* imageFactory, ID2D1StrokeStyle1* stroke);
	void DeletePatternImage();

	void CreateLineImages(ID2D1Factory1* d2Factory, IWICImagingFactory* imageFactory, ID2D1StrokeStyle1* stroke);
	void DeleteLineImages();
};