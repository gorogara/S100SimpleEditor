#include "stdafx.h"
#include "Contact.h"

#include "..\\DLL_MessageProcess\DLL_MessageProcess.h"
Contact::Contact(void)
{

}
Contact::~Contact(void)
{

}

void Contact::GetContents(MSXML2::IXMLDOMNodePtr pNode)
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

		if (baseName.compare("phone") == 0)
		{
			phone.GetContents(pChildNode);
		}
		else if (baseName.compare("address") == 0)
		{
			address.GetContents(pChildNode);
		}
		else if (baseName.compare("onlineResource") == 0)
		{
			onlineResource.GetContents(pChildNode);
		}
		else if (baseName.compare("hoursOfService") == 0)
		{
			hoursOfService = pChildNode->Gettext();
		}
		else if (baseName.compare("contactInstructions") == 0)
		{
			contactInstructions = pChildNode->Gettext();
		}
	}
}
void Contact::GetContents(pugi::xml_node& node)
{
	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		const pugi::char_t* instructionName = instruction.name();

		if (!strcmp(instructionName, "S100CI:phone"))
		{
			Telephone* phoneData = new Telephone();
			phoneData->GetContents(instruction);
			SetPhone(*phoneData);  
		}
		else if (!strcmp(instructionName, "S100CI:address"))
		{
			
			Address* add = new Address();
			add->GetContents(instruction);
			SetAddress(*add);  
		}
		else if (!strcmp(instructionName, "S100CI:onlineResource"))
		{
			OnlineResource* online = new OnlineResource();
			online->GetContents(instruction);
			SetOnlineResource(*online);  
		}
		else if (!strcmp(instructionName, "S100CI:hoursOfService"))
		{
			SetHoursOfSerivce((char*)instruction.child_value());  
		}
		else if (!strcmp(instructionName, "S100CI:contactInstructions"))
		{
			SetContactInstructions((char*)instruction.child_value());  
		}
		else 
		{
			std::wstring content = pugi::as_wide(instructionName);
			content.append(L" is another data");
			KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, content.c_str(),KRS_MSG_PROCESS::Developer_Mode,KRS_MSG_PROCESS::FC);
		}
	}
}

void Contact::SetPhone(Telephone& value)
{
	phone = value;
}

Telephone& Contact::Getphone()
{
	return phone;
}

void Contact::SetAddress(Address& value)
{
	address = value;
}

Address& Contact::GetAddress() 
{
	return address;
}

void Contact::SetOnlineResource(OnlineResource& value)
{
	onlineResource = value;
}

OnlineResource& Contact::GetOnlineResource()
{
	return onlineResource;
}

void Contact::SetHoursOfSerivce(char* value) 
{
	hoursOfService = pugi::as_wide(value);
}

std::wstring Contact::GetHoursOfService() 
{
	return hoursOfService;
}

void Contact::SetContactInstructions(char* value) 
{
	contactInstructions = pugi::as_wide(value);
}

std::wstring Contact::GetContactInstructions()
{
	return contactInstructions;
}