#pragma once

class NATF
{

public:
	unsigned ATTL;
	wstring ATVL;

public:
	unsigned GetFieldLength(char lexicalLevel); 
	bool Save(CFile *file, char lexicalLevel);
};
typedef std::list<NATF*> LISTNATF;