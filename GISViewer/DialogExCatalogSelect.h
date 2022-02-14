#pragma once  

class Catalog;
class Catalogue;
class CatalogItem;

class CDialogExCatalogSelect : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExCatalogSelect)

public:
	CDialogExCatalogSelect(CWnd* pParent = NULL); 
	virtual ~CDialogExCatalogSelect(); 
	enum { IDD = IDD_DIALOG_CATALOG_SELECT };

public:
	std::vector<CatalogItem*> m_catalogItems;
	std::vector< Catalogue *> m_catalogItemList;
	static bool OpenFileMode; 
	Catalog* m_selectedCatalog; 
	int m_selectedIndex;
	CString m_fileName;
	void SetCatalogListCtrl();
	CButton SeletButton;

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedListObject(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSelectpcfcbutton();

};
