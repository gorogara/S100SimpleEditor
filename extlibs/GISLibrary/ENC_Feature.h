#pragma once
#include "ENC_ConditionalSymbol.h"
#include "FRID.h"
#include "FOID.h"

#include <Windows.h>
#include <list>
#include <unordered_map>

using namespace std;
class ENCCell;
class DRDirectoryInfo;
class ENCGeometry;
class Scaler;
class ENC_Vector;

class ATTF;
class NATF;
class FFPT;
class FFPC;
class FSPT;
class FSPC;

class CSParameters;

class ENC_Feature
{
public:
	ENC_Feature();
	virtual ~ENC_Feature();

public:
	FRID m_frid;
	FOID m_foid;
	list<ATTF*> m_attfList;
	list<NATF*> m_natfList;
	list<FFPT*> m_ffptList;
	FFPC *m_ffpc;
	list<FSPT*> m_fsptList;
	FSPC *m_fspc;

	list<ENC_Vector*> m_vectorList;

	ENCGeometry* m_geometry;

	int m_scaleMin;
	int m_scaleMax;
	int m_bShownAllScale;

	int m_displayPriority;
	int m_viewingGroup; 
	int m_displayCategory;
	int m_radarOver;
	bool m_hasText; 

	ENC_ConditionalSymbol *m_cs;

public:

	void CreateCS(ENCCell *cell, CSParameters *cs, bool bSENC = false);
	void DrawGeometry(HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawSoundingInfo(HDC &hDC, Scaler *scaler, double offset = 0);

	bool ReadRecord(DRDirectoryInfo *dir, BYTE*& buf, char ATTF_LEXICAL, char NATF_LEXICAL);
	bool SaveRecord(CFile *file, unsigned char DRIndex, char ATTF_LEXICAL, char NATF_LEXICAL);
	bool RemoveAllFields();
	bool UpdateFields(ENC_Feature* fe, unsigned ffptLexical, unsigned fsptLexical); 
	void Serialize(CArchive &ar);
};

typedef list<ENC_Feature*> FeatureList;
typedef unordered_map<__int64, ENC_Feature*> FeatureHash;
typedef pair <__int64, ENC_Feature*> Feature_Pair;

