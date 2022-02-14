
#include "stdafx.h"
#include "S101LuaScriptingReference.h"
#include "feature_catalog.h"
#include "portrayal_catalog.h"
#include "host_data.h"
#include "host_functions.h"
#include "lua_session.h"
#include "lua_functions.h"

#include <iostream>
#include <string>
#include <afxwin.h> 
#include <afxext.h> 

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h> 
#include <afxodlgs.h> 
#include <afxdisp.h> 
#endif 

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h> 
#endif 

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h> 
#endif 

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h> 
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h> 
#endif 



#include "GISLibrary/S101Cell.h" 
#include "../FeatureCatalog/Catalog.h"

#include <afxcmn.h>
#include "GeoMetryLibrary\\ENCCommon.h"
#include "../DLL_MessageProcess/DLL_MessageProcess.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib" )

string g_unknown_attribute_value;

S101LuaScriptingReference::S101LuaScriptingReference()
{
	m_lua_session = NULL;                                                                                            
}


S101LuaScriptingReference::~S101LuaScriptingReference()
{
	if(m_lua_session)
		delete m_lua_session;
	m_lua_session = NULL;
}

S101LuaScriptingReference theInstance;

namespace KRS_LUA_SCRIPT_REFERENCE
{
	void InitPortrayal(/*const char* inputSchema, */const char* featureCatalog, const char* topLevelRule, S101Cell* cell, FeatureCatalogue* fc)
	{
		if(theInstance.m_lua_session)
			delete theInstance.m_lua_session;

		if (cell)
		{
			theInstance.m_s101_cell = cell;
		}
		if (fc)
		{
			theInstance.m_s101_feature_catalogue = fc;
		}

		theInstance.m_lua_session = NULL; 
		const char *feature_catalog = featureCatalog;//argv[2];
		string top_level_rule(topLevelRule);//argv[3];     
		pTheFC = fc;      

		hd_init(/*input_schema, */cell);

		pc_init("..\\ProgramData\\S101_Portrayal\\portrayal_catalogue.xml");    
		theInstance.m_lua_session = new lua_session();   

		theInstance.m_lua_session->register_function("HostGetFeatureIDs", HostGetFeatureIDs);
		theInstance.m_lua_session->register_function("HostFeatureGetCode", HostFeatureGetCode);
		theInstance.m_lua_session->register_function("HostGetInformationTypeIDs", HostGetInformationTypeIDs);
		theInstance.m_lua_session->register_function("HostInformationTypeGetCode", HostInformationTypeGetCode);
		theInstance.m_lua_session->register_function("HostFeatureGetSimpleAttribute", HostFeatureGetSimpleAttribute);
		theInstance.m_lua_session->register_function("HostFeatureGetComplexAttributeCount", HostFeatureGetComplexAttributeCount);
		theInstance.m_lua_session->register_function("HostFeatureGetSpatialAssociations", HostFeatureGetSpatialAssociations);
		theInstance.m_lua_session->register_function("HostFeatureGetAssociatedFeatureIDs", HostFeatureGetAssociatedFeatureIDs);
		theInstance.m_lua_session->register_function("HostFeatureGetAssociatedInformationIDs", HostFeatureGetAssociatedInformationIDs);
		theInstance.m_lua_session->register_function("HostGetSpatialIDs", HostGetSpatialIDs);
		theInstance.m_lua_session->register_function("HostGetSpatial", HostGetSpatial);
		theInstance.m_lua_session->register_function("HostSpatialGetAssociatedInformationIDs", HostSpatialGetAssociatedInformationIDs);
		theInstance.m_lua_session->register_function("HostSpatialGetAssociatedFeatureIDs", HostSpatialGetAssociatedFeatureIDs);
		theInstance.m_lua_session->register_function("HostInformationTypeGetSimpleAttribute", HostInformationTypeGetSimpleAttribute);
		theInstance.m_lua_session->register_function("HostInformationTypeGetComplexAttributeCount", HostInformationTypeGetComplexAttributeCount);

		theInstance.m_lua_session->register_function("HostGetFeatureTypeCodes", HostGetFeatureTypeCodes);
		theInstance.m_lua_session->register_function("HostGetInformationTypeCodes", HostGetInformationTypeCodes);
		theInstance.m_lua_session->register_function("HostGetSimpleAttributeTypeCodes", HostGetSimpleAttributeTypeCodes);
		theInstance.m_lua_session->register_function("HostGetComplexAttributeTypeCodes", HostGetComplexAttributeTypeCodes);
		theInstance.m_lua_session->register_function("HostGetRoleTypeCodes", HostGetRoleTypeCodes);
		theInstance.m_lua_session->register_function("HostGetInformationAssociationTypeCodes", HostGetInformationAssociationTypeCodes);
		theInstance.m_lua_session->register_function("HostGetFeatureAssociationTypeCodes", HostGetFeatureAssociationTypeCodes);
		theInstance.m_lua_session->register_function("HostGetFeatureTypeInfo", HostGetFeatureTypeInfo);
		theInstance.m_lua_session->register_function("HostGetInformationTypeInfo", HostGetInformationTypeInfo);
		theInstance.m_lua_session->register_function("HostGetSimpleAttributeTypeInfo", HostGetSimpleAttributeTypeInfo);
		theInstance.m_lua_session->register_function("HostGetComplexAttributeTypeInfo", HostGetComplexAttributeTypeInfo);

		theInstance.m_lua_session->register_function("HostSpatialRelate", HostSpatialRelate);

		theInstance.m_lua_session->register_function("HostDebuggerEntry", HostDebuggerEntry);

		theInstance.m_lua_session->register_function("HostPortrayalEmit", HostPortrayalEmit);   

		string rules_path = top_level_rule.substr(0, top_level_rule.find_last_of('\\'));   

		string path = rules_path + (string)"\\?.lua";

		theInstance.m_lua_session->set_field("package", "path", path.c_str());   

		theInstance.m_lua_session->load_file(top_level_rule);   

		g_unknown_attribute_value = theInstance.m_lua_session->call<string>("GetUnknownAttributeString", { 1.0 });   

		theInstance.m_lua_session->call<bool>("TypeSystemChecks", { true });   

		theInstance.m_lua_session->get_function("PortrayalInitializeContextParameters");

		auto cps = pc_get_context_parameters();

		vector<lua_variant> cpts;

		for (auto cp : cps)
			cpts.push_back(theInstance.m_lua_session->call("PortrayalCreateContextParameter", { cp.name, cp.type, cp.default_value }));

		theInstance.m_lua_session->push(cpts);

		theInstance.m_lua_session->call_raw(1);
	}                                                                                 


	void PortrayalSetContextParameter(const char*  parameterName, const char*  parameterValue)
	{
		theInstance.m_lua_session->call("PortrayalSetContextParameter", { parameterName, parameterValue});
	}
		
	
	void RemoveResultDrawingInstructions()
	{
		resultDrawingInstructions.clear();

		if (theInstance.m_lua_session)
			delete theInstance.m_lua_session;
		theInstance.m_lua_session = NULL;
		
		hd_delete(); 
	}


	void SaveDrawingInstructions(std::string path)
	{
		ofstream file;
		file.open(path);

		for (
			auto i = resultDrawingInstructions.begin();
			i != resultDrawingInstructions.end();
			i++)
		{
			file << i->featureID << std::endl;
			file << i->drawingInstructions << std::endl;
			file << i->observedParameters << std::endl;
		}

		file.close();
	}


	std::list<Result_DrawingInstruction>* GetResultDrawingInstructions()
	{
		theInstance.m_lua_session->call("PortrayalMain");                                                           

		return &resultDrawingInstructions;
	}
}