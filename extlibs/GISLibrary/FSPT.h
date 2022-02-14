#pragma once
#include <list>

class FSPT
{
public: 
	unsigned RCNM;  
	unsigned RCID; 

	unsigned ORNT; 
	unsigned USAG;  
	unsigned MASK;  
public:
	unsigned GetFieldLength(); 
	bool Save(CFile *file);
};
typedef std::list<FSPT*> LISTFSPT;