
#include "stdafx.h"
#include "host_data.h"
#include "rapidxml.hpp"

#include "GISLibrary\\S101Cell.h"
#include "GISLibrary\\F_CUCO.h"
#include "GISLibrary\\F_PTAS.h"
#include "GISLibrary\\F_CCOC.h"
#include "GISLibrary\\F_SPAS.h"
#include "GISLibrary\\F_C3IL.h"
#include "GISLibrary\\F_C2IL.h"
#include "GISLibrary\\F_C2IT.h"
#include "GISLibrary\\F_RIAS.h"
#include "GISLibrary\\F_ATTR.h"
#include "GISLibrary\\F_INAS.h"
#include "GISLibrary\\R_SurfaceRecord.h"
#include "GISLibrary\\R_PointRecord.h"
#include "GISLibrary\\R_CompositeRecord.h"
#include "GISLibrary\\R_CurveRecord.h"
#include "GISLibrary\\R_InformationRecord.h"
#include "GISLibrary\\R_FeatureRecord.h"
#include "GISLibrary\\R_MultiPointRecord.h"
#include "GISLibrary\\ATTR.h"
#include "GISLibrary\\C3IL.h"
#include "GISLibrary\IC2D.h"
#include "GISLibrary\\CodeWithNumericCode.h"
#include "GISLibrary\\CUCO.h"
#include "GISLibrary\\SPAS.h"
#include "GISLibrary\\PTAS.h"
#include "GISLibrary\\RIAS.h"

#include "..\\FeatureCatalog\\Catalog.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <stdlib.h>
#include <iomanip>

using namespace std;
using namespace rapidxml;  
static S101Cell *cell;
static FeatureCatalogue *feature_catalog;  

static vector<string> s_feature_ids; 
static vector<string> s_information_ids;

static map<string, R_FeatureRecord*> s_feature_nodes; 
static map<string, R_InformationRecord*> s_information_nodes; 
static map<string, R_PointRecord*> s_spatial_point_nodes;
static map<string, R_MultiPointRecord*> s_spatial_mpoint_nodes;
static map<string, R_CurveRecord*> s_spatial_curve_nodes;
static map<string, R_CompositeRecord*> s_spatial_ccurve_nodes;
static map<string, R_SurfaceRecord*> s_spatial_surface_nodes;
static map<string, set<string>*> s_spatial_features;

static spatial_association get_spatial_association(PTAS* ptas);
static spatial_association get_spatial_association(CUCO* cuco);
static spatial_association get_spatial_association(F_SPAS* spatial);
static spatial_association get_spatial_association(RIAS* rias);


extern string g_unknown_attribute_value;

char* ConvertWCtoC(wchar_t* str)
{ 
	char* pStr = nullptr; 
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	if (strSize <= 0)
	{
		OutputDebugString(_T("Failed to WideCharToMultiByte()\n"));
		return nullptr;
	} 
	pStr = new char[strSize]; 
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
	return pStr;
}

static string WstringToString(CString& value)
{
	auto cValue = ConvertWCtoC((wchar_t*)std::wstring(value).c_str());
	string result(cValue);
	delete[] cValue;
	return result;
}

static void add_child_nodes(xml_node<>* parent_node, map<string, xml_node<>*> &node_map)
{
	for (auto node = parent_node->first_node(); node; node = node->next_sibling())
	{
		auto id = node->first_attribute("id")->value();

		node_map[id] = node;
	}
}

static void get_referenced_spatials(string spatial_id, vector<string> *spatials)
{
	vector<string> ret;

	int findOffset = 0;
	int splitOffset = 0;
	string token = "|";
	while ((splitOffset = spatial_id.find(token, findOffset)) != std::string::npos)
	{
		ret.push_back(spatial_id.substr(findOffset, splitOffset - findOffset));
		findOffset = splitOffset + token.length();
	}
	ret.push_back(spatial_id.substr(findOffset, spatial_id.length() - findOffset)); 

	string spatial_type;

	if (ret[0] == "Point")
	{
		auto spatial = s_spatial_point_nodes[spatial_id];

		spatial_type = ret[0];
		spatials->push_back(spatial_id);
	}
	else if (ret[0] == "MultiPoint")
	{
		auto spatial = s_spatial_mpoint_nodes[spatial_id];

		spatial_type = ret[0];
		spatials->push_back(spatial_id);
	}
	else 
	if (ret[0] == "Curve")
	{
		auto spatial = s_spatial_curve_nodes[spatial_id];

		spatial_type = ret[0];
		spatials->push_back(spatial_id);  

		POSITION pos = spatial->m_ptas->m_arr.GetHeadPosition();

		while (pos)
		{
			PTAS* ptas = spatial->m_ptas->m_arr.GetNext(pos);
			string boundaryType;
			switch (ptas->m_topi)
			{
			case 1:
				boundaryType = "Begin";
				break;
			case 2:
				boundaryType = "End";
				break;
			}
			if (boundaryType == "Begin")
				spatials->push_back(get_spatial_association(ptas).spatial_type);  
			else
				spatials->push_back(get_spatial_association(ptas).spatial_type); 
		}
	}
	else if (ret[0] == "CompositeCurve")
	{
		auto spatial = s_spatial_ccurve_nodes[spatial_id];

		spatial_type = ret[0];
		spatials->push_back(spatial_id);

		composite_curve composite_curve;

		for (auto itorParent = spatial->m_cuco.begin(); itorParent != spatial->m_cuco.end(); itorParent++)
		{
			F_CUCO* cucoParent = *itorParent;

			for (auto itor = cucoParent->m_arr.begin(); itor != cucoParent->m_arr.end(); itor++)
			{
				CUCO* cuco = *itor;

				get_referenced_spatials(get_spatial_association(cuco).spatial_id, spatials);
			}
		}
	}
	else if (ret[0] == "Surface")
	{
		auto spatial = s_spatial_surface_nodes[spatial_id];

		spatial_type = ret[0];
		spatials->push_back(spatial_id);

		surface surface;

		for (auto itorParent = spatial->m_rias.begin(); itorParent != spatial->m_rias.end(); itorParent++)
		{
			F_RIAS* riasParent = *itorParent;
			for (auto itor = riasParent->m_arr.begin(); itor != riasParent->m_arr.end(); itor++)
			{
				RIAS* rias = *itor;
				string usage;

				switch (rias->m_usag)
				{
				case 1:
					usage = "Outer";
					break;
				case 2:
					usage = "Inner";
					break;
				}

				if (usage == "Outer")
				{
					get_referenced_spatials(get_spatial_association(rias).spatial_id, spatials);
				}
				else
				{
					if (!surface.interior_rings.has_value())
						surface.interior_rings = vector<spatial_association>();

					get_referenced_spatials(get_spatial_association(rias).spatial_id, spatials);
				}
			}
		}
	}                     
}

