#pragma once

#include <string>
class Result_DrawingInstruction
{
public:
	Result_DrawingInstruction() {};
	virtual ~Result_DrawingInstruction() {};
public:
	std::string featureID;
	std::string drawingInstructions;
	std::string observedParameters;
};