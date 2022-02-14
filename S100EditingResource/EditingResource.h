#pragma once
#include <vector>

//enum EdtCommand
//{
//	E_DELETE = 1,
//	E_UPDATE = 2,
//	E_INSERT = 3
//};

//enum EdtDateType
//{
//	E_NULL = 0,
//	E_F_C2IL = 1,
//	E_F_C2IT = 2
//};

//enum EdtOrient
//{
//	E_FORWARD = 0,
//	E_BACKWARD = 1
//};

//enum EdtTopologyIndicator
//{
//	E_TOPI_BEGNNING = 1,
//	E_TOPI_END = 2
//};

/*
Editing Unit PTR Define

	- Type 1
		Index 1 (0) : Vector Record
		Index 2 (1) : C2IL Field
		Index 3 (2) : IC2D
		Index 4 (3) : IC2D Index

	- Type 2
		Index 1 (0) : Vector Record
		Index 2 (1) : C2IT Field
*/

//class EdtUnit
//{
//public:
//	EdtUnit()
//	{
//		unitType = 0;
//	}
//public:
//	/*
//	Editing Unit PTR Define
//
//	- Unit Type 1
//	Index 1 (0) : Vector Record
//
//	- Unit Type 2
//	Index 1 (0) : Attribute Record
//	*/
//	int unitType;
//	std::vector<DWORD_PTR> data;
//};

//class EdtVector : public EdtUnit
//{
//public:
//	EdtVector()
//	{
//		unitType = 1;
//		type = E_NULL;
//		deleted = false;
//	}
//public:
//	/*
//	Editing Unit PTR Define
//
//	- Type 1
//	Index 1 (0) : Vector Record
//	Index 2 (1) : C2IL Field
//	Index 3 (2) : IC2D
//	Index 4 (3) : 1: Forward / 2: Backward
//
//	- Type 2
//	Index 1 (0) : Vector Record
//	Index 2 (1) : C2IT Field
//	Index 3 (2) : 1: Beginning Node / 2: End Node / 3: Beginning_End
//	*/
//	EdtDateType type;
//	bool deleted;
//};

//class EdtAttribute : public EdtUnit
//{
//public:
//	EdtAttribute()
//	{
//		unitType = 2;
//		type = 0;
//		deleted = false;
//	}
//public:
//	/*
//	Editing Unit PTR Define
//
//	- Type 1
//	Index 1 (0) : Feature Record
//	Index 2 (1) : Attribute Field
//	*/
//	int type;
//	bool deleted;
//};

//class EdtWorkUnit
//{
//public:
//	/*
//		enum EdtCommand
//		{
//			E_DELETE = 1,
//			E_UPDATE = 2,
//			E_INSERT = 3,
//			E_MOVE = 4
//		};
//	*/
//	EdtCommand cmd;
//	std::vector<DWORD_PTR> data;
//};