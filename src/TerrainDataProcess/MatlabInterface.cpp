#include "MatlabInterface.h"

namespace JDGC
{
	MatlabInterface::MatlabInterface()
	{

	}

	mxArray * MatlabInterface::createString(const std::string str)
	{
		return mxCreateString(str.c_str());
	}

	mxArray * MatlabInterface::createCharArray(size_t ndim, size_t * dims)
	{
		return mxCreateCharArray(ndim, dims);
	}

	mxArray * MatlabInterface::createDoubleScalar(double value)
	{
		return mxCreateDoubleScalar(value);
	}

	mxArray * MatlabInterface::createDoubleMatrix(size_t m, size_t n, int flag)
	{
		return mxCreateDoubleMatrix(m, n, (mxComplexity)flag);
	}

	mxArray * MatlabInterface::createCellMatrix(size_t row, size_t col)
	{
		return mxCreateCellMatrix(row, col);
	}

	mxArray * MatlabInterface::createCellArray(size_t ndim, const size_t * dims)
	{
		return mxCreateCellArray(ndim, dims);
	}

	mxArray * MatlabInterface::createStructArray(size_t ndim, const size_t * dims, int nfields, const char ** fieldnames)
	{
		return mxCreateStructArray(ndim, dims, nfields, fieldnames);
	}

	mxArray * MatlabInterface::createStructMatrix(size_t m, size_t n, int nfields, const char ** fieldnames)
	{
		return mxCreateStructMatrix(m, n, nfields, fieldnames);
	}

	mxArray * MatlabInterface::duplicateArray(mxArray * mx)
	{
		return mxDuplicateArray(mx);
	}

	void MatlabInterface::setData(mxArray * mx, void * newdata)
	{
		mxSetData(mx, newdata);
	}

	void MatlabInterface::setCell(mxArray * mx, size_t i, mxArray * value)
	{
		mxSetCell(mx, i, value);
	}

	void MatlabInterface::setFiled(mxArray * mx, size_t i, const char * fieldname, mxArray * value)
	{
		mxSetField(mx, i, fieldname, value);
	}

	void MatlabInterface::setFieldByNumber(mxArray * mx, size_t i, int fieldnum, mxArray * value)
	{
		mxSetFieldByNumber(mx, i, fieldnum, value);
	}

	void MatlabInterface::setRowDims(mxArray * mx, size_t m)
	{
		mxSetM(mx, m);
	}

	void MatlabInterface::setColumnDims(mxArray * mx, size_t n)
	{
		mxSetN(mx, n);
	}

	void MatlabInterface::setDims(mxArray * mx, const size_t *m, const size_t n)
	{
		mxSetDimensions(mx, m, n);
	}

	float * MatlabInterface::getPReal(mxArray * mx)
	{
		return (float *)mxGetPr(mx);
	}

	void MatlabInterface::destroy(mxArray * mx)
	{
		mxDestroyArray(mx);
	}

	void MatlabInterface::free(void *ptr)
	{
		mxFree(ptr);
	}

	bool MatlabInterface::isEmpty(mxArray * mx)
	{
		return mxIsEmpty(mx);
	}

}