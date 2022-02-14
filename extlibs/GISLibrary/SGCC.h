#pragma once

class SGCC
{
public:
	SGCC::SGCC()
	{
		CCUI = 0;
		CCIX = 0;
		CCNC = 0;
	}

public:
	unsigned CCUI;  
	unsigned CCIX; 
	unsigned CCNC; 

public:
	unsigned GetFieldLength(); 
	bool Save(CFile *file);
};
