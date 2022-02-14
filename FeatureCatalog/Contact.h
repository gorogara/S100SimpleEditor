#pragma once
#include "XML_Item.h"
#include "Telephone.h"
#include "Address.h"
#include "OnlineResource.h"

#include <pugixml.hpp>

class Contact :
	public XML_Item
{
public:
	Contact(void);
	virtual ~Contact(void);
	
private:
	Telephone phone;
	Address address;
	OnlineResource onlineResource;
	std::wstring hoursOfService;
	std::wstring contactInstructions;
	
public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

	void SetPhone(Telephone& value);
	Telephone& Getphone();

	void SetAddress(Address& value);
	Address& GetAddress();

	void SetOnlineResource(OnlineResource& value);
	OnlineResource& GetOnlineResource();

	void SetHoursOfSerivce(char* value);
	std::wstring GetHoursOfService();

	void SetContactInstructions(char* value);
	std::wstring GetContactInstructions();
};