void hd_delete()
{
	for (auto feature_id : s_feature_ids)
	{
		vector<string> ref_spatials;

		auto spatials = hd_get_feature_spatial_associations(feature_id);

		for (auto spatial : spatials)
			get_referenced_spatials(spatial.spatial_id, &ref_spatials);

		for (auto spatial : ref_spatials)
		{
			if (!s_spatial_features.count(spatial))
				delete  s_spatial_features[spatial];
		}
	}  

}

void hd_init(/*const char *input_schema, */S101Cell *c)
{          


	s_feature_ids.clear();

	s_feature_nodes.clear();
	s_information_nodes.clear(); 
	s_spatial_features.clear();   
	__int64 key = 0;
	cell = c;
	R_FeatureRecord* fr = NULL;
	POSITION pos = c->m_feaMap.GetStartPosition();

	while (pos != NULL)
	{
		c->m_feaMap.GetNextAssoc(pos, key, fr);

		int id = fr->m_frid.m_name.RCID;

		string sid = to_string(id);

		s_feature_ids.push_back(sid);

		s_feature_nodes[sid] = fr;
	}

	R_InformationRecord* ir = NULL;
	pos = cell->m_infMap.GetStartPosition();

	while (pos != NULL)
	{
		c->m_infMap.GetNextAssoc(pos, key, ir);

		int id = ir->m_irid.m_name.RCID;

		string sid = to_string(id);

		s_information_ids.push_back(sid);

		s_information_nodes[sid] = ir;
	}

	R_PointRecord* pr = NULL;
	pos = cell->m_ptMap.GetStartPosition();
	while (pos != NULL)
	{
		cell->m_ptMap.GetNextAssoc(pos, key, pr);

		if (pr->m_c2it)
		{
			int id = pr->m_prid.m_name.RCID;

			string sid = "Point|" + to_string(id);

			s_spatial_point_nodes[sid] = pr;
		}
	}

	R_MultiPointRecord* mpr = NULL;
	pos = cell->m_mpMap.GetStartPosition();
	while (pos != NULL)
	{
		cell->m_mpMap.GetNextAssoc(pos, key, mpr);

		int id = mpr->m_mrid.m_name.RCID;

		string sid = "MultiPoint|" + to_string(id);

		s_spatial_mpoint_nodes[sid] = mpr;
	}

	R_CurveRecord* cr = NULL;
	pos = cell->m_curMap.GetStartPosition();
	while (pos != NULL)
	{
		cell->m_curMap.GetNextAssoc(pos, key, cr);

		int id = cr->m_crid.m_name.RCID;

		string sid = "Curve|" + to_string(id);

		s_spatial_curve_nodes[sid] = cr;
	}

	R_CompositeRecord* ccr = NULL;
	pos = cell->m_comMap.GetStartPosition();
	while (pos != NULL)
	{
		cell->m_comMap.GetNextAssoc(pos, key, ccr);
		if(!ccr)
			continue;
		int id = ccr->m_ccid.m_name.RCID;

		string sid = "CompositeCurve|" + to_string(id);

		s_spatial_ccurve_nodes[sid] = ccr;
	}

	R_SurfaceRecord* sr = NULL;
	pos = cell->m_surMap.GetStartPosition();
	while (pos != NULL)
	{
		cell->m_surMap.GetNextAssoc(pos, key, sr);

		int id = sr->m_srid.m_name.RCID;

		string sid = "Surface|" + to_string(id);

		s_spatial_surface_nodes[sid] = sr;
	}   

	for (auto feature_id : s_feature_ids)
	{
		vector<string> ref_spatials;

		auto spatials = hd_get_feature_spatial_associations(feature_id);

		for (auto spatial : spatials)
			get_referenced_spatials(spatial.spatial_id, &ref_spatials);
		for (auto spatial : ref_spatials)
		{
			if (!s_spatial_features.count(spatial))
				s_spatial_features[spatial] = new set<string>();

			auto spatial_features = s_spatial_features[spatial];

			spatial_features->insert(feature_id);
		}
	}
}

