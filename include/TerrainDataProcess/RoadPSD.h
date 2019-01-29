#ifndef ROADPSD_H
#define ROADPSD_H

#include "common/Export.h"
#include "MatlabConnect.h"
#include "MatlabInterface.h"


namespace JDGC
{
	/************************************************************************/
	/*	���ܣ�����·�湦�����ܶ�����                                                                     */
	/************************************************************************/
	class RoadPSD
	{
	public:
		RoadPSD();
		~RoadPSD();

		/** ���õ�·�������ܶ�������� */
		void setRoadPSDData();

		void generationData();

	private:
		MatlabConnect *_connenctMatlab;
		MatlabInterface *_matlab;

		mxArray *_a1;
		mxArray *_a2;
		mxArray *_a3;
		mxArray *_a4;
	};
}

#endif // !ROADPSD_H
