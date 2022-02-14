#pragma once 
class PortrayalCatalogue;
class CGISViewerView;
class S101Cell;
class CDialogTDSDataset : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogTDSDataset)

public:
	CDialogTDSDataset(PortrayalCatalogue* portrayalCatalogue, CWnd* pParent = NULL); 
	virtual ~CDialogTDSDataset(); 
	enum { IDD = IDD_DIALOG_CREATE_TDS };
	
public:
	PortrayalCatalogue *pc;
	CGISViewerView *m_pView;


public:
	__int64 prohibitedAreaKeyValue;
	__int64 cautionaryAreaKeyValue;
	unsigned prohibitedAreaID;
	unsigned cautionaryAreaID;

	unsigned prohibitedAreaSpatialID;
public:
	void WriteCellBoundary(CFile *, S101Cell*);
protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnTds1();
	afx_msg void OnBnClickedBtnTds2();
	afx_msg void OnBnClickedBtnTds3();
	afx_msg void OnBnClickedBtnTds4();
	afx_msg void OnBnClickedBtnTds5();
	afx_msg void OnBnClickedBtnTds6();
	afx_msg void OnBnClickedBtnTds7();
	afx_msg void OnBnClickedBtnTds8();
	afx_msg void OnBnClickedBtnTds9();
	afx_msg void OnBnClickedBtnTds10();
	afx_msg void OnBnClickedBtnTds11();
	afx_msg void OnBnClickedBtnTds12();
	afx_msg void OnBnClickedBtnTds13();
	afx_msg void OnBnClickedBtnTds14();
	afx_msg void OnBnClickedBtnTds15();
	afx_msg void OnBnClickedBtnTds16();
	afx_msg void OnBnClickedBtnTds17();
	afx_msg void OnBnClickedBtnTds18();
	afx_msg void OnBnClickedBtnTds19();
	afx_msg void OnBnClickedBtnTds20();
	afx_msg void OnBnClickedBtnTds21();
	afx_msg void OnBnClickedBtnTds22();
	afx_msg void OnBnClickedBtnTds23();
	afx_msg void OnBnClickedBtnTds24();
	afx_msg void OnBnClickedBtnTds25();
	afx_msg void OnBnClickedBtnTds26();
	afx_msg void OnBnClickedBtnTds27();
	afx_msg void OnBnClickedBtnTds28();
	afx_msg void OnBnClickedBtnTds29();
	afx_msg void OnBnClickedBtnTds30();
	afx_msg void OnBnClickedBtnTds31();
	afx_msg void OnBnClickedBtnTds32();
	afx_msg void OnBnClickedBtnTds33();
	afx_msg void OnBnClickedBtnTds34();
	afx_msg void OnBnClickedBtnTds35();
	afx_msg void OnBnClickedBtnTds36();
	afx_msg void OnBnClickedBtnTds37();
	afx_msg void OnBnClickedBtnTds38();
	afx_msg void OnBnClickedBtnTds39();
	afx_msg void OnBnClickedBtnTds40();
	afx_msg void OnBnClickedChangeDsnm();
};
