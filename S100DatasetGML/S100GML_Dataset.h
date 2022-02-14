#pragma once

#include "S100GML_FeatureType.h"
#include "S100GML_InformationType.h"
#include "S100GML_Attribute.h"
#include "S100DatasetGML.h"

#include <string>
#include <list>
#include <unordered_map>

class S100GML_Dataset;

class Catalog;
class S101Cell;
class R_FeatureRecord;
class R_InformationRecord;

namespace S100DatasetGML
{
	class S100GML_FeatureType;
	class S100GML_InformationType;

	class S100GML_Dataset
	{
	public:
		S100GML_Dataset();
		virtual ~S100GML_Dataset();
		std::unordered_map<std::wstring, std::wstring> gml_namespace;

		std::unordered_map<std::wstring, S100GML_Attribute> attribute;
		std::unordered_map<std::wstring, S100GML_FeatureType*> features;
		std::unordered_map<std::wstring, S100GML_InformationType*> informations;

		void SetFeatureToFeatureAssociation(S101Cell* cell, R_FeatureRecord* orgFr, R_FeatureRecord* objFr);
		void SetFeatureToInformationAssociation(S101Cell* cell, R_FeatureRecord* orgFr, R_InformationRecord* objIr);
		void SetInformationToInformationAssociation(S101Cell* cell, R_InformationRecord* orgIr, R_InformationRecord* objIr);
	};

	S100GMLDLL_API S100GML_Dataset* S100GML_OPEN(std::wstring filepath, Catalog* catalog);
	S100GMLDLL_API S100GML_Dataset* S100GML_OPENByPugi(std::wstring filepath, Catalog* catalog);
	S100GMLDLL_API void S100GML_DELETE(S100GML_Dataset* dataset);
}