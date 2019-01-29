#ifndef OPENCRG_H
#define OPENCRG_H

#include "common/Export.h"
#include "common/common.h"
#include "MatlabConnect.h"
#include "MatlabInterface.h"

namespace JDGC
{
	/************************************************************************/
	/* 功能：CRG文件生成                                                                     */
	/************************************************************************/
	class JDCG_EXPORT_API OpenCRG
	{
	public:
		OpenCRG();
		virtual ~OpenCRG();

		bool setMatlabWorkPath(std::string path);

		/** 设置CRG参数 */
		void setCRGParamters(RoadCurveData *data, const std::string commnet);

		/** 生成CRG数据 */
		void generateCRGData();
		
		/** 保存CRG数据 */
		void save(std::string path, CRGDATATYPE type = KRBI);

	protected:
		/** 设置CRGmatlab库函数环境 */
		bool initOpenCRGLibEnv();
		
		/** 保存数据 */
		void setOpenCRGData(RoadCurveData *data);
		void setComment(const std::string commnet);
		
		void setIncArray();
		void setUArray();
		void setVArray();
		void setCurveArray();
		void setSlopeArray();
		void setBankkingArray();

		void setZData();
	private:
		MatlabInterface *_matlab;
		MatlabConnect *_connectMatlab;

		RoadCurveData *_data;

		mxArray *_comment;
		mxArray *_zData;
		mxArray *_inc;
		mxArray *_u;
		mxArray *_v;
		mxArray *_curve;
		mxArray *_slope;
		mxArray *_bankking;

		mxArray *_CRGDataStruct;
	};
}


#endif // !OPENCRG_H
