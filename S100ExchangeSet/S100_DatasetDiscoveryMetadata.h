#pragma once
#include "ProductSpecification.h"
#include "ProducingAgency.h"
#include "BoundingBox.h"
#include "S100_19115DatasetMetadata.h"
#include "S100_SupportFileDiscoveryMetadata.h"
#include <string>
#include <list>

namespace Dataset
{
	class S100_DatasetDiscoveryMetadata
	{
	public:
		S100_DatasetDiscoveryMetadata();
		virtual ~S100_DatasetDiscoveryMetadata();

	private:
		std::wstring	fileName;
		std::wstring	filePath;
		std::wstring	description;
		int				dataProtection = 0;
		std::wstring	purpose;
		std::wstring	specificUsage;
		int				editionNumber = 0;
		int				updateNumber = 0;
		std::wstring	updateApplicationDate;
		std::wstring	issueDate;
		ProductSpecification productSpecification;
		ProducingAgency producingAgendataProtectioncy;
		int				optimumDisplayScale = 0;
		int				maximumDisplayScale = 0;
		int				minimumDisplayScale = 0;
		std::wstring	horizontalDatumReference;
		int				horizontalDatumValue = 0;
		std::wstring	verticalDatum;
		std::wstring	soundingDatum;
		std::wstring	dataType;
		std::wstring	dataTypeVersion;
		BoundingBox		boundingBox;
		std::wstring	comment;
		std::wstring	checkSum;
		std::list<S100_19115DatasetMetadata> s100_19115DatasetMetadata;
		std::list<S100_SupportFileDiscoveryMetadata> s100_SupportFileDiscoveryMetadata;

	public:
		void SetFileName(std::wstring value);
		void SetFilePath(std::wstring value);
		void SetDescrition(std::wstring value);
		void SetDataProtection(int value);
		void SetPurpose(std::wstring value);
		void SetSpecificUsage(std::wstring value);
		void SetEditionNumber(int value);
		void SetUpdateNumber(int value);
		void SetUpdateApplicationDate(std::wstring value);
		void SetIssueDate(std::wstring value);
		void SetProductSpecification(ProductSpecification value);
		void SetProducingAgendataProtectioncy(ProducingAgency value);
		void SetOptimumDisplayScale(int value);
		void SetMaximumDisplayScale(int value);
		void SetMinimumDisplayScale(int value);
		void SetHorizontalDatumReference(std::wstring value);
		void SetHorizontalDatumValue(int value);
		void SetVerticalDatum(std::wstring value);
		void SetSoundingDatum(std::wstring value);
		void SetDataType(std::wstring value);
		void SetDataTypeVersion(std::wstring value);
		void SetBoundingBox(BoundingBox value);
		void SetComment(std::wstring value);
		void SetCheckSum(std::wstring value);
		void SetS100_19115DatasetMetadata(std::list<S100_19115DatasetMetadata> value);
		void SetS100_SupportFileDiscoveryMetadata(std::list<S100_SupportFileDiscoveryMetadata> value);

		std::wstring GetFileName();
		std::wstring GetFilePath();
		std::wstring GetDescrition();
		int GetDataProtection();
		std::wstring GetPurpose();
		std::wstring GetSpecificUsage();
		int GetEditionNumber();
		int GetUpdateNumber();
		std::wstring GetUpdateApplicationDate();
		std::wstring GetIssueDate();
		ProductSpecification GetProductSpecification();
		ProducingAgency GetProducingAgendataProtectioncy();
		int GetOptimumDisplayScale();
		int GetMaximumDisplayScale();
		int GetMinimumDisplayScale();
		std::wstring GetHorizontalDatumReference();
		int GetHorizontalDatumValue();
		std::wstring GetVerticalDatum();
		std::wstring GetSoundingDatum();
		std::wstring GetDataType();
		std::wstring GetDataTypeVersion();
		BoundingBox GetBoundingBox();
		std::wstring GetComment();
		std::wstring GetCheckSum();
		std::list<S100_19115DatasetMetadata>  GetS100_19115DatasetMetadata();
		std::list<S100_SupportFileDiscoveryMetadata> GetS100_SupportFileDiscoveryMetadata();
	};
}