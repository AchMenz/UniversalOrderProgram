#include <sqlite3.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "DB.hpp"

DB::DB(const char* DatabaseName)
{
   rc = sqlite3_open(DatabaseName, &db);

   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }
}

DB::~DB()
{
}

int DB::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void DB::createTables(std::string sqlFromFile)
{
   
   char *sql;

   /* Create SQL statement */
   sql = (char*) sqlFromFile.c_str();
   
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stderr, "Table created successfully\n");
   }
}

void DB::closeDatabase()
{
   sqlite3_close(db);
   fprintf(stdout, "Database succesfully closed.\n");
}