#pragma once

#include <unordered_map>

namespace ENCCommon
{
	extern unsigned DrawingType;  
	extern bool   SymbolizedAreaBoundary;  
	extern bool   SeabedAreaType;  


	extern double SAFETY_DEPTH; 
	extern double SAFETY_CONTOUR; 
	extern double SHALLOW_CONTOUR; 
	extern double DEEP_CONTOUR; 

	extern bool DISPLAY_PLANE;

	extern bool   TWO_SHADES;
	extern bool   SHALLOW_PATTERN;
	extern bool   USE_SPATIAL_QUERY;

	extern bool   SOUNDING;  

	extern bool   LIGHTS;  

	extern bool   CONTOUR_LABELS;  

	extern bool	  TEXTOUT;

	extern bool	  SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER;

	extern bool	  FULL_SECTORS;

	extern int	  DISTANCE_TAGS;

	extern bool   APPLY_SCALE_MIN;  
	extern bool   SHOW_NOBJNM; 

	extern bool   AVOID_CLUTTER; 

	extern bool   SHOW_LIST_ABBREVIATION;

	extern bool   WGS84_TEXT_TYPE;

	enum DisplayModeTable {
		base = 0,
		standard = 1,
		all = 2
	};
	extern DisplayModeTable  DISPLAY_MODE;

	extern __int64 OVER_GROUP;

	extern __int64 GetOverGroup(int viewGroup);

	extern std::unordered_map<int, bool> objectDisplaySettings;
	extern std::unordered_map<std::wstring, bool> featureDisplaySettings; 
	enum ColorTable
	{
		Day = 0,
		Dusk,
		Night,
	};

	extern ColorTable m_eColorTable;

	enum UserMode {
		User_Mode,
		Developer_Mode,
		User_Developer_Mode
	};
	extern UserMode m_UserMode;

	enum  ReportingData {
		None, 
		PC,
		FC,
		DataSet
	};
	extern UserMode m_ReportingData;  
	extern bool   SHOW_USER_WRECK;
	extern bool   SHOW_USER_MEMORIES;
	extern bool   SHOW_USER_FISHERY_ZONE;
	extern bool   SHOW_USER_IMAGE_LAYER;

	extern bool	  SHOW_USER_COAST_AREA;
	extern bool	  SHOW_USER_COAST_AREA_DETAIL; 

	extern double S111_SREF;
	extern double S111_LREF;
	extern double S111_SHIGH;
	extern double S111_Alpha; 

	extern bool APPLY_DATA_COVERAGE_SCALE;


	extern std::wstring DISPLAY_FONT_NAME;
	extern int DISPLAY_FONT_SIZE;

	extern float DISPLAY_SYMBOL_SCALE; 
	extern bool AREA_SYMBOL_DYNAMIC_POSITION_MODE;

	enum UnitDistance {
		unitDistance_km = 0,
		unitDistance_nautical_mile = 1,
	};

	extern UnitDistance UNIT_DISTANCE;

	extern int	  INTEROPERABILITY_LEVEL;  
	extern BOOL	SHOW_TEXT_PLACEMENT; 
	extern BOOL SHOW_UNCERTAINTY; 
	extern int T_APPLY_OVER_N_UNDER_SCALE;
	extern int T_CURRENT_SCALE;  
}