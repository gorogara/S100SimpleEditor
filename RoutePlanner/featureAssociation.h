#pragma once
#include <string>
namespace RT
{
	class featureAssociation
	{
	public:
		featureAssociation();
		virtual ~featureAssociation();
	public:
		std::wstring id;
		std::wstring arcrole;
		std::wstring title;
		std::wstring href;
	public:
		void GetContent(MSXML2::IXMLDOMNodePtr nodePtr);
	};
}