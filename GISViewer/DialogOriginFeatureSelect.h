#pragma once 
class NewFeatureManager;
class CDialogOriginFeatureSelect : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogOriginFeatureSelect)

public:
	CDialogOriginFeatureSelect(CWnd* pParent = NULL); 
	virtual ~CDialogOriginFeatureSelect(); 
	enum { IDD = IDD_DIALOG_ADD_FEATURE_SELECT };

public:
	NewFeatureManager *m_pNewFeatureManager;
	
	void SetCatalogListCtrl();

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	afx_msg void OnBnClickedOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedListObject(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
};
