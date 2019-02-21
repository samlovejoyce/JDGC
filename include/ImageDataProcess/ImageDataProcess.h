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

		/** ��ȡ��ǰ���εĲ��δ�С */
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

		/** ����UTMͶӰ����ת��ͼƬ��UV���� */
		void convertUTM2UV(double x, double y, int &nx, int &ny);

		/** ����UV����ת��ͼƬ��UTMͶӰ���� */
		void convertUV2UTM(int nx, int ny, double &x, double &y);

		void releaseMemory();

	private:
		GDALDataset *_poDataset;
		GDALRasterBand *_poCurRasterBand;

		std::string _projMessage;

		int _nImageXSize;		/** ͼƬ�Ŀ�Ⱥ͸߶� */
		int _nImageYSize;

		int _nXBlockSize;		/**  */
		int _nYBlockSize;

		int _nXBlocksNo;
		int _nYBlocksNo;

		int _nRasterBandCount; /** ͼ�񲨶����� */

		float *fBlockData = nullptr;
		double padfTransform[6];
	};
}
#endif // !IMAGEPROCESS_H

