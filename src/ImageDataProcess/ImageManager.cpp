#include "ImageManager.h"
#include "ImageDataProcess.h"

#include <common/common.h>

#include <odb/mysql/transaction.hxx>

namespace JDGC {
	ImageManager::ImageManager()
	{
		_isConnect = false;
		curImagePath = "E:\\JDGC Project document\\Terrain tif\\changzhi_dsm.tif";

		db = std::auto_ptr<odb::database>(new odb::mysql::database(DB_USER_NAME, DB_PASSWORD, DB_NAME));
	}


	ImageManager::~ImageManager()
	{
	}

	void ImageManager::setImagePath(std::string path)
	{
		curImagePath = path;
	}

	void ImageManager::readImage()
	{
		ImageProcess *pImageProcess = new ImageProcess();
		if (pImageProcess->openFile(curImagePath))
		{
			int nBandCount = pImageProcess->getBandCount();
			pImageProcess->getImageHeight();
			pImageProcess->getImageWidth();

			/** 图像波段数循环 */
			for (int i = 0; i < nBandCount; i++)
			{
				GDALRasterBand *pCurBand = pImageProcess->getCurRasterBand(pImageProcess->getDataset(), i + 1);

				pImageProcess->calculateCurBandBlocksNo(pCurBand);

				float *data = nullptr;
				int xBlocksNo = pImageProcess->getXBlocksNo();/** 当前图像波段的分块数量 */
				int yBlocksNo = pImageProcess->getYBlocksNo();

				for (unsigned int y = 0; y < yBlocksNo; y++)
				{
					for (unsigned int x = 0; x < xBlocksNo; x++)
					{
						int xBandSize, yBandSize;
						data = (float *)pImageProcess->getBlockData(pCurBand, x, y, &xBandSize, &yBandSize);

						storeData(data, x, y, xBandSize, yBandSize);						
					}
					
				}
			}
		}

	}

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

	std::vector<float> ImageManager::getDataBlock(float x, float y)
	{
		odb::transaction t(db->begin());

		/** Coordinate convert:Cartesian to image  pixel*/


		return std::vector<float>();
	}

	float ImageManager::getPointHeight(float x, float y)
	{
		return 0.0f;
	}
	
}
