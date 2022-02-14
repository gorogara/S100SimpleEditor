#pragma once
#include <list>

class VRPT
{
public: 
	unsigned RCNM;  
	unsigned RCID; 

	unsigned ORNT; 
	unsigned USAG;  
	unsigned TOPI; 
	unsigned MASK; 

public:
	unsigned GetFieldLength();
	bool Save(CFile *file);
};

typedef std::list<VRPT*> LISTVRPT;