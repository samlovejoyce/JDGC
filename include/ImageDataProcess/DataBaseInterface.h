#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H
#include <Export.h>

#include <mysql.h>
#include <string>

namespace JDGC
{
#define MAX_DATA_LENGTH 128*128

	class JDCG_EXPORT_API DataBaseInterface
	{
	public:
		DataBaseInterface(std::string host,
		std::string user,
		std::string password,
		std::string database,
		unsigned int port = 0,
		const char *unixSocket = nullptr,
		unsigned long clientFlag = 0);

		DataBaseInterface(DataBaseInterface & db);
		
		~DataBaseInterface();

		bool isConnected() { return _isConnected; }

		void connect();

		int execute(const std::string& sql);
		
		
		int insert(int xNo, int yNo,const int xSize, const int ySize, float *data);
		int query(int x, int y);

		void commit();

	private:
		MYSQL *_db;

		std::string _host;
		std::string _user;
		std::string _password;
		std::string _database;
		//std::string _initialCommand;
		unsigned int _port;
		const char *_unixSocket;
		unsigned long _clientFlag;

		bool _isConnected;
	};
}



#endif // !DATABASEINTERFACE_H
