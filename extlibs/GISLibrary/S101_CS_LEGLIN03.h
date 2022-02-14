#include "S101_ConditionalSymbol.h"

#include "..\\PLLibrary\\SYParameters.h"
#include "..\\PLLibrary\\LSParameters.h"
#include "..\\PLLibrary\\LCParameters.h"

class S101Cell;
class R_FeatureRecord;
class SGeometry;

class S101_CS_LEGLIN03 : public S101_ConditionalSymbol
{
	
public:
	S101_CS_LEGLIN03(R_FeatureRecord*, std::wstring);
	virtual ~S101_CS_LEGLIN03();
	
	int m_select;
	int m_plnspd;

	SYParameters m_SYParam;
	LCParameters m_LCParam;
	LSParameters m_LSParam;

	int m_DrawingType;

	void CheckCSVariable(S101Cell* cell, bool bSENC = false);
	void ChooseSymbol();
	void DrawGeometry(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);
	void DrawTextInfo(SGeometry *geo, HDC &hDC, Scaler *scaler, double offset = 0);

	void Serialize(CArchive &ar);
};
