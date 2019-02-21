#ifndef DATABASEEXCEPTION_H
#define DATABASEEXCEPTION_H

#include <Export.h>

#include <string>
#include <mysql.h>

namespace JDGC {
	class JDCG_EXPORT_API DatabaseException
	{
	public:
		DatabaseException(const std::string &initialMessage, const int errorno, const char *sqlState, const char *errorMessage);
		DatabaseException(MYSQL *db, const std::string &initialMessage);
		DatabaseException(MYSQL_STMT *stmt, const std::string &initialMessage);

		/** friend function is not a member function of any class */
		friend std::ostream &operator<<(std::ostream &out, const DatabaseException &exp);

	private:
		int _errorno;
		std::string _sqlState;
		std::string _initialMessage;
		std::string _errorMessage;
	};
}
#endif // !DATABASEEXCEPTION_H
