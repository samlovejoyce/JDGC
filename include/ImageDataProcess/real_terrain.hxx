#ifndef REAL_TERRAIN_H
#define REAL_TERRAIN_H

#include <vector>
#include <string>

#include <odb/core.hxx>  // 1 header file

typedef std::vector<float> buffer;
#pragma db value(buffer) type("MEDIUMBLOB")

#pragma db object no_id	// 2 
class real_terrain
{
public:
	real_terrain(unsigned int xno, unsigned int yno, 
		/*unsigned int markno,*/ 
		unsigned short xsize,
		unsigned short ysize, buffer data) :xblocksno(xno), yblocksno(yno)
		/*, mark(markno)*/, xblocksize(xsize), yblocksize(ysize) {
		zdata.assign(data.begin(), data.end());
	}

	void setValue(unsigned int xno, unsigned int yno, 
		unsigned int markno, 
		unsigned short xsize,
		unsigned short ysize, buffer data)
	{
		xblocksno = xno;
		yblocksno = yno;
		/*mark = markno;*/
		xblocksize = xsize;
		yblocksize = ysize;
		zdata.swap(data);
	}

private:
	real_terrain() {}			// 3 
	friend class odb::access;	// 4 
	
	unsigned int xblocksno;
	unsigned int yblocksno;
	/*unsigned int mark;*/
	unsigned short xblocksize;
	unsigned short yblocksize;

	buffer zdata;

	/** ´´½¨Ë÷Òý */
#pragma db index("xIdx") method("BTREE") member(xblocksno, "DESC")
#pragma db index("yIdx") method("BTREE") member(yblocksno, "DESC")
};

#endif // !REAL_TERRAIN_H
