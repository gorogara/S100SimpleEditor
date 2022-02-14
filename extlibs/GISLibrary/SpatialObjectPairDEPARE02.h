#pragma once

class LSParameters;
struct SpatialObjectPairDEPARE02
{
public:
	SpatialObjectPairDEPARE02() {
		m_itorVecCnt = 0;
		m_bShareDEPCNT = false;
		m_ShareDEPCNT_VALDCO = 0.0;
		m_bShareDEPARE_DRGARE = false;
		m_bShareDEPARE_DRGARE_DRVAL1 = -1;
		m_bShareAnotherGROUP1Feature = false;
		m_bShareLNDARE_UNSARE = false;
		m_bShareOthers = false;
		m_LSSymbol = nullptr;
	}
	~SpatialObjectPairDEPARE02()
	{
	}

public:
	int m_itorVecCnt; 

	LSParameters* m_LSSymbol;

	bool m_bShareDEPCNT;
	double m_ShareDEPCNT_VALDCO;
	bool m_bShareDEPARE_DRGARE;
	double m_bShareDEPARE_DRGARE_DRVAL1;
	bool m_bShareAnotherGROUP1Feature;
	bool m_bShareLNDARE_UNSARE;
	bool m_bShareOthers;
};