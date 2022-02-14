#include "stdafx.h"
#include "S100_CatalogueMetadata.h"
namespace Dataset
{
	S100_CatalogueMetadata::S100_CatalogueMetadata()
	{

	}
	S100_CatalogueMetadata::~S100_CatalogueMetadata()
	{

	}
	void S100_CatalogueMetadata::SetCatalogType(std::wstring value)
	{
		catalogType = value;
	}
	void S100_CatalogueMetadata::SetFileName(std::wstring value)
	{
		fileName = value;
	}
	void S100_CatalogueMetadata::SetName(std::wstring value)
	{
		name = value;
	}
	void S100_CatalogueMetadata::SetFileLocation(std::wstring value)
	{
		fileLocation = value;
	}
	void S100_CatalogueMetadata::SetPurpose(std::wstring value)
	{
		purpose = value;
	}
	void S100_CatalogueMetadata::SetEditionNumber(std::wstring value)
	{
		editionNumber = value;
	}

	void S100_CatalogueMetadata::SetIssueDate(std::wstring value)
	{
		issueDate = value;
	}

	void S100_CatalogueMetadata::SetProductSpecification(ProductSpecification value)
	{
		productSpecification = value;
	}

	void S100_CatalogueMetadata::SetDataType(std::wstring value)
	{
		dataType = value;
	}

	void S100_CatalogueMetadata::SetComment(std::wstring value)
	{
		comment = value;
	}

	void S100_CatalogueMetadata::SetCheckSum(std::wstring value)
	{
		checkSum = value;
	} 

	std::wstring S100_CatalogueMetadata::GetCatalogType() 
	{
		return catalogType;
	}

	std::wstring S100_CatalogueMetadata::GetFileName()
	{
		return fileName;
	}

	std::wstring S100_CatalogueMetadata::GetName()
	{
		return name;
	}

	std::wstring S100_CatalogueMetadata::GetFileLoacation()
	{
		return fileLocation;
	}

	std::wstring S100_CatalogueMetadata::GetPurpose()
	{
		return purpose;
	}

	std::wstring S100_CatalogueMetadata::GetEditionNumber()
	{
		return editionNumber;
	}

	std::wstring S100_CatalogueMetadata::GetIssueDate()
	{
		return issueDate;
	}

	ProductSpecification S100_CatalogueMetadata::GetProductSpecification()
	{
		return productSpecification;
	}

	std::wstring S100_CatalogueMetadata::GetDataType()
	{
		return dataType;
	}

	std::wstring S100_CatalogueMetadata::GetComment()
	{
		return comment;
	}

	std::wstring S100_CatalogueMetadata::GetCheckSum()
	{
		return checkSum;
	}
}
