#pragma once
#include "XML_Item.h"

#include <pugixml.hpp>
#include <string>

class Address :
	public XML_Item
{
public:
	Address();
	virtual ~Address();

private:
	std::wstring deliveryPoint; 
	std::wstring city; 
	std::wstring administrativeArea;
	std::wstring postalCode; 
	std::wstring country;
	std::wstring electronicMailAddress;

public:
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

	void SetDeliveryPoint(char* value);
	std::wstring GetDeliveryPoint();
	 
	void SetCity(char* value);
	std::wstring GetCity();

	void SetAdministrativeArea(char* value);
	std::wstring GetAdministrativeArea();

	void SetPostalCode(char* value);
	std::wstring GetPostalCode();

	void SetCountry(char* value);
	std::wstring GetCountry();

	void SetElectronicMailAddress(char* value);
	std::wstring GetElectronicMailAddress();
};