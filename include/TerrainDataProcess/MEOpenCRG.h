#ifndef ME_OPENCRG_H
#define ME_OPENCRG_H

#include "common/Export.h"
#include "common/common.h"
#include "MatlabConnect.h"

#include <matrix.h>

#include <string>

namespace JDGC {

	/**
	 * ����opencrg����
	 */
	class JDCG_EXPORT_API MEOpenCRG
	{
	public:
		MEOpenCRG();
		~MEOpenCRG();

		/** ����CRG���� */
		void loadCrgData(const std::string crgFile);

		/** ����CRG���� */
		bool saveCrgData(const std::string crgFile);

		/** ����matlab����·����CRG�� */
		void changeMatlabWorkPathToCRG(const std::string path = CRG_MATLAB_LIB_PATH);

		/** ����CRG���ݴ洢�ṹ */
		bool createCrgDataFiled();

		/** ����CRG���ݽṹ�����������µ�matlab��engine�� */
		bool setCrgDataComment(const std::string comment);

		/** ����CRG���ݽṹ��Z��ֵ�����µ�matlab��engine�� */
		bool setCrgDataZValues(double **data);

		/** ����CRG���ݽṹ���������ݲ����µ�matlab��engine�� */
		bool setCrgDataToMatlabEngine();

		/** ����CRG���ݽṹ������ */
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
