#pragma once 

class CDialogExDeleteWaypoint : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExDeleteWaypoint)

public:
	CDialogExDeleteWaypoint(CWnd* pParent = NULL); 
	virtual ~CDialogExDeleteWaypoint(); 
	enum { IDD = IDD_DIALOG_DELETE_WP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	CString m_strWaypointNumber;
};
