#pragma once

class PortrayalCatalogue; 
class SENC_LineStyleBase
{
public:
	SENC_LineStyleBase();
	virtual ~SENC_LineStyleBase();

public: 
	int type = 0; 

	std::vector<ID2D1PathGeometry*> geometryVector;

public:
	void SetType(int value);
	int GetType();

	virtual void ChangePallete(PortrayalCatalogue *pc) {};
};