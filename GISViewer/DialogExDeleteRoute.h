#pragma once 

class CDialogExDeleteRoute : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExDeleteRoute)

public:
	CDialogExDeleteRoute(CWnd* pParent = NULL); 
	virtual ~CDialogExDeleteRoute(); 
	enum { IDD = IDD_DIALOG_DELETE_ROUTE_CONFIRM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	CString m_strRouteName;
};
