#pragma once
class ObjectName
{
public:
	ObjectName();
	virtual ~ObjectName();

public:
	__int64 m_objName;
	unsigned m_agen;
	unsigned m_fidn;
	unsigned m_fids;

public:
	__int64 GetName();
	unsigned GetLength();
};