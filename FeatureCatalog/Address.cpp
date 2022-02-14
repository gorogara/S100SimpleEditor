#include "stdafx.h"
#include "Address.h"
#include "..\\DLL_MessageProcess\DLL_MessageProcess.h"


Address::Address()
{
}


Address::~Address()
{
}


void Address::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare("deliveryPoint") == 0)
		{
			deliveryPoint = pChildNode->Gettext();
		}
		else if (baseName.compare("city") == 0)
		{
			city = pChildNode->Gettext();
		}
		else if (baseName.compare("administrativeArea") == 0)
		{
			administrativeArea = pChildNode->Gettext();
		}
		else if (baseName.compare("postalCode") == 0)
		{
			postalCode = pChildNode->Gettext();
		}
		else if (baseName.compare("country") == 0)
		{
			country = pChildNode->Gettext();
		}
		else if (baseName.compare("electronicMailAddress") == 0)
		{
			electronicMailAddress = pChildNode->Gettext();
		}
	}
}
void Address::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName, "S100CI:deliveryPoint"))
		{
			SetDeliveryPoint((char*)instruction.child_value()); 
		}
		else if (!strcmp(instructionName, "S100CI:city")) 
		{
			SetCity((char*)instruction.child_value()); 

		}
		else if (!strcmp(instructionName, "S100CI:administrativeArea"))
		{
			SetAdministrativeArea((char*)instruction.child_value()); 
		}
		else if (!strcmp(instructionName, "S100CI:postalCode"))
		{
			SetPostalCode((char*)instruction.child_value()); 
		}
		else if (!strcmp(instructionName, "S100CI:country"))
		{
			SetCountry((char*)instruction.child_value()); 
		}
		else if (!strcmp(instructionName, "S100CI:electronicMailAddress"))
		{
			SetElectronicMailAddress((char*)instruction.child_value()); 
		}
		else 
		{
			std::wstring content = pugi::as_wide(instructionName);
			content.append(L"is another data");
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, content.c_str(),KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}

	}
}

void Address::SetDeliveryPoint(char* value)
{
	deliveryPoint =pugi::as_wide(value);
}

std::wstring Address::GetDeliveryPoint() 
{
	return deliveryPoint;
}

void Address::SetCity(char* value) 
{
	city = pugi::as_wide(value);
}

std::wstring Address::GetCity()
{
	return city;
}

void Address::SetAdministrativeArea(char* value) 
{
	administrativeArea = pugi::as_wide(value);
}

std::wstring Address::GetAdministrativeArea() 
{
	return administrativeArea;
}

void Address::SetPostalCode(char* value) 
{
	postalCode = pugi::as_wide(value);
}

std::wstring Address::GetPostalCode() 
{
	return postalCode;
}

void Address::SetCountry(char* value) 
{
	country = pugi::as_wide(value);
}

std::wstring Address::GetCountry() 
{
	return country;
}

void Address::SetElectronicMailAddress(char* value) 
{
	electronicMailAddress = pugi::as_wide(value);
}

std::wstring Address::GetElectronicMailAddress()
{
	return electronicMailAddress;
}