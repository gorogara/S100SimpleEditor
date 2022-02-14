#pragma once

class LSParameters;
struct SpatialObjectPairDEPCNT03
{
public:
	SpatialObjectPairDEPCNT03() {
		m_LSSymbol = nullptr;
	}
	virtual ~SpatialObjectPairDEPCNT03()
	{
	}
	int m_itorVecCnt; 

	LSParameters* m_LSSymbol;
};
