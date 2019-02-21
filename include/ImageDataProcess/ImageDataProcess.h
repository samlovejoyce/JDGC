#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <gdal_priv.h>

#include "common/Export.h"
#include "FileManeger.h"

namespace JDGC {
	class JDCG_EXPORT_API ImageDataProcess
	{
	public:
		ImageDataProcess();
		~ImageDataProcess();

		bool openFile(std::string file);

		int getBandCount();
		int getImageWidth();
		int getImageHeight();

		void initImageData();

		const char* getProjectionInfo();

		/** 获取当前波段的波段大小 */
		void setCurBandBlockSize(GDALRasterBand *poBand);

		int getCurBandXBlockSize() { return _nXBlockSize; }
		int getCurBandYBlockSize() { return _nYBlockSize; }
		int getXBlocksNo() { return _nXBlocksNo; }
		int getYBlocksNo() { return _nYBlocksNo; }

		void calculateCurBandBlocksNo(GDALRasterBand *poBand);

		float *getBlockData(GDALRasterBand *poBand, int nXBlockNo, int nYBlockNo, int &realXBlockSize, int &realYBlockSize);

		GDALRasterBand *getCurRasterBand(GDALDataset *poDataset, int index);
		GDALDataset *getDataset() { return _poDataset; }

		void gdalConvertUTMToWGS84(GDALDataset *poDataset, double x, double y);

		/** 根据UTM投影坐标转换图片的UV坐标 */
		void convertUTM2UV(double x, double y, int &nx, int &ny);

		/** 根据UV坐标转换图片的UTM投影坐标 */
		void convertUV2UTM(int nx, int ny, double &x, double &y);

		void releaseMemory();

	private:
		GDALDataset *_poDataset;
		GDALRasterBand *_poCurRasterBand;

		std::string _projMessage;

		int _nImageXSize;		/** 图片的宽度和高度 */
		int _nImageYSize;

		int _nXBlockSize;		/**  */
		int _nYBlockSize;

		int _nXBlocksNo;
		int _nYBlocksNo;

		int _nRasterBandCount; /** 图像波段总数 */

		float *fBlockData = nullptr;
		double padfTransform[6];
	};
}
#endif // !IMAGEPROCESS_H

