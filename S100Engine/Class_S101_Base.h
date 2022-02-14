#pragma once

using namespace std;
#include <map>
#include <vector>
#include <d2d1.h>

typedef std::vector <unsigned int>	VEC_B1;  
struct ST_DSID
{
	unsigned int				nRCNM; 
	unsigned int				nRCID; 
	CString					strENSP; 
	CString					strENED; 
	CString					strPRSP; 
	CString					strPRED; 
	CString					strPROF; 
	CString					strDSNM; 
	CString					strDSTL; 
	CString					strDSRD; 
	CString					strDSLG; 
	CString					strDSAB; 
	CString					strDSED; 
	VEC_B1					vecDSTC; 

	ST_DSID()
	{
		nRCNM = 0; 
		nRCID = 0; 
		strENSP.Empty(); 
		strENED.Empty(); 
		strPRSP.Empty(); 
		strPRED.Empty(); 
		strPROF.Empty(); 
		strDSNM.Empty(); 
		strDSTL.Empty(); 
		strDSRD.Empty(); 
		strDSLG.Empty(); 
		strDSAB.Empty(); 
		strDSED.Empty(); 
		vecDSTC.clear();
	}
};

struct ST_DSSI
{
	double					fDCOX; 
	double					fDCOY; 
	double					fDCOZ; 
	unsigned int				nCMFX; 
	unsigned int				nCMFY; 
	unsigned int				nCMFZ; 
	unsigned int				nNOIR; 
	unsigned int				nNOPN; 
	unsigned int				nNOMN; 
	unsigned int				nNOCN; 
	unsigned int				nNOXN; 
	unsigned int				nNOSN; 
	unsigned int				nNOFR; 

	ST_DSSI()
	{
		fDCOX = 0.0; 
		fDCOY = 0.0; 
		fDCOZ = 0.0; 
		nCMFX = 0; 
		nCMFY = 0; 
		nCMFZ = 0; 
		nNOIR = 0; 
		nNOPN = 0; 
		nNOMN = 0; 
		nNOCN = 0; 
		nNOXN = 0; 
		nNOSN = 0; 
		nNOFR = 0; 
	}
};

struct ST_SUBFIELD
{
	CString					strCode;			
	unsigned int				nNumeric;		

	ST_SUBFIELD()
	{
		strCode.Empty();
		nNumeric = 0;
	}
};
typedef std::vector <ST_SUBFIELD>		VEC_SUBFIELD;

struct ST_ATTR_NATC
{
	unsigned int					nNATC; 
	unsigned int					nATIX; 
	unsigned int					nPAIX; 
	unsigned int					nATIN; 
	CString							strATVL; 

	ST_ATTR_NATC()
	{
		nNATC = 0;
		nATIX = 0;
		nPAIX = 0;
		nATIN = 0;
		strATVL.Empty();
	}
};
typedef std::vector <ST_ATTR_NATC>		VEC_ATTR_NATC;

struct ST_ATTR
{
	VEC_ATTR_NATC			vecNATC;

	ST_ATTR()
	{
		vecNATC.clear();
	}
};
typedef std::vector <ST_ATTR>		VEC_ATTR;

struct ST_DSGI
{
	ST_DSID			stDSID;
	ST_DSSI			stDSSI;
	VEC_SUBFIELD	vecATCS;
	VEC_SUBFIELD	vecITCS;
	VEC_SUBFIELD	vecFTCS;
	VEC_SUBFIELD	vecIACS;
	VEC_SUBFIELD	vecFACS;
	VEC_SUBFIELD	vecARCS;
	VEC_ATTR		vecATTR;

	ST_DSGI()
	{
		vecATCS.clear();
		vecITCS.clear();
		vecFTCS.clear();
		vecIACS.clear();
		vecFACS.clear();
		vecARCS.clear();
		vecATTR.clear();
	}
};  
struct ST_CSID
{
	unsigned int					nRCNM; 
	unsigned int					nRCID; 
	unsigned int					nNCRC; 

	ST_CSID()
	{
		nRCNM = 0;
		nRCID = 0;
		nNCRC = 0;
	}
};

struct  ST_CRSH
{
	unsigned int					nCRIX; 
	unsigned int					nCRST; 
	unsigned int					nCSTY; 
	CString						strCRNM; 
	CString						strCRSI; 
	unsigned int					nCRSS; 
	CString						strSCRI; 

	ST_CRSH()
	{
		nCRIX = 0;
		nCRST = 0;
		nCSTY = 0;
		strCRNM.Empty();
		strCRSI.Empty();
		nCRSS = 0;
		strSCRI.Empty();
	}
};
typedef std::vector <ST_CRSH>		VEC_CRSH;

struct ST_CSAX
{
	unsigned int					nAXTY; 
	unsigned int					nAXUM; 

	ST_CSAX()
	{
		nAXTY = 0;
		nAXUM = 0;
	}
};
typedef std::vector <ST_CSAX>		VEC_CSAX;

struct ST_PROJ
{
	unsigned int					nPROM; 
	double						fPRP1; 
	double						fPRP2; 
	double						fPRP3; 
	double						fPRP4; 
	double						fPRP5; 
	double						fFEAS; 
	double						fFNOR; 

	ST_PROJ()
	{
		nPROM = 0;
		fPRP1 = 0.0;
		fPRP2 = 0.0;
		fPRP3 = 0.0;
		fPRP4 = 0.0;
		fPRP5 = 0.0;
		fFEAS = 0.0;
		fFNOR = 0.0;
	}
};

struct ST_GDAT
{
	CString						strDTNM;
	CString						strELNM;
	double						fESMA;
	unsigned int					nESPT;
	double						fESPM;
	CString						strCMNM;
	double						fCMGL;

	ST_GDAT()
	{
		strDTNM.Empty();
		strELNM.Empty();
		fESMA = 0.0;
		nESPT = 0;
		fESPM = 0.0;
		strCMNM.Empty();
		fCMGL = 0.0;
	}
};

struct ST_VDAT
{
	CString						strDTNM; 
	CString						strDTID; 
	unsigned int					nDTSR; 
	CString						strSCRI; 

	ST_VDAT()
	{
		strDTNM.Empty();
		strDTID.Empty();
		nDTSR = 0;
		strSCRI.Empty();
	}
};

struct ST_DCRS
{
	ST_CSID			stCSID;
	VEC_CRSH		vecCRSH;
	ST_CSAX			stCSAX;
	ST_PROJ			stPROJ;
	ST_GDAT			stGDAT;
	ST_VDAT			stVDAT;

	ST_DCRS()
	{
		vecCRSH.clear();
	}
};  
struct ST_IRID
{
	unsigned int					nRCNM; 
	unsigned int					nRCID; 
	unsigned int					nNITC; 
	unsigned int					nRVER; 
	unsigned int					nRUIN; 

	ST_IRID()
	{
		nRCNM = 0;
		nRCID = 0;
		nNITC = 0;
		nRVER = 0;
		nRUIN = 0;
	}
};

struct ST_INAS_NATC
{
	unsigned int					nNATC; 
	unsigned int					nATIX; 
	unsigned int					nPAIX; 
	unsigned int					nATIN; 
	CString						strATVL; 

	ST_INAS_NATC()
	{
		nNATC = 0;
		nATIX = 0;
		nPAIX = 0;
		nATIN = 0;
		strATVL.Empty();
	}
};
typedef std::vector <ST_INAS_NATC>		VEC_INAS_NATC;

struct ST_INAS
{
	unsigned int					nRRNM; 
	unsigned int					nRRID; 
	unsigned int					nNIAC; 
	unsigned int					nNARC; 
	unsigned int					nIUIN; 
	VEC_INAS_NATC				vecNATC;

	ST_INAS()
	{
		nRRNM = 0;
		nRRID = 0;
		nNIAC = 0;
		nNARC = 0;
		nIUIN = 0;
		vecNATC.clear();
	}
};
typedef std::vector <ST_INAS>		VEC_INAS;

struct ST_INFO_RECORD
{
	ST_IRID			stIRID;
	VEC_ATTR		vecATTR;
	VEC_INAS			vecINAS;
	
	ST_INFO_RECORD()
	{
		vecATTR.clear();
		vecINAS.clear();
	}
};
typedef std::vector <ST_INFO_RECORD>		VEC_INFO_RECORD;  
struct ST_ID
{
	unsigned int					nRCNM; 
	unsigned int					nRCID; 
	unsigned int					nRVER; 
	unsigned int					nRUIN; 

	ST_ID()
	{
		nRCNM = 0;
		nRCID = 0;
		nRVER = 0;
		nRUIN = 0;
	}
};

struct ST_C2IT
{
	int							nYCOO;
	int							nXCOO;

	ST_C2IT()
	{
		nYCOO = 0;
		nXCOO = 0;
	}
};
typedef std::vector <ST_C2IT>		VEC_C2IT;

struct ST_C3IT
{
	int							nVCID;
	int							nYCOO;
	int							nXCOO;
	int							nZCOO;

	ST_C3IT()
	{
		nVCID = 0;
		nYCOO = 0;
		nXCOO = 0;
		nZCOO = 0;
	}
};
typedef std::vector <ST_C3IT>		VEC_C3IT;

struct ST_C2FT
{
	double					fYCOO;
	double					fXCOO;

	ST_C2FT()
	{
		fYCOO = 0.0;
		fXCOO = 0.0;
	}
};
typedef std::vector <ST_C2FT>		VEC_C2FT;

struct ST_C3FT
{
	int							nVCID;
	double					fYCOO;
	double					fXCOO;
	double					fZCOO;

	ST_C3FT()
	{
		nVCID = 0;
		fYCOO = 0.0;
		fXCOO = 0.0;
		fZCOO = 0.0;
	}
};
typedef std::vector <ST_C3IT>		VEC_C3IT;

struct ST_POINT_RECORD
{
	ST_ID						stPRID;
	ST_C2IT					stC2IT;
	ST_C3IT					stC3IT;
	ST_C2FT					stC2FT;
	ST_C3FT					stC3FT;
	VEC_INAS					vecINAS;

	ST_POINT_RECORD()
	{
		vecINAS.clear();
	}
};
typedef std::vector <ST_POINT_RECORD>		VEC_POINT_RECORD;  
struct ST_C2IL
{
	int							nYCOO; 
	int							nXCOO; 

	ST_C2IL()
	{
		nYCOO = 0;
		nXCOO = 0;
	}
};
typedef std::vector <ST_C2IL>		VEC_C2IL;

struct ST_C3IL_XYZ
{
	int							nYCOO;
	int							nXCOO;
	int							nZCOO;

	ST_C3IL_XYZ()
	{
		nYCOO = 0;
		nXCOO = 0;
		nZCOO = 0;
	}
};
typedef std::vector <ST_C3IL_XYZ>		VEC_C3IL_XYZ;

struct ST_C3IL
{
	int							nVCID;
	VEC_C3IL_XYZ			vecXYZ;

	ST_C3IL()
	{
		nVCID = 0;
		vecXYZ.clear();
	}
};
typedef std::vector <ST_C3IL>		VEC_C3IL;

struct ST_C2FL
{
	double					fYCOO;
	double					fXCOO;

	ST_C2FL()
	{
		fYCOO = 0.0;
		fXCOO = 0.0;
	}
};
typedef std::vector <ST_C2FL>		VEC_C2FL;

struct ST_C3FL_XYZ
{
	double					fYCOO;
	double					fXCOO;
	double					fZCOO;

	ST_C3FL_XYZ()
	{
		fYCOO = 0.0;
		fXCOO = 0.0;
		fZCOO = 0.0;
	}
};
typedef std::vector <ST_C3FL_XYZ>		VEC_C3FL_XYZ;

struct ST_C3FL
{
	int							nVCID;
	VEC_C3FL_XYZ			vecXYZ;

	ST_C3FL()
	{
		nVCID = 0;
		vecXYZ.clear();
	}
};
typedef std::vector <ST_C3FL>		VEC_C3FL;

struct ST_COCC
{
	unsigned int				nCOUI;
	unsigned int				nCOIX;
	unsigned int				nNCOR;

	ST_COCC()
	{
		nCOUI = 0;
		nCOIX = 0;
		nNCOR = 0;
	}
};

struct ST_MULTI_POINT_RECORD
{
	ST_ID						stMRID;
	ST_COCC					stCOCC;
	VEC_C2IL					vecC2IL;
	VEC_C3IL					vecC3IL;
	VEC_C2FL					vecC2FL;
	VEC_C3FL					vecC3FL;
	VEC_INAS					vecINAS;

	ST_MULTI_POINT_RECORD()
	{
		vecC2IL.clear();
		vecC3IL.clear();
		vecC2FL.clear();
		vecC3FL.clear();
		vecINAS.clear();
	}
};
typedef std::vector <ST_MULTI_POINT_RECORD>		VEC_MULTI_POINT_RECORD;  
struct ST_PTAS 
{
	unsigned int				nRRNM; 
	unsigned int				nRRID; 
	unsigned int				nTOPI; 

	ST_PTAS()
	{
		nRRNM = 0;
		nRRID = 0;
		nTOPI = 0;
	}
};
typedef std::vector <ST_PTAS>		VEC_PTAS;

struct ST_SECC
{
	unsigned int				nSEUI; 
	unsigned int				nSEIX; 
	unsigned int				nNSEG; 

	ST_SECC()
	{
		nSEUI = 0;
		nSEIX = 0;
		nNSEG = 0;
	}
};

struct ST_SEGH
{
	unsigned int				nINTP;  

	ST_SEGH()
	{
		nINTP = 0;
	}
};
typedef std::vector<ST_SEGH>			VEC_SEGH; 
struct ST_CURVE_RECORD
{
	ST_ID						stCRID; 
	VEC_PTAS					vecPTAS; 
	ST_SECC					stSECC;
	VEC_SEGH				vecSEGH; 
	ST_COCC					stCOCC;
	VEC_C2IL					vecC2IL; 
	VEC_C3IL					vecC3IL;
	VEC_C2FL					vecC2FL;
	VEC_C3FL					vecC3FL;
	VEC_INAS					vecINAS;

	ST_CURVE_RECORD()
	{
		vecPTAS.clear();
		vecSEGH.clear();
		vecC2IL.clear();
		vecC3IL.clear();
		vecC2FL.clear();
		vecC3FL.clear();
		vecINAS.clear();
	}
};
typedef std::vector<ST_CURVE_RECORD>			VEC_CURVE_RECORD;  
struct ST_CCOC
{
	unsigned int				nCCUI; 
	unsigned int				nCCIX; 
	unsigned int				nNCCO; 

	ST_CCOC()
	{
		nCCUI = 0;
		nCCIX = 0;
		nNCCO = 0;
	}
};

struct ST_CUCO_RRNM
{
	unsigned int				nRRNM; 
	unsigned int				nRRID; 
	unsigned int				nORNT; 

	ST_CUCO_RRNM()
	{
		nRRNM = 0;
		nRRID = 0;
		nORNT = 1;
	}
};
typedef std::vector<ST_CUCO_RRNM>			VEC_CUCO_RRNM;

struct ST_CUCO
{
	VEC_CUCO_RRNM		vecRRNM;

	ST_CUCO()
	{
		vecRRNM.clear();
	}
};
typedef std::vector<ST_CUCO>					VEC_CUCO;

struct ST_COMP_CURVE_RECORD
{
	ST_ID						stCCID;
	ST_CCOC					stCCOC;
	VEC_CUCO				vecCUCO;
	VEC_INAS					vecINAS;

	ST_COMP_CURVE_RECORD()
	{
		vecCUCO.clear();
		vecINAS.clear();
	}
};
typedef std::vector<ST_COMP_CURVE_RECORD>		VEC_COMP_CURVE_RECORD;  
struct ST_RIAS_RRNM
{
	unsigned int				nRRNM; 
	unsigned int				nRRID; 
	unsigned int				nORNT; 
	unsigned int				nUSAG; 
	unsigned int				nRAUI; 

	ST_RIAS_RRNM()
	{
		nRRNM = 0;
		nRRID = 0;
		nORNT = 1;
		nUSAG = 1;
		nRAUI = 1;
	}
};
typedef std::vector<ST_RIAS_RRNM>		VEC_RIAS_RRNM;

struct ST_RIAS
{
	VEC_RIAS_RRNM			vecRRNM;

	ST_RIAS()
	{
		vecRRNM.clear();
	}
};
typedef std::vector<ST_RIAS>		VEC_RIAS;

struct ST_SURFACE_RECORD
{
	ST_ID					stSRID;
	VEC_RIAS				vecRIAS;
	VEC_INAS				vecINAS;

	ST_SURFACE_RECORD()
	{
		vecRIAS.clear();
		vecINAS.clear();
	}
};
typedef std::vector<ST_SURFACE_RECORD>		VEC_SURFACE_RECORD;  
struct ST_FRID
{
	unsigned int				nRCNM; 
	unsigned int				nRCID; 
	unsigned int				nNFTC; 
	unsigned int				nRVER; 
	unsigned int				nRUIN; 

	ST_FRID()
	{
		nRCNM = 0;
		nRCID = 0;
		nNFTC = 0;
		nRVER = 0;
		nRUIN = 0;
	}
};

struct ST_FOID
{
	unsigned int				nAGEN; 
	unsigned int				nFIDN; 
	unsigned int				nFIDS; 

	ST_FOID()
	{
		nAGEN = 0;
		nFIDN = 0;
		nFIDS = 0;
	}
};

struct ST_SPAS_RRNM
{
	unsigned int				nRRNM;
	unsigned int				nRRID;
	unsigned int				nORNT;
	unsigned int				nSMIN; 
	unsigned int				nSMAX; 
	unsigned int				nSAUI; 

	ST_SPAS_RRNM()
	{
		nRRNM = 0;
		nRRID = 0;
		nORNT = 0;
		nSMIN = 0;
		nSMAX = 0;
		nSAUI = 0;
	}
};
typedef std::vector<ST_SPAS_RRNM>		VEC_SPAS_RRNM;

struct ST_SPAS
{
	VEC_SPAS_RRNM		vecRRNM;
	ST_SPAS()
	{
		vecRRNM.clear();
	}
};
typedef std::vector<ST_SPAS>		VEC_SPAS;

struct ST_FASC_NATC
{
	unsigned int				nNATC;
	unsigned int				nATIX;
	unsigned int				nPAIX;
	unsigned int				nATIN;
	CString					strATVL;

	ST_FASC_NATC()
	{
		nNATC = 0;
		nATIX = 0;
		nPAIX = 0;
		nATIN = 0;
		strATVL.Empty();
	}
};
typedef std::vector<ST_FASC_NATC>		VEC_FASC_NATC;

struct ST_FASC
{
	unsigned int				nRRNM;
	unsigned int				nRRID;
	unsigned int				nNFAC; 
	unsigned int				nNARC; 
	unsigned int				nFAUI; 
	VEC_FASC_NATC			vecNATC;

	ST_FASC()
	{
		nRRNM = 0;
		nRRID = 0;
		nNFAC = 0;
		nNARC = 0;
		nFAUI = 0;
		vecNATC.clear();
	}
};
typedef std::vector<ST_FASC>		VEC_FASC;

struct ST_THAS_RRNM
{
	unsigned int				nRRNM;
	unsigned int				nRRID;
	unsigned int				nTAUI; 

	ST_THAS_RRNM()
	{
		nRRNM = 0;
		nRRID = 0;
		nTAUI = 0;
	}
};
typedef std::vector<ST_THAS_RRNM>		VEC_THAS_RRNM;

struct ST_THAS
{
	VEC_THAS_RRNM		vecRRNM;

	ST_THAS()
	{
		vecRRNM.clear();
	}
};
typedef std::vector<ST_THAS>		VEC_THAS;

struct ST_MASK_RRNM
{
	unsigned int				nRRNM;
	unsigned int				nRRID;
	unsigned int				nMIND; 
	unsigned int				nMUIN; 

	ST_MASK_RRNM()
	{
		nRRNM = 0;
		nRRID = 0;
		nMIND = 0;
		nMUIN = 0;
	}
};
typedef std::vector<ST_MASK_RRNM>		VEC_MASK_RRNM;

struct ST_MASK
{
	VEC_MASK_RRNM		vecRRNM;

	ST_MASK()
	{
		vecRRNM.clear();
	}
};
typedef std::vector<ST_MASK>		VEC_MASK;

struct ST_FEATURE_RECORD
{
	ST_FRID				stFRID;
	ST_FOID				stFOID;
	VEC_ATTR			vecATTR;
	VEC_INAS				vecINAS;
	VEC_SPAS				vecSPAS;
	VEC_FASC				vecFASC;
	VEC_THAS			vecTHAS;
	VEC_MASK			vecMASK;

	ST_FEATURE_RECORD()
	{
		vecATTR.clear();
		vecINAS.clear();
		vecSPAS.clear();
		vecFASC.clear();
		vecTHAS.clear();
		vecMASK.clear();
	}
};
typedef std::vector<ST_FEATURE_RECORD>		VEC_FEATURE_RECORD;

class CClass_S101_Base
{
public:
	CClass_S101_Base();
	virtual ~CClass_S101_Base(); 
public:
	ST_DSGI						m_stDSGI; 
	ST_DCRS						m_stDCRS; 
	VEC_INFO_RECORD				m_vecInfoRecord; 
	VEC_POINT_RECORD			m_vecPointRecord; 
	VEC_MULTI_POINT_RECORD	    m_vecMultiPointRecord; 
	VEC_CURVE_RECORD			m_vecCurveRecord; 
	VEC_COMP_CURVE_RECORD	    m_vecCompCurveRecord; 
	VEC_SURFACE_RECORD			m_vecSurfaceRecord; 
	VEC_FEATURE_RECORD			m_vecFeatureRecord; 

	std::map<int, ST_FEATURE_RECORD*> m_mapFeatureRecord;
	std::map<int, ST_INFO_RECORD*> m_mapInformationRecord;
	std::map<int, ST_POINT_RECORD*> m_mapPointRecord;
	std::map<int, ST_MULTI_POINT_RECORD*> m_mapMultiPointRecord;
	std::map<int, ST_CURVE_RECORD*> m_mapCurveRecord;
	std::map<int, ST_COMP_CURVE_RECORD*> m_mapCompositeCurveRecord;
	std::map<int, ST_SURFACE_RECORD*> m_mapSurfaceRecord;

	std::map<int, CString> m_mapFeatureName;
	std::map<int, CString> m_mapInformationName;
	std::map<int, CString> m_mapAttributeName;       
public: 
	bool				LoadBaseCell(CString strFilePath); 
	bool				ParsingBaseCell(const BYTE *pData); 
	bool				Parsing_8211(const BYTE *pData, int &nRecordLength); 
	bool				Parsing_DSGI(const BYTE *pData, int &nRecordLength); 
	bool				Parsing_DSID(const BYTE *pData, int nFieldLength); 
	bool				Parsing_DSSI(const BYTE *pData, int nFieldLength); 
	bool				Parsing_ATCS(const BYTE *pData, int nFieldLength); 
	bool				Parsing_ITCS(const BYTE *pData, int nFieldLength); 
	bool				Parsing_FTCS(const BYTE *pData, int nFieldLength); 
	bool				Parsing_IACS(const BYTE *pData, int nFieldLength); 
	bool				Parsing_FACS(const BYTE *pData, int nFieldLength); 
	bool				Parsing_ARCS(const BYTE *pData, int nFieldLength); 
	bool				Parsing_ATTR(const BYTE *pData, VEC_ATTR_NATC &vecNATC, int nFieldLength); 
	bool				Parsing_DCRS(const BYTE *pData, int &nRecordLength); 
	bool				Parsing_CSID(const BYTE *pData, int nFieldLength); 
	bool				Parsing_CRSH(const BYTE *pData, int nFieldLength); 
	bool				Parsing_CSAX(const BYTE *pData, int nFieldLength); 
	bool				Parsing_PROJ(const BYTE *pData, int nFieldLength); 
	bool				Parsing_GDAT(const BYTE *pData, int nFieldLength); 
	bool				Parsing_VDAT(const BYTE *pData, int nFieldLength); 
	bool				Parsing_InfoRecord(const BYTE *pData, ST_INFO_RECORD &stInfoRecord, int &nRecordLength); 
	bool				Parsing_IRID(const BYTE *pData, ST_INFO_RECORD &stInfoRecord, int nFieldLength); 
	bool				Parsing_INAS(const BYTE *pData, VEC_INAS &vecINAS, int nFieldLength); 
	bool				Parsing_PointRecord(const BYTE *pData, ST_POINT_RECORD &stPointRecord, int &nRecordLength); 
	bool				Parsing_ID(const BYTE *pData, ST_ID &stID, int nFieldLength); 
	bool				Parsing_C2IT(const BYTE *pData, ST_C2IT &stC2IT, int nFieldLength); 
	bool				Parsing_C3IT(const BYTE *pData, ST_C3IT &stC3IT, int nFieldLength); 
	bool				Parsing_C2FT(const BYTE *pData, ST_C2FT &stC2FT, int nFieldLength); 
	bool				Parsing_C3FT(const BYTE *pData, ST_C3FT &stC3FT, int nFieldLength); 
	bool				Parsing_MultiPointRecord(const BYTE *pData, ST_MULTI_POINT_RECORD &stMultiPointRecord, int &nRecordLength); 
	bool				Parsing_COCC(const BYTE *pData, ST_COCC &stCOCC, int nFieldLength); 
	bool				Parsing_C2IL(const BYTE *pData, VEC_C2IL &vecC2IL, int nFieldLength); 
	bool				Parsing_C3IL(const BYTE *pData, VEC_C3IL &vecC3IL, int nFieldLength); 
	bool				Parsing_C2FL(const BYTE *pData, VEC_C2FL &vecC2FL, int nFieldLength); 
	bool				Parsing_C3FL(const BYTE *pData, VEC_C3FL &vecC3FL, int nFieldLength); 
	bool				Parsing_CurveRecord(const BYTE *pData, ST_CURVE_RECORD &stCurveRecord, int &nRecordLength); 
	bool				Parsing_PTAS(const BYTE *pData, VEC_PTAS &vecPTAS, int nFieldLength); 
	bool				Parsing_SECC(const BYTE *pData, ST_SECC &stSECC, int nFieldLength); 
	bool				Parsing_SEGH(const BYTE *pData, VEC_SEGH &vecSEGH, int nFieldLength); 
	bool				Parsing_CompositeCurveRecord(const BYTE *pData, ST_COMP_CURVE_RECORD &stCompCurveRecord, int &nRecordLength); 
	bool				Parsing_CCOC(const BYTE *pData, ST_CCOC &stCCOC, int nFieldLength); 
	bool				Parsing_CUCO(const BYTE *pData, VEC_CUCO_RRNM &vecRRNM, int nFieldLength); 
	bool				Parsing_SurfaceRecord(const BYTE *pData, ST_SURFACE_RECORD &stSurfaceRecord, int &nRecordLength); 
	bool				Parsing_RIAS(const BYTE *pData, VEC_RIAS_RRNM &vecRRNM, int nFieldLength); 
	bool				Parsing_FeatureRecord(const BYTE *pData, ST_FEATURE_RECORD &stFeatureRecord, int &nRecordLength); 
	bool				Parsing_FRID(const BYTE *pData, ST_FRID &stFRID, int nFieldLength); 
	bool				Parsing_FOID(const BYTE *pData, ST_FOID &stFOID, int nFieldLength); 
	bool				Parsing_SPAS(const BYTE *pData, VEC_SPAS_RRNM &vecRRNM, int nFieldLength); 
	bool				Parsing_FASC(const BYTE *pData, ST_FASC &stFASC, int nFieldLength); 
	bool				Parsing_THAS(const BYTE *pData, VEC_THAS_RRNM &vecRRNM, int nFieldLength); 
	bool				Parsing_MASK(const BYTE *pData, VEC_MASK_RRNM &vecRRNM, int nFieldLength); 
	int					CharDataToInt(const BYTE *pData, int nCount); 
	CString			FindTag(const BYTE *pData); 
	CString			GetUTF_8(char *pData, int &nCount); 
	ST_POINT_RECORD*       GetPointRecord(int id);
	ST_MULTI_POINT_RECORD* GetMultiPointRecord(int id);
	ST_CURVE_RECORD*       GetCurveRecord(int id);
	ST_COMP_CURVE_RECORD*  GetCompositeCurveRecord(int id);
	ST_SURFACE_RECORD*     GetSurfaceRecord(int id);
	ST_FEATURE_RECORD*     GetFeatureRecord(int id);

	bool CheckBase();
	void Output(CString& str);     
	int GetGeometryTypeFromFeatureRecord(int id);   
	bool CheckSPAS();      
	CString GetFeatureTypeCamelCase(int featureTypeCode);      
	CString GetInformationTypeCamelCase(int informationTypeCode);      
	CString GetAttributeCamelCase(int attributeCode);

	void GetPoints(ST_FEATURE_RECORD *pFeatureRecord, std::vector<D2D1_POINT_2F>& points);
	D2D1_POINT_2F GetPoint(ST_POINT_RECORD* pST_POINT_RECORD);
	void GetPoints(ST_CURVE_RECORD* pST_CURVE_RECORD, std::vector<D2D1_POINT_2F>& points);
	void GetPoints(ST_COMP_CURVE_RECORD* pST_COMP_CURVE_RECORD, std::vector<D2D1_POINT_2F>& points);
	void GetPoints(ST_SURFACE_RECORD* pST_SURFACE_RECORD, std::vector<D2D1_POINT_2F>& points);

	void GetBoundingBox(float& xmin, float& ymin, float& xmax, float& ymax, int& scaleMin, int& scaleMax);
	void GetBoundingBox(int featureID, float& xmin, float& ymin, float& xmax, float& ymax);

	void GenerateMapForRecord();

	int GetCodeByAttributeName(CString attributeName);
	int GetCodeByFeatureName(CString featureName);
	int GetCodeByInformationName(CString informationName);

	bool CheckFTCS(); 

	void GetFeatureByFeatureName(CString featureName, std::vector<ST_FEATURE_RECORD*>& vecFeatrue);
	void GetFeatureByFeatureNumericCode(int numericCode, std::vector<ST_FEATURE_RECORD*>& vecFeatrue);

	int fileSize = 0;
};