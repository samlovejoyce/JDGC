#ifndef MATLABINTERFACE_H
#define MATLABINTERFACE_H

#include "common/Export.h"
#include "MatlabConnect.h"

namespace JDGC
{
	class JDCG_EXPORT_API MatlabInterface
	{
	public:
		MatlabInterface();
		virtual ~MatlabInterface(){}

		/** for string */
		virtual mxArray *createString(const std::string str);
		virtual mxArray *createCharArray(size_t ndim, size_t *dims);
		
		/** for numeric */
		virtual mxArray *createDoubleScalar(double value);
		virtual mxArray *createDoubleMatrix(size_t m, size_t n, int flag = 0);

		/** for cell */
		virtual mxArray *createCellMatrix(size_t row = 1, size_t col = 1);
		virtual mxArray *createCellArray(size_t ndim, const size_t *dims);

		/** for struct */
		virtual mxArray *createStructArray(size_t ndim, const size_t *dims, int nfields, const char **fieldnames);
		virtual mxArray *createStructMatrix(size_t m, size_t n, int nfields, const char **fieldnames);

		/** copy data */
		virtual mxArray *duplicateArray(mxArray *mx);

		/** for setting */
		virtual void setData(mxArray *mx, void *newdata);

		virtual void setCell(mxArray *mx, size_t i, mxArray *value);
		virtual void setFiled(mxArray *mx, size_t i, const char *fieldname, mxArray *value);
		virtual void setFieldByNumber(mxArray *mx, size_t i, int fieldnum, mxArray *value);

		virtual void setRowDims(mxArray *mx, size_t m);
		virtual void setColumnDims(mxArray *mx, size_t n);
		virtual void setDims(mxArray *mx, const size_t *m, const size_t n);

		/** for get */
		virtual float *getPReal(mxArray *mx);
		//virtual double *getPReal(mxArray *mx);

		virtual void destroy(mxArray *mx);
		virtual void free(void *ptr);

		/** for  */
		virtual bool isEmpty(mxArray *mx);
	};
}


#endif // !MATLABINTERFACE_H
