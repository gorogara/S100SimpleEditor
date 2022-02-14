#pragma once
#include "ENCCommon.h"

class ENCConfiguration
{
public:
	ENCConfiguration(){};
	virtual ~ENCConfiguration(){};

	int DrawingType;   
				
	bool SymbolizedAreaBoundary;  

	bool SeabedAreaType;  
	double SAFETY_DEPTH; 
	double SAFETY_CONTOUR; 
	double SHALLOW_CONTOUR;
	double DEEP_CONTOUR;   
	
	bool   TWO_SHADES;     
	bool   USE_SPATIAL_QUERY;     
	bool   SHALLOW_PATTERN;

	bool   SOUNDING;  

	bool   LIGHTS;  

	bool   CONTOUR_LABELS;  

	bool	TEXTOUT;

	bool	SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER;

	bool	FULL_SECTORS;

	int		DISTANCE_TAGS;

	bool   APPLY_SCALE_MIN;  
	
	bool   SHOW_NOBJNM; 

	bool AVOID_CLUTTER; 

	bool   SHOW_LIST_ABBREVIATION;
	
	bool   WGS84_TEXT_TYPE;

	ENCCommon::DisplayModeTable  DISPLAY_MODE;
	ENCCommon::ColorTable m_eColorTable;
	ENCCommon::UserMode m_UserMode;
	ENCCommon::ReportingData m_ReportingData;


	ENCCommon::UnitDistance UNIT_DISTANCE;

	std::unordered_map<int, bool> objectDisplaySettings;
	std::unordered_map<std::wstring, bool> featureDisplaySettings;

	__int64 OVER_GROUP;

	__int64 GetOverGroup(int viewGroup);

	bool   SHOW_USER_COAST_AREA;
	bool   SHOW_USER_COAST_AREA_DETAIL;

	int INTEROPERABILITY_LEVEL;

	std::wstring DISPLAY_FONT_NAME;
	int DISPLAY_FONT_SIZE;
};

