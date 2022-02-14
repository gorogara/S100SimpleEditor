#pragma once

#include "GML_DatasetMetaDataProperty.h"
#include "GML_Feature.h"
#include "GML_Vector.h"
#include "GML_SpatialObject.h"

#import <msxml4.dll>

class Catalog;
class GML_DataSetAttribute;
class S_240_DGNSS : public GML_SpatialObject
{
public:
	S_240_DGNSS();
	virtual ~S_240_DGNSS();
	bool Open(CString _filepath);
	void GetENCObject(MSXML2::IXMLDOMNodePtr listPtr);
};

