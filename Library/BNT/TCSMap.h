/*
**	BNT Solution co,. ltd
**  Tidal current uv_map DLL.
**
**  All rights reserved.
*/
#pragma once
#include <Windows.h>

#ifdef DLLTCSMAP_EXPORTS
#	define TCSMAP_DLLITF __declspec(dllexport)
#else
#	define TCSMAP_DLLITF __declspec(dllimport)
#endif

typedef struct TCSMap_HANDLE_definition {int __unused;} *TCSMap_HANDLE;


typedef enum TCSMap_PROJECTION_tag
{
	TCS_PRJ_LATLON,
	TCS_PRJ_UTM,
	TCS_PRJ_TM,
	TCS_PRJ_MAX,
} TCSMap_PROJECTION;

typedef enum TCSMap_SPHEROID_tag
{
	TCS_SPH_WGS84,
	TCS_SPH_GRS80,
	TCS_SPH_BESSEL,
	TCS_SPH_MAX
} TCSMap_SPHEROID;

typedef union TCSMap_coord_param_tag
{
	struct
	{
		int xzone;
		char yzone;
	} utm;
	enum
	{
		TM_SEO_BU,
		TM_JUNG_BU,
		TM_DONG_BU,
		TM_JEJU
	} tm;
} TCSMap_coord_param;

typedef struct TCSMap_coord_tag
{
	TCSMap_PROJECTION projection;
	TCSMap_SPHEROID spheroid;
	TCSMap_coord_param param;
} TCSMap_coord;


typedef struct TCSMap_METADATA_tag
{
	char model_id[256];
	char model_name[256];
	double x_lt;
	double y_lt;
	double x_rb;
	double y_rb;
	char harmonic_classes[512];
	int harmonic_class_count;
	double creation_date;  //SYSTEMTIME������ ��ȯ : <OleAuto.h>�� VariantTimeToSystemTime �Լ� �̿�.
	int max_lod_level; // lod = 0 (���� ������), lod = max (ū ������). 0~max ������ ���� ����ؾ� ��.
} TCSMap_METADATA;

typedef struct TCSMap_DATA_tag
{
	double x;
	double y;
	double u;	//x-direction velocity
	double v;	//y-direction velocity
	double h;
} TCSMap_DATA;

typedef void (*TCSMap_ERROR_HANDLER)(const char* desc, ULONG_PTR callee_param);

/*
** TCSMap �Լ����� ����ϱ� ���� �ݵ�� ȣ��. ������� ������� ��ü ���α׷����� �ѹ��� ȣ��
*/
bool TCSMAP_DLLITF TCSMap_CoInitialize();

/*
** TCSMap �Լ� ��� �� �ݵ�� ȣ��. ������� ������� ��ü ���α׷����� �ѹ��� ȣ��.
** ȣ���� �Ϸ� �� �Ŀ��� ���̻� TCSMap �Լ��� ����� �� ����.
*/
void TCSMAP_DLLITF TCSMap_CoUninitialize();


/*
** TCSMap_HANDLE�� �� ����� �� ȣ��. 
*/
void TCSMAP_DLLITF TCSMap_CloseHandle(TCSMap_HANDLE handle);


typedef TCSMap_HANDLE TCSMap_DATA_HANDLE;

/*
** ���� �����̷��� �Լ�. Default�� stderr.
** error_handler : ���� �Լ�. void f(const char* desc, ULONG_PTR callee_param); ���¸� ������ ��.
*/
void TCSMAP_DLLITF TCSMap_SetErrorHandler(TCSMap_ERROR_HANDLER error_handler, ULONG_PTR callee_param);


/*
** ������ �ʱ�ȭ �Լ�.
**  data_path : ��ġ������ ������ ������ ���.
**	Success : NULL�� �ƴ� TCSMap_DATA_HANDLE ��
**	Fail : NULL. ���� ������ ���� �Լ��� ���� ȣ�� ��.
*/
TCSMap_DATA_HANDLE TCSMAP_DLLITF TCSMap_LoadData(const char* data_path, TCSMap_coord* bind_coord);

/*
** ��Ÿ ������ Ȯ��
**  data_handle : NULL�� �ƴ� �ڵ�
**	Success : TCSMap_METADATA. �� ���� �ǹ̰� ����.
**	Fail : TCSMap_METADATA. �� ���� �ǹ̰� ����. max_lod_level�� ���� -1.
*/
TCSMap_METADATA TCSMAP_DLLITF TCSMap_MetaData(TCSMap_DATA_HANDLE data_handle);

