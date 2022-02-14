#pragma once
#include <string>

namespace RT
{
	class informationAssociation
	{
	public:
		informationAssociation();
		virtual ~informationAssociation();

	public:
		std::wstring id;
		std::wstring arcrole;
		std::wstring title;
		std::wstring href;

	public:
		void GetContent(MSXML2::IXMLDOMNodePtr nodePtr);
		void Save(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr
			, std::wstring arcrole, std::wstring title, std::wstring href, std::wstring gml_id);
	};
}
