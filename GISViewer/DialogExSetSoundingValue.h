#pragma once 

class DialogExSetSoundingValue : public CDialogEx
{
	DECLARE_DYNAMIC(DialogExSetSoundingValue)

public:
	DialogExSetSoundingValue(CWnd* pParent = nullptr); 
	virtual ~DialogExSetSoundingValue(); 
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SOUNDING_VALUE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
private:
	float m_soundingValue;
public:
	afx_msg void OnBnClickedOk();

public:
	float GetSoundingValue();
};
