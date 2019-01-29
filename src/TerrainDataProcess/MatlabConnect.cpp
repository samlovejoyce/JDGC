#include "MatlabConnect.h"


using namespace JDGC;

MatlabConnect *MatlabConnect::_instance = nullptr;

MatlabConnect::MatlabConnect()
	:_engine(nullptr)
{
}

MatlabConnect::~MatlabConnect()
{
	closeMatlabEngine();
}

MatlabConnect * MatlabConnect::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new MatlabConnect();
	}
	return _instance;
}

bool MatlabConnect::openMatlabEngine()
{
	if (!_engine)
	{
		_engine = engOpen(nullptr);
		/* Òþ²ØMatlabÃüÁîÐÐ´°¿Ú */
		engSetVisible(_engine, true);
	}
	return true;
}

bool MatlabConnect::runMatlabCmd(const std::string cmd)
{
	if(engEvalString(_engine, cmd.c_str()) !=0 )
		return false;

	return true;
}

bool MatlabConnect::putVariable(const std::string name, const mxArray * mx)
{
	if( engPutVariable(_engine, name.c_str(), mx) != 0)
		return false;
	return true;
}

mxArray *MatlabConnect::getVariable(const std::string name)
{
	mxArray *mx = nullptr;
	mx = engGetVariable(_engine, name.c_str());
	if (!mx)
		return nullptr;
	return mx;
}

void MatlabConnect::closeMatlabEngine()
{
	if (_engine)
	{
		engClose(_engine);
		_engine = nullptr;
	}
}

