#include "ImageDataProcess.h"

namespace JDGC
{
	ImageDataProcess::ImageDataProcess()
	{
	}


	ImageDataProcess::~ImageDataProcess()
	{
		releaseMemory();

		GDALClose((GDALDatasetH)_poDataset);
		GDALDestroy();
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/11
	* 功能描述: 使用GDAL打开图像文件
	************************************************************************************/
	bool ImageDataProcess::openFile(std::string pszFileName)
	{
		GDALAllRegister();

		_poDataset = (GDALDataset *)GDALOpen(pszFileName.c_str(), GA_ReadOnly);
		if (!_poDataset)
		{
			return false;
		}
		_projMessage = _poDataset->GetProjectionRef();
		return true;
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/11
	* 功能描述: 获取图片的波段总数
	************************************************************************************/
	int ImageDataProcess::getBandCount()
	{
		if (!_poDataset)
			return 0;

		_nRasterBandCount = _poDataset->GetRasterCount();
		return _nRasterBandCount;
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/11
	* 功能描述: 获取图像的宽度
	************************************************************************************/
	int ImageDataProcess::getImageWidth()
	{
		if (!_poDataset)
			return 0;

		_nImageXSize = _poDataset->GetRasterXSize();
		return _nImageXSize;
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/11
	* 功能描述: 获取图像的高度
	************************************************************************************/
	int ImageDataProcess::getImageHeight()
	{
		if (!_poDataset)
			return 0;

		_nImageYSize = _poDataset->GetRasterYSize();
		return _nImageYSize;
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace 
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/30
	* 功能描述:
	************************************************************************************/
	void ImageDataProcess::initImageData()
	{
		getImageWidth();
		getImageHeight();

		_poDataset->GetGeoTransform(padfTransform);
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/11
	* 功能描述: 获取图像的投影信息
	************************************************************************************/
	const char * ImageDataProcess::getProjectionInfo()
	{
		if (!_poDataset)
			return nullptr;

		return _poDataset->GetProjectionRef();
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/16
	* 功能描述: 获取当前波段的区块大小
	************************************************************************************/
	void ImageDataProcess::setCurBandBlockSize(GDALRasterBand * poBand)
	{
		if (poBand)
			poBand->GetBlockSize(&_nXBlockSize, &_nYBlockSize);
		else
		{
			_nXBlockSize = 0;
			_nYBlockSize = 0;
		}
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/17
	* 功能描述: 计算当前波段的块数量
	************************************************************************************/
	void ImageDataProcess::calculateCurBandBlocksNo(GDALRasterBand * poBand)
	{
		if (poBand)
		{
			setCurBandBlockSize(poBand);
			_nXBlocksNo = (_nImageXSize + _nXBlockSize - 1) / _nXBlockSize;
			_nYBlocksNo = (_nImageYSize + _nYBlockSize - 1) / _nYBlockSize;
		}
		else
		{
			_nXBlocksNo = 0;
			_nYBlocksNo = 0;
		}
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/17
	* 功能描述: 获取波段的第(nXBolockNo， nYBolockNo)块的数据
	************************************************************************************/
	float *ImageDataProcess::getBlockData(GDALRasterBand * poBand, int nXBlockNo, int nYBlockNo, int &realXBlockSize, int &realYBlockSize)
	{
		if (!poBand)
			return nullptr;

		float *dataarray = nullptr;
		GDALDataType eDataType = poBand->GetRasterDataType();
		if (eDataType == GDT_Float32)
		{
			/** 申请对应的数据空间 */
			if (fBlockData == nullptr)
			{
				fBlockData = new float[_nXBlockSize * _nYBlockSize];
				//memset(fBlockData, 0, sizeof(float) * (realXBlockSize * realYBlockSize));
			}
			
			/** 将数据存放到内存中 */
			CPLErr err = poBand->ReadBlock(nXBlockNo, nYBlockNo, fBlockData);
			if (err == CE_None)
			{
				//Compute the portion of the block that is valid for partial edge blocks.
				poBand->GetActualBlockSize(nXBlockNo, nYBlockNo, &realXBlockSize, &realYBlockSize);

			}
			/** 对数据进行有效性处理 */
			for (int iY = 0; iY < realYBlockSize; iY++)
			{
				for (int iX = 0; iX < realXBlockSize; iX++)
				{
					if ((fBlockData[iX + iY* _nXBlockSize]) > 1000)
					{
						fBlockData[iX + iY* _nXBlockSize] = 0.0;
					}
					else if ((fBlockData[iX + iY* _nXBlockSize]) < -100.0)
					{
						fBlockData[iX + iY* _nXBlockSize] = 0.0;
					}
				}
			}
		}
		return fBlockData;
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/17
	* 功能描述: 获取当前波段的指针
	************************************************************************************/
	GDALRasterBand * ImageDataProcess::getCurRasterBand(GDALDataset * poDataset, int index)
	{
		if (!poDataset)
			return nullptr;

		_poCurRasterBand = poDataset->GetRasterBand(index);

		return _poCurRasterBand;
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/11
	* 功能描述: 将UTM投影坐标系统转换为WGS84经纬坐标系统
	************************************************************************************/
	void ImageDataProcess::gdalConvertUTMToWGS84(GDALDataset * poDataset, double x, double y)
	{
		const char *pszProjection = poDataset->GetProjectionRef();
		OGRSpatialReference *psrFrom = new OGRSpatialReference(pszProjection);

		OGRSpatialReference *psrTo = new OGRSpatialReference();
		psrTo->importFromEPSG(4326);

		OGRCoordinateTransformation* coordTrans = OGRCreateCoordinateTransformation(psrFrom, psrTo);

		double lat = x, lon = y;
		coordTrans->Transform(1, &lat, &lon);
	}

	/************************************************************************************
	* Copyright (c) 2019 All Rights Reserved.
	* 命名空间：JDGC
	* 创建人  ：sharperm@163.com
	* 创建时间：2019/01/30
	* 功能描述: 根据UTM投影坐标转换图像UV坐标
	************************************************************************************/
	void ImageDataProcess::convertUTM2UV(double x, double y, int & nx, int & ny)
	{
		double tempx = ((x - padfTransform[0]) * padfTransform[4] - (y - padfTransform[3]) * padfTransform[1]) /
			(padfTransform[2] * padfTransform[4] - padfTransform[1] * padfTransform[5]);
		double tempy = ((x - padfTransform[0]) * padfTransform[5] - (y - padfTransform[3]) * padfTransform[2]) /
			(padfTransform[1] * padfTransform[5] - padfTransform[4] * padfTransform[2]);

		if ((tempx - floor(tempx)) < 0.5)
			x = floor(tempx);
		else
			x = ceil(tempx);

		if ((tempy - floor(tempy)) < 0.5)
			y = floor(tempy);
		else
			y = ceil(tempy);

	}

	/************************************************************************************
	* Copyright (c) 2019 All Rights Reserved.
	* 命名空间：JDGC
	* 创建人  ：sharperm@163.com
	* 创建时间：2019/01/30
	* 功能描述: 根据UV坐标转换图片的UTM投影坐标
	************************************************************************************/
	void ImageDataProcess::convertUV2UTM(int nx, int ny, double & x, double & y)
	{
		x = padfTransform[0] + nx * padfTransform[1] + ny * padfTransform[2];
		y = padfTransform[3] + nx * padfTransform[4] + ny * padfTransform[5];
	}
	void ImageDataProcess::releaseMemory()
	{
		if (fBlockData != nullptr)
		{
			delete [] fBlockData;
			fBlockData = nullptr;
		}
	}
}