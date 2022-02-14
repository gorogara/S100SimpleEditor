#pragma once 

class CDialogExMovePoint : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExMovePoint)

public:
	CDialogExMovePoint(CWnd* pParent = NULL); 
	virtual ~CDialogExMovePoint(); 
	enum { IDD = IDD_DIALOG_MOVE_POINT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	double m_lat;
	double m_lon;
	afx_msg void OnBnClickedOk();
	double m_latMin;
	double m_lonMin;
	double m_latSec;
	double m_lonSec;
};
