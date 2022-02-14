#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


class GeoPoint;
class Scaler;




class Bag;

class ClibS102App : public CWinApp
{
public:
	ClibS102App();
	virtual BOOL InitInstance();

	std::vector<Bag*> bags;
	bool on;
	bool bDrawSelectedGrid;
	GeoPoint* ptSelectedGrid;

	CDC* pDC;
	int bS104 = false;

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};