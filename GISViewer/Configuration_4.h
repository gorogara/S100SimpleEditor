#pragma once
#include "afxwin.h"
#include "CheckListCtrl.h"

class CConfigrationDlg;
class CConfiguration_4 : public CDialogEx
{
	DECLARE_DYNAMIC(CConfiguration_4)

public:
	CConfiguration_4(CWnd* pParent = nullptr); 
	virtual ~CConfiguration_4(); 
	enum { IDD = IDD_DIALOG_CONFIG_4 };

	CConfigrationDlg* m_pParent;
	SpatialObject *spatialObject = nullptr;
private:


protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	DECLARE_MESSAGE_MAP()

public: 

	virtual BOOL OnInitDialog();
	CCheckListCtrl m_visualFeatureList;
};
