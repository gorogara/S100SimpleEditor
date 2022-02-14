#pragma once 

class CComboBoxCtrl : public CComboBox
{
	DECLARE_DYNAMIC(CComboBoxCtrl)

public:
	CComboBoxCtrl();
	virtual ~CComboBoxCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchange();
};