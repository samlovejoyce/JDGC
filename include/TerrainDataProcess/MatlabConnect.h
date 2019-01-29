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
		/** 初始化matlab引擎环境 */
		bool openMatlabEngine();
		
		/** 关闭matlab引擎运行环境 */
		void closeMatlabEngine(); 
		
		/** 执行matlab命令 */
		bool runMatlabCmd(const std::string cmd);

		bool putVariable(const std::string name, const mxArray *mx);
		mxArray* getVariable(const std::string name);
		
		/** 获取matlab的engine指针 */
		Engine* getMatlabEngine() { return _engine; }
	private:
		static MatlabConnect *_instance;
		Engine* _engine;
	};
}
#endif // ! MATLABCONNECT_H

