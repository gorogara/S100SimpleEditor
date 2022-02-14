// DTree.cpp : 구현 파일입니다. 

#include "stdafx.h" 
#include "TreeFeatureType.h" 

IMPLEMENT_DYNAMIC(CTreeFeatureType, CTree)

CTreeFeatureType::CTreeFeatureType()
{

}

CTreeFeatureType::~CTreeFeatureType()
{
}


BEGIN_MESSAGE_MAP(CTreeFeatureType, CTreeFeatureType)
	ON_NOTIFY_REFLECT(NM_CLICK, &CTreeFeatureType::OnNMClick)
END_MESSAGE_MAP() 

void CTreeFeatureType::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{ 
	CPoint p;
	GetCursorPos(&p);
	::ScreenToClient(m_hWnd, &p);
	UINT nFlags = 0;
	HTREEITEM hltem = NULL;
	hltem = HitTest(p, &nFlags);  

	if (hltem)
	{                           

	}
	*pResult = 0;
}
