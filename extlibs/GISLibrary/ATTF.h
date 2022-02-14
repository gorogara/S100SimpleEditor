#pragma once
#include <list>
#include <string>
class ATTF
{
public:
	unsigned ATTL;
	std::wstring ATVL; 

public:
	unsigned GetFieldLength(char lexicalLevel);
	bool Save(CFile *file, char lexicalLevel);
};

typedef std::list<ATTF*> LISTATTF;