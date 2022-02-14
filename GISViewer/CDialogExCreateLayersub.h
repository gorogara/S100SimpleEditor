#pragma once

#include "afxcmn.h"
#include "afxwin.h"
#include "Resource.h" 
#include "stdafx.h"
#include "DialogExCreateInformationFeature.h"
#include "DialogExCreateAutoRelation.h"
#include <unordered_map> 
class S101Cell;
class CInformationCodeStringAddPath :public CInformationCodeString 
{
public:
	R_DSGIR* dsgir;
	CString filepath;
	FeatureCatalogue* featureCatalog;
};

class CFeatureCodeStringAutoAddPath : public CFeatureCodeStringAuto 
{
public:
	R_DSGIR*  dsgir;
	CString filepath;
	FeatureCatalogue* featureCatalog;
};

class CDialogExCreateLayersub : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExCreateLayersub)

public:
	CDialogExCreateLayersub(CWnd* pParent = nullptr); 
	virtual ~CDialogExCreateLayersub(); 
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LAYERSUB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()

public :
	virtual BOOL OnInitDialog();
	void SetLayerFeatureData(S101Cell* cell);
	CTreeCtrl LayerFeatureTree;

	std::vector<CInformationCodeStringAddPath> infolist;
	std::vector<CFeatureCodeStringAutoAddPath> featurelist;
};
