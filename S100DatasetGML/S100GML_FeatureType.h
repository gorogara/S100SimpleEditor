#pragma once

#include "S100GML_Attribute.h"
#include "S100GML_Association.h"

#include <string>
#include <list>

class R_FeatureRecord;

namespace S100DatasetGML
{
	class S100GML_Geometry;
	class S100GML_FeatureType
	{
	public:
		S100GML_FeatureType();
		virtual ~S100GML_FeatureType();

	public:
		R_FeatureRecord* GetFr();
		void SetFr(R_FeatureRecord* value);

		std::wstring GetCamelCase();
		void SetCamelCase(std::wstring value);

		std::wstring GetId();
		void SetId(std::wstring value);

		S100GML_Geometry* GetGeometry();
		void SetGeometry(S100GML_Geometry* value);


	public: 
		R_FeatureRecord* fr;

		std::wstring camelCase;
		std::wstring id;

		std::list<S100GML_Attribute> attribute;
		std::list<S100GML_Association> association;

		S100GML_Geometry* geometry;
	};
}