vector<string> hd_get_feature_ids() 
{
	vector<string> feature_ids;

	for (auto id : s_feature_ids)
		feature_ids.push_back(id);

	return feature_ids;
}

string hd_get_feature_code(string id)//C�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
{
	R_FeatureRecord* fr = s_feature_nodes[id];

	auto f1 = cell->m_dsgir.m_ftcs->m_arr.find(fr->m_frid.m_nftc);
	if (f1 == cell->m_dsgir.m_ftcs->m_arr.end())
	{
		return "";
	}
	std::wstring s1 =std::wstring( f1->second->m_code);
	string ret;
	ret.assign(s1.begin(), s1.end());
	f1->second->m_code.ReleaseBuffer();

	return ret;
}

static spatial_association get_spatial_association(F_SPAS* spatial)//C�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
{
	spatial_association sa;
	for (auto itor = spatial->m_arr.begin(); itor != spatial->m_arr.end(); itor++)
	{
		SPAS* spas = *itor;  
		string primitive1;
		switch (spas->m_name.RCNM)
		{
		case 110: primitive1 = "Point"; break;
		case 115: primitive1 = "MultiPoint"; break;
		case 120: primitive1 = "Curve"; break;
		case 125: primitive1 = "CompositeCurve"; break;
		case 130: primitive1 = "Surface"; break;
		default: 
			break;
		}
		string orientation = "Forward";
		if (spas->m_name.RCNM == 120 || spas->m_name.RCNM == 125)
		{
			switch (spas->m_ornt)
			{
			case 1:
				orientation = "Forward";
				break;
			case 2:
				orientation = "Reverse";
				break;
			}
		} 
		sa = { primitive1, primitive1 + "|" + to_string(spas->m_name.RCID), orientation };
	}
	return sa;
} 
static spatial_association get_spatial_association(PTAS* ptas)
{
	spatial_association sa;

	string primitive1 = "Point";

	sa = { primitive1, primitive1 + "|" + to_string(ptas->m_name.RCID) };
	return sa;
} 
static spatial_association get_spatial_association(CUCO* cuco)
{
	spatial_association sa;

	string primitive1;

	switch (cuco->m_name.RCNM)
	{
	case 120: primitive1 = "Curve"; break;
	case 125: primitive1 = "CompositeCurve"; 
		break;
	default: break;//Err
	}

	string orientation;

	switch (cuco->m_ornt)
	{
	case 1:
		orientation = "Forward";
		break;
	case 2:
		orientation = "Reverse";
		break;
	}

	sa = { primitive1, primitive1 + "|" + to_string(cuco->m_name.RCID), orientation };

	return sa;
}  
static spatial_association get_spatial_association(RIAS* rias)
{
	spatial_association sa;

	string primitive1;

	switch (rias->m_name.RCNM)
	{
	case 120: primitive1 = "Curve"; break;
	case 125: primitive1 = "CompositeCurve"; break; 
	default: break;//Err
	}

	string orientation;

	switch (rias->m_ornt)
	{
	case 1:
		orientation = "Forward";
		break;
	case 2:
		orientation = "Reverse";
		break;
	}

	sa = { primitive1, primitive1 + "|" + to_string(rias->m_name.RCID), orientation };

	return sa;
}  
vector<spatial_association> hd_get_feature_spatial_associations(string id)
{
	auto feature = s_feature_nodes[id]; 


	vector<spatial_association> sas;
	for (auto spatial = feature->m_spas.begin(); spatial != feature->m_spas.end(); spatial++)
	{
		spatial_association a = get_spatial_association(*spatial);
		sas.push_back(a);
	}

	return sas;
} 

