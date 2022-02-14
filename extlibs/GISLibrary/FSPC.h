#pragma once

class FSPC
{
public:
	FSPC::FSPC()
	{
		FSUI = 0;
		FSIX = 0;
		NSPT = 0;
	}

public:
	unsigned FSUI;  
	unsigned FSIX; 
	unsigned NSPT; 

	

public:
	unsigned GetFieldLength(); 
	bool Save(CFile *file);
};