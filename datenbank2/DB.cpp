#include <stdio.h>
#include <stdlib.h>
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

//hier werden die Werte für queryResult zwischengespeichert
std::map <std::string, std::string> temp;
//hier werden die Abfrageresultate in einer globalen Variable zwischengespeichert (Value ist Map: temp)
std::map <int, std::map<std::string, std::string> > queryResult;
//Schleifenzählvariable für callback_select...-Durchläufe
int countDatasets = 0;

//static functions, only for intern use
int DB::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int DB::callback_select(void *data, int argc, char **argv, char **azColName)
{
   int i;
   //fprintf(stderr, "%s: ", (const char*)data);
   
   //leere Tempmap
   temp.clear();
   for(i=0; i<argc; i++){
      //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      temp[azColName[i]] = (char*) (argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   
   //füge das Tempmap zur Ergebnismap hinzu
   queryResult[countDatasets] = temp;

   //zähle die Schleifenvariable hoch
   countDatasets++;
   return 0;
}

void DB::executeSqlInsert(sqlite3 *db, char* sql, char *zErrMsg, int rc, std::string funktionsname)
{
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stderr, "SQL-Operation '%s' executed successfully\n", funktionsname.c_str());
   }
}

void DB::executeSqlSelect(sqlite3 *db, char *sql, char *zErrMsg, int rc, const void* data, std::string funktionsname)
{
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback_select, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stderr,"SQL-Operation '%s' executed successfully\n", funktionsname.c_str());
   }
   
   //stelle die Schleifenvariable wieder auf 0
   countDatasets = 0;
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

   //erzeuge einen String mit dem Funktionsname, der executeSqlInsert übergeben wird
   std::string funktionsname(__func__);
   //führe Sql-Code aus
   executeSqlInsert(db, sql, zErrMsg, rc, funktionsname);
}

void DB::insertRecordWare(std::string name, std::string warengruppe)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "INSERT INTO Ware (Name, Warengruppe, Preis_pro_kg, Preis_pro_St) " \
             "VALUES ('" + name + "', '" + warengruppe + "', 0, 0);";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();

   //erzeuge einen String mit dem Funktionsname, der executeSqlInsert übergeben wird
   std::string funktionsname(__func__);
   //führe Sql-Code aus
   executeSqlInsert(db, sql, zErrMsg, rc, funktionsname);
}

std::vector<std::string> DB::getAlleWarengruppenFromDB()
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "SELECT Name FROM Warengruppe ORDER BY Name";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   //Die globale Variable "queryResult" wird dadurch mit einer Map belegt.
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname);
   
   //hohle das query-result aus der globalen Variable queryResult
   //der Resultatvektor
   std::vector<std::string> result;
   //eine Zwischenspeichermap
   std::map<std::string, std::string> tempMap;
   //durchlaufe queryResult
   for (auto const& dataset : queryResult)
   {
      //durchlaufe die Maps in queryResult
      for (auto const& valuesOfDataset : dataset.second)
      {
         //fülle die Zwischenspeichermap
         tempMap[valuesOfDataset.first] = valuesOfDataset.second;
      }
      //füge Strings "Name" zum Resultatvektor hinzu
      result.push_back(tempMap["Name"]);
   }
   return result;
}

std::vector<Ware> DB::getAlleWarenFromDB()
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "SELECT * FROM Ware ORDER BY Warengruppe, Name;";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   //Die globale Variable "queryResult" wird dadurch mit einer Map belegt.
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname);
   
   //hohle das query-result aus der globalen Variable queryResult
   //der Resultatvektor
   std::vector<Ware> result;
   //eine Zwischenspeichermap
   std::map<std::string, std::string> tempMap;
   //durchlaufe queryResult
   for (auto const& dataset : queryResult)
   {
      //durchlaufe die Maps in queryResult
      for (auto const& valuesOfDataset : dataset.second)
      {
         //fülle die Zwischenspeichermap
         tempMap[valuesOfDataset.first] = valuesOfDataset.second;
      }
      
      //erzeuge Objekte vom Typ Ware aus der Zwischenspeichermap
      Ware wareTemp(tempMap["Name"], tempMap["Warengruppe"], \
      std::stof(tempMap["Preis_pro_kg"]), std::stof(tempMap["Preis_pro_St"]), 0, 0, tempMap["Kommentar"]);
      //füge Objekte vom Typ Ware zum Resultatvektor hinzu
      result.push_back(wareTemp);
   }
   return result;
}

void DB::updatePreisProKg(std::string ware, std::string warengruppe, float preis)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "UPDATE Ware SET Preis_pro_kg = " + std::to_string(preis) + " \
             WHERE Name = '" + ware + "' AND Warengruppe = '" + warengruppe + "';";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname);
}

void DB::updatePreisProSt(std::string ware, std::string warengruppe, float preis)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "UPDATE Ware SET Preis_pro_St = " + std::to_string(preis) + " \
             WHERE Name = '" + ware + "' AND Warengruppe = '" + warengruppe + "';";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname);
}

void DB::updateKommentar(std::string ware, std::string warengruppe, std::string kommentar)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "UPDATE Ware SET Kommentar = '" + kommentar + "' \
             WHERE Name = '" + ware + "' AND Warengruppe = '" + warengruppe + "';";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname);
}