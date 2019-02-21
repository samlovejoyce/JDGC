#include "ImageManager.h"

#include <common/common.h>

//#include <odb/mysql/transaction.hxx>

namespace JDGC {

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* �����ռ䣺rootnamespace 
	* �����ˣ� 0XFFFFFFFF
	* ����ʱ�䣺2019/01/30
	* ��������: ͼƬ���ݹ����캯��
	************************************************************************************/
	ImageManager::ImageManager()
	{
		_pImageProcess = new ImageDataProcess();
		
		setImagePath("E:\\JDGC Project document\\Terrain tif\\changzhi_dsm.tif");

		_db = new DataBaseInterface(DB_HOST_NAME, DB_USER_NAME, DB_PASSWORD, DB_DATABASE_NAME);
	}

	ImageManager::~ImageManager()
	{
		//if (_pTerrainBlockData)
		{
			//delete _pTerrainBlockData;
		}
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* �����ռ䣺rootnamespace 
	* �����ˣ� 0XFFFFFFFF
	* ����ʱ�䣺2019/01/30
	* ��������: ���õ�ǰͼƬ��·��
	************************************************************************************/
	void ImageManager::setImagePath(std::string path)
	{
		curImagePath = path;
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* �����ռ䣺rootnamespace 
	* �����ˣ� 0XFFFFFFFF
	* ����ʱ�䣺2019/01/30
	* ��������: ����ͼƬ
	************************************************************************************/
	bool ImageManager::loadImage(std::string path)
	{
		if (_pImageProcess->openFile(path))
		{
			_pImageProcess->initImageData();
			return true;
		}
		return false;
	}

	/************************************************************************************
	* Copyright (c) 2019 All Rights Reserved.
	* �����ռ䣺JDGC 
	* ������  ��0XFFFFFFFF
	* ����ʱ�䣺2019/01/30
	* ��������: ����ͼƬ����
	************************************************************************************/
	void ImageManager::readImageData()
	{
		if (loadImage(curImagePath) )
		{
			int nBandCount = _pImageProcess->getBandCount();

			if(!_db->isConnected()) _db->connect();

			/** ͼ�񲨶���ѭ�� */
			for (int i = 0; i < nBandCount; i++)
			{
				GDALRasterBand *pCurBand = _pImageProcess->getCurRasterBand(_pImageProcess->getDataset(), i + 1);

				_pImageProcess->calculateCurBandBlocksNo(pCurBand);

				
				int xBlocksNo = _pImageProcess->getXBlocksNo();/** ��ǰͼ�񲨶εķֿ����� */
				int yBlocksNo = _pImageProcess->getYBlocksNo();

				for (int y = 0; y < yBlocksNo; y++)
				{
					for (int x = 0; x < xBlocksNo; x++)
					{		
						int xBandSize = 0, yBandSize = 0;
						float *data = nullptr;
						
						data = _pImageProcess->getBlockData(pCurBand, x, y, xBandSize, yBandSize);

						/** �����ȡ�������ݿ�����ݶ�Ϊ��Чֵ���򲻴洢 */
						bool store = false;
						for (int index = 0; index < xBandSize * yBandSize; index++)
						{
							if (data[index] != 0.0)
							{
								store = true;
								break;
							}
						}
						if (store)
							_db->insert(x, y, xBandSize, yBandSize, data);

						_pImageProcess->releaseMemory();
					}
				}			
			}
		}
	}

}
