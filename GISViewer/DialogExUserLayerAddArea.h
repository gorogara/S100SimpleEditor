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
	CDialogExUserLayerAddArea(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogExUserLayerAddArea();

	void DBtoUI();
	void UItoDB();
	void DBtoView();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_USERLAYER_ADD_AREA };
	CGISViewerView* m_pView;
	std::vector<PointD> points;

	// ���̾�α� ����
	CString   m_strName;
	CString   m_strDescription;
	CListCtrl m_ListCtrlCoordinates;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
