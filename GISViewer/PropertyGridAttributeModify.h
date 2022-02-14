#pragma once 

class SpatialObject;
class AttributeBinding;
class S101Cell;

class CPropertyGridAttributeModify : public CMFCPropertyGridCtrl
{
	DECLARE_DYNAMIC(CPropertyGridAttributeModify)

public:
	CPropertyGridAttributeModify();
	virtual ~CPropertyGridAttributeModify();

	CPropertyGridAttributeModify(const CPropertyGridAttributeModify& obj)
	{
		*this = obj;
	}

	void operator=(const CPropertyGridAttributeModify& obj) {}

public: 
	CMFCPropertyGridProperty *pSelectedProperty;
	void SetSpatialObject(SpatialObject *spatialObject);
	SpatialObject *spatialObject = nullptr;

public:
	S101Cell* GetS101Cell();
	
private:
	int ComplexAttriIndexnum = 0; 

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point); 
	afx_msg void OnDeleteAttribute();

	void ComplexAttriIndexnumSet(int num);
	int ComplexAttriIndexnumGet(); 
	bool CheckingAttriData(CString inputname);

	afx_msg void OnAttributeeditOpen();
	afx_msg void OnAtttributeeditOpen();
	afx_msg void OnAtttributeeditDelete();
};