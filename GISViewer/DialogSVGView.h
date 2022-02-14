#pragma once


class CGISLibraryApp; 

class CDialogSVGView : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSVGView)

public:
	CDialogSVGView(CWnd* pParent = NULL); 
	virtual ~CDialogSVGView(); 
	enum { IDD = IDD_DIALOG_SYMBOL_VIEW };

public:
	CGISLibraryApp				*m_pGisLib; 
	CDC mem_dc;
	CBitmap memBitmap;
	CDC transDC;
	CBitmap transBitmap;
	CDC map_dc;
	CBitmap mapBitmap;

	void DeleteDCs();
protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};