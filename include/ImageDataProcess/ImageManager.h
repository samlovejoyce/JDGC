#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include "../common/Export.h"
#include "ImageDataProcess.h"

#include <memory>	// std::auto_ptr

#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/mysql/database.hxx>

#include "real_terrain.hxx"
#include "real_terrain-odb.hxx"

namespace JDGC {
	class JDCG_EXPORT_API ImageManager
	{
	public:
		ImageManager();
		~ImageManager();

		/** ���õ�ǰҪ���õ�ͼƬ��·�� */
		void setImagePath(std::string path);

		/** ����ͼƬ */
		bool loadImage(std::string path);
		
		/** ͼƬ���ݷ��� */
		void readImageData();

		/** ͼƬ���ݴ洢 */
		void storeData(float *pdata, int xno, int yno, int xsize, int ysize);

		std::vector<float> getDataBlock(float x, float y);

		float getPointHeight(float x, float y);

	private:
		ImageProcess *_pImageProcess;
		std::string curImagePath;

		std::auto_ptr<odb::database> db;
	};
}

#endif // !IMAGEMANAGER_H


