// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface           


#pragma once
#include "MainFrm.h"
#include <vector>

class CGISViewerDoc : public CDocument
{
protected: 
	CGISViewerDoc();
	DECLARE_DYNCREATE(CGISViewerDoc) 
public: 
public: 
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif  
public:
	virtual ~CGISViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	std::vector<CString> m_systemFontList; 
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS 
	void SetSearchContent(const CString& value);
#endif 
public:
	afx_msg void OnBtnGpsMyLoc();
	afx_msg void OnButtonConfig();
	afx_msg void OnSerialPorts();    
	afx_msg void OnButtonFcpcsetting();
};
