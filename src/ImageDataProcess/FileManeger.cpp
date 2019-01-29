#include "FileManeger.h"
#include <io.h>

namespace JDGC
{
	FileManeger::FileManeger()
	{
	}


	FileManeger::~FileManeger()
	{
		_files.clear();
	}

	FileManeger::FileManeger(const std::string path)
	{
		getFiles(path, _files);
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/11
	* 功能描述: 获取指定位置的文件名称
	************************************************************************************/
	std::string FileManeger::getFileName(const int nIndex)
	{
		if (_files.size() == 0)
			return nullptr;
		return _files.at(nIndex);
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/11
	* 功能描述: 获取文件中文件的数量
	************************************************************************************/
	int FileManeger::getFileCount() const
	{
		return _files.size();
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/11
	* 功能描述: 设置文件夹路径
	************************************************************************************/
	void FileManeger::setFilePath(std::string path)
	{
		getFiles(path, _files);
	}

	void FileManeger::setFilePath(std::string path, std::string filespec)
	{
		getFiles(path, _files, filespec);
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/11
	* 功能描述: 获取某一文件夹下的所有文件
	************************************************************************************/
	void FileManeger::getFiles(std::string path, std::vector<std::string>& files)
	{
		//文件句柄
		long hFile = -1;
		struct _finddata_t fileInfo;
		std::string p;
		std::string temppath = p.assign(path).append("/*");

		hFile = _findfirst(temppath.c_str(), &fileInfo);
		if (hFile != -1)
		{
			do
			{
				if ((fileInfo.attrib & _A_SUBDIR))
				{
					if (strcmp(fileInfo.name, ".") != 0 && strcmp(fileInfo.name, "..") != 0)
					{
						temppath = p.assign(path).append("\\").append(fileInfo.name);
						getFiles(temppath, files);
						printf("%s\n", fileInfo.name);
					}
				}
				else
				{
					files.push_back(p.assign(path).append("\\").append(fileInfo.name));
					printf("%s\n", fileInfo.name);
				}
			} while (_findnext(hFile, &fileInfo) == 0);
			_findclose(hFile);
		}
	}

	/************************************************************************************
	* Copyright (c) year All Rights Reserved.
	* 命名空间：rootnamespace
	* 创建人： 0XFFFFFFFF
	* 创建时间：2019/01/11
	* 功能描述: 获取某一文件夹下指定后缀的所有文件(例如：".tif", ".png"...)
	************************************************************************************/
	void FileManeger::getFiles(std::string path, std::vector<std::string>& files, std::string filespec)
	{
		//文件句柄
		long hFile = -1;
		struct _finddata_t fileInfo;
		std::string p;
		std::string temppath = p.assign(path).append("/*");

		hFile = _findfirst(temppath.c_str(), &fileInfo);
		if (hFile != -1)
		{
			do
			{
				if ((fileInfo.attrib & _A_SUBDIR))
				{
					if (strcmp(fileInfo.name, ".") != 0 && strcmp(fileInfo.name, "..") != 0)
					{
						temppath = p.assign(path).append("\\").append(fileInfo.name);
						getFiles(temppath, files);
						printf("%s\n", fileInfo.name);
					}
				}
				else
				{
					std::string temp = fileInfo.name;
					if (temp.find(filespec.c_str()) != std::string::npos)
					{
						files.push_back(p.assign(path).append("\\").append(fileInfo.name));
						printf("%s\n", fileInfo.name);
					}
				}
			} while (_findnext(hFile, &fileInfo) == 0);
			_findclose(hFile);
		}
	}

}
