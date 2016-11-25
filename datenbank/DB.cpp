#include <sqlite3.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

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

int DB::executeSql(sqlite3 *db, char* sql, char *zErrMsg, int rc, std::string funktionsname)
{
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return 1;
   }
   else
   {
      fprintf(stderr, "SQL-Operation '%s' executed successfully\n", funktionsname.c_str());
      return 0;
   }
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

void DB::insertRecordWarengruppe(std::string name, std::string kommentar)
{
   char *sql;
   
   //Alle Varchar(n) Felder in  SQLite werden automatisch zum Datentyp "Text",
   //der unendlich viele Zeichen aufnimmt. Das n spielt also keine Rolle.
   //Die Strings können so lang sein, wie irgend möglich. Es muss nicht auf
   //Länge geprüft werden.
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "INSERT INTO Warengruppe (Name, Kommentar) " \
             "VALUES ('" + name + "', '" + kommentar + "');";
   
   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();

   //erzeuge einen String mit dem Funktionsname, der executeSql übergeben wird
   std::string funktionsname(__func__);
   //führe Sql-Code aus
   executeSql(db, sql, zErrMsg, rc, funktionsname);
}

void DB::insertRecordWare(std::string name, long id_warengruppe, std::string warennummer, std::string kommentar)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "INSERT INTO Ware (Name, ID_Warengruppe, Warennummer, Kommentar) " \
             "VALUES ('" + name + "', " + std::to_string(id_warengruppe) + "," \
             " '" + warennummer + "', '" + kommentar + "');";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();

   //erzeuge einen String mit dem Funktionsname, der executeSql übergeben wird
   std::string funktionsname(__func__);
   //führe Sql-Code aus
   executeSql(db, sql, zErrMsg, rc, funktionsname);
}

void DB::insertRecordBestellung(std::string zieldatum, std::string zielzeit, std::string kommentar)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "INSERT INTO Bestellung (Zieldatum, Zielzeit, Kommentar) " \
             "VALUES ('" + zieldatum + "', '" + zielzeit + "'," \
             " '" + kommentar + "');";
   
   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSql übergeben wird
   std::string funktionsname(__func__);
   //führe Sql-Code aus
   executeSql(db, sql, zErrMsg, rc, funktionsname);
}

//fügt einen Datensatz in Bestellung_Detail ein...
void DB::insertRecordBestellungDetail(long id_ware, long id_bestellung, float menge_in_kg, float menge_in_stueck, float bestellpreis, std::string kommentar)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "INSERT INTO Bestellung_Detail (ID_Ware, ID_Bestellung, Menge_in_kg, Menge_in_Stueck, Bestellpreis, Kommentar) " \
             "VALUES (" + std::to_string(id_ware) + "," + std::to_string(id_bestellung) + ", " \
             + std::to_string(menge_in_kg) + ", " + std::to_string(menge_in_stueck) + ", " \
             + std::to_string(bestellpreis) + ", '" + kommentar + "');";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();

   //erzeuge einen String mit dem Funktionsname, der executeSql übergeben wird
   std::string funktionsname(__func__);
   //führe Sql-Code aus
   executeSql(db, sql, zErrMsg, rc, funktionsname);
}

void DB::insertRecordPreisHistory(long id_ware, std::string datum, float preis_pro_kg, float preis_pro_stueck, bool aktuell)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "INSERT INTO Preis_History (ID_Ware, Datum, Preis_pro_kg, Preis_pro_Stueck, Aktuell) " \
             "VALUES (" + std::to_string(id_ware) + ", '" + datum + "', " \
             + std::to_string(preis_pro_kg) + ", " + std::to_string(preis_pro_stueck) + ", " \
             + std::to_string(aktuell) + ");";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();

   //erzeuge einen String mit dem Funktionsname, der executeSql übergeben wird
   std::string funktionsname(__func__);
   //führe Sql-Code aus
   executeSql(db, sql, zErrMsg, rc, funktionsname);
}
