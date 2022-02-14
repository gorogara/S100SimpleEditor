#include "stdafx.h"
#include "S100_DatasetDiscoveryMetadata.h"
namespace Dataset
{
	S100_DatasetDiscoveryMetadata::S100_DatasetDiscoveryMetadata()
	{

	}
	S100_DatasetDiscoveryMetadata::~S100_DatasetDiscoveryMetadata() 
	{

	}

	void S100_DatasetDiscoveryMetadata::SetFileName(std::wstring value) 
	{
		fileName = value;
	}
	void S100_DatasetDiscoveryMetadata::SetFilePath(std::wstring value)
	{
		filePath = value;
	}
	void S100_DatasetDiscoveryMetadata::SetDescrition(std::wstring value)
	{
		description = value;
	}
	void S100_DatasetDiscoveryMetadata::SetDataProtection(int value)
	{
		dataProtection = value;
	}
	void S100_DatasetDiscoveryMetadata::SetPurpose(std::wstring value)
	{
		purpose = value;
	}
	void S100_DatasetDiscoveryMetadata::SetSpecificUsage(std::wstring value)
	{
		specificUsage = value;
	}
	void S100_DatasetDiscoveryMetadata::SetEditionNumber(int value)
	{
		editionNumber = value;
	}
	void S100_DatasetDiscoveryMetadata::SetUpdateNumber(int value)
	{
		updateNumber = value;
	}
	void S100_DatasetDiscoveryMetadata::SetUpdateApplicationDate(std::wstring value)
	{
		updateApplicationDate = value;
	}
	void S100_DatasetDiscoveryMetadata::SetIssueDate(std::wstring value)
	{
		issueDate = value;
	}
	void S100_DatasetDiscoveryMetadata::SetProductSpecification(ProductSpecification value)
	{
		productSpecification = value;
	}
	void S100_DatasetDiscoveryMetadata::SetProducingAgendataProtectioncy(ProducingAgency value)
	{
		producingAgendataProtectioncy = value;
	}
	void S100_DatasetDiscoveryMetadata::SetOptimumDisplayScale(int value)
	{
		optimumDisplayScale = value;
	}
	void S100_DatasetDiscoveryMetadata::SetMaximumDisplayScale(int value)
	{
		maximumDisplayScale = value;
	}
	void S100_DatasetDiscoveryMetadata::SetMinimumDisplayScale(int value)
	{
		minimumDisplayScale = value;
	}
	void S100_DatasetDiscoveryMetadata::SetHorizontalDatumReference(std::wstring value)
	{
		horizontalDatumReference = value;
	}
	void S100_DatasetDiscoveryMetadata::SetHorizontalDatumValue(int value)
	{
		horizontalDatumValue = value;
	}

	void S100_DatasetDiscoveryMetadata::SetVerticalDatum(std::wstring value)
	{
		verticalDatum = value;
	}

	void S100_DatasetDiscoveryMetadata::SetSoundingDatum(std::wstring value)
	{
		soundingDatum = value;
	}

	void S100_DatasetDiscoveryMetadata::SetDataType(std::wstring value)
	{
		dataType = value;
	}

	void S100_DatasetDiscoveryMetadata::SetDataTypeVersion(std::wstring value)
	{
		dataTypeVersion = value;
	}

	void S100_DatasetDiscoveryMetadata::SetBoundingBox(BoundingBox value)
	{
		boundingBox = value;
	}

	void S100_DatasetDiscoveryMetadata::SetComment(std::wstring value)
	{
		comment = value;
	}

	void S100_DatasetDiscoveryMetadata::SetCheckSum(std::wstring value)
	{
		checkSum = value;
	}
	void S100_DatasetDiscoveryMetadata::SetS100_19115DatasetMetadata(std::list<S100_19115DatasetMetadata> value)
	{
		s100_19115DatasetMetadata = value;
	}
	void S100_DatasetDiscoveryMetadata::SetS100_SupportFileDiscoveryMetadata(std::list<S100_SupportFileDiscoveryMetadata> value)
	{
		s100_SupportFileDiscoveryMetadata = value;
	} 

	std::wstring S100_DatasetDiscoveryMetadata::GetFileName()
	{
		return fileName;
	}

	std::wstring S100_DatasetDiscoveryMetadata::GetFilePath()
	{
		return filePath;
	}

	std::wstring S100_DatasetDiscoveryMetadata::GetDescrition()
	{
		return description;
	}

	int S100_DatasetDiscoveryMetadata::GetDataProtection()
	{
		return dataProtection;
	}

	std::wstring S100_DatasetDiscoveryMetadata::GetPurpose()
	{
		return purpose;
	}

	std::wstring S100_DatasetDiscoveryMetadata::GetSpecificUsage()
	{
		return specificUsage;
	}

	int S100_DatasetDiscoveryMetadata::GetEditionNumber()
	{
		return editionNumber;
	}

	int S100_DatasetDiscoveryMetadata::GetUpdateNumber()
	{
		return updateNumber;
	}

	std::wstring S100_DatasetDiscoveryMetadata::GetUpdateApplicationDate()
	{
		return updateApplicationDate;
	}
	std::wstring S100_DatasetDiscoveryMetadata::GetIssueDate()
	{
		return issueDate;
	}
	ProductSpecification S100_DatasetDiscoveryMetadata::GetProductSpecification()
	{
		return productSpecification;
	}
	ProducingAgency S100_DatasetDiscoveryMetadata::GetProducingAgendataProtectioncy()
	{
		return producingAgendataProtectioncy;
	}
	int S100_DatasetDiscoveryMetadata::GetOptimumDisplayScale()
	{
		return optimumDisplayScale;
	}
	int S100_DatasetDiscoveryMetadata::GetMaximumDisplayScale()
	{
		return maximumDisplayScale;
	}
	int S100_DatasetDiscoveryMetadata::GetMinimumDisplayScale()
	{
		return minimumDisplayScale;
	}
	std::wstring S100_DatasetDiscoveryMetadata::GetHorizontalDatumReference()
	{
		return horizontalDatumReference;
	}
	int S100_DatasetDiscoveryMetadata::GetHorizontalDatumValue()
	{
		return horizontalDatumValue;
	}
	std::wstring S100_DatasetDiscoveryMetadata::GetVerticalDatum()
	{
		return verticalDatum;
	}
	std::wstring S100_DatasetDiscoveryMetadata::GetSoundingDatum()
	{
		return soundingDatum;
	}
	std::wstring S100_DatasetDiscoveryMetadata::GetDataType()
	{
		return dataType;
	}
	std::wstring S100_DatasetDiscoveryMetadata::GetDataTypeVersion()
	{
		return dataTypeVersion;
	}
	BoundingBox S100_DatasetDiscoveryMetadata::GetBoundingBox()
	{
		return boundingBox;
	}
	std::wstring S100_DatasetDiscoveryMetadata::GetComment()
	{
		return comment;
	}
	std::wstring S100_DatasetDiscoveryMetadata::GetCheckSum()
	{
		return checkSum;
	}
	std::list<S100_19115DatasetMetadata> S100_DatasetDiscoveryMetadata::GetS100_19115DatasetMetadata()
	{
		return s100_19115DatasetMetadata;
	}
	std::list<S100_SupportFileDiscoveryMetadata> S100_DatasetDiscoveryMetadata::GetS100_SupportFileDiscoveryMetadata()
	{
		return s100_SupportFileDiscoveryMetadata;
	}
	
}
