#include "ImageDataProcess.h"

namespace JDGC
{
	ImageProcess::ImageProcess()
	{
		fBlockData = nullptr;
	}


	ImageProcess::~ImageProcess()
	{

		GDALClose((GDALDatasetH)_poDataset);
		GDALDestroy();
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* �����ռ䣺rootnamespace
	* �����ˣ� 0XFFFFFFFF
	* ����ʱ�䣺2019/01/11
	* ��������: ʹ��GDAL��ͼ���ļ�
	************************************************************************************/
	bool ImageProcess::openFile(std::string pszFileName)
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
	* �����ռ䣺rootnamespace
	* �����ˣ� 0XFFFFFFFF
	* ����ʱ�䣺2019/01/11
	* ��������: ��ȡͼƬ�Ĳ�������
	************************************************************************************/
	int ImageProcess::getBandCount()
	{
		if (!_poDataset)
			return 0;

		_nRasterBandCount = _poDataset->GetRasterCount();
		return _nRasterBandCount;
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* �����ռ䣺rootnamespace
	* �����ˣ� 0XFFFFFFFF
	* ����ʱ�䣺2019/01/11
	* ��������: ��ȡͼ��Ŀ��
	************************************************************************************/
	int ImageProcess::getImageWidth()
	{
		if (!_poDataset)
			return 0;

		_nImageXSize = _poDataset->GetRasterXSize();
		return _nImageXSize;
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* �����ռ䣺rootnamespace
	* �����ˣ� 0XFFFFFFFF
	* ����ʱ�䣺2019/01/11
	* ��������: ��ȡͼ��ĸ߶�
	************************************************************************************/
	int ImageProcess::getImageHeight()
	{
		if (!_poDataset)
			return 0;

		_nImageYSize = _poDataset->GetRasterYSize();
		return _nImageYSize;
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* �����ռ䣺rootnamespace
	* �����ˣ� 0XFFFFFFFF
	* ����ʱ�䣺2019/01/11
	* ��������: ��ȡͼ���ͶӰ��Ϣ
	************************************************************************************/
	const char * ImageProcess::getProjectionInfo()
	{
		if (!_poDataset)
			return nullptr;

		return _poDataset->GetProjectionRef();
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* �����ռ䣺rootnamespace
	* �����ˣ� 0XFFFFFFFF
	* ����ʱ�䣺2019/01/16
	* ��������: ��ȡ��ǰ���ε������С
	************************************************************************************/
	void ImageProcess::setCurBandBlockSize(GDALRasterBand * poBand)
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
	* �����ռ䣺rootnamespace
	* �����ˣ� 0XFFFFFFFF
	* ����ʱ�䣺2019/01/17
	* ��������: ���㵱ǰ���εĿ�����
	************************************************************************************/
	void ImageProcess::calculateCurBandBlocksNo(GDALRasterBand * poBand)
	{
		if (poBand)
		{
			setCurBandBlockSize(poBand);
			//int nXBlocks = (poBand->GetXSize() + nXBlockSize - 1) / nXBlockSize;
			//int nYBlocks = (poBand->GetYSize() + nYBlockSize - 1) / nYBlockSize;
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
	* �����ռ䣺rootnamespace
	* �����ˣ� 0XFFFFFFFF
	* ����ʱ�䣺2019/01/17
	* ��������: ��ȡ���εĵ�(nXBolockNo�� nYBolockNo)�������
	************************************************************************************/
	void * ImageProcess::getBlockData(GDALRasterBand * poBand, int nXBlockNo, int nYBlockNo, int *realXBlockSize, int *realYBlockSize)
	{
		if (!poBand)
			return nullptr;

		int nRealXBlockSize, nRealYBlockSize;

		/** ������ſ��ʵ��ͼƬ��С */
		//nRealXBlockSize = ((_nImageXSize - (nXBlockNo + 1) * _nXBlockSize) > 0) ? _nXBlockSize : (_nImageXSize - nXBlockNo * _nXBlockSize);
		//nRealYBlockSize = ((_nImageYSize - (nYBlockNo + 1) * _nYBlockSize) > 0) ? _nYBlockSize : (_nImageYSize - nYBlockNo * _nYBlockSize);

		/** �����Ӧ�����ݿռ� */
		//float *blockData = nullptr;
		GDALDataType eDataType = poBand->GetRasterDataType();
		if (eDataType == GDT_Float32)
		{
			if (fBlockData)
				delete fBlockData;
			fBlockData = new float[_nXBlockSize * _nYBlockSize];
			//blockData = new float[_nXBlockSize * _nYBlockSize];
			/** �����ݴ�ŵ��ڴ��� */
			poBand->ReadBlock(nXBlockNo, nYBlockNo, fBlockData);

			//Compute the portion of the block that is valid for partial edge blocks.
			poBand->GetActualBlockSize(nXBlockNo, nYBlockNo, &nRealXBlockSize, &nRealYBlockSize);			

			/** �����ݽ�����Ч�Դ��� */
			for (int iY = 0; iY < nRealYBlockSize; iY++)
			{
				for (int iX = 0; iX < nRealXBlockSize; iX++)
				{
					if ((fBlockData[iX + iY* nRealXBlockSize]) > 1000)
					{
						fBlockData[iX + iY* nRealXBlockSize] = 0.0;
					}
					else if ((fBlockData[iX + iY* nRealXBlockSize]) < -100.0)
					{
						fBlockData[iX + iY* nRealXBlockSize] = 0.0;
					}
				}
			}
		}

		*realXBlockSize = nRealXBlockSize;
		*realYBlockSize = nRealYBlockSize;
		return fBlockData;
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* �����ռ䣺rootnamespace
	* �����ˣ� 0XFFFFFFFF
	* ����ʱ�䣺2019/01/17
	* ��������: ��ȡ��ǰ���ε�ָ��
	************************************************************************************/
	GDALRasterBand * ImageProcess::getCurRasterBand(GDALDataset * poDataset, int index)
	{
		if (!poDataset)
			return nullptr;

		_poCurRasterBand = poDataset->GetRasterBand(index);

		return _poCurRasterBand;
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* �����ռ䣺rootnamespace
	* �����ˣ� 0XFFFFFFFF
	* ����ʱ�䣺2019/01/11
	* ��������: ��UTMͶӰ����ϵͳת��ΪWGS84��γ����ϵͳ
	************************************************************************************/
	void ImageProcess::gdalConvertUTMToWGS84(GDALDataset * poDataset, double x, double y)
	{
		const char *pszProjection = poDataset->GetProjectionRef();
		OGRSpatialReference *psrFrom = new OGRSpatialReference(pszProjection);

		OGRSpatialReference *psrTo = new OGRSpatialReference();
		psrTo->importFromEPSG(4326);

		OGRCoordinateTransformation* coordTrans = OGRCreateCoordinateTransformation(psrFrom, psrTo);

		double lat = x, lon = y;
		coordTrans->Transform(1, &lat, &lon);
	}

}