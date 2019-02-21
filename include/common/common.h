#ifndef COMMON_H
#define COMMON_H

#include <vector>

/* ���ݿ������������ */
#define DB_HOST_NAME "localhost"
#define DB_USER_NAME "root"
#define DB_PASSWORD "123456"
#define DB_PORT 3306
#define DB_DATABASE_NAME "terraindb"
#define DB_SOCKET_NAME nullptr
#define DB_FLAG 0

/**
* ����CRG���ߵĻ����������
*/
struct RoadCurveBase
{
	float length;
	float radiusStart;
	float radiusEnd;

	RoadCurveBase() :length(0.0), radiusStart(0.0), radiusEnd(0.0) {}

	RoadCurveBase &operator=(const RoadCurveBase other) {
		length = other.length;
		radiusStart = other.radiusStart;
		radiusEnd = other.radiusEnd;
		return *this;
	}
};

/**
* ��·��������
*/
typedef std::vector<RoadCurveBase> CURVE_VECTOR;

struct RoadCurveData
{
	std::string comment;	/** ���� */
	float uben;				/** u��x���������ʼ�� */
	float uend;				/** u��x������Ľ����� */
	float uinc;				/** u��x����������� */
	float vben;				/** v��y���������ʼ�� */
	float vend;				/** v��y������Ľ����� */
	float vinc;				/** v��y����������� */
	CURVE_VECTOR curve;		/** ���������� */
	CURVE_VECTOR slope;		/** ��·�������ϣ��¶ȣ����� */
	CURVE_VECTOR banking;	/** ��·�������ϵ����� */

	float **zData;			/** ��·�߳����� */
};

/**
* CRG���ݴ洢����
*/
enum CRGDATATYPE {
	KRBI = 0,		// 'KRBI'  binary float32
	KDBI,           // 'KDBI'  binary float64
	LRFI,			// 'LRFI'  ascii single precision
	LDFI			// 'LDFI'  ascii double precision
};

/* crgData���ݽṹ������������ */
#define CRG_DATA "data"					/* ���ͣ�struct */
#define CRG_DATA_CT "ct"				/* ���ͣ�cell */
#define CRG_DATA_Z "z"
#define CRG_DATA_V "v"
#define CRG_DATA_U "u"
#define CRG_DATA_B "b"
#define CRG_DATA_C "c"
#define CRG_DATA_S "s"
#define CRG_DATA_UINC "uinc"
#define CRG_DATA_VINC "vinc"
#define CRG_DATA_INC "inc"

/** crg���ݽṹ�ĸ����ֶ����� */
const char* crgDataFiledName[] =
{
	CRG_DATA_Z,
	CRG_DATA_V,
	CRG_DATA_U,
	CRG_DATA_CT,
	CRG_DATA_B,
	CRG_DATA_C,
	CRG_DATA_S
};
/** crg���ݽṹ�ֶγ��� */
#define CRG_DATA_FILED_LENGTH 7

/** crg���ݹ̶�����nv��ֵ */
#define CRG_DATA_NV 201

/** openCRG��MATLAB�������ļ� */
#define CRG_MATLAB_LIB_PATH "..\\..\\3rd\\OpenCRG.1.1.2\\matlab"


/**
 * TIF���θ߳�ͼƬ��UTMͶӰ���귶Χ
 */
#define TIF_PROJCOORDINATE_TOP 4012092.780
#define TIF_PROJCOORDINATE_LEFT 678840.900
#define TIF_PROJCOORDINATE_RIGHT 679193.070
#define TIF_PROJCOORDINATE_BOTTOM 4011029.950

#endif // !COMMON_H
