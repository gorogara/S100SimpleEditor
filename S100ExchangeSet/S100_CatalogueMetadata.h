#pragma once
#include<string>
#include "ProductSpecification.h"
namespace Dataset
{
	class S100_CatalogueMetadata
	{
	public:

		S100_CatalogueMetadata();
		~S100_CatalogueMetadata();

	private:
		std::wstring	catalogType;
		std::wstring	fileName;
		std::wstring	name;
		std::wstring	fileLocation;
		std::wstring	purpose;
		std::wstring	editionNumber;
		std::wstring	issueDate;
		ProductSpecification productSpecification;
		std::wstring	dataType;
		std::wstring	comment;
		std::wstring	checkSum;

	public:
		void SetCatalogType(std::wstring value);
		void SetFileName(std::wstring value);
		void SetName(std::wstring value);
		void SetFileLocation(std::wstring value);
		void SetPurpose(std::wstring value);
		void SetEditionNumber(std::wstring value);
		void SetIssueDate(std::wstring value);
		void SetProductSpecification(ProductSpecification value);
		void SetDataType(std::wstring value);
		void SetComment(std::wstring value);
		void SetCheckSum(std::wstring value); 

		std::wstring GetCatalogType();
		std::wstring GetFileName();
		std::wstring GetName();
		std::wstring GetFileLoacation();
		std::wstring GetPurpose();
		std::wstring GetEditionNumber();
		std::wstring GetIssueDate();
		ProductSpecification GetProductSpecification();
		std::wstring GetDataType();
		std::wstring GetComment();
		std::wstring GetCheckSum();
	};
}