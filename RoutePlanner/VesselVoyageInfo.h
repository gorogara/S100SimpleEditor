#pragma once
#include <string>

namespace RT
{
	class VesselVoyageInfo
	{
	public:
		VesselVoyageInfo();
		virtual ~VesselVoyageInfo();

	public:
		std::wstring id;
		std::wstring voyageNumber;
		std::wstring vesselMetacentricHeight;

	public:
		void GetContent(MSXML2::IXMLDOMNodePtr nodePtr);
		void Save(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr);
	};
}