#ifndef REALTERRAIN_H
#define REALTERRAIN_H

#include <soci/soci.h>

struct TerrainBlock
{
	int xNo;
	int yNo;
	int xSize;
	int ySize;
	std::string zData;
};

namespace soci
{
	template<>
	struct type_conversion<TerrainBlock>
	{
		typedef values base_type;

		static void from_base(base_type const & in, indicator ind, TerrainBlock & out)
		{
			if (ind == i_null) return;
			out.xNo = in.get<int>("xblocksno");
			out.yNo = in.get<int>("yblocksno");
			out.xSize = in.get<int>("xblocksize");
			out.ySize = in.get<int>("yblocksize");
			out.zData = in.get<std::string>("zdata");
		}

		static void to_base(TerrainBlock const & in, base_type & out, indicator & ind)
		{
			out.set("xblocksno", in.xNo);
			out.set("yblocksno", in.yNo);
			out.set("xblocksize", in.xSize);
			out.set("yblocksize", in.ySize);
			out.set("zdata", in.zData);
			ind = i_ok;
		}
	};
}


class Session
{
public:
	Session(soci::session &sql):_session(sql) {}

	int insert(TerrainBlock tb);
	int insert(int xNo, int yNo, int xSize, int ySize, std::vector<float>data);
	int update(TerrainBlock tb);

	int query();

private:
	soci::session& _session;
};

#endif // !REALTERRAIN_H
