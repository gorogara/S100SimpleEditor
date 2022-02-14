#pragma once
#include "PortrayalCatalogue.h"
#include "S100_DisplayList.h"
#include "SENC_DisplayList.h"
#include "S100_NullInstruction.h"
#include "S100_PointInstruction.h"
#include "S100_LineInstruction.h"
#include "S100_AreaInstruction.h"
#include "S100_TextInstruction.h"
#include "S100_AugmentedPath.h"
#include "S100_AugmentedRay.h"
#include "SENC_NullInstruction.h"
#include "SENC_PointInstruction.h"
#include "SENC_LineInstruction.h"
#include "SENC_AreaInstruction.h"
#include "SENC_TextInstruction.h"
#include "SENC_AugmentedRay.h"
#include "SENC_AugmentedPath.h"

#include <string>

class S101Cell;
class S111Cell;
class BAG;

class PCOutputSchemaManager
{
public: 
	PCOutputSchemaManager();
	virtual ~PCOutputSchemaManager();
	
public: 
	S100_DisplayList *displayList; 
	SENC_DisplayList *displayListSENC;

	PortrayalCatalogue *m_portrayalCatalog;

public: 
	bool ReadPCOutputXML(std::wstring path, S101Cell* cell);
	bool ReadPCOutputXMLByPugiXML(std::wstring path, S101Cell* cell);
	bool ReadPCOutputXML(std::wstring path, S111Cell* cell);
	bool ReadPCOutputXML(std::wstring path, BAG* cell);

	void GenerateSENCInstruction(S101Cell* cell);
	void GenerateSENCInstruction(S111Cell* cell);
	void GenerateSENCInstruction(BAG* cell);

	SENC_NullInstruction* GetSENCFromS100(S100_NullInstruction*);
	SENC_PointInstruction* GetSENCFromS100(S100_PointInstruction*);
	SENC_LineInstruction* GetSENCFromS100(S100_LineInstruction*);
	SENC_AreaInstruction* GetSENCFromS100(S100_AreaInstruction*);
	SENC_TextInstruction* GetSENCFromS100(S100_TextInstruction*);
	SENC_AugmentedRay* GetSENCFromS100(S100_AugmentedRay*);
	SENC_AugmentedPath* GetSENCFromS100(S100_AugmentedPath*);

	void GetSENCFromS100Common(S100_Instruction* tp, SENC_Instruction* si);

	void ChangePallete(PortrayalCatalogue *pc);
};