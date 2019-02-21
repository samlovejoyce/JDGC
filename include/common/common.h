#ifndef COMMON_H
#define COMMON_H

#include <vector>

/* 数据库连接所需参数 */
#define DB_HOST_NAME "localhost"
#define DB_USER_NAME "root"
#define DB_PASSWORD "123456"
#define DB_PORT 3306
#define DB_DATABASE_NAME "terraindb"
#define DB_SOCKET_NAME nullptr
#define DB_FLAG 0

/**
* 构成CRG曲线的基本数据组成
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
* 道路曲率数据
*/
typedef std::vector<RoadCurveBase> CURVE_VECTOR;

struct RoadCurveData
{
	std::string comment;	/** 声明 */
	float uben;				/** u（x）坐标的起始点 */
	float uend;				/** u（x）坐标的结束点 */
	float uinc;				/** u（x）坐标的增量 */
	float vben;				/** v（y）坐标的起始点 */
	float vend;				/** v（y）坐标的结束点 */
	float vinc;				/** v（y）坐标的增量 */
	CURVE_VECTOR curve;		/** 中心线曲率 */
	CURVE_VECTOR slope;		/** 道路纵切面上（坡度）曲率 */
	CURVE_VECTOR banking;	/** 道路横切面上的曲率 */

	float **zData;			/** 道路高程数据 */
};

/**
* CRG数据存储类型
*/
enum CRGDATATYPE {
	KRBI = 0,		// 'KRBI'  binary float32
	KDBI,           // 'KDBI'  binary float64
	LRFI,			// 'LRFI'  ascii single precision
	LDFI			// 'LDFI'  ascii double precision
};

/* crgData数据结构所包含的域名 */
#define CRG_DATA "data"					/* 类型：struct */
#define CRG_DATA_CT "ct"				/* 类型：cell */
#define CRG_DATA_Z "z"
#define CRG_DATA_V "v"
#define CRG_DATA_U "u"
#define CRG_DATA_B "b"
#define CRG_DATA_C "c"
#define CRG_DATA_S "s"
#define CRG_DATA_UINC "uinc"
#define CRG_DATA_VINC "vinc"
#define CRG_DATA_INC "inc"

/** crg数据结构的各个字段名称 */
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
/** crg数据结构字段长度 */
#define CRG_DATA_FILED_LENGTH 7

/** crg数据固定常量nv的值 */
#define CRG_DATA_NV 201

/** openCRG的MATLAB库所在文件 */
#define CRG_MATLAB_LIB_PATH "..\\..\\3rd\\OpenCRG.1.1.2\\matlab"


/**
 * TIF地形高程图片的UTM投影坐标范围
 */
#define TIF_PROJCOORDINATE_TOP 4012092.780
#define TIF_PROJCOORDINATE_LEFT 678840.900
#define TIF_PROJCOORDINATE_RIGHT 679193.070
#define TIF_PROJCOORDINATE_BOTTOM 4011029.950

#endif // !COMMON_H
