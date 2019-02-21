#include "DatabaseException.h"

namespace JDGC
{
	DatabaseException::DatabaseException(const std::string &initialMessage, const int errorno, const char *sqlState, const char *errorMessage)
	{
		_initialMessage = initialMessage;
		_sqlState = sqlState;
		_errorMessage = errorMessage;
		_errorno = errorno;
	}

	DatabaseException::DatabaseException(MYSQL *db, const std::string &initialMessage)
	{
		_errorno = mysql_errno(db);
		_errorMessage = mysql_error(db);
		_initialMessage = initialMessage;
		_sqlState = mysql_sqlstate(db);
	}

	DatabaseException::DatabaseException(MYSQL_STMT *stmt, const std::string &initialMessage)
	{
		_errorno = mysql_stmt_errno(stmt);
		_errorMessage = mysql_stmt_error(stmt);
		_initialMessage = initialMessage;
		_sqlState = mysql_stmt_sqlstate(stmt);
	}

	std::ostream &operator<<(std::ostream &out, const DatabaseException &exp)
	{
		// TODO: 在此处插入 return 语句
		out << exp._initialMessage.c_str() << " ERROR " << exp._errorno << "(" << exp._sqlState.c_str() << ") " << exp._errorMessage.c_str();
		return out;
	}
}