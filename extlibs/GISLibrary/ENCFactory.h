#pragma once
#include "ENCCell.h"
#include "SG2D.h"

struct FRID_INFO
{
	unsigned prim;
	unsigned group;
	unsigned objc;
};

struct FOID_INFO
{
	unsigned agen;
	unsigned fidn;
	unsigned fids;
};

struct VRID_INFO
{
	unsigned rcnm;
};

struct WP_INFO
{
	SG2D EX_POSITION;
	ENC_Vector* EX_CONNECTED;

	WP_INFO()
	{
		EX_CONNECTED = NULL;
	}

	~WP_INFO()
	{
	}
};

class ENCFactory
{
public:
	ENCFactory();
	ENCFactory(wstring datasetName);
	virtual ~ENCFactory();

private:
	ENCCell *m_cell;
	int m_recordIdentificationNumber;
	WP_INFO m_wpInfo;
	CGeoObjectMap	*p_object;
	CAttributeMap	*p_attribute;
	CColorMap		*p_color;
	CSymbolMap		*p_symbol; 

public:
	ENCCell* GetENC();
	void CreateENC(wstring datasetName);
	void SetENC(ENCCell* pCell);
	void SetDataSetIdentification(unsigned intendUsage, unsigned producingAgency, wstring comment);
	void SetDataSetStructureInformation(unsigned ATTFLexical  = 1, unsigned NATFLexical = 2);
	void SetDataSetParameter(unsigned verticalDatum, unsigned soundingDatum, unsigned compilationScaleOfData, wstring comment);

	ENC_Feature* CreateFeatureRecord(FRID_INFO frid, FOID_INFO foid);
	void SetFeatureAttf(ENC_Feature *fe, int code, wstring value);
	void SetFeatureNatf(ENC_Feature *fe, int code, wstring value);
	void SetFeatureFfpt(ENC_Feature *fe, ENC_Feature* foreinerFe, int relationshipIndi, wstring comment);
	void SetFeatureFspt(ENC_Feature *fe, ENC_Vector* ve, int ornt = 1, int usage = 1, int mask = 2);

	ENC_Vector* CreateVectorRecord(VRID_INFO vrid);
	void SetVectorATTV(ENC_Vector *ve, int code, wstring value);
	void SetVectorVRPT(ENC_Vector *ve, ENC_Vector *foreinerVe, int topologyIndi);
	void SetVectorSG2D(ENC_Vector *ve, list<SG2D> sg2dList);
	void SetVectorSG3D(ENC_Vector *ve, list<SG3D> sg3dList);
	void SetVectorSG2D(ENC_Vector *ve, list<int> lx, list<int> ly);
	void SetVectorSG3D(ENC_Vector *ve, list<int> lx, list<int> ly, list<int> lz);

	
	int AddWP(double lon, double lat);  
};