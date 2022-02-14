//Comm.h   

#ifndef __COMM_H__
#define __COMM_H__

#define COM_MAXBLOCK     4095
#define COM_MAXPORTS       10 

#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04 

#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13
#define ASCII_STX		0x02
#define ASCII_ETX		0xFE

#define WM_RECEIVEDATA WM_USER+100  
#define ZERO_MEMORY(s)	::ZeroMemory(&s, sizeof(s)) 
#define FC_DTRDSR	0x01
#define FC_RTSCTS	0x02
#define FC_XONXOFF	0x04
#define	FC_NONE		0x00

#define ASCII_XON	0x11
#define ASCII_XOFF	0x13 
#define CS_REGKEY_SETTINGS     _T("통신환경")
#define CS_REGENTRY_PORT       _T("PORT")
#define CS_REGENTRY_PARITY     _T("PARITY")
#define CS_REGENTRY_BAUD       _T("BAUD")
#define CS_REGENTRY_DATABITS   _T("DATABITS")
#define CS_REGENTRY_STOPBITS   _T("STOPBITS")
#define CS_REGENTRY_FLOW       _T("FLOW") 

typedef struct _TTYSTRUCT
{
   BYTE		byCommPort; 
   BYTE		byXonXoff;
   BYTE		byByteSize;
   BYTE		byFlowCtrl;
   BYTE		byParity;
   BYTE		byStopBits;
   DWORD	dwBaudRate;

} TTYSTRUCT, *LPTTYSTRUCT;  
extern BYTE _nFlow[4]; 
extern int _nDataValues[2]; 
extern int _nBaudRates[12]; 
extern BYTE _nStopBits[2];

class CComm : public CObject
{

   DECLARE_DYNCREATE( CComm )
public:	
	HANDLE      idComDev ; 
	BOOL        fConnected; 
	BYTE        abIn[ COM_MAXBLOCK + 1] ; 
	HWND		m_hwnd; 
	BOOL		bTxEmpty;  
public:
	CComm( ); 
	BOOL OpenCommPort(LPTTYSTRUCT lpTTY); 
	BOOL DestroyComm(); 
	int  ReadCommBlock( LPSTR data, int len); 
	BOOL WriteCommBlock( LPSTR data, DWORD len); 
	BOOL SetupConnection(LPTTYSTRUCT lpTTY); 
	BOOL CloseConnection( ); 
	void SetReadData(LPSTR data, int nLen); 
	void SetHwnd(HWND hwnd);
	void EscapeCommFunction(DWORD dwFunc) ; 
public:   
	OVERLAPPED  osWrite, osRead; 
public:     
public:
		
	virtual ~CComm();  
protected:
}; 
#endif