#include "stdafx.h"
#include "Citation.h"

#include "..\\DLL_MessageProcess\DLL_MessageProcess.h"
Citation::Citation()
{

}

Citation::~Citation()
{

}

void Citation::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	USES_CONVERSION;

	MSXML2::IXMLDOMNodeListPtr pNodeList = pNode->GetchildNodes();

	int cnt = pNodeList->Getlength();
	for (int i = 0; i < cnt; i++) {
		MSXML2::IXMLDOMNodePtr pChildNode = pNodeList->Getitem(i);
		if (pChildNode == NULL)
			continue;
		if (!pChildNode->baseName)
			continue;

		std::string baseName = std::string(W2A(pChildNode->baseName));

		if (baseName.compare("title") == 0)
		{
			title = pChildNode->Gettext();
		}
		else if (baseName.compare("aternateTitle") == 0)
		{
			aternateTitle.push_back(std::wstring(pChildNode->Gettext()));
		}
		else if (baseName.compare("date") == 0)
		{
			Date d;
			d.GetContents(pChildNode);
			date.push_back(d);
		}
		else if (baseName.compare("edition") == 0)
		{
			edition = pChildNode->Gettext();
		}
		else if (baseName.compare("editionDate") == 0)
		{
			editionDate.GetContents(pChildNode);
		}
		else if (baseName.compare("identifier") == 0)
		{
			identifier = pChildNode->Gettext();
		}
		else if (baseName.compare("identifierType") == 0)
		{
			identifierType = pChildNode->Gettext();
		}
		else if (baseName.compare("citedResponsibleParty") == 0)
		{
			citedResponsibleParty.GetContents(pChildNode);
		}
		else if (baseName.compare("presentationForm") == 0)
		{
			presentationForm.GetContents(pChildNode);
		}
		else if (baseName.compare("series") == 0)
		{
			series.GetContents(pChildNode);
		}
		else if (baseName.compare("otherCitationDetails") == 0)
		{
			otherCitationDetails = pChildNode->Gettext();
		}
		else if (baseName.compare("collectiveTitle") == 0)
		{
			collectiveTitle = pChildNode->Gettext();
		}
		else if (baseName.compare("ISBN") == 0)
		{
			ISBN = pChildNode->Gettext();
		}
		else if (baseName.compare("ISSN") == 0)
		{
			ISSN = pChildNode->Gettext();
		}
	}
}
void Citation::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100CI:title"))
		{ 
			SetTitle((char*)instruction.child_value());
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:title setting Clear", KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:aternateTitle"))
		{
			SetAternateTitle((char*)instruction.child_value()); 
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:aternateTitle setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:date"))
		{
			Date* date = new Date();
			date->GetContents(instruction);
			SetDate(date); 
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:date setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:edition"))
		{
			SetEdition((char*)instruction.child_value()); 
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:edition setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:editionDate"))
		{
			DateExt* dateext = new DateExt();
			dateext->GetContents(instruction);
			SetEditionDate(*dateext); 
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:editionDate setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:identifier"))
		{
			SetIdentifier((char*)instruction.child_value()); 
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:identifier setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:identifierType"))
		{
			SetIdentifierType((char*)instruction.child_value()); 
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:identifierType setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:citedResponsibleParty"))
		{
			ResponsibleParty* party = new ResponsibleParty();
			party->GetContents(instruction);
			SetCitedResponsibleParty(*party); 
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:citedResponsibleParty setting Clear",KRS_MSG_PROCESS::Developer_Mode, KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:presentationForm"))
		{
			PresentationFormCode* code = new PresentationFormCode();
			code->GetContents(instruction);
			SetPresentationForm(*code); 
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:presentationForm setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:series"))
		{
			Series* series = new Series();
			series->GetContents(instruction);
			SetSeries(*series); 
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:series setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:otherCitationDetails"))
		{
			SetOtherCicationDetails((char*)instruction.child_value()); 
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:otherCitationDetails setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:collectiveTitle"))
		{
			SetCollectiveTitle((char*)instruction.child_value()); 
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:collectiveTitle setting Clear", KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:ISBN"))
		{
			SetISBN((char*)instruction.child_value()); 
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:ISBN setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else if (!strcmp(instructionName, "S100CI:ISSN"))
		{
			SetISSN((char*)instruction.child_value()); 
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"S100CI:ISSN setting Clear",KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
		else 
		{
			std::wstring content = pugi::as_wide(instructionName);
			content.append(L" is another data");
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, content.c_str(),KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
	}
}

void Citation::SetTitle(char* value) 
{
	title =pugi::as_wide(value);
}

std::wstring Citation::GetTitle()
{
	return title;
}

void Citation::SetAternateTitle(char* value) 
{
	aternateTitle.push_back(pugi::as_wide(value));
}

void Citation::SetAternateTitle(std::list<std::wstring>& value)
{
	aternateTitle = value;
}

std::list<std::wstring>& Citation::GetAternateTitle()
{
	return aternateTitle;
}

void Citation::SetDate(Date* value)
{
	date.push_back(*value);
}
void Citation::SetDate(std::list<Date>& value)
{
	date = value;
}

std::list<Date>& Citation::GetDate()
{
	return date;
}

void Citation::SetEdition(char* value)
{
	edition =pugi::as_wide(value);
}

std::wstring Citation::GetEdition()
{	
	return edition;
}

void Citation::SetEditionDate(DateExt& value)
{
	editionDate = value;
}

DateExt& Citation::GetEditionDate()
{
	return editionDate;
}

void Citation::SetIdentifier(char* value)
{
	identifier =pugi::as_wide(value);
}

std::wstring Citation::GetIdentifier()
{
	return identifier;
}

void Citation::SetIdentifierType(char* value)
{
	identifierType = pugi::as_wide(value);
}

std::wstring Citation::GetIdentifierType()
{
	return identifierType;
}

void Citation::SetCitedResponsibleParty(ResponsibleParty& value)
{
	citedResponsibleParty = value;
}

ResponsibleParty& Citation::GetCitedResponsibleParty()
{
	return citedResponsibleParty;
}

void Citation::SetPresentationForm(PresentationFormCode& value)
{
	presentationForm = value; 
}

PresentationFormCode& Citation::GetPresentationForm()
{
	return presentationForm;
}

void Citation::SetSeries(Series& value)
{
	series = value;
}

Series& Citation::GetSeries()
{
	return series;
}

void Citation::SetOtherCicationDetails(char* value)
{
	otherCitationDetails =pugi::as_wide(value);
}

std::wstring Citation::GetOtherCitationDetails() 
{
	return otherCitationDetails;
}

void Citation::SetCollectiveTitle(char* value)
{
	collectiveTitle = pugi::as_wide(value);
}

std::wstring Citation::GetCollectiveTitle() 
{
	return collectiveTitle;
}

void Citation::SetISBN(char* value) 
{
	ISBN = pugi::as_wide(value);
}

std::wstring Citation::GetISBN() 
{
	return ISBN;
}

void Citation::SetISSN(char* value) 
{
	ISSN = pugi::as_wide(value);
}

std::wstring Citation::GetISSN()
{
	return ISSN;
}