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
	double creation_date;  //SYSTEMTIME으로의 볂환 : <OleAuto.h>의 VariantTimeToSystemTime 함수 이용.
	int max_lod_level; // lod = 0 (작은 데이터), lod = max (큰 데이터). 0~max 사이의 값을 사용해야 함.
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
** TCSMap 함수들을 사용하기 전에 반드시 호출. 스레드와 상관없이 전체 프로그램에서 한번만 호출
*/
bool TCSMAP_DLLITF TCSMap_CoInitialize();

/*
** TCSMap 함수 사용 후 반드시 호출. 스레드와 상관없이 전체 프로그램에서 한번만 호출.
** 호출이 완료 된 후에는 더이상 TCSMap 함수를 사용할 수 없다.
*/
void TCSMAP_DLLITF TCSMap_CoUninitialize();


/*
** TCSMap_HANDLE을 다 사용한 후 호출. 
*/
void TCSMAP_DLLITF TCSMap_CloseHandle(TCSMap_HANDLE handle);


typedef TCSMap_HANDLE TCSMap_DATA_HANDLE;

/*
** 에러 리다이렉션 함수. Default는 stderr.
** error_handler : 전역 함수. void f(const char* desc, ULONG_PTR callee_param); 형태를 가져야 함.
*/
void TCSMAP_DLLITF TCSMap_SetErrorHandler(TCSMap_ERROR_HANDLER error_handler, ULONG_PTR callee_param);


/*
** 데이터 초기화 함수.
**  data_path : 수치조류도 데이터 파일의 경로.
**	Success : NULL이 아닌 TCSMap_DATA_HANDLE 값
**	Fail : NULL. 에러 내용은 에러 함수를 통해 호출 됨.
*/
TCSMap_DATA_HANDLE TCSMAP_DLLITF TCSMap_LoadData(const char* data_path, TCSMap_coord* bind_coord);

/*
** 메타 데이터 확인
**  data_handle : NULL이 아닌 핸들
**	Success : TCSMap_METADATA. 각 값이 의미가 있음.
**	Fail : TCSMap_METADATA. 각 값이 의미가 없음. max_lod_level의 값이 -1.
*/
TCSMap_METADATA TCSMAP_DLLITF TCSMap_MetaData(TCSMap_DATA_HANDLE data_handle);

/*
** 데이터 로드 영역 지정 함수.
**  data_handle : NULL이 아닌 핸들
**	x_lt / y_lt : 데이터 영역의 좌상단 좌표. TCSMap_METADATA의 값 참조.
**	x_rb / y_rb : 데이터 영역의 우하단 좌표. TCSMap_METADATA의 값 참조.
**  lod : 로드할 Level of detail.
**     데이터 영역과 lod에 따라서 계산 속도, 메모리 크기, 데이터 정밀도가 다르다.
**	   적당한 값은 실제 데이터에 따라 틀리므로, 여러가지 테스트를 거쳐 값을 결정해야 한다.
**	   [수치모델 1km 표층.dat]의 경우, lod=7이고 한반도 서해 전체를 영역으로 지정하면 메모리 크기가 2GByte를 넘어간다.
**									   lod=1이고 한반도 서해 전체를 영역으로 지정하면 메모리 크기가 5MByte를 넘기지 않는다.
**		lod 값을 큰 값으로 쓰기위해서는 데이터 영역을 좁혀서 사용해야 한다.
**
**	Success : true
**	Fail : false
*/
bool TCSMAP_DLLITF TCSMap_SetRegion(TCSMap_DATA_HANDLE data_handle, double x_lt, double y_lt, double x_rb, double y_rb, int lod);

/*
** 프레임 지정 함수
**		조류도는 시간에 따라서 값이 계산된다. 값을 산출하기 위해서는 정확한 시간이 지정되어야 한다.
**		시작 시간과 끝 시간을 지정하면, 분 단위로 두 시각 사이의 모든 조류값이 계산된다.
**  data_handle : NULL이 아닌 핸들
**  start : 프레임 시작 시간.
**  end : 프레임 끝 시간.
**	Success : 계산된 프레임 개수
**	Fail :  -1.
*/
int TCSMAP_DLLITF TCSMap_SetFrame(TCSMap_DATA_HANDLE data_handle, const SYSTEMTIME& start, const SYSTEMTIME& end,int interval_in_minute);

typedef TCSMap_HANDLE TCSMap_FRAME_HANDLE;

/*
** 데이터 계산 및 결과 가져오기 함수
**		모든 계산이 완료될때까지, 함수는 Block된다.
**		계산된 프레임은 frame_array_buffer에 저장되어 리턴된다.
**  data_handle : NULL이 아닌 핸들
**  frame_array_buffer : 프레임 핸들을 저장할 버퍼
**  buffer_size : 버퍼의 크기
**	Success : 계산된 프레임 개수
**	Fail :  -1.
*/
int TCSMAP_DLLITF TCSMap_LockDataSync(TCSMap_DATA_HANDLE data_handle, TCSMap_FRAME_HANDLE* frame_array_buffer, int buffer_size);

typedef void (*TCSMap_BUILD_DONE)(ULONG_PTR callee_param);

/*
** 데이터 계산 및 결과 가져오기 함수
**		함수는 우선 리턴되며, 계산이 완료 되면 build_done이 호출된다.
**		함수가 리턴될때는 frame_array_buffer에 값이 채워지지 않으며, build_done이 호출될때 frame_array_buffer에 값이 채워진다.
**		frame_array_buffer 사용에 주의하여야 한다.
**
**  data_handle : NULL이 아닌 핸들
**  frame_array_buffer : 프레임 핸들을 저장할 버퍼
**  buffer_size : 버퍼의 크기
**  build_done : 계산이 완료될때 호출되어야 할 함수. NULL이 입력되면 에러가 발생.
**  callee_param : build_done 호출시 같이 호출되어야 할 파라미터.
**	Success : 계산된 프레임 개수
**	Fail :  -1.
*/
int TCSMAP_DLLITF TCSMap_LockDataAsync(TCSMap_DATA_HANDLE data_handle, TCSMap_FRAME_HANDLE* frame_array_buffer, int buffer_size, TCSMap_BUILD_DONE build_done, ULONG_PTR callee_param);


/*
** 각 프레임에서 실제 조류 데이터를 가져오는 함수.
**		내부 프레임 인스턴스에 저장된 배열의 포인터를 data_array에 저장하는 방식이다.
**		내부 프레임 인스턴스에 저장된 배열은 frame_handle이 유효할 동안 유효하다.
**
**  frame_handle : NULL이 아닌 핸들
**  data_array : 데이터가 저장된 배열의 포인터를 저장할 파라미터
**  data_size : 실제 데이터의 크기
**
**	Success : true
**	Fail :  false
*/
bool TCSMAP_DLLITF TCSMap_GetFrameData(TCSMap_FRAME_HANDLE frame_handle, TCSMap_DATA** data_array, int* data_size);



