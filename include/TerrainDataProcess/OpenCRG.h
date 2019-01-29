#ifndef OPENCRG_H
#define OPENCRG_H

#include "common/Export.h"
#include "common/common.h"
#include "MatlabConnect.h"
#include "MatlabInterface.h"

namespace JDGC
{
	/************************************************************************/
	/* ���ܣ�CRG�ļ�����                                                                     */
	/************************************************************************/
	class JDCG_EXPORT_API OpenCRG
	{
	public:
		OpenCRG();
		virtual ~OpenCRG();

		bool setMatlabWorkPath(std::string path);

		/** ����CRG���� */
		void setCRGParamters(RoadCurveData *data, const std::string commnet);

		/** ����CRG���� */
		void generateCRGData();
		
		/** ����CRG���� */
		void save(std::string path, CRGDATATYPE type = KRBI);

	protected:
		/** ����CRGmatlab�⺯������ */
		bool initOpenCRGLibEnv();
		
		/** �������� */
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
