#ifndef ME_OPENCRG_H
#define ME_OPENCRG_H

#include "common/Export.h"
#include "common/common.h"
#include "MatlabConnect.h"

#include <matrix.h>

#include <string>

namespace JDGC {

	/**
	 * 处理opencrg数据
	 */
	class JDCG_EXPORT_API MEOpenCRG
	{
	public:
		MEOpenCRG();
		~MEOpenCRG();

		/** 载入CRG数据 */
		void loadCrgData(const std::string crgFile);

		/** 保存CRG数据 */
		bool saveCrgData(const std::string crgFile);

		/** 更改matlab工作路径到CRG库 */
		void changeMatlabWorkPathToCRG(const std::string path = CRG_MATLAB_LIB_PATH);

		/** 创建CRG数据存储结构 */
		bool createCrgDataFiled();

		/** 设置CRG数据结构的声明并更新到matlab的engine中 */
		bool setCrgDataComment(const std::string comment);

		/** 设置CRG数据结构的Z的值并更新到matlab的engine中 */
		bool setCrgDataZValues(double **data);

		/** 设置CRG数据结构的其他数据并更新到matlab的engine中 */
		bool setCrgDataToMatlabEngine();

		/** 设置CRG数据结构的数据 */
		void setCrgDataStruct(CrgData * data);

	private:
		mxArray* pCrgData;
		mxArray* pCrgDataCt;
		mxArray* pCrgDataZ;
		mxArray* pCrgDataV;
		mxArray* pCrgDataU;
		mxArray* pCrgDataBanking;
		mxArray* pCrgDataPhi;
		mxArray* pCrgDataSlope;

		CrgData *crgDataStruct;
		double *crgDataZ;

		MatlabConnect *matlabEngineBase;

	};
}

#endif // !ME_OPENCRG_H
