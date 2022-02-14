// Coordinates Move를 위한 다이얼로그 클래스 

#pragma once
#include "afxwin.h"
#include "EditWGS84.h"

class CDialogExMovePoint3 : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExMovePoint3)

public:
	CDialogExMovePoint3(CWnd* pParent = NULL); 
	virtual ~CDialogExMovePoint3();
	virtual BOOL OnInitDialog(); 
	enum { IDD = IDD_DIALOG_MOVE_POINT_3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	CEditWGS84 m_EditPos;
	double lon;
	double lat;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditPos();
};
