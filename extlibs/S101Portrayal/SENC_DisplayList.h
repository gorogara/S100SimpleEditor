#pragma once

#include <list>

class SENC_Instruction;
class SENC_DisplayList
{
public: 
	SENC_DisplayList();
	virtual ~SENC_DisplayList();

public: 
	std::list<SENC_Instruction*> displayInstructions;
public:  
	void GetDrawingInstruction(int priority, int type, int currentScale, std::list<SENC_Instruction*> &itList); 
	void RemoveInstruction(std::list<SENC_Instruction*>::iterator itor);

	void GetDrawingInstructionByCondition(int priority, int type, int currentScale, std::list<SENC_Instruction*> &itList, unsigned FeatureID_textPlacement);

	void ChangePallete(PortrayalCatalogue *pc);
};

