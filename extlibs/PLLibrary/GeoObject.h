#pragma once
class CGeoObject
{
public:
	CGeoObject();
	virtual ~CGeoObject();
	CString Acronym;
	int Code;
	int type;
	CString Project;
	CString Object_class;  
	class _Attribute
	{
	public:
		_Attribute();
		virtual~_Attribute();

	public:
		CString Attribute_name;
		int Attribute_type;
	};
	CArray<CGeoObject::_Attribute,CGeoObject::_Attribute&> Attribute[3];
	
	int Geometric_primitives;
	CString Remarks;
	CString Distinction;
	CString References_INT_1;
	CString References_M_4;
	CString Page_number;
	CString Version_number;		
	CString Theme;
	int	Scale_min;  
};
