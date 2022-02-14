#include "stdafx.h"
#include "S100_IC_SuppressedFeatureInstance.h"


S100_IC_SuppressedFeatureInstance::S100_IC_SuppressedFeatureInstance()
{
}


S100_IC_SuppressedFeatureInstance::~S100_IC_SuppressedFeatureInstance()
{
}

void S100_IC_SuppressedFeatureInstance::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	((S100_IC_FeatureDerivation*)this)->GetContents(pNode);
}

void S100_IC_SuppressedFeatureInstance::GetContents(pugi::xml_node node)
{
	((S100_IC_FeatureDerivation*)this)->GetContents(node);
}