#pragma once
#include <string>
#include <list>

class FFPT
{
public: 
	unsigned AGEN; 
	unsigned FIDN; 
	unsigned FIDS; 

	unsigned RIND; 
	std::wstring COMT; 

public:
	unsigned GetFieldLength(); 
	bool Save(CFile *file);
};
typedef std::list<FFPT*> LISTFFPT;