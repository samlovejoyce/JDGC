#include <iostream>

#include "ImageManager.h"

//#define SOCI_TEST 0

#ifdef SOCI_TEST
#include <SOCI/soci.h>

struct RealTerrain {
	int xBlocksNo;
	int yBlocksNo;
	short xBlockSize;
	short yBlockSize;
	std::vector<std::string> zData;
};
namespace soci
{
	template<>
	struct type_conversion<RealTerrain>
	{
		typedef values base_type;
		static void from_base(const values &v, indicator ind, RealTerrain &realTerrain)
		{
			realTerrain.xBlocksNo = v.get<int>("xblocksno");
			realTerrain.yBlocksNo = v.get<int>("yblocksno");
			realTerrain.xBlockSize = v.get<short>("xblocksize");
			realTerrain.yBlockSize = v.get<short>("yblocksize");
			realTerrain.zData = v.get<std::vector<std::string>>("zdata");
		}

		static void to_base(const RealTerrain& realTerrain, values& v, indicator& ind)
		{
			v.set("xblocksno", realTerrain.xBlocksNo);
			v.set("yblocksno", realTerrain.yBlocksNo);
			v.set("xblocksize", realTerrain.xBlockSize);
			v.set("yblocksize", realTerrain.yBlockSize);
			v.set("zdata", realTerrain.zData);
		}

		int insert(int xno, int yno, short xsize, short ysize, std::vector<std::string> data)
		{

		}
	};

}


#endif // SOCI_TEST



void testImageProcess()
{
	JDGC::ImageManager *pImage = new JDGC::ImageManager();
	pImage->readImageData();
}

int main()
{
	testImageProcess();
	//getchar();
	return 0;
}