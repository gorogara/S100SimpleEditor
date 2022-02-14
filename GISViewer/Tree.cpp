// Tree.cpp : ���� �����Դϴ�. 

#include "stdafx.h"
#include "Tree.h"
#include "MainFrm.h"
#include "resource.h" 

IMPLEMENT_DYNAMIC(CTree, CTreeCtrl)

CTree::CTree()
{

}

CTree::~CTree()
{
}


BEGIN_MESSAGE_MAP(CTree, CTreeCtrl)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP() 


void CTree::SetNodeName(CString nodeName)
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	NodeName = nodeName;
}

CString CTree::GetNodeName()
{
	return NodeName;
}

void CTree::AddTreeNode(HTREEITEM *PNode, HTREEITEM *CNode, CString Data, int Color)
{
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 30;

	switch (Color)
	{
	case 1: 
		*CNode = InsertItem(Data, *PNode);
		SetItemColor(*CNode, RGB(0, 0, 255)); 
		break;
	case 2:
		*CNode = InsertItem(Data, *PNode);
		SetItemColor(*CNode, RGB(190, 50, 50)); 
		break;
	case 3:
		*CNode = InsertItem(Data, *PNode);
		SetItemColor(*CNode, RGB(230, 152, 74)); 
		break;
	case 4:
		*CNode = InsertItem(Data, *PNode);
		SetItemColor(*CNode, RGB(58, 207, 195)); 
		break;
	case 5:
		*CNode = InsertItem(Data, *PNode);
		SetItemColor(*CNode, RGB(168, 156, 141)); 
		break;
	case 6:
		*CNode = InsertItem(Data, *PNode);
		SetItemColor(*CNode, RGB(0, 134, 157)); 
		break;
	case 7:
		*CNode = InsertItem(Data, *PNode);
		SetItemColor(*CNode, RGB(224, 105, 112)); 
		break;
	case 8:
		*CNode = InsertItem(Data, *PNode);
		SetItemColor(*CNode, RGB(147, 139, 242)); 
		break;
	case 9:
		*CNode = InsertItem(Data, *PNode);
		SetItemColor(*CNode, RGB(36, 65, 181)); 
		break;
	case 10:
		*CNode = InsertItem(Data, *PNode);
		SetItemColor(*CNode, RGB(153, 81, 136)); 
		break;
	case 11:
		*CNode = InsertItem(Data, *PNode);
		SetItemColor(*CNode, RGB(61, 65, 84)); 
		break;
	case 12:
		*CNode = InsertItem(Data, *PNode);
		SetItemColor(*CNode, RGB(19, 170, 240)); 
		break;
	default:
		*CNode = InsertItem(Data, *PNode);
		SetItemColor(*CNode, RGB(0, 0, 0)); 
	}
	Expand(*PNode, TVM_EXPAND);  
} 
void CTree::SetItemFont(HTREEITEM hItem, LOGFONT& logfont)
{
	Color_Font cf;
	if (!m_mapColorFont.Lookup(hItem, cf))
		cf.color = (COLORREF)-1;
	cf.logfont = logfont;
	m_mapColorFont[hItem] = cf;
} 
void CTree::SetItemBold(HTREEITEM hItem, BOOL bBold)
{
	SetItemState(hItem, bBold ? TVIS_BOLD : 0, TVIS_BOLD);
} 
void CTree::SetItemColor(HTREEITEM hItem, COLORREF color)
{
	Color_Font cf;
	if (!m_mapColorFont.Lookup(hItem, cf))
		cf.logfont.lfFaceName[0] = '\0';
	cf.color = color;
	m_mapColorFont[hItem] = cf;
} 
BOOL CTree::GetItemFont(HTREEITEM hItem, LOGFONT * plogfont)
{
	Color_Font cf;
	if (!m_mapColorFont.Lookup(hItem, cf))
		return FALSE;
	if (cf.logfont.lfFaceName[0] == '\0')
		return FALSE;
	*plogfont = cf.logfont;
	return TRUE;

} 
BOOL CTree::GetItemBold(HTREEITEM hItem)
{
	return GetItemState(hItem, TVIS_BOLD) & TVIS_BOLD;
} 
COLORREF CTree::GetItemColor(HTREEITEM hItem)
{ 
	Color_Font cf;
	if (!m_mapColorFont.Lookup(hItem, cf))
		return (COLORREF)-1;
	return cf.color;

}

void CTree::OnPaint()
{
	CPaintDC dc(this);   
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CRect rcClip, rcClient;
	dc.GetClipBox(&rcClip);
	GetClientRect(&rcClient); 
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
	memDC.SelectObject(&bitmap); 
	CRgn rgn;
	rgn.CreateRectRgnIndirect(&rcClip);
	memDC.SelectClipRgn(&rgn);
	rgn.DeleteObject(); 
	CWnd::DefWindowProc(WM_PAINT, (WPARAM)memDC.m_hDC, 0);

	HTREEITEM hItem = GetFirstVisibleItem();

	int iItemCount = GetVisibleCount() + 1;
	while (hItem && iItemCount--)
	{
		CRect rect; 
		UINT selflag = TVIS_DROPHILITED | TVIS_SELECTED;
		Color_Font cf;  

		if ((GetItemState(hItem, selflag) & selflag)
			&& ::GetFocus() == m_hWnd)
			;
		else if (m_mapColorFont.Lookup(hItem, cf))
		{
			CFont *pFontDC;
			CFont fontDC;
			LOGFONT logfont;

			if (cf.logfont.lfFaceName[0] != '\0')
				logfont = cf.logfont;
			else { 
				CFont *pFont = GetFont();
				pFont->GetLogFont(&logfont);
			}

			if (GetItemBold(hItem))
				logfont.lfWeight = 700;

			fontDC.CreateFontIndirect(&logfont);
			pFontDC = memDC.SelectObject(&fontDC);

			if (cf.color != (COLORREF)-1)
				memDC.SetTextColor(cf.color);
			else
				memDC.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));


			CString sItem = GetItemText(hItem);

			GetItemRect(hItem, &rect, TRUE);
			memDC.SetBkColor(GetSysColor(COLOR_WINDOW));
			memDC.TextOut(rect.left + 2, rect.top + 1, sItem);

			memDC.SelectObject(pFontDC);
		}
		hItem = GetNextVisibleItem(hItem);
	}


	dc.BitBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &memDC,
		rcClip.left, rcClip.top, SRCCOPY);

	memDC.DeleteDC();
}



int CTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1; 

	CBitmap Bmp1;
	Bmp1.LoadBitmap(IDB_BITMAP1);
	ImgList.Create(16, 16, ILC_COLOR24, 3, 0);
	ImgList.Add(&Bmp1, RGB(0, 233, 233));

	SetImageList(&ImgList, TVSIL_NORMAL);
	return 0;
}