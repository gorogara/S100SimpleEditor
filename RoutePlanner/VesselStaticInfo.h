#pragma once
#include "VesselVoyageInfo.h"

#include <list>

namespace RT
{
	class informationAssociation;
	class VesselVoyageInfo;

	class VesselStaticInfo
	{
	public:
		VesselStaticInfo();
		virtual ~VesselStaticInfo();

	public:
		std::list<informationAssociation*> iaList;
		std::wstring id;
		std::wstring vesselName;
		std::wstring vesselType;
		VesselVoyageInfo* vesselVoyageInfo;

	public:
		void GetContent(MSXML2::IXMLDOMNodePtr nodePtr);
		void Save(MSXML2::IXMLDOMDocument2Ptr pDoc, MSXML2::IXMLDOMElementPtr ptr);
	};

}