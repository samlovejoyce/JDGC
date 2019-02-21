#include "DataBaseInterface.h"
#include "DatabaseException.h"

namespace JDGC
{
	DataBaseInterface::DataBaseInterface(std::string host, 
		std::string user, 
		std::string password, 
		std::string database, 
		unsigned int port, 
		const char * unixSocket, 
		unsigned long clientFlag)
	{
		_host = host;
		_user = user;
		_password = password;
		_database = database;
		_port = port;
		_unixSocket = unixSocket;
		_clientFlag = clientFlag;

		_isConnected = false;
	}
	DataBaseInterface::DataBaseInterface(DataBaseInterface & db)
	{
		_host = db._host;
		_user = db._user;
		_password = db._password;
		_database = db._database;
		_port = db._port;
		_unixSocket = db._unixSocket;
		_clientFlag = db._clientFlag;

		_isConnected = db._isConnected;

		if ((_db = mysql_init(NULL)) == NULL)
			throw DatabaseException("Error tryng to initialize MYSQL database", 0, "------", "insufficient memory");

		if (db._isConnected)
		{
			try
			{
				connect();
			}
			catch (DatabaseException &)
			{
				mysql_close(_db);
				throw;
			}
		}
	}
	
	DataBaseInterface::~DataBaseInterface()
	{
		mysql_close(_db);
	}
	
	void DataBaseInterface::connect()
	{
		//printf("MySQL client version: %s\n", mysql_get_client_info());
		if ((_db = mysql_init((MYSQL*)NULL)) == NULL)
			throw DatabaseException("Error tryng to initialize MYSQL database", 0, "------", "insufficient memory");

		if (_host == "")
		{
			if (mysql_real_connect(_db, NULL, NULL, NULL, _database.c_str(), 0, NULL, 0) == NULL)
				throw DatabaseException(_db, "Error in Database::Connect");
		}
		else
		{
			if (mysql_real_connect(_db, _host.c_str(), _user.c_str(), _password.c_str(), _database.c_str(), _port, _unixSocket, _clientFlag) == NULL)
				throw DatabaseException(_db, "Error in Database::Connect");
		}

		_isConnected = true;
		if (mysql_set_character_set(_db, "utf8") != 0)
		{
			throw DatabaseException(_db, "Error in Database::Connect");
		}
	}
	
	int DataBaseInterface::execute(const std::string& sql)
	{
		if (mysql_query(_db, sql.c_str()) != 0)
			throw DatabaseException(_db, "Error in Database::Execute");

		MYSQL_RES *result = mysql_store_result(_db);
		if (result != NULL)
		{
			mysql_free_result(result);
			throw DatabaseException("Error in Database::Execute", 0, "-----", "statements passed to execute should never return results.");
		}

		return mysql_affected_rows(_db);
	}

	int DataBaseInterface::insert(int xNo, int yNo, const int xSize, const int ySize, float * data)
	{
		char sql[MAX_DATA_LENGTH * sizeof(float) * 2 + 1024];
		char *end = nullptr;
		sprintf(sql, "INSERT INTO real_terrain VALUES (%d,%d,%d,%d,", xNo, yNo, xSize, ySize);
		end = sql + strlen(sql);
		*end++ = '\'';
		end += mysql_real_escape_string(_db, end, (char*)data, (sizeof(float) * xSize * ySize) );
		*end++ = '\'';
		*end++ = ')';

		unsigned long len = (unsigned long)(end - sql);
		if (mysql_real_query(_db, sql, len))
		{
			printf("%s", mysql_error(_db));
			return -1;
		}			
		return 0;
	}
	
	
	int DataBaseInterface::query(int x, int y)
	{
		MYSQL_RES *result = nullptr;
		MYSQL_ROW row;
		float *zdata = nullptr;

		char *sql = new char[256];		
		sprintf(sql, "SELECT * FROM real_terrain WHERE xblocksno = %f AND yblocksno = %f;", x, y);
		if (mysql_real_query(_db, sql, strlen(sql)))
		{
			fprintf(stderr, "%s\n", mysql_error(_db));
			return -1;
		}

		if (result = mysql_store_result(_db))
		{
			fprintf(stderr, "%s\n", mysql_error(_db));
			return -1;
		}
	
		int fieldsNum = mysql_num_fields(result);
		while ((row = mysql_fetch_row(result)) )
		{
			int xsize = atoi(row[2]);
			int ysize = atoi(row[3]);

			zdata = new float[xsize * ysize];
			memcpy(zdata, row[4], sizeof(float) * xsize * ysize);
		}

		mysql_free_result(result);
		return 0;
	}

	void DataBaseInterface::commit()
	{
		if (mysql_query(_db, "COMMIT") != 0)
			throw DatabaseException(_db, "Error in Database::Commit");
	}
}

