#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h" 

class CGISViewerView;

#include "DockablePaneLayerManager.h"
#include "DockablePanePickReport.h"
#include "DockablePaneAttributeList.h"
#include "DockablePaneCurrentSelection.h"
#include "DockablePaneEditWindow.h"
#include "DockablePaneRoutePlan.h"
#include "DockablePaneRelation.h"
#include "DockablePaneLogger.h"
#include "DialogCellFeatureList.h"

#include "GISLibrary\\BasicFile.h"

class CGISViewerApp : public CWinAppEx
{

public:
	CGISViewerApp();
	virtual ~CGISViewerApp();//¼Ò¸êÀÚ Ãß°¡

public:
	ULONG gdiplusToken; 

	CGISViewerView* pView;

	CDockablePane*            m_pTabbedBarVal;
	CDockablePaneLayerManager		m_pDockablePaneLayerManager;
	CDockablePanePickReport			m_DockablePanePickReport;
	CDockablePaneCurrentSelection	m_DockablePaneCurrentSelection;
	CDockablePaneAttributeList		m_DockablePaneAttributeList;
	CDockablePaneEditWindow			m_DockablePaneEditWindow;
	CDockablePaneRoutePlan          m_DockablePaneRoutePlan;
	CDockablePaneRelation           m_DockablePaneRelation;
	CDockablePaneLogger             m_DockablePaneLogger;
	
	CDialogCellFeatureList			*m_pDialogCellFeatureList = nullptr;

	std::vector<BasicFile>			BasicFilePath; 
	
	bool							userMode = false;

	UINT  m_nAppLook;   
	bool viewerMode = true; 
public:
	virtual BOOL InitInstance();

	virtual int ExitInstance();

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	void InitDocument();
	
	DECLARE_MESSAGE_MAP()

public:
	void LoadSettings();
	void SaveSettings();
	void MapRefresh();
	void SetRibbonMenu();
	void SettingFcPcSvg(); 

	std::wstring GetColorTable();

	CDockablePaneAttributeList& GetDockFeatureInformationList();

	bool IsViewerMode();
	bool IsEditingMode();

public:
	afx_msg void OnButtonDeleteMeasurement();
	afx_msg void OnBtnTdsDlg();
	afx_msg void OnUpdateUsermodeButton(CCmdUI *pCmdUI);
	afx_msg void OnUsermodeButton();
	afx_msg void OnAppAbout();

private:
	void InitStartingLocation();
	void PC_FCPathSetting();
	void BasicFileSetting();

	void InitStartingDatasetLoading(CString argument);
	void DatasetOpen(CString _product, CString _path);

	void InitCatalogSelectionDialog();
};

extern CGISViewerApp theApp;