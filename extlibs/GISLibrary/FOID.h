#pragma once

class FOID
{
public:
	unsigned AGEN; 
	unsigned FIDN; 
	unsigned FIDS; 

public:
	unsigned GetFieldLength(); 
	bool Save(CFile *file);
};