/**
 * 
 *	主要功能：CRG文件的生成（直线）
 *
 *
 */

#include "MEOpenCRG.h"
namespace JDGC
{
	MEOpenCRG::MEOpenCRG()
		: pCrgData(nullptr)
		, pCrgDataCt(nullptr)
		, pCrgDataU(nullptr)
		, pCrgDataV(nullptr)
		, pCrgDataZ(nullptr)
		, pCrgDataPhi(nullptr)
		, matlabEngineBase(nullptr)
	{
		matlabEngineBase = MatlabConnect::getInstance();
		changeMatlabWorkPathToCRG();
	}

	MEOpenCRG::~MEOpenCRG()
	{
		mxDestroyArray(pCrgData);
		mxDestroyArray(pCrgDataCt);
		mxDestroyArray(pCrgDataZ);
		mxDestroyArray(pCrgDataV);
		mxDestroyArray(pCrgDataU);
		mxDestroyArray(pCrgDataPhi);
	}

	void MEOpenCRG::loadCrgData(const std::string crgFile)
	{
		std::string command;
		std::string retFiledName = "data";
		command = retFiledName + " = crg_read( \'" + crgFile + "\');";

		if (matlabEngineBase->runMatlabCmd(command))
			pCrgData = engGetVariable(matlabEngineBase->getMatlabEngine(), retFiledName.c_str());
	}

	bool MEOpenCRG::saveCrgData(const std::string crgFile)
	{
		std::string command = CRG_DATA;
		command = "ans = crg_single(" + command + ");";

		if (!matlabEngineBase->runMatlabCmd(command))
		{
			return false;

		}
		command = CRG_DATA;
		command = "crg_write(ans, \'" + crgFile + "\');";

		if (!matlabEngineBase->runMatlabCmd(command))
			return false;

		return true;
	}

	void MEOpenCRG::changeMatlabWorkPathToCRG(const std::string path /* = CRG_MATLAB_LIB_PATH*/)
	{
		std::string command;
		command = "cd " + path + ";";

		if (matlabEngineBase->runMatlabCmd(command))
		{
			command = "crg_init;";

			if (!matlabEngineBase->runMatlabCmd(command))
				return;
		}
	}

	bool MEOpenCRG::createCrgDataFiled()
	{
		if (pCrgData == nullptr)
		{
			int ndim = 1;
			size_t dims[] = { 1, 1 };
			pCrgData = mxCreateStructArray(ndim, dims, CRG_DATA_FILED_LENGTH, crgDataFiledName);
		}
		if (engPutVariable(matlabEngineBase->getMatlabEngine(), CRG_DATA, pCrgData) != 0)
		{
			return false;
		}
		return true;
	}

	bool MEOpenCRG::setCrgDataComment(const std::string comment)
	{
		mxArray *tempStr = nullptr;

		if (pCrgDataCt == nullptr)
		{
			/** 创建mxString型变量 */
			pCrgDataCt = mxCreateCellMatrix(1, 1);
		}

		tempStr = mxCreateString(comment.c_str());
		mxSetCell(pCrgDataCt, 0, tempStr);

		/** 给mxComment变量赋值 */
		mxSetField(pCrgData, 0, CRG_DATA_CT, pCrgDataCt);

		if (engPutVariable(matlabEngineBase->getMatlabEngine(), CRG_DATA, pCrgData) != 0)
			return false;
		mxDestroyArray(tempStr);

		return true;
	}

