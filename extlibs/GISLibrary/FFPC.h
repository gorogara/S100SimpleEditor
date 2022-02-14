#pragma once

class FFPC
{
public:
	unsigned FFUI;  
	unsigned FFIX; 
	unsigned NOPT; 

	FFPC::FFPC()
	{
		FFUI = 0;
		FFIX = 0;
		NOPT = 0;
	}

public:
	unsigned GetFieldLength(); 
	bool Save(CFile *file);
};
