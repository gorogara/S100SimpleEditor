#pragma once


#include "PLCommon.h" 
class Symbol;

class CSymbolManager
{
public:
	CSymbolManager();
	virtual ~CSymbolManager();

public:
	SymbolColor *m_Color; 
	Symbol		*m_Symbol; 
	Symbol      *m_Pattern; 
	Symbol      *m_Composite; 
	Symbol      *m_CompositeSymbol; 

	int  m_nColor; 
	int  m_nSymbol; 
	int  m_nPattern; 
	int  m_nComposite; 
	int  m_nCompositeSymbol; 

	bool isOpenColor; 
	bool isOpenSymbol; 
	bool isOpenPattern; 
	bool isOpenComposite; 
	bool isOpenCompositeSymbol; 

public:
	bool OpenColor(CString _PahtName); 
	bool ReOpenColor(CString _PathName); 
	bool OpenSymbol(CString _PathName); 
	bool OpenPattern(CString _PathName); 
	bool OpenComposite(CString _PathName); 
	bool OpenCompositeSymbol(CString _PathName);

	Symbol* GetSymbol(CString name); 
	Symbol* GetSymbol(int index);
	Symbol* GetPattern(CString name);
	Symbol* GetPattern(int index);
	Symbol* GetComposite(CString name);
	Symbol* GetComposite(int index);
	Symbol* GetCompositeSymbol(CString name);
	Symbol* GetCompositeSymbol(int index);

	Symbol* GetPTRCompositeSymbol(CString name);
	Symbol* GetPTRCompositeSymbol(int index);

	int GetSymbolCount();
	int GetColorCount();
	int GetPatternCount();
	int GetCompositeCount();
	int GetCompositeSymbolCount();

	void DrawSymbol(CString name, CDC* pDC, POINT point, double rotation = 0.0);
	void DrawSymbol(int index, CDC* pDC, POINT point, double rotation = 0.0);

	void DrawPattern(CString name, CDC* pDC, POINT point);
	void DrawPattern(int index, CDC* pDC, POINT point);

	void DrawComposite(CString name, CDC* pDC, POINT point);
	void DrawComposite(int index, CDC* pDC, POINT point);

	void DrawCompositeSymbol(CString name, CDC* pDC, POINT point);
	void DrawCompositeSymbol(int index, CDC* pDC, POINT point);

	void UpdateColor(); 

};