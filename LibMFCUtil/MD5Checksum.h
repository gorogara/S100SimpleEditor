/*****************************************************************************************

***		MD5Checksum.h: interface for the MD5Checksum class.

***		Developed by Langfine Ltd. 
***		Released to the public domain 12/Nov/2001.
***		Please visit our website www.langfine.com

***		Any modifications must be clearly commented to distinguish them from Langfine's 
***		original source code. Please advise Langfine of useful modifications so that we 
***		can make them generally available. 

*****************************************************************************************/


#if !defined(AFX_MD5CHECKSUM_H__2BC7928E_4C15_11D3_B2EE_A4A60E20D2C3__INCLUDED_)
#define AFX_MD5CHECKSUM_H__2BC7928E_4C15_11D3_B2EE_A4A60E20D2C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif    
class CMD5Checksum  
{
public: 
	static CString GetMD5(BYTE* pBuf, UINT nLength);
	static CString GetMD5(CFile& File);
	static CString GetMD5(const CString& strFilePath);

protected: 
	CMD5Checksum();
	virtual ~CMD5Checksum() {}; 
	void Transform(BYTE Block[64]);
	void Update(BYTE* Input, ULONG nInputLen);
	CString Final();
	inline DWORD RotateLeft(DWORD x, int n);
	inline void FF( DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T);
	inline void GG( DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T);
	inline void HH( DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T);
	inline void II( DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T); 
	inline void DWordToByte(BYTE* Output, DWORD* Input, UINT nLength);
	inline void ByteToDWord(DWORD* Output, BYTE* Input, UINT nLength);

private:
	BYTE  m_lpszBuffer[64]; 
	ULONG m_nCount[2]; 
	ULONG m_lMD5[4]; 
};

#endif 








