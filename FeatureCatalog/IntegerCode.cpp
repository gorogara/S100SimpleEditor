
#include "stdafx.h"
#include "IntegerCode.h"


IntegerCode::IntegerCode()
{
}


IntegerCode::~IntegerCode()
{
}



void IntegerCode::GetContents(MSXML2::IXMLDOMNodePtr pNode)
{
	SetValueInteger(_wtoi(pNode->Gettext())); 
}
void IntegerCode::GetContents(pugi::xml_node& node)
{
	SetValueInteger(std::stoi(node.child_value())); 
}