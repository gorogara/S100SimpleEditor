// FileLoad.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "afxwin.h"
#include "FileLoad.h"
#include "afxdialogex.h"

#include <iostream>
#include <locale.h>

using namespace std;


FileLoad::FileLoad(CString path) : m_Path(path)
{

}

FileLoad::~FileLoad()
{
}

FileLoad::FileLoad(FileLoad &pStd)
{

} 
CString FileLoad::FileLoadFromPath()
{
	
	CString strPathName = m_Path;
	CStdioFile file;
	char* read;
	CString rStr;

	if (file.Open(strPathName, CFile::modeRead)) {
		ULONGLONG nBytes = file.GetLength();
		if (nBytes >= 0) {
			read = new char[int(nBytes + 1)];
			file.Read(read, (int)nBytes);
			read[nBytes] = 0;
			rStr.Empty();
			rStr = CString(read);
			delete read;
		}
		file.Close();


		m_LoadStr = rStr;
		
	}

	return m_LoadStr;
	
}
