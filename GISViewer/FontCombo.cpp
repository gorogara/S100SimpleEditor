// FontCombo.cpp : implementation file 

#include "stdafx.h"
#include "FontCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif  

CFontCombo::CFontCombo()
{
	required_charset = ANSI_CHARSET;
}

CFontCombo::~CFontCombo()
{
}


BEGIN_MESSAGE_MAP(CFontCombo, CComboBox)   
END_MESSAGE_MAP()  

void CFontCombo::ProcessFonts(void)
{
	LOGFONT lf;
	POSITION pos;

	lf.lfCharSet = required_charset;
	lf.lfFaceName[0]='\0';

	::EnumFontFamiliesEx( this->GetParent()->GetDC()->m_hDC, &lf, (FONTENUMPROC) CFontCombo::EnumFontFamExProc, (LPARAM) &fontlist, 0);
	this->ResetContent();
	for(pos = fontlist.GetHeadPosition(); pos != NULL;)
		this->AddString(fontlist.GetNext(pos));
}

int CALLBACK CFontCombo::EnumFontFamExProc(ENUMLOGFONTEX *lpelfe,NEWTEXTMETRICEX *lpntme,int FontType,LPARAM lParam)
{
	CStringList* m_temp = (CStringList*) lParam;

	m_temp->AddTail(lpelfe->elfFullName);
	return 1; 
} 
void CFontCombo::PreSubclassWindow() 
{
	this->ProcessFonts();
	this->SelectString(0, _T("±¼¸²"));
	CComboBox::PreSubclassWindow();
}