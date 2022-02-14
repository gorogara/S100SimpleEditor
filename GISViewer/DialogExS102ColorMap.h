#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ColorMapCalculator.h"
#include "ColorMapCatalog.h"
#include "ColorMap.h" 

class CDialogExS102ColorMap : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExS102ColorMap)

public:
	CDialogExS102ColorMap(CWnd* pParent = NULL); 
	virtual ~CDialogExS102ColorMap(); 
	enum { IDD = IDD_DIALOG_S102_COLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	CComboBoxEx m_ComboEx;
	CComboBox m_comboCnt;
	afx_msg void OnBnClickedButtonClassification();

	void InsertItemIntoComboBox();
	void InsertItemIntoComboBoxCnt();
	void InitCatalog();

	nmColorMap::ColorMapCatalog catalog;
	nmColorMap::ColorMap colormap;
	nmColorMap::ColorMapCalculator calculator;
	virtual BOOL OnInitDialog();

	CImageList m_ImageList;
	int m_nBitmapIndex;
	CBitmap m_Bitmap;
	afx_msg void OnNMCustomdrawListColorMap(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio10();
	CButton m_btnClassification;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonApply();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedOk();

	int type;
	afx_msg void OnCbnSelchangeComboboxex1();
	afx_msg void OnCbnSelchangeCombo1();
};
