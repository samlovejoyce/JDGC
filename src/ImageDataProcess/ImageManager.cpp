#include "ImageManager.h"

#include <common/common.h>

#include <odb/mysql/transaction.hxx>

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
		_pImageProcess = new ImageProcess();
		setImagePath("E:\\JDGC Project document\\Terrain tif\\changzhi_dsm.tif");

		db = std::auto_ptr<odb::database>(new odb::mysql::database(DB_USER_NAME, DB_PASSWORD, DB_NAME));
	}

	ImageManager::~ImageManager()
	{
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

			/** 图像波段数循环 */
			for (int i = 0; i < nBandCount; i++)
			{
				GDALRasterBand *pCurBand = _pImageProcess->getCurRasterBand(_pImageProcess->getDataset(), i + 1);

				_pImageProcess->calculateCurBandBlocksNo(pCurBand);

				float *data = nullptr;
				int xBlocksNo = _pImageProcess->getXBlocksNo();/** 当前图像波段的分块数量 */
				int yBlocksNo = _pImageProcess->getYBlocksNo();

				for (unsigned int y = 0; y < yBlocksNo; y++)
				{
					for (unsigned int x = 0; x < xBlocksNo; x++)
					{
						int xBandSize, yBandSize;
						data = (float *)_pImageProcess->getBlockData(pCurBand, x, y, xBandSize, yBandSize);

						storeData(data, x, y, xBandSize, yBandSize);
					}
				}
			}
		}
	}

	/************************************************************************************
	* Copyright (c) 2019 All Rights Reserved.
	* 命名空间：JDGC 
	* 创建人  ：0XFFFFFFFF
	* 创建时间：2019/01/30
	* 功能描述: 数据存储到数据库中
	************************************************************************************/
	void ImageManager::storeData(float * pdata, int xno, int yno, int xsize, int ysize)
	{
		odb::transaction t(db->begin());

		std::vector<float> vData;
		for (int iY = 0; iY < ysize; iY++)
		{
			for (int iX = 0; iX < xsize; iX++)
			{
				vData.push_back(pdata[iX + iY * xsize]);
			}
		}

		real_terrain rt(xno, yno, xsize, ysize, vData);
		db->persist(rt);
		t.commit();
	}

	/************************************************************************************
	* Copyright (c) 2019 All Rights Reserved.
	* 命名空间：JDGC
	* 创建人  ：sharperm@163.com
	* 创建时间：2019/01/30
	* 功能描述: 
	************************************************************************************/
	std::vector<float> ImageManager::getDataBlock(float x, float y)
	{
		int nx, ny;
		/** Coordinate convert:Cartesian to image  pixel*/
		_pImageProcess->convertUTM2UV(x, y, nx, ny);
		
		typedef odb::query<real_terrain> query;
		typedef odb::result<real_terrain> result;

		int xblockno = nx / _pImageProcess->getCurBandXBlockSize();
		int yblockno = ny / _pImageProcess->getCurBandYBlockSize();
		
		odb::transaction t(db->begin());
		result r(db->query<real_terrain>(query::xblocksno == xblockno && query::yblocksno == yblockno));
		if (r.size() != 0)
			 return r.begin()->getZData();

		return std::vector<float>();
	}
	
	float ImageManager::getPointHeight(float x, float y)
	{
		return 0.0f;
	}
}
