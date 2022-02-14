#pragma once

#include "..\\GeoMetryLibrary\\ENCPoint.h"

#include <string>
class ShipInfo : public ENCPoint
{
public:
	ShipInfo();
	virtual ~ShipInfo();
public:
	bool m_bOwnShip;
	std::wstring m_name;
	std::wstring m_description;
};