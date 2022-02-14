#include "stdafx.h"
#include "ELE_displayPlanes.h"


ELE_displayPlanes::ELE_displayPlanes()
{
}


ELE_displayPlanes::~ELE_displayPlanes()
{
	for (auto itor = S100_IC_DisplayPlanes.begin(); itor != S100_IC_DisplayPlanes.end(); itor++)
	{
		delete *itor;
	}
}



void ELE_displayPlanes::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr pChildNode = pNodeList->Getitem(i);
		if (pChildNode == NULL)
			continue;

		if (!pChildNode->baseName)
			continue;

		std::wstring baseName = std::wstring(pChildNode->baseName);

		if (baseName.compare(L"S100_IC_DisplayPlane") == 0)
		{
			S100_IC_DisplayPlane *dp = new S100_IC_DisplayPlane;
			dp->GetContents(pChildNode);
			S100_IC_DisplayPlanes.push_back(dp);

		}
		else
		{

		}

	}   
	BuildHashMap();
}

void ELE_displayPlanes::GetContents(pugi::xml_node node)
{
	for (auto instruction=node.first_child(); instruction; instruction=instruction.next_sibling()) 
	{
		auto instructionName = instruction.name();

		if (!strcmp(instructionName,"S100_IC_DisplayPlane"))
		{
			S100_IC_DisplayPlane *dp = new S100_IC_DisplayPlane;
			dp->GetContents(instruction);
			S100_IC_DisplayPlanes.push_back(dp);
		}

	}


	BuildHashMap();
}

void ELE_displayPlanes::BuildHashMap()
{
	std::vector<std::wstring> in;
	std::wstring key;

	for (auto itor = S100_IC_DisplayPlanes.begin(); itor != S100_IC_DisplayPlanes.end(); itor++)
	{
		S100_IC_DisplayPlane *dp = *itor;        
		in.push_back(dp->identifier);
		key = CreateHashMapKey(in);
		map_DPID.insert(std::unordered_map<std::wstring, S100_IC_DisplayPlane*>::value_type(key, dp));        
		in.push_back(dp->identifier);
		in.push_back(dp->name);
		key = CreateHashMapKey(in);
		map_DPNM.insert(std::unordered_map<std::wstring, S100_IC_DisplayPlane*>::value_type(key, dp));

		for (auto itor = dp->features.S100_IC_Features.begin(); itor != dp->features.S100_IC_Features.end(); itor++)
		{
			S100_IC_Feature *f = &(*itor);            
			in.push_back(EnumToString_DataProduct(f->product));
			in.push_back(f->featureCode);
			in.push_back(EnumToString_Geometry(f->geometry));
			key = CreateHashMapKey(in);

			auto fi = map_DP_FCODE.find(key); 
			if (fi == map_DP_FCODE.end())
			{
				std::list<S100_IC_Feature*> fcode_features;
				fcode_features.push_back(f);
				map_DP_FCODE.insert(std::unordered_map<std::wstring, std::list<S100_IC_Feature*>> ::value_type(key, fcode_features));
			}
			else
			{
				std::list<S100_IC_Feature*> *fcode_features = &fi->second;
				fcode_features->push_back(f);
			}
		}
	}
}