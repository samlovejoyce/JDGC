#ifndef ROADPSD_H
#define ROADPSD_H

#include "common/Export.h"
#include "MatlabConnect.h"
#include "MatlabInterface.h"


namespace JDGC
{
	/************************************************************************/
	/*	功能：生成路面功率谱密度数据                                                                     */
	/************************************************************************/
	class RoadPSD
	{
	public:
		RoadPSD();
		~RoadPSD();

		/** 设置道路功率谱密度所需参数 */
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
