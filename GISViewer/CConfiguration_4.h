#pragma once
#include "stdafx.h"

// CConfiguration_4 대화 상자

class CConfiguration_4 : public CDialogEx
{
	DECLARE_DYNAMIC(CConfiguration_4)

public:
	CConfiguration_4(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConfiguration_4();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CONFIG_4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
