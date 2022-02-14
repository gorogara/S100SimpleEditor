#pragma once
#include "GML_Association.h"
class GML_InformationAssociation : public GML_Association
{
public:
	GML_InformationAssociation();
	virtual ~GML_InformationAssociation();
public:
	bool m_bReverseAssociation;
};