/*
** ������ �ε� ���� ���� �Լ�.
**  data_handle : NULL�� �ƴ� �ڵ�
**	x_lt / y_lt : ������ ������ �»�� ��ǥ. TCSMap_METADATA�� �� ����.
**	x_rb / y_rb : ������ ������ ���ϴ� ��ǥ. TCSMap_METADATA�� �� ����.
**  lod : �ε��� Level of detail.
**     ������ ������ lod�� ���� ��� �ӵ�, �޸� ũ��, ������ ���е��� �ٸ���.
**	   ������ ���� ���� �����Ϳ� ���� Ʋ���Ƿ�, �������� �׽�Ʈ�� ���� ���� �����ؾ� �Ѵ�.
**	   [��ġ�� 1km ǥ��.dat]�� ���, lod=7�̰� �ѹݵ� ���� ��ü�� �������� �����ϸ� �޸� ũ�Ⱑ 2GByte�� �Ѿ��.
**									   lod=1�̰� �ѹݵ� ���� ��ü�� �������� �����ϸ� �޸� ũ�Ⱑ 5MByte�� �ѱ��� �ʴ´�.
**		lod ���� ū ������ �������ؼ��� ������ ������ ������ ����ؾ� �Ѵ�.
**
**	Success : true
**	Fail : false
*/
bool TCSMAP_DLLITF TCSMap_SetRegion(TCSMap_DATA_HANDLE data_handle, double x_lt, double y_lt, double x_rb, double y_rb, int lod);

/*
** ������ ���� �Լ�
**		�������� �ð��� ���� ���� ���ȴ�. ���� �����ϱ� ���ؼ��� ��Ȯ�� �ð��� �����Ǿ�� �Ѵ�.
**		���� �ð��� �� �ð��� �����ϸ�, �� ������ �� �ð� ������ ��� �������� ���ȴ�.
**  data_handle : NULL�� �ƴ� �ڵ�
**  start : ������ ���� �ð�.
**  end : ������ �� �ð�.
**	Success : ���� ������ ����
**	Fail :  -1.
*/
int TCSMAP_DLLITF TCSMap_SetFrame(TCSMap_DATA_HANDLE data_handle, const SYSTEMTIME& start, const SYSTEMTIME& end,int interval_in_minute);

typedef TCSMap_HANDLE TCSMap_FRAME_HANDLE;

/*
** ������ ��� �� ��� �������� �Լ�
**		��� ����� �Ϸ�ɶ�����, �Լ��� Block�ȴ�.
**		���� �������� frame_array_buffer�� ����Ǿ� ���ϵȴ�.
**  data_handle : NULL�� �ƴ� �ڵ�
**  frame_array_buffer : ������ �ڵ��� ������ ����
**  buffer_size : ������ ũ��
**	Success : ���� ������ ����
**	Fail :  -1.
*/
int TCSMAP_DLLITF TCSMap_LockDataSync(TCSMap_DATA_HANDLE data_handle, TCSMap_FRAME_HANDLE* frame_array_buffer, int buffer_size);

typedef void (*TCSMap_BUILD_DONE)(ULONG_PTR callee_param);

/*
** ������ ��� �� ��� �������� �Լ�
**		�Լ��� �켱 ���ϵǸ�, ����� �Ϸ� �Ǹ� build_done�� ȣ��ȴ�.
**		�Լ��� ���ϵɶ��� frame_array_buffer�� ���� ä������ ������, build_done�� ȣ��ɶ� frame_array_buffer�� ���� ä������.
**		frame_array_buffer ��뿡 �����Ͽ��� �Ѵ�.
**
**  data_handle : NULL�� �ƴ� �ڵ�
**  frame_array_buffer : ������ �ڵ��� ������ ����
**  buffer_size : ������ ũ��
**  build_done : ����� �Ϸ�ɶ� ȣ��Ǿ�� �� �Լ�. NULL�� �ԷµǸ� ������ �߻�.
**  callee_param : build_done ȣ��� ���� ȣ��Ǿ�� �� �Ķ����.
**	Success : ���� ������ ����
**	Fail :  -1.
*/
int TCSMAP_DLLITF TCSMap_LockDataAsync(TCSMap_DATA_HANDLE data_handle, TCSMap_FRAME_HANDLE* frame_array_buffer, int buffer_size, TCSMap_BUILD_DONE build_done, ULONG_PTR callee_param);


/*
** �� �����ӿ��� ���� ���� �����͸� �������� �Լ�.
**		���� ������ �ν��Ͻ��� ����� �迭�� �����͸� data_array�� �����ϴ� ����̴�.
**		���� ������ �ν��Ͻ��� ����� �迭�� frame_handle�� ��ȿ�� ���� ��ȿ�ϴ�.
**
**  frame_handle : NULL�� �ƴ� �ڵ�
**  data_array : �����Ͱ� ����� �迭�� �����͸� ������ �Ķ����
**  data_size : ���� �������� ũ��
**
**	Success : true
**	Fail :  false
*/
bool TCSMAP_DLLITF TCSMap_GetFrameData(TCSMap_FRAME_HANDLE frame_handle, TCSMap_DATA** data_array, int* data_size);



