#ifndef MATLABCONNECT_H
#define MATLABCONNECT_H

#include "common/Export.h"
#include "common/common.h"

#include <engine.h>
#include <string>

namespace JDGC {

	class JDCG_EXPORT_API MatlabConnect
	{
		MatlabConnect();
	public:
		~MatlabConnect();

	public:

		static MatlabConnect *getInstance();
		/** ��ʼ��matlab���滷�� */
		bool openMatlabEngine();
		
		/** �ر�matlab�������л��� */
		void closeMatlabEngine(); 
		
		/** ִ��matlab���� */
		bool runMatlabCmd(const std::string cmd);

		bool putVariable(const std::string name, const mxArray *mx);
		mxArray* getVariable(const std::string name);
		
		/** ��ȡmatlab��engineָ�� */
		Engine* getMatlabEngine() { return _engine; }
	private:
		static MatlabConnect *_instance;
		Engine* _engine;
	};
}
#endif // ! MATLABCONNECT_H

