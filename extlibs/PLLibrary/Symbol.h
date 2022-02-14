#pragma once
#include "PLCommon.h"
#include <vector>

class Vector;
class CSymbolManager;
class Symbol
{
public:
	Symbol(void);
	~Symbol(void);

	void ReadSYMB(char *buf3); 
	void ReadSYMD(char *buf3); 
	void ReadSXPO(char *buf3); 
	void ReadSCRF(char *buf2, char *buf3);  

	void ReadSVCT(char *buf3); 

	void ReadPATD(char *buf3); 
	void ReadLIND(char *buf3); 

	void MakeVector();
	SymbolColorRef GetPen(char c);
	void Delete();
	void Draw(CDC *pDC);
	void Draw(CDC *pDC, POINT point);
	void Draw(CDC *pDC, POINT point, double rotation);

	void Draw(Graphics *pG); 
	void Draw(Graphics *pG, POINT point); 
	void Draw(Graphics *pG, POINT point, double rotation); 

	void SetColor(SymbolColor* color_list, int count); 
	void UpdateColor(SymbolColor *color_list, int count);

	void GetName(char *name);

	void ReadSC(char *buf3);

	CSymbolManager *m_pSymbolManager;

	char id[8]; 
	char name[9]; 
	char* exposition;
	SymbolColorRef *color;
	std::vector<Vector*> vector;
	int SYCL; 
	int SYRW; 
	int SYHL; 
	int SYVL; 
	int SBXC; 
	int SBXR; 

	int color_num; 
	int vector_num;

	int current_width;
	int current_transparent;
	SymbolColorRef current_pen;

	int PM1_num; 
	int CoverXmin;
	int CoverYmin;
	int CoverXmax;
	int CoverYmax; 
	enum TypeOfFillPattern {
		STG, 
		LIN
	}; 

	enum TypeOfFillPattern typeOfFillPattern; 
	enum Spacing {
		CON, 
		SCL
	}; 

	enum Spacing spacing;

	int PAMI; 
	int PAMA; 
};