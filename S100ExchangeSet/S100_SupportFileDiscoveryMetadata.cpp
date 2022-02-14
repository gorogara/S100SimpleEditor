#include "stdafx.h"
#include "S100_SupportFileDiscoveryMetadata.h"
namespace Dataset
{
	S100_SupportFileDiscoveryMetadata::S100_SupportFileDiscoveryMetadata()
	{

	}
	S100_SupportFileDiscoveryMetadata::~S100_SupportFileDiscoveryMetadata() 
	{

	}

	void S100_SupportFileDiscoveryMetadata::SetFileName(std::wstring value)
	{
		fileName = value;
	}

	void S100_SupportFileDiscoveryMetadata::SetFileLoaction(std::wstring value)
	{
		fileLocation = value;
	}

	void S100_SupportFileDiscoveryMetadata::SetPurPose(std::wstring value)
	{
		purpose = value;
	}

	void S100_SupportFileDiscoveryMetadata::SetEditionNumber(std::wstring value)
	{
		editionNumber = value;
	}

	void S100_SupportFileDiscoveryMetadata::SetIssueDate(std::wstring value)
	{
		issueDate = value;
	}

	void S100_SupportFileDiscoveryMetadata::SetDataType(std::wstring value)
	{
		dataType = value;
	}

	void S100_SupportFileDiscoveryMetadata::SetComment(std::wstring value)
	{
		comment = value;
	}

	void S100_SupportFileDiscoveryMetadata::SetCheckSum(std::wstring value)
	{
		checkSum = value;
	}

	std::wstring S100_SupportFileDiscoveryMetadata::GetFileName()
	{
		return fileName;
	}
	std::wstring S100_SupportFileDiscoveryMetadata::GetFileLocation()
	{
		return fileLocation;
	}
	std::wstring S100_SupportFileDiscoveryMetadata::GetPurpose()
	{
		return purpose;
	}
	std::wstring S100_SupportFileDiscoveryMetadata::GetEditionNumber()
	{
		return editionNumber;
	}
	std::wstring S100_SupportFileDiscoveryMetadata::GetIssueDate()
	{
		return issueDate;
	}
	std::wstring S100_SupportFileDiscoveryMetadata::GetDataType()
	{
		return dataType;
	}
	std::wstring S100_SupportFileDiscoveryMetadata::GetComment()
	{
		return comment;
	}
	std::wstring S100_SupportFileDiscoveryMetadata::GetCheckSum()
	{
		return checkSum;
	}
	
}
