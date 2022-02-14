#pragma once 

class CDialogExCloseProgram : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExCloseProgram)

public:
	CDialogExCloseProgram(CWnd* pParent = NULL); 
	virtual ~CDialogExCloseProgram(); 
	enum { IDD = IDD_DIALOG_PROGRAM_CLOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
};
