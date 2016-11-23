#ifndef DB_HPP
#define DB_HPP

#include <sqlite3.h> 
#include <string>

class DB
{
public:

   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

   DB(const char* DatabaseName);
   ~DB();

   static int callback(void *NotUsed, int argc, char **argv, char **azColName);

   void createTables(std::string sqlFromFile);
   void closeDatabase();
};

#endif // DB_HPP
