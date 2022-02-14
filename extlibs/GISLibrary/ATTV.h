#pragma once
#include <string>
#include <list>

class ATTV
{
public:
	unsigned ATTL;
	std::wstring ATVL;

public: 
	unsigned GetFieldLength();
	bool Save(CFile *file);
};
typedef std::list<ATTV*> LISTATTV;