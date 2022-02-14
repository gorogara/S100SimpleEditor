#pragma once

class DDR
{
public:
	int size = 0;
	BYTE* content = nullptr;

public:
	void Set(BYTE* buffer);
};