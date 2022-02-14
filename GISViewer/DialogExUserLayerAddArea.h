#pragma once

#include "afxcmn.h"
#include "../GISLibrary/ENCFactory.h"

#include <vector>
#include "afxwin.h"

class CGISViewerView;

class CDialogExUserLayerAddArea : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExUserLayerAddArea)

public:
	CDialogExUserLayerAddArea(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogExUserLayerAddArea();

	void DBtoUI();
	void UItoDB();
	void DBtoView();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_USERLAYER_ADD_AREA };
	CGISViewerView* m_pView;
	std::vector<PointD> points;

	// 다이얼로그 변수
	CString   m_strName;
	CString   m_strDescription;
	CListCtrl m_ListCtrlCoordinates;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
