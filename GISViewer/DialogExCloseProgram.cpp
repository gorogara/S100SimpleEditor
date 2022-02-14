// DialogExCloseProgram.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExCloseProgram.h"
#include "afxdialogex.h" 

IMPLEMENT_DYNAMIC(CDialogExCloseProgram, CDialogEx)

CDialogExCloseProgram::CDialogExCloseProgram(CWnd* pParent )
	: CDialogEx(CDialogExCloseProgram::IDD, pParent)
{

}

CDialogExCloseProgram::~CDialogExCloseProgram()
{
}

void CDialogExCloseProgram::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogExCloseProgram, CDialogEx)
END_MESSAGE_MAP() 
