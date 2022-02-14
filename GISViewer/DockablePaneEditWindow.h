#pragma once 
#include "PropertyGridAttributeModify.h"
#include "PropertyGridVectorModify.h"
#include "MFCTabCtrlMsgToParent.h"

#include "..\\S100EditingResource\\EditingResource.h"
#include "..\\FeatureCatalog\\ListedValues.h"

#include <unordered_map>
#include <list>

class SpatialObject;
class ENC_Feature;
class R_FeatureRecord;
class R_InformationRecord;
class R_VectorRecord;
class R_PointRecord;
class R_MultiPointRecord;
class R_CurveRecord;
class R_CompositeRecord;
class R_SurfaceRecord;
class ENC_Vector;
class CAttribute;
class CGISViewerView;
class CGISLibraryApp;
class EditingContent;

class AttributeBinding;
class SimpleAttribute;
class ComplexAttribute;
class EdtVector;
class Item;  
class MultiData
{
public:
	int type;

	std::vector<DWORD_PTR> data;
}; 
class CDockablePaneEditWindow : public CDockablePane
{
	DECLARE_DYNAMIC(CDockablePaneEditWindow)
	
public:
	CDockablePaneEditWindow();
	virtual ~CDockablePaneEditWindow();

public:
	void SetFeatureRecord(ENC_Feature* pObject);
	void SetFeatureRecord(R_FeatureRecord* pFeature);
	void SetFeatureRecord(R_InformationRecord* pInformation);
	void SetAttributes();
	void SetVectors();
	void SetVector(int RCNM, R_VectorRecord* r, CMFCPropertyGridProperty *pSuperProperty = nullptr);
	void SetVector(R_PointRecord* r, CMFCPropertyGridProperty *pSuperProperty = nullptr);
	void SetVector(R_MultiPointRecord* r, CMFCPropertyGridProperty *pSuperProperty = nullptr);
	void SetVector(R_CurveRecord* r, CMFCPropertyGridProperty *pSuperProperty = nullptr);
	void SetVector(R_CompositeRecord* r, CMFCPropertyGridProperty *pSuperProperty = nullptr);
	void SetVector(R_SurfaceRecord* r, CMFCPropertyGridProperty *pSuperProperty = nullptr);

	void SetVector(ENC_Vector* v, CMFCPropertyGridProperty *pSuperProperty = nullptr);

	void SetFeatureList();
	void DeleteAllItems();
	void DeleteAttributeItems();
	void DeleteVectorItems();

	bool ChcekAttribteUpperValue(AttributeBinding* ab);
	void AddAttribute(CAttribute* pAttr);
	void AddAttribute(AttributeBinding* ab, CMFCPropertyGridProperty *pSuperProperty = nullptr, unsigned parentIndex = 0);
	void AddSimpleAttribute(SimpleAttribute* sa, CMFCPropertyGridProperty *pSuperProperty = nullptr, unsigned parentIndex = 0);
	void AddComplexAttribute(ComplexAttribute* ca, CMFCPropertyGridProperty *pSuperProperty = nullptr, unsigned parentIndex = 0);  
	bool CheckingAttriData(AttributeBinding* ab, CString inputName, CMFCPropertyGridProperty *pSuperProperty); 
	void SettingEnumType(std::list<ListedValues> list, CMFCPropertyGridProperty* pSuperProperty); 
	  
	unsigned GetATCS(std::wstring code);
	unsigned GetATIX(unsigned natc, unsigned parentIndex);

	void SetPropListFont();

	void SetSpatialObject(SpatialObject *object);
	SpatialObject *GetSpatialObject();
	S101Cell* GetS101Cell();

public:
	void SetEditingContent(EditingContent *ec);

public:
	afx_msg int OnCreate(LPCREATESTRUCT lp);
	afx_msg void OnSize(UINT nType,int cx,int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP();

private :
	CImageList			m_imageList;
	CFont				m_fntPropList;
	CPropertyGridVectorModify			m_wndListVector; 
	SpatialObject *m_cell;
public:
	CGISViewerView *m_pView;
	CMFCTabCtrlMsgToParent	m_wndTabs;
	
	EditingContent* m_pEdtContent;
	static CPropertyGridAttributeModify		m_wndListAttribute;  

	int m_vIndex; 
	ENC_Feature* m_pObject; 
	R_FeatureRecord* m_pFeature;
	R_InformationRecord* m_pInformation;
	MultiData* m_selectedMultiData;

	std::unordered_map<CMFCPropertyGridProperty*, MultiData*> m_propertyAttributeMultiData;
	std::unordered_map<CMFCPropertyGridProperty*, MultiData*> m_propertyVectorMultiData;

	void DrawVectorData(CDC* pDC, CGISLibraryApp *pGisLib, const int _offX = 0, const int _offY = 0);
	bool SelectMultiData(EdtVector* ev);

	MultiData* InsertPropertyMultiData(
		int multidataType, 
		CMFCPropertyGridProperty* pGP, 
		DWORD_PTR pointer_1, 
		DWORD_PTR pointer_2 = NULL, 
		DWORD_PTR pointer_3 = NULL, 
		DWORD_PTR pointer_4 = NULL);


	BOOL MoveVectorToPoint(int x, int y);
	CString m_selectedObjectType;
	CString m_selectedInformationName;
	afx_msg LRESULT OnPropertyChanged(WPARAM wparam, LPARAM lparam);
	virtual BOOL PreTranslateMessage(MSG* pMsg); 
};


