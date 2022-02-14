// S100DatasetManager.h : S100DatasetManager DLL�� �⺻ ��� �����Դϴ�. 

#pragma once     

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h" 

namespace S100DatasetGML
{
	class S100GML_Dataset;
}

class S101Layer;
class Catalog;
class PortrayalCatalogue;

namespace S100DatasetMgr
{   
	S101Layer* CreateSENCFromGML(Catalog* catalog, PortrayalCatalogue* portrayalCatalog, S100DatasetGML::S100GML_Dataset* dataset);
}

class CS100DatasetManagerApp : public CWinApp
{
public:
	CS100DatasetManagerApp(); 
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