static vector<string> get_simple_attribute_values(R_FeatureRecord* fr, string path, string attribute_code)
{
	vector<string> attr_values;
	vector<string> path_items;
	vector<int> atixs;

	size_t offset = 0;

	if (!path.empty())
		path += ";";        
	std::istringstream iss(path);
	std::string token;
	while (std::getline(iss, token, ';'))
	{
		auto colonIndex = token.find_first_of(':'); 

		if (colonIndex >= 0 && colonIndex < token.length() - 1)
		{
			int atixIndex = colonIndex + 1;
			auto strAtix = token.substr(atixIndex, token.length() - atixIndex);
			auto atix = atoi(strAtix.c_str());
			atixs.push_back(atix);

			auto code = token.substr(0, colonIndex);
			path_items.push_back(code);
		}
	}

	if (atixs.size() == path_items.size())
	{
		int cnt = atixs.size();                         

		bool find = false;
		int currentAtix = 0;
		int currentPaix = 0;
		if (fr->m_attr.size() > 0)
		{
			auto fattr = fr->m_attr.front();
			if (fattr->m_arr.size() > 0)
			{
				int parentIndex = -1;
				for (int i = 0; i < cnt; i++)
				{
					for (auto j = parentIndex > 0? parentIndex : 0; j < (int)fattr->m_arr.size(); j++)
					{
						auto attr = fattr->m_arr.at(j);

						auto item = cell->m_dsgir.m_atcs->m_arr.find(attr->m_natc);
						if (item != cell->m_dsgir.m_atcs->m_arr.end())
						{
							auto code = WstringToString(item->second->m_code);
							auto atix = attr->m_atix;
							if (path_items.at(i) == code && atixs.at(i) == atix)
							{
								parentIndex = j;
								break;
							}
						}
						else
						{
							OutputDebugString(_T("Attribute code error\n"));
						}
					}
				}

				parentIndex++;

				if (parentIndex != -1 || cnt == 0)
				{
					if (cnt == 0)
					{
						parentIndex = 0;
					}

					if (parentIndex <= (int)fattr->m_arr.size())
					{
						for (int i = 0; i < (int)fattr->m_arr.size(); i++)
						{
							auto attr = fattr->m_arr.at(i);

							auto item = cell->m_dsgir.m_atcs->m_arr.find(attr->m_natc);
							if (item != cell->m_dsgir.m_atcs->m_arr.end())
							{
								auto code = WstringToString(item->second->m_code);
								if (parentIndex == 0)
								{
									if (code == attribute_code && attr->m_paix == 0)
									{
										auto value = WstringToString(attr->m_atvl);
										if (value.compare("") == 0)
										{
											value = g_unknown_attribute_value;
										}
										attr_values.push_back(value);
										continue;
									}
								}
								else
								{
									if (code == attribute_code && attr->m_paix == parentIndex)
									{
										auto value = WstringToString(attr->m_atvl);
										if (value.compare("") == 0)
										{
											value = g_unknown_attribute_value;
										}
										attr_values.push_back(value);
										continue;
									}
								}
							}
							else
							{
								OutputDebugString(_T("Attribute code error1\n"));
							}
						}
					}
					else
					{
						OutputDebugString(_T("Parent index error\n"));
					}
				}
				else
				{
					OutputDebugString(_T("ParentIndex Error\n"));
				}
			}
		}
	}
	else
	{
		OutputDebugString(_T("Attribute path error\n"));
	}
	return attr_values;                                                         
}

static vector<string> get_simple_attribute_values(R_InformationRecord* Ir, string path, string attribute_code)
{
	vector<string> attr_values;
	vector<string> path_items;

	size_t offset = 0;
	size_t found;

	if (!path.empty())
		path += ";";

	while ((found = path.find_first_of(';', offset)) != string::npos)
	{
		auto path_item = path.substr(offset, found - offset);

		path_items.push_back(path_item);

		offset = found + 1;
	}

	for (auto itorParent = Ir->m_attr.begin(); itorParent != Ir->m_attr.end(); itorParent++)
	{
		F_ATTR* attrParent = *itorParent;

		for (auto itor = attrParent->m_arr.begin(); itor != attrParent->m_arr.end(); itor++)
		{
			ATTR* attr = *itor;

			auto aitor = cell->m_dsgir.m_atcs->m_arr.find(attr->m_natc);
			if (aitor != cell->m_dsgir.m_atcs->m_arr.end())
			{
				wstring code =std::wstring( aitor->second->m_code);
				string attributeAcronym;
				attributeAcronym.assign(code.begin(), code.end());
				aitor->second->m_code.ReleaseBuffer();   

				if (attributeAcronym.compare(attribute_code) == 0)
				{
					if (offset != 0)
					{
						wstring value =std::wstring( attr->m_atvl);
						string r_value;
						r_value.assign(value.begin(), value.end());
						attr->m_atvl.ReleaseBuffer();


						string parent_name = *path_items.begin();
						auto split = parent_name.find(':', 0);
						auto parent_code_in_path = parent_name.substr(0, split);

						ATTR* parent_attribute = attrParent->m_arr[attr->m_paix - 1];

						auto paitor = cell->m_dsgir.m_atcs->m_arr.find(parent_attribute->m_natc);
						if (paitor != cell->m_dsgir.m_atcs->m_arr.end())
						{
							wstring parent_code =std::wstring( paitor->second->m_code);
							string parent_attributeAcronym;
							parent_attributeAcronym.assign(parent_code.begin(), parent_code.end());
							paitor->second->m_code.ReleaseBuffer();

							if (parent_code_in_path.compare(parent_attributeAcronym) == 0)
							{
								if (r_value.compare("") == 0)
								{
									r_value = g_unknown_attribute_value;
								}
								attr_values.push_back(r_value);
							}
						}   
					}
					else
					{
						if(attr->m_atvl.GetLength() > 0)
						{
							wstring value =std::wstring(attr->m_atvl);
							string r_value;
							r_value.assign(value.begin(), value.end());
							attr->m_atvl.ReleaseBuffer();
						}
						else
						{
							string r_value = g_unknown_attribute_value;
							attr_values.push_back(r_value);
						}
					}
				}
			}
		}
	}

	return attr_values;
}


static int get_complex_attribute_count(R_FeatureRecord* fr, string path, string attribute_code)
{
	int attr_count = 0;

	vector<string> attr_values;
	vector<string> path_items;

	size_t offset = 0;
	size_t found;

	if (!path.empty())
		path += ";";

	while ((found = path.find_first_of(';', offset)) != string::npos)
	{
		auto path_item = path.substr(offset, found - offset);

		path_items.push_back(path_item);

		offset = found + 1;
	}

	for (auto itorParent = fr->m_attr.begin(); itorParent != fr->m_attr.end(); itorParent++)
	{
		F_ATTR* attrParent = *itorParent;

		for (auto itor = attrParent->m_arr.begin(); itor != attrParent->m_arr.end(); itor++)
		{
			ATTR* attr = *itor;

			auto aitor = cell->m_dsgir.m_atcs->m_arr.find(attr->m_natc);
			if (aitor != cell->m_dsgir.m_atcs->m_arr.end())
			{
				wstring code = std::wstring( aitor->second->m_code);
				string attributeAcronym;
				attributeAcronym.assign(code.begin(), code.end());
				aitor->second->m_code.ReleaseBuffer();

				if (attributeAcronym.compare(attribute_code) == 0)
				{
					if (offset != 0)
					{
						wstring value = std::wstring( attr->m_atvl);
						string r_value;
						r_value.assign(value.begin(), value.end());
						attr->m_atvl.ReleaseBuffer();

						string parent_name = *path_items.rbegin();
						auto split = parent_name.find(':', 0);
						auto parent_code_in_path = parent_name.substr(0, split);
						auto parent_sequence_in_path = parent_name.substr(split+1, parent_name.size() - split-1);
						auto n_parent_sequence_in_path = atoi(parent_sequence_in_path.c_str());

						ATTR* parent_attribute = attrParent->m_arr[attr->m_paix - 1];

						auto paitor = cell->m_dsgir.m_atcs->m_arr.find(parent_attribute->m_natc);
						if (paitor != cell->m_dsgir.m_atcs->m_arr.end())
						{
							wstring parent_code =std::wstring( paitor->second->m_code);
							string parent_attributeAcronym;
							parent_attributeAcronym.assign(parent_code.begin(), parent_code.end());
							paitor->second->m_code.ReleaseBuffer();

							if (parent_code_in_path.compare(parent_attributeAcronym) == 0 &&
								n_parent_sequence_in_path == parent_attribute->m_atix)
							{
								attr_count++;
							}
						}
					}
					else
					{
						wstring value =std::wstring( attr->m_atvl);
						string r_value;
						r_value.assign(value.begin(), value.end());
						attr->m_atvl.ReleaseBuffer();

						attr_count++;
					}
				}
			}
		}
	}                              

	return attr_count;
}

static int get_complex_attribute_count(R_InformationRecord* Ir, string path, string attribute_code)
{
	int attr_count = 0;

	vector<string> attr_values;
	vector<string> path_items;

	size_t offset = 0;
	size_t found;

	if (!path.empty())
		path += ";";

	while ((found = path.find_first_of(';', offset)) != string::npos)
	{
		auto path_item = path.substr(offset, found - offset);

		path_items.push_back(path_item);

		offset = found + 1;
	}

	for (auto itorParent = Ir->m_attr.begin(); itorParent != Ir->m_attr.end(); itorParent++)
	{
		F_ATTR* attrParent = *itorParent;

		for (auto itor = attrParent->m_arr.begin(); itor != attrParent->m_arr.end(); itor++)
		{
			ATTR* attr = *itor;

			auto aitor = cell->m_dsgir.m_atcs->m_arr.find(attr->m_natc);
			if (aitor != cell->m_dsgir.m_atcs->m_arr.end())
			{
				wstring code =std::wstring( aitor->second->m_code);
				string attributeAcronym;
				attributeAcronym.assign(code.begin(), code.end());
				aitor->second->m_code.ReleaseBuffer();   

				if (attributeAcronym.compare(attribute_code) == 0)
				{
					if (offset != 0)
					{
						wstring value =std::wstring( attr->m_atvl);
						string r_value;
						r_value.assign(value.begin(), value.end());
						attr->m_atvl.ReleaseBuffer();


						string parent_name = *path_items.begin();
						auto split = parent_name.find(':', 0);
						auto parent_code_in_path = parent_name.substr(0, split);

						ATTR* parent_attribute = attrParent->m_arr[attr->m_paix - 1];

						auto paitor = cell->m_dsgir.m_atcs->m_arr.find(parent_attribute->m_natc);
						if (paitor != cell->m_dsgir.m_atcs->m_arr.end())
						{
							wstring parent_code =std::wstring( paitor->second->m_code);
							string parent_attributeAcronym;
							parent_attributeAcronym.assign(parent_code.begin(), parent_code.end());
							paitor->second->m_code.ReleaseBuffer();

							if (parent_code_in_path.compare(parent_attributeAcronym) == 0)
							{
								attr_count++;
							}
						}   
					}
					else
					{
						wstring value =std::wstring( attr->m_atvl);
						string r_value;
						r_value.assign(value.begin(), value.end());
						attr->m_atvl.ReleaseBuffer();

						attr_count++;
					}
				}
			}
		}
	}                               

	return attr_count;
}

vector<string> hd_get_feature_simple_attribute_values(string id, string path, string attribute_code)
{
	return get_simple_attribute_values(s_feature_nodes[id], path, attribute_code);
}

int hd_get_feature_complex_attribute_count(string id, string path, string attribute_code)
{
	int a = get_complex_attribute_count(s_feature_nodes[id], path, attribute_code);
	return a;
}

vector<string> hd_get_information_type_ids()
{
	vector<string> information_ids1;

	for (auto information : s_information_nodes)
		information_ids1.push_back(information.first);

	return information_ids1;
}

string hd_get_information_type_code(string id)//C�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
{
	R_InformationRecord* ir = s_information_nodes[id];

	auto i1 = cell->m_dsgir.m_itcs->m_arr.find(ir->m_irid.m_nitc);
	if (i1 == cell->m_dsgir.m_itcs->m_arr.end())
	{
		return "";
	}
	std::wstring s1 =std::wstring(i1->second->m_code);
	string ret;
	ret.assign(s1.begin(), s1.end());
	i1->second->m_code.ReleaseBuffer();

	return ret;
}

vector<string> hd_get_information_type_simple_attribute_values(string id, string path, string attribute_code)
{
	return get_simple_attribute_values(s_information_nodes[id], path, attribute_code);
}

int hd_get_information_type_complex_attribute_count(string id, string path, string attribute_code)
{
	return get_complex_attribute_count(s_information_nodes[id], path, attribute_code);
} 
vector<string> hd_get_feature_associated_information_ids(string feature_id, string association_code, optional<string> role_code)
{
	vector<string> information_ids1;

	auto feature = s_feature_nodes[feature_id];

	if (feature->m_inas.size() > 0)
	{
		for (auto itorParent = feature->m_inas.begin(); itorParent != feature->m_inas.end(); itorParent++)
		{
			F_INAS* f_inas = *itorParent;   
			auto asitor = cell->m_dsgir.m_iacs->m_arr.find(f_inas->m_niac);
			auto ritor = cell->m_dsgir.m_arcs->m_arr.find(f_inas->m_narc);

			wstring asName = std::wstring(asitor->second->m_code);
			wstring roleName =std::wstring( ritor->second->m_code);

			string r_asName, r_roleName;

			r_asName.assign(asName.begin(), asName.end());
			r_roleName.assign(roleName.begin(), roleName.end());

			asitor->second->m_code.ReleaseBuffer();
			ritor->second->m_code.ReleaseBuffer();

			if (!role_code.has_value() || r_roleName == role_code.value())
				information_ids1.push_back(to_string(f_inas->m_name.RCID));
		}
	}

	return information_ids1;
}


vector<string> hd_get_feature_associated_feature_ids(string feature_id, string association_code, optional<string> role_code)
{
	vector<string> feature_ids;

	auto feature = s_feature_nodes[feature_id];

	if (feature->m_inas.size() > 0)
	{
		for (auto itorParent = feature->m_inas.begin(); itorParent != feature->m_inas.end(); itorParent++)
		{
			F_INAS* f_inas = *itorParent;   
			auto asitor = cell->m_dsgir.m_iacs->m_arr.find(f_inas->m_niac);
			auto ritor = cell->m_dsgir.m_arcs->m_arr.find(f_inas->m_narc);

			wstring asName =std::wstring( asitor->second->m_code);
			wstring roleName =std::wstring( ritor->second->m_code);

			string r_asName, r_roleName;

			r_asName.assign(asName.begin(), asName.end());
			r_roleName.assign(roleName.begin(), roleName.end());

			asitor->second->m_code.ReleaseBuffer();
			ritor->second->m_code.ReleaseBuffer();

			if (!role_code.has_value() || r_roleName == role_code.value())
				feature_ids.push_back(to_string(f_inas->m_name.RCID));
		}
	}

	return feature_ids;
} 


vector<string> hd_get_spatial_associated_information_ids(string spatial_id, string association_code, optional<string> role_code)
{ 
	vector<string> ret;

	int findOffset = 0;
	int splitOffset = 0;
	string token = "|";
	while ((splitOffset = spatial_id.find(token, findOffset)) != std::string::npos)
	{
		ret.push_back(spatial_id.substr(findOffset, splitOffset - findOffset));
		findOffset = splitOffset + token.length();
	}
	ret.push_back(spatial_id.substr(findOffset, spatial_id.length() - findOffset)); 
	vector<string> information_ids1;
	if (ret[0] == "Point")
	{
		auto spatial = s_spatial_point_nodes[spatial_id];

		if (spatial->m_inas.size() > 0)
		{
			for (auto itorParent = spatial->m_inas.begin(); itorParent != spatial->m_inas.end(); itorParent++)
			{
				F_INAS* f_inas = *itorParent;

				auto asitor = cell->m_dsgir.m_iacs->m_arr.find(f_inas->m_niac);
				auto ritor = cell->m_dsgir.m_arcs->m_arr.find(f_inas->m_narc);

				wstring asName =std::wstring( asitor->second->m_code);
				wstring roleName =std::wstring( ritor->second->m_code);

				string r_asName, r_roleName;

				r_asName.assign(asName.begin(), asName.end());
				r_roleName.assign(roleName.begin(), roleName.end());

				asitor->second->m_code.ReleaseBuffer();
				ritor->second->m_code.ReleaseBuffer();

				if (!role_code.has_value() || r_roleName == role_code.value())
					information_ids1.push_back(to_string(f_inas->m_name.RCID));
			}
		}
	}
	else if (ret[0] == "MultiPoint")
	{
		auto spatial = s_spatial_mpoint_nodes[spatial_id];

		if (spatial->m_inas.size() > 0)
		{
			for (auto itorParent = spatial->m_inas.begin(); itorParent != spatial->m_inas.end(); itorParent++)
			{
				F_INAS* f_inas = *itorParent;

				auto asitor = cell->m_dsgir.m_iacs->m_arr.find(f_inas->m_niac);
				auto ritor = cell->m_dsgir.m_arcs->m_arr.find(f_inas->m_narc);

				wstring asName = std::wstring(asitor->second->m_code);
				wstring roleName = std::wstring(ritor->second->m_code);

				string r_asName, r_roleName;

				r_asName.assign(asName.begin(), asName.end());
				r_roleName.assign(roleName.begin(), roleName.end());

				asitor->second->m_code.ReleaseBuffer();
				ritor->second->m_code.ReleaseBuffer();

				if (!role_code.has_value() || r_roleName == role_code.value())
					information_ids1.push_back(to_string(f_inas->m_name.RCID));
			}
		}
	}// { auto spatial = s_spatial_multipoint_nodes[spatial_id]; }
	else if (ret[0] == "Curve")
	{
		auto spatial = s_spatial_curve_nodes[spatial_id];

		if (spatial->m_inas.size() > 0)
		{
			for (auto itorParent = spatial->m_inas.begin(); itorParent != spatial->m_inas.end(); itorParent++)
			{
				F_INAS* f_inas = *itorParent;

				auto asitor = cell->m_dsgir.m_iacs->m_arr.find(f_inas->m_niac);
				auto ritor = cell->m_dsgir.m_arcs->m_arr.find(f_inas->m_narc);

				wstring asName = std::wstring(asitor->second->m_code);
				wstring roleName = std::wstring(ritor->second->m_code);

				string r_asName, r_roleName;

				r_asName.assign(asName.begin(), asName.end());
				r_roleName.assign(roleName.begin(), roleName.end());

				asitor->second->m_code.ReleaseBuffer();
				ritor->second->m_code.ReleaseBuffer();

				if (!role_code.has_value() || r_roleName == role_code.value())
					information_ids1.push_back(to_string(f_inas->m_name.RCID));
			}
		}
	}
	else if (ret[0] == "CompositeCurve")
	{
		auto spatial = s_spatial_ccurve_nodes[spatial_id];

		if (spatial->m_inas.size() > 0)
		{
			for (auto itorParent = spatial->m_inas.begin(); itorParent != spatial->m_inas.end(); itorParent++)
			{
				F_INAS* f_inas = *itorParent;

				auto asitor = cell->m_dsgir.m_iacs->m_arr.find(f_inas->m_niac);
				auto ritor = cell->m_dsgir.m_arcs->m_arr.find(f_inas->m_narc);

				wstring asName = std::wstring(asitor->second->m_code);
				wstring roleName = std::wstring(ritor->second->m_code);

				string r_asName, r_roleName;

				r_asName.assign(asName.begin(), asName.end());
				r_roleName.assign(roleName.begin(), roleName.end());

				asitor->second->m_code.ReleaseBuffer();
				ritor->second->m_code.ReleaseBuffer();

				if (!role_code.has_value() || r_roleName == role_code.value())
					information_ids1.push_back(to_string(f_inas->m_name.RCID));
			}
		}
	}
	else if (ret[0] == "Surface")
	{
		auto spatial = s_spatial_surface_nodes[spatial_id];

		if (spatial->m_inas.size() > 0)
		{
			for (auto itorParent = spatial->m_inas.begin(); itorParent != spatial->m_inas.end(); itorParent++)
			{
				F_INAS* f_inas = *itorParent;

				auto asitor = cell->m_dsgir.m_iacs->m_arr.find(f_inas->m_niac);
				auto ritor = cell->m_dsgir.m_arcs->m_arr.find(f_inas->m_narc);

				wstring asName =std::wstring(asitor->second->m_code);
				wstring roleName = std::wstring(ritor->second->m_code);

				string r_asName, r_roleName;

				r_asName.assign(asName.begin(), asName.end());
				r_roleName.assign(roleName.begin(), roleName.end());

				asitor->second->m_code.ReleaseBuffer();
				ritor->second->m_code.ReleaseBuffer();

				if (!role_code.has_value() || r_roleName == role_code.value())
					information_ids1.push_back(to_string(f_inas->m_name.RCID));
			}
		}
	}
	else {}//Err

	return information_ids1;
}

vector<string> hd_get_spatial_associated_feature_ids(string spatial_id)
{
	vector<string> feature_ids;

	if (s_spatial_features.count(spatial_id))
		for (auto feature_id : *s_spatial_features[spatial_id])
			feature_ids.push_back(feature_id);

	return feature_ids;
}


vector<string> hd_get_spatial_ids()
{ 
	vector<string> spatial_ids;  

	return spatial_ids;
}


spatial_type hd_get_spatial_type(string spatial_id)
{
	vector<string> ret;

	int findOffset = 0;
	int splitOffset = 0;
	string token = "|";

	while ((splitOffset = spatial_id.find(token, findOffset)) != std::string::npos)
	{
		ret.push_back(spatial_id.substr(findOffset, splitOffset - findOffset));
		findOffset = splitOffset + token.length();
	}
	ret.push_back(spatial_id.substr(findOffset, spatial_id.length() - findOffset));

	string spatial_type = ret[0];

	if (spatial_type == "Point")
		return spatial_type::point;
	else if (spatial_type == "MultiPoint")
		return spatial_type::multi_point;
	else if (spatial_type == "Curve")
		return spatial_type::curve;
	else if (spatial_type == "CompositeCurve")
		return spatial_type::composite_curve;
	else if (spatial_type == "Surface")
		return spatial_type::surface;

	assert(false);

	return spatial_type::unknown;
}

static point get_point(F_C2IT *coordinate)
{
	point point;

	if (coordinate)
	{
		point =
		{
			to_string(coordinate->m_xcoo),
			to_string(coordinate->m_ycoo)
		};
	}
	else
	{
		assert(false);
	}

	return point;
}

static point get_point(C3IL *coordinate)
{
	point point;
	if (!coordinate)
	{
		return point;
	}

	double x = coordinate->m_xcoo / (double)cell->m_dsgir.m_dssi.m_cmfx;
	double y = coordinate->m_ycoo / (double)cell->m_dsgir.m_dssi.m_cmfy;
	double z = coordinate->m_zcoo / (double)cell->m_dsgir.m_dssi.m_cmfz;   

	std::wstringstream sstreamVal;
	sstreamVal.setf(ios::fixed);
	sstreamVal.setf(ios::showpoint);

	sstreamVal.precision(7);
	sstreamVal << x;
	std::wstring wsx = sstreamVal.str();
	std::string sx;
	sx.assign(wsx.begin(), wsx.end());
	sstreamVal.str(L"");

	sstreamVal << y;
	std::wstring wsy = sstreamVal.str();
	std::string sy;
	sy.assign(wsy.begin(), wsy.end());
	sstreamVal.str(L"");

	sstreamVal.precision(2);
	sstreamVal << z;
	std::wstring wsz = sstreamVal.str();
	std::string sz;
	sz.assign(wsz.begin(), wsz.end());
	sstreamVal.str(L"");


	point =
	{
		sx,
		sy,
		sz
	};


	return point;
}

point hd_get_point(string spatial_id)
{
	auto spatial = s_spatial_point_nodes[spatial_id];

	auto coordinate = spatial->m_c2it;

	return get_point(coordinate);
}

multipoint hd_get_multipoint(std::string spatial_id)
{
	multipoint multipoint;

	auto spatial = s_spatial_mpoint_nodes[spatial_id];

	for (auto itor = spatial->m_c3il.begin(); itor != spatial->m_c3il.end(); itor++)
	{
		F_C3IL *c3il = *itor;
		for (auto itor = c3il->m_arr.begin(); itor != c3il->m_arr.end(); itor++)
		{
			C3IL* c3il = *itor;
			multipoint.points.push_back(get_point(c3il));
		}
	}

	return multipoint;
} 
curve hd_get_curve(std::string spatial_id)
{
	curve curve;

	auto spatial = s_spatial_curve_nodes[spatial_id];

	POSITION pos = spatial->m_ptas->m_arr.GetHeadPosition();

	while (pos)
	{
		PTAS* ptas = spatial->m_ptas->m_arr.GetNext(pos);
		string boundaryType;
		switch (ptas->m_topi)
		{
		case 1:
			boundaryType = "Begin";
			break;
		case 2:
			boundaryType = "End";
			break;
		}
		if (boundaryType == "Begin")
			curve.start_point = get_spatial_association(ptas);  
		else
			curve.end_point = get_spatial_association(ptas); 
	}

	for (auto itorParent = spatial->m_c2il.begin(); itorParent != spatial->m_c2il.end(); itorParent++)
	{
		F_C2IL* c2il = *itorParent;

		curve_segment curve_segment;

		curve_segment.interpolation = "Loxodromic";
		for (auto itor = c2il->m_arr.begin(); itor != c2il->m_arr.end(); itor++)
		{
			IC2D* ic2d = *itor;
			curve_segment.control_points.push_back({ to_string(ic2d->m_xcoo), to_string(ic2d->m_ycoo) });
		}

		curve.segments.push_back(curve_segment);
	}

	return curve;
}  
composite_curve hd_get_composite_curve(std::string spatial_id)
{
	composite_curve composite_curve;

	auto spatial = s_spatial_ccurve_nodes[spatial_id];

	for (auto itorParent = spatial->m_cuco.begin(); itorParent != spatial->m_cuco.end(); itorParent++)
	{
		F_CUCO* cucoParent = *itorParent;

		string spatialType;

		for (auto itor = cucoParent->m_arr.begin(); itor != cucoParent->m_arr.end(); itor++)
		{
			CUCO* cuco = *itor;

			composite_curve.curve_associations.push_back(get_spatial_association(cuco));
		}
	}

	return composite_curve;
} 

surface hd_get_surface(std::string spatial_id)
{
	surface surface;

	auto spatial = s_spatial_surface_nodes[spatial_id];

	for (auto itorParent = spatial->m_rias.begin(); itorParent != spatial->m_rias.end(); itorParent++)
	{
		F_RIAS* riasParent = *itorParent;
		for (auto itor = riasParent->m_arr.begin(); itor != riasParent->m_arr.end(); itor++)
		{
			RIAS* rias = *itor;
			string usage;

			switch (rias->m_usag)
			{
			case 1:
				usage = "Outer";
				break;
			case 2:
				usage = "Inner";
				break;
			}

			if (usage == "Outer")
			{
				surface.exterior_ring = get_spatial_association(rias);
			}
			else
			{
				if (!surface.interior_rings.has_value())
					surface.interior_rings = vector<spatial_association>();

				surface.interior_rings.value().push_back(get_spatial_association(rias));
			}
		}
	}

	return surface;
}
