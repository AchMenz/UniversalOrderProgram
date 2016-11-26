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
std::map <int, std::map<std::string, std::string>> queryResult;
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

std::string DB::getWareNamePerID(long id, sqlite3 *db, char *zErrMsg, int rc, const void* data)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "SELECT Name FROM Ware WHERE ID = " + std::to_string(id) + ";";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   //Die globale Variable "queryResult" wird dadurch mit einer Map belegt.
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname);
   
   return queryResult[0]["Name"];
}

//instance functions
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

   //erzeuge einen String mit dem Funktionsname, der executeSqlInsert übergeben wird
   std::string funktionsname(__func__);
   //führe Sql-Code aus
   executeSqlInsert(db, sql, zErrMsg, rc, funktionsname);
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

   //erzeuge einen String mit dem Funktionsname, der executeSqlInsert übergeben wird
   std::string funktionsname(__func__);
   //führe Sql-Code aus
   executeSqlInsert(db, sql, zErrMsg, rc, funktionsname);
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
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlInsert übergeben wird
   std::string funktionsname(__func__);
   //führe Sql-Code aus
   executeSqlInsert(db, sql, zErrMsg, rc, funktionsname);
}

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

   //erzeuge einen String mit dem Funktionsname, der executeSqlInsert übergeben wird
   std::string funktionsname(__func__);
   //führe Sql-Code aus
   executeSqlInsert(db, sql, zErrMsg, rc, funktionsname);
}

void DB::insertRecordPreisHistory(long id_ware, std::string datum, float preis_pro_kg, float preis_pro_stueck, bool aktuell)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "INSERT INTO Preis_History (ID_Ware, ID_Warengruppe, Datum, Preis_pro_kg, Preis_pro_Stueck, Aktuell) " \
             "VALUES (" + std::to_string(id_ware) + ", '" + datum + "', " \
             + std::to_string(preis_pro_kg) + ", " + std::to_string(preis_pro_stueck) + ", " \
             + std::to_string(aktuell) + ");";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();

   //erzeuge einen String mit dem Funktionsname, der executeSqlInsert übergeben wird
   std::string funktionsname(__func__);
   //führe Sql-Code aus
   executeSqlInsert(db, sql, zErrMsg, rc, funktionsname);
}

std::vector<Warengruppe> DB::getAlleWarengruppenFromDB()
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "SELECT * FROM Warengruppe";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   //Die globale Variable "queryResult" wird dadurch mit einer Map belegt.
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname);
   
   //hohle das query-result aus der globalen Variable queryResult
   //der Resultatvektor
   std::vector<Warengruppe> result;
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
      
      //erzeuge Objekte vom Typ Warengruppe aus der Zwischenspeichermap
      Warengruppe warengruppeTemp(std::stol(tempMap["ID"]), tempMap["Name"], tempMap["Kommentar"]);
      //füge Objekte vom Typ Warengruppe zum Resultatvektor hinzu
      result.push_back(warengruppeTemp);
   }
   return result;
}

std::vector<Ware> DB::getAlleWarenOfOneWarengruppeFromDB(std::string warengruppe)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "SELECT * FROM Ware WHERE ID_Warengruppe = (Select ID From Warengruppe WHERE Name = '" + warengruppe + "');";

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
      Ware wareTemp(std::stol(tempMap["ID"]), tempMap["Name"], warengruppe, 4.5, 6.7, tempMap["Warennummer"], tempMap["Kommentar"]);
      //füge Objekte vom Typ Ware zum Resultatvektor hinzu
      result.push_back(wareTemp);
   }
   return result;
}

std::vector<Preis_History> DB::getAllePreiseOfOneWarengruppeAndOneWare(std::string warengruppe, std::string ware)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   
   if (ware == "")
   //Es wurde keine Ware angegeben.
   {
      //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
      sqlPrae = "PRAGMA foreign_keys = on;\n" \
                "SELECT * FROM Preis_History WHERE ID_Warengruppe = (Select ID From Warengruppe WHERE Name = '" + warengruppe + "');";
   }
   else
   //Es wurde eine Ware angegeben.
   {
      //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
      sqlPrae = "PRAGMA foreign_keys = on;\n" \
                "SELECT * FROM Preis_History WHERE ID_Warengruppe = (Select ID From Warengruppe WHERE Name = '" + warengruppe + \
                "') AND ID_Ware = (Select ID From Ware WHERE Name = '" + ware + "');";
   }

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   //Die globale Variable "queryResult" wird dadurch mit einer Map belegt.
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname);
   
   //hohle das query-result aus der globalen Variable queryResult
   //der Resultatvektor
   std::vector<Preis_History> result;
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
      
      //erzeuge Objekte vom Typ Preis_History aus der Zwischenspeichermap
      Preis_History preisTemp(std::stol(tempMap["ID"]), getWareNamePerID(std::stol(tempMap["ID_Ware"]), db, zErrMsg, rc, data), warengruppe, tempMap["Datum"], std::stoi(tempMap["Aktuell"]), std::stof(tempMap["Preis_pro_kg"]), std::stof(tempMap["Preis_pro_Stueck"]));
      //füge Objekte vom Typ Preis_History zum Resultatvektor hinzu
      result.push_back(preisTemp);
   }
   return result;
}

std::vector<Bestellung> DB::getAlleBestellungenOrOne(std::string zieldatum)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   
   if (zieldatum == "")
   //Es wurde kein Datum angegeben. Gib alle Bestellungen aus.
   {
      //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
      sqlPrae = "PRAGMA foreign_keys = on;\n" \
                "SELECT * FROM Bestellung;";
   }
   else
   //Es wurde ein Datum angegeben. Gib nur die Bestellungen für dieses Datum aus.
   {
      //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
      sqlPrae = "PRAGMA foreign_keys = on;\n" \
                "SELECT * FROM Bestellung WHERE Zieldatum = '" + zieldatum + "';";
   }

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   //Die globale Variable "queryResult" wird dadurch mit einer Map belegt.
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname);
   
   //hohle das query-result aus der globalen Variable queryResult
   //der Resultatvektor
   std::vector<Bestellung> result;
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
      
      //erzeuge Objekte vom Typ Bestellung aus der Zwischenspeichermap
      Bestellung bestellTemp(std::stol(tempMap["ID"]), tempMap["Name"], tempMap["Zieldatum"], tempMap["Zielzeit"], tempMap["Kommentar"]);
      //füge Objekte vom Typ Bestellung zum Resultatvektor hinzu
      result.push_back(bestellTemp);
   }
   return result;
}