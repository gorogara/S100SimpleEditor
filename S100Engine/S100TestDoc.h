  


#pragma once


class CS100TestDoc : public CDocument
{
protected: 
	CS100TestDoc();
	DECLARE_DYNCREATE(CS100TestDoc) 
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
	virtual ~CS100TestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected: 
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS 
	void SetSearchContent(const CString& value);
#endif 
};
