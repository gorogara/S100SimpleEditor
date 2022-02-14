#pragma once
#include "Tree.h"
#include "..\\FeatureCatalog\\Catalog.h"
#include "..\\FeatureCatalog\\AttributeBinding.h" 

class CGeoObject;
class FeatureType;
class InformationType;
class CDialogTreeAttributeList : public CTree
{
	DECLARE_DYNAMIC(CDialogTreeAttributeList)

public:
	CDialogTreeAttributeList();
	virtual ~CDialogTreeAttributeList(); 
	int m_type;
	int selectIndex;
	CMFCPropertyGridProperty *pParentAttribute = nullptr;
	int selectIndexNum = 0;
	

public:
	void SetShowTree(CGeoObject* ot);
	void SetShowTree(Catalog* _catalog, FeatureType* ft);
	void SetShowTree(Catalog* _catalog, InformationType* ift);
	void InsertAttribute(HTREEITEM &item);

	void ComplexSetShowTree(Catalog* _catalog, AttributeBinding* ab); 
	void BaseSetShowThee(); 

protected:	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};

