#pragma once
#include <string>

class CATD
{
public:
	std::wstring RCNM; 
	std::wstring RCID; 

	unsigned iRCID; 

	std::wstring FILE;  
	std::wstring LFIL;  
	std::wstring VOLM;    
	std::wstring IMPL;     
	std::wstring SLAT;
	double dSLAT;   
	std::wstring WLON;
	double dWLON;    
	std::wstring NLAT;
	double dNLAT;   
	std::wstring ELON;
	double dELON;    
	std::wstring CRCS;  
	std::wstring COMT;  
public:
	unsigned GetFieldLength();
	bool Save(CFile *file);
};