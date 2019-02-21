#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include "../common/Export.h"
#include "ImageDataProcess.h"
#include "DataBaseInterface.h"

#include <memory>	// std::auto_ptr

//#include <odb/database.hxx>
//#include <odb/transaction.hxx>
//#include <odb/mysql/database.hxx>
//
//#include "real_terrain.hxx"
//#include "real_terrain-odb.hxx"

namespace JDGC {
	class JDCG_EXPORT_API ImageManager
	{
	public:
		ImageManager();
		~ImageManager();

		/** 设置当前要是用的图片的路径 */
		void setImagePath(std::string path);

		/** 载入图片 */
		bool loadImage(std::string path);
		
		/** 图片数据访问 */
		void readImageData();

	private:
		ImageDataProcess *_pImageProcess;
		std::string curImagePath;

		DataBaseInterface *_db;
	};
}

#endif // !IMAGEMANAGER_H


