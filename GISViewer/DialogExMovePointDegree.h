#pragma once
#include "afxwin.h" 

class CDialogExMovePointDegree : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExMovePointDegree)

public:
	CDialogExMovePointDegree(CWnd* pParent = NULL); 
	virtual ~CDialogExMovePointDegree(); 
	enum { IDD = IDD_DIALOG_MOVE_POINT_DEGREE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 
	bool CheckEmpty(const std::wstring& _lat, const std::wstring& _lon) const;
	bool CheckForm(const std::wstring& _lat, const std::wstring& _lon) const;
	double GetDegree(const std::wstring& _str) const;

	bool CheckInput(std::wstring& _lat, std::wstring& _lon);
	bool SetMemberData(std::wstring& _lat, std::wstring& _lon);

	DECLARE_MESSAGE_MAP()
	bool bLat;
	bool bLon;

public:
	afx_msg void OnBnClickedOk();
	CEdit m_EditLat;
	CEdit m_EditLon;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnSetfocusEditLat();

	double lon;
	double lat;
	afx_msg void OnEnKillfocusEditLat();
	afx_msg void OnEnKillfocusEditLon();
	void SplitCoordinates();

	CString m_strLat;
	CString m_strLon;
};