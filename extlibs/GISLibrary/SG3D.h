#pragma once
#include "SG2D.h"

class SG3D : public SG2D
{
public:
	int VE3D; 

public:
	unsigned GetFieldLength();
	bool Save(CFile *file);
};
typedef std::list<SG3D*> LISTSG3D;