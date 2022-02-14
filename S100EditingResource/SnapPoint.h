#pragma once

class EdtVector;

class SnapPoint
{
public:
	SnapPoint();
	virtual ~SnapPoint();

public:
	EdtVector* ev;
	int x;
	int y;
};