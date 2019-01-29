#include "CoordinateConvert.h"

namespace JDGC {

	/**
	*  仿真场景平面坐标示意图,长宽为(x, y)	   图像uv坐标的长宽分别为(u,v)，图像的采样间隔分别是：
	*  p点归一化之后的（x1',y1')				du，dv(单位：毫米/像素）。
	*   x1'=x1/x								u=x1'*u/du + u0
	*	y1'=y1/y								v=y1'*v/dv + v0
	*   
	*											o0(0,0)
	* y |									   y |-----------------------> u
	*   |										 |
	*   |          . p(x1,y1)					 |
	*   |										 |			. p(x1,y1)
	*   |										 |
	*   |										 |
	*   |										 |
	*   |--------------------------> x			 |------------------------> x
	*											v (u0,v0)
	*/
	CoordinateConvert::CoordinateConvert()
	{
		_pUVCoordinate = new UVCoordinate;
		_pXYCoordinate = new XYCoordinate;
	}
	CoordinateConvert::~CoordinateConvert()
	{
		delete _pUVCoordinate;
		delete _pXYCoordinate;
	}
	void CoordinateConvert::convertXYToUV(double x, double y, int &u, int &v)
	{
		double x1 = x / _pXYCoordinate->xLength;
		double y1 = y / _pXYCoordinate->yLength;

		u = x1 * _pUVCoordinate->uLength / _pUVCoordinate->uResolution + _pXYCoordinate->u0;
		v = y1 * _pUVCoordinate->vLength / _pUVCoordinate->vResolution + _pXYCoordinate->v0;

	}
	void CoordinateConvert::getBlocksNo(int u, int v, int & xblocksNo, int & yblocksNo)
	{

	}
	void CoordinateConvert::initUVCoordinate(UVCoordinate uv)
	{
		_pUVCoordinate->uLength = uv.uLength;
		_pUVCoordinate->vLength = uv.vLength;
		_pUVCoordinate->uResolution = uv.uResolution;
		_pUVCoordinate->vResolution = uv.vResolution;
	}
	void CoordinateConvert::initUVCoordinate(UVCoordinate * puv)
	{
		_pUVCoordinate->uLength = puv->uLength;
		_pUVCoordinate->vLength = puv->vLength;
		_pUVCoordinate->uResolution = puv->uResolution;
		_pUVCoordinate->vResolution = puv->vResolution;
	}

	void CoordinateConvert::initXYCoordinate(XYCoordinate xy)
	{
		_pXYCoordinate->xLength = xy.xLength;
		_pXYCoordinate->yLength = xy.yLength;
		_pXYCoordinate->u0 = xy.u0;
		_pXYCoordinate->v0 = xy.v0;
	}
	void CoordinateConvert::initXYCoordinate(XYCoordinate * pxy)
	{
		_pXYCoordinate->xLength = pxy->xLength;
		_pXYCoordinate->yLength = pxy->yLength;
		_pXYCoordinate->u0 = pxy->u0;
		_pXYCoordinate->v0 = pxy->v0;
	}
}