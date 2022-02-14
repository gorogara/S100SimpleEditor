#pragma once
#include <string>
#include <list>
namespace S100DatasetGML
{
	class S100GML_Attribute
	{
	public:
		S100GML_Attribute();
		virtual ~S100GML_Attribute();

	public:
		

	public:
		S100GML_Attribute* parentAttr;

		std::list<S100GML_Attribute> childAttr;
		std::wstring camelCase;
		std::wstring value;
	};
}
