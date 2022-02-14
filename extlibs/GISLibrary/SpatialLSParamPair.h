#pragma once
class LSParameters;

struct SpatialLSParamPair
{
public:
	SpatialLSParamPair()
	{
		m_startIndex = 0;
		m_size = 0;
		m_LSSymbol = nullptr;
	}
	SpatialLSParamPair(size_t startIndex, size_t size, LSParameters *LSParam)
	{
		m_startIndex = startIndex;
		m_size = size;
		m_LSSymbol = LSParam;
	}
	~SpatialLSParamPair() {};

public:
	size_t m_startIndex;
	size_t m_size;
	LSParameters* m_LSSymbol;
};