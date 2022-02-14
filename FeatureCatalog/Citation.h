#pragma once
#include "XML_Item.h"
#include "Date.h"
#include "PresentationFormCode.h"
#include "ResponsibleParty.h"
#include "Series.h"

#include <pugixml.hpp>
#include <string>

class Citation : public XML_Item
{

public:
	Citation();
	virtual ~Citation();

private:
	std::wstring title;
	std::list<std::wstring> aternateTitle;
	std::list<Date> date;
	std::wstring edition;
	DateExt editionDate;
	std::wstring identifier;
	std::wstring identifierType;
	ResponsibleParty citedResponsibleParty;
	PresentationFormCode presentationForm;
	Series series;
	std::wstring otherCitationDetails;
	std::wstring collectiveTitle;
	std::wstring ISBN;
	std::wstring ISSN;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

	void SetTitle(char* value);
	std::wstring GetTitle();

	void SetAternateTitle(char* value);
	void SetAternateTitle(std::list<std::wstring>& value);
	std::list<std::wstring>& GetAternateTitle();
	

	void SetDate(Date* value);
	void SetDate(std::list<Date>& value);
	std::list<Date>& GetDate();

	void SetEdition(char* value);
	std::wstring GetEdition();                        

	void SetEditionDate(DateExt& value);
	DateExt& GetEditionDate();

	void SetIdentifier(char* value);
	std::wstring GetIdentifier();

	void SetIdentifierType(char* value);
	std::wstring GetIdentifierType();

	void SetCitedResponsibleParty(ResponsibleParty& value);
	ResponsibleParty& GetCitedResponsibleParty();

	void SetPresentationForm(PresentationFormCode& value);
	PresentationFormCode& GetPresentationForm();
	
	void SetSeries(Series& value);
	Series& GetSeries();

	void SetOtherCicationDetails(char* value);
	std::wstring GetOtherCitationDetails();

	void SetCollectiveTitle(char* value);
	std::wstring GetCollectiveTitle();

	void SetISBN(char* value);
	std::wstring GetISBN();

	void SetISSN(char* value);
	std::wstring GetISSN();
};