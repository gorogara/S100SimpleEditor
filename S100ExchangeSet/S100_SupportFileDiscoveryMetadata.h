#pragma once
#include <string>

namespace Dataset
{
	class S100_SupportFileDiscoveryMetadata
	{
	public:
		S100_SupportFileDiscoveryMetadata();
		virtual ~S100_SupportFileDiscoveryMetadata();

	private:
		std::wstring fileName;
		std::wstring fileLocation;
		std::wstring purpose;
		std::wstring editionNumber;
		std::wstring issueDate;
		std::wstring dataType;
		std::wstring comment;
		std::wstring checkSum;

	public:
		void SetFileName(std::wstring value);
		void SetFileLoaction(std::wstring value);
		void SetPurPose(std::wstring value);
		void SetEditionNumber(std::wstring value);
		void SetIssueDate(std::wstring value);
		void SetDataType(std::wstring value);
		void SetComment(std::wstring value);
		void SetCheckSum(std::wstring value);

		std::wstring GetFileName();
		std::wstring GetFileLocation();
		std::wstring GetPurpose();
		std::wstring GetEditionNumber();
		std::wstring GetIssueDate();
		std::wstring GetDataType();
		std::wstring GetComment();
		std::wstring GetCheckSum();
	};
}