#ifndef COORDINATECONVERT_H
#define COORDINATECONVERT_H

#include "common/Export.h"

namespace JDGC {

	struct UVCoordinate {
		int uLength;
		int vLength;
		float uResolution;
		float vResolution;
	};

	struct XYCoordinate {
		float xLength;
		float yLength;
		int u0;
		int v0;
	};

	class JDCG_EXPORT_API CoordinateConvert
	{
	public:
		CoordinateConvert();
		~CoordinateConvert();

		void convertXYToUV(double x, double y, int &u, int &v);
		void getBlocksNo(int u, int v, int &xblocksNo, int &yblocksNo);

		void initUVCoordinate(UVCoordinate uv);
		void initUVCoordinate(UVCoordinate* puv);
		
		void initXYCoordinate(XYCoordinate xy);
		void initXYCoordinate(XYCoordinate* pxy);

	private:

		UVCoordinate *_pUVCoordinate;
		XYCoordinate *_pXYCoordinate;
	};
}
#endif // !COORDINATECONVERT_H
