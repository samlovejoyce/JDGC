#ifndef FILEMANEGER_H
#define FILEMANEGER_H

#include "common/Export.h"

#include <vector>
#include <string>

namespace JDGC
{
	class JDCG_EXPORT_API FileManeger
	{
	public:
		FileManeger();
		~FileManeger();

		FileManeger(const std::string path);

		std::string getFileName(const int nIndex);

		int getFileCount() const;
		void setFilePath(std::string path);
		void setFilePath(std::string path, std::string filespec);


	protected:
		void getFiles(std::string path, std::vector<std::string> &files);
		void getFiles(std::string path, std::vector<std::string> &files, std::string filespec);

	private:
		std::vector<std::string> _files;
	};
}
#endif // !FILEMANEGER_H