	bool MEOpenCRG::setCrgDataZValues(double ** data)
	{
		if (!pCrgData)
			return false;

		crgDataZ = new double[(int)crgDataStruct->crgDataUEnd * CRG_DATA_NV];
		for (int i = 0; i < CRG_DATA_NV; i++)
		{
			for (int j = 0; j < (int)crgDataStruct->crgDataUEnd; j++)
			{
				crgDataZ[i * (int)crgDataStruct->crgDataUEnd + j] = data[j][i];
			}
		}

		/** 设置data.z的数据 */
		pCrgDataZ = mxCreateDoubleMatrix((int)crgDataStruct->crgDataUEnd, CRG_DATA_NV, mxREAL);
		if (engPutVariable(matlabEngineBase->getMatlabEngine(), CRG_DATA_Z, pCrgDataZ) != 0)
			return false;

		double *tempZ = (double *)mxGetPr(pCrgDataZ);
		memcpy(tempZ, crgDataZ, (int)crgDataStruct->crgDataUEnd * CRG_DATA_NV * sizeof(double));

		if (engPutVariable(matlabEngineBase->getMatlabEngine(), CRG_DATA_Z, pCrgDataZ) == 0)
			mxSetField(pCrgData, 0, CRG_DATA_Z, pCrgDataZ);
		else
			return false;

		/** 更新data的数据 */
		if (engPutVariable(matlabEngineBase->getMatlabEngine(), CRG_DATA, pCrgData) != 0)
			return false;

		return true;
	}

	bool MEOpenCRG::setCrgDataToMatlabEngine()
	{
		if (!pCrgData)
		{
			return false;
		}

		mxArray *pNv = mxCreateDoubleScalar(CRG_DATA_NV);
		engPutVariable(matlabEngineBase->getMatlabEngine(), "nv", pNv);

		mxArray *pNu = mxCreateDoubleScalar(crgDataStruct->crgDataUEnd);
		engPutVariable(matlabEngineBase->getMatlabEngine(), "nu", pNu);

		mxArray *pUinc = mxCreateDoubleScalar(crgDataStruct->crgDataUInc);
		engPutVariable(matlabEngineBase->getMatlabEngine(), "uinc", pUinc);

		mxArray *pVinc = mxCreateDoubleScalar(crgDataStruct->crgDataVInc);
		engPutVariable(matlabEngineBase->getMatlabEngine(), "vinc", pVinc);

		/* 设置临时v值 */
		pCrgDataV = mxCreateDoubleMatrix(1, CRG_DATA_NV, mxREAL);
		double *tempvalue = new double[CRG_DATA_NV - 1];
		for (int i = 0; i < CRG_DATA_NV; i++)
		{
			tempvalue[i] = i * crgDataStruct->crgDataVInc - crgDataStruct->crgDataVMax;
		}

		double *temp = mxGetPr(pCrgDataV);
		memcpy(temp, tempvalue, CRG_DATA_NV * sizeof(double));
		if (engPutVariable(matlabEngineBase->getMatlabEngine(), CRG_DATA_V, pCrgDataV) != 0)
			return false;

		/* ======================== 设置data的数据 ================================ */

		/* 设置data.u的数据 */
		pCrgDataU = mxCreateDoubleScalar((crgDataStruct->crgDataUEnd - 1) * crgDataStruct->crgDataUInc);
		mxSetField(pCrgData, 0, CRG_DATA_U, pCrgDataU);

		/* 设置data.v的数据 */
		pCrgDataV = mxCreateDoubleScalar((crgDataStruct->crgDataVMax - 1) * crgDataStruct->crgDataVInc / 2);
		mxSetField(pCrgData, 0, CRG_DATA_V, pCrgDataV);

		/* 设置data.b的数据*/
		pCrgDataBanking = mxCreateDoubleScalar(0);
		mxSetField(pCrgData, 0, CRG_DATA_B, pCrgDataBanking);

		/* 设置data.b的数据*/
		pCrgDataPhi = mxCreateDoubleScalar(0);
		mxSetField(pCrgData, 0, CRG_DATA_C, pCrgDataPhi);

		/* 设置data.b的数据*/
		pCrgDataSlope = mxCreateDoubleScalar(0);
		mxSetField(pCrgData, 0, CRG_DATA_S, pCrgDataSlope);

		if (engPutVariable(matlabEngineBase->getMatlabEngine(), CRG_DATA, pCrgData) != 0)
			return false;

		mxDestroyArray(pNu);
		mxDestroyArray(pNv);
		mxDestroyArray(pUinc);
		mxDestroyArray(pVinc);

		return true;
	}

	void MEOpenCRG::setCrgDataStruct(CrgData * data)
	{
		crgDataStruct = data;
	}
}


