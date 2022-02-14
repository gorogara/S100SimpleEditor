#if !defined(AFX_CHECKLISTCTRL_H__B02295B1_44F0_46AE_985A_6067632408FB__INCLUDED_)
#define AFX_CHECKLISTCTRL_H__B02295B1_44F0_46AE_985A_6067632408FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif   
#include "CheckHeadCtrl.h"
#include "GISLibrary/GISLibrary.h"  

class CCheckListCtrl : public CListCtrl
{ 
public:
	CCheckListCtrl(); 
public: 
private:
	BOOL	m_blInited;
	CImageList	m_checkImgList;
	CGISViewerView *pView;

public:
	BOOL Init();

protected:
	CCheckHeadCtrl	m_checkHeadCtrl;     
public:
	virtual ~CCheckListCtrl(); 
protected: 
	afx_msg void OnItemChanged(NMHDR* pNMHDR, LRESULT* pResult); 

	DECLARE_MESSAGE_MAP()
};   

#endif 
