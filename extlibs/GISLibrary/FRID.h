#pragma once

class FRID
{
public:
	unsigned RCNM; 
	unsigned RCID; 
	unsigned PRIM; 
	unsigned GRUP; 
	unsigned OBJL; 
	unsigned RVER; 
	unsigned RUIN; 

public:
	unsigned GetFieldLength(); 
	bool Save(CFile *file);
};