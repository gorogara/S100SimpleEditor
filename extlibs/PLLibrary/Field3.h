#pragma once

class SYParameters;
class TEParameters;
class TXParameters;
class LSParameters;
class LCParameters;
class ACParameters;
class APParameters;
class CSParameters;

class Field3
{
public:
	Field3();
	virtual~Field3();

public:
	SYParameters *SY;
	TEParameters *TE;
	TXParameters *TX;
	LSParameters *LS;
	LCParameters *LC;
	ACParameters *AC;
	APParameters *AP;
	CSParameters *CS; 
public:
	int SYtCnt, TEtCnt, TXtCnt, LStCnt, LCtCnt, ACtCnt, APtCnt, CStCnt;
};
