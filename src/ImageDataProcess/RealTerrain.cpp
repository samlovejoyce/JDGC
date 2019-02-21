#include "RealTerrain.h"
#include <iostream>

using namespace soci;

int Session::insert(TerrainBlock tb)
{
	try
	{
		_session << "insert into real_terrain values(:xblocksno, :yblocksno, :xbolcksize, :yblocksize, :zdata)",use(tb);

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}
	return 0;
}

int Session::insert(int xNo, int yNo, int xSize, int ySize, std::vector<float> data)
{
	try
	{
		_session << "insert into real_terrain values(:xblocksno, :yblocksno, :xbolcksize, :yblocksize, :zdata)", 
			use(xNo), use(yNo), use(xSize), use(ySize), use(data);

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}
	return 0;
}

int Session::update(TerrainBlock tb)
{
	return 0;
}

int Session::query()
{
	return 0;
}
