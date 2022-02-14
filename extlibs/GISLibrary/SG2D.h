#pragma once
#include <list>

class SG2D
{
public:
	int	YCOO; 
	int XCOO; 

public:
	unsigned GetFieldLength(); 
	bool Save(CFile *file);
};

typedef std::list<SG2D*> LISTSG2D;