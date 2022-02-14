#pragma once

#include "S100GML_Attribute.h"
#include "S100GML_Association.h"

class R_InformationRecord;

namespace S100DatasetGML
{
	class S100GML_InformationType
	{
	public:
		S100GML_InformationType();
		virtual ~S100GML_InformationType(); 
		R_InformationRecord* ir;

		std::wstring camelCase;
		std::wstring id;

		std::list<S100GML_Attribute> attribute;
		std::list<S100GML_Association> association;
	};
}
