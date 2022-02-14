#pragma once
#include "Tree.h" 

class CTreeFeatureType : public CTree
{
	DECLARE_DYNAMIC(CTreeFeatureType)

public:
	CTreeFeatureType();
	virtual ~CTreeFeatureType();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};


