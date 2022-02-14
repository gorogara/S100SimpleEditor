#pragma once
#include "S100_Symbol.h"
#include "S100_VectorPoint.h"
#include "S100_PatternFill.h"

#include "..\\extlibs\pugixml\include\pugixml.hpp"

class S100_SymbolFill
	: public S100_PatternFill
{
public:
	S100_SymbolFill();
	virtual ~S100_SymbolFill();

public: 
	std::wstring clipSymbols; 
	S100_Symbol* symbol;
	S100_VectorPoint* v1;
	S100_VectorPoint* v2;

public:
	bool ReadFile(std::wstring path);
	bool ReadFileByPugiXml(std::wstring path);
	void GetContents(MSXML2::IXMLDOMNodePtr pNode);
	void GetContents(pugi::xml_node& node);

};

