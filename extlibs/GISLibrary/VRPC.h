#pragma once
class VRPC
{
public:
	VRPC::VRPC()
	{
		VPUI = 0;
		VPIX = 0;
		NVPT = 0;
	}
public:
	unsigned VPUI;  
	unsigned VPIX; 
	unsigned NVPT; 
	

public:
	unsigned GetFieldLength(); 
	bool  Save(CFile *file);
};
