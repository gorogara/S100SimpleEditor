#pragma once

class VRID
{
public:
	unsigned RCNM;  
	unsigned RCID; 
	unsigned RVER;// <M, b12, ?>	Record version
	unsigned RUIN; 

public: 
	unsigned GetFieldLength(); 
	bool Save(CFile *file);
};