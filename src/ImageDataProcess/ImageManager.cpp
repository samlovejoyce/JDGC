#include "ImageManager.h"

#include <common/common.h>

//#include <odb/mysql/transaction.hxx>

namespace JDGC {

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace 
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/30
	* 功能描述: 图片数据管理构造函数
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
	* 命名空间：rootnamespace 
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/30
	* 功能描述: 设置当前图片的路径
	************************************************************************************/
	void ImageManager::setImagePath(std::string path)
	{
		curImagePath = path;
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace 
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/30
	* 功能描述: 载入图片
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
	* 命名空间：JDGC 
	* 创建人  ：0XFFFFFFFF
	* 创建时间：2019/01/30
	* 功能描述: 访问图片数据
	************************************************************************************/
	void ImageManager::readImageData()
	{
		if (loadImage(curImagePath) )
		{
			int nBandCount = _pImageProcess->getBandCount();

			if(!_db->isConnected()) _db->connect();

			/** 图像波段数循环 */
			for (int i = 0; i < nBandCount; i++)
			{
				GDALRasterBand *pCurBand = _pImageProcess->getCurRasterBand(_pImageProcess->getDataset(), i + 1);

				_pImageProcess->calculateCurBandBlocksNo(pCurBand);

				
				int xBlocksNo = _pImageProcess->getXBlocksNo();/** 当前图像波段的分块数量 */
				int yBlocksNo = _pImageProcess->getYBlocksNo();

				for (int y = 0; y < yBlocksNo; y++)
				{
					for (int x = 0; x < xBlocksNo; x++)
					{		
						int xBandSize = 0, yBandSize = 0;
						float *data = nullptr;
						
						data = _pImageProcess->getBlockData(pCurBand, x, y, xBandSize, yBandSize);

						/** 如果读取到的数据块的数据都为无效值，则不存储 */
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
