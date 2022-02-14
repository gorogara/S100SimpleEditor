#pragma once
class RecordName
{
public:
	RecordName();
	virtual ~RecordName();

public: 
	unsigned RCNM; 
	unsigned RCID;

public:
	__int64 GetName();
	unsigned GetLength();
};