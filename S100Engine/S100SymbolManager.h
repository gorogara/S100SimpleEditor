#pragma once

#include "SVGReader.h"
#include <map>

class S100SymbolManager
{
public:
	S100SymbolManager();
	virtual ~S100SymbolManager();

public: 
	std::map<std::wstring, SVGReader> svgSymbols;

public: 
	bool Open(std::wstring _path);
	void CreateSVGGeometry(ID2D1Factory1* m_pDirect2dFactory);
	SVGReader* GetSVG(std::wstring _name);

private:
	char* ConvertCStringToChar(CString path);
};