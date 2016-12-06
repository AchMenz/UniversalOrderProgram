#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "DB.h"

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
//Schleifenzählvariable für callback_select...-Durchläufe
int countDatasets = 0;

//static functions, only for intern use
int DB::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   return 0;
}

int DB::callback_select(void *data, int argc, char **argv, char **azColName, std::map <int, std::map<std::string, std::string> > queryResult)
{
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   
   //leere Tempmap
   temp.clear();
   for(i=0; i<argc; i++){
      //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      temp[azColName[i]] = (char*) (argv[i] ? argv[i] : "NULL");
   }
   
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
      fprintf(stderr, "SQL-Operation error in '%s'.\n", funktionsname.c_str());
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stderr, "SQL-Operation '%s' executed successfully\n", funktionsname.c_str());
	   //fprintf(stderr, "SQL-Insert: %s", sql);
   }
}

void DB::executeSqlSelect(sqlite3 *db, char *sql, char *zErrMsg, int rc, const void* data, std::string funktionsname, std::map <int, std::map<std::string, std::string> > queryResult)
{
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback_select(queryResult), (void*)data, &zErrMsg);
   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "SQL-Operation error in '%s'.\n", funktionsname.c_str());
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stderr,"SQL-Operation '%s' executed successfully\n", funktionsname.c_str());
	   fprintf(stderr, "SQL-Insert: %s", sql);
  }
   
   //stelle die Schleifenvariable wieder auf 0
   countDatasets = 0;
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

void DB::insertRecordInWarengruppe(std::string name, std::string kommentar)
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

void DB::insertRecordInWare(std::string name, std::string warengruppe)
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

void DB::insertRecordInAbsenderEmpfaenger(std::string tabelle, std::string name , std::string adresse, std::string emailadresse)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "INSERT INTO " + tabelle + " (Name, Adresse, Emailadresse) " \
             "VALUES ('" + name + "', '" + adresse + "', '" + emailadresse + "');";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();

   //erzeuge einen String mit dem Funktionsname, der executeSqlInsert übergeben wird
   std::string funktionsname(__func__);
   //führe Sql-Code aus
   executeSqlInsert(db, sql, zErrMsg, rc, funktionsname);
}

std::vector<std::string> DB::getAlleWarengruppenNamen()
{
   //hier werden die Abfrageresultate in einer globalen Variable zwischengespeichert (Value ist Map: temp)
   std::map <int, std::map<std::string, std::string> > queryResult;

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
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname, queryResult);
   
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
   queryResult.clear();
   return result;
}

std::vector<std::string> DB::getAlleEmpfaengerNamen()
{
   //hier werden die Abfrageresultate in einer globalen Variable zwischengespeichert (Value ist Map: temp)
   std::map <int, std::map<std::string, std::string> > queryResult;

   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "SELECT Name FROM Empfaenger ORDER BY Name";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   //Die globale Variable "queryResult" wird dadurch mit einer Map belegt.
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname, queryResult);
   
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
   queryResult.clear();
   return result;
}

std::vector<std::string> DB::getAlleAbsenderNamen()
{
   //hier werden die Abfrageresultate in einer globalen Variable zwischengespeichert (Value ist Map: temp)
   std::map <int, std::map<std::string, std::string> > queryResult;

   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "SELECT Name FROM Absender ORDER BY Name";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   //Die globale Variable "queryResult" wird dadurch mit einer Map belegt.
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname, queryResult);
   
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
   queryResult.clear();   
   return result;
}

std::vector<Empfaenger> DB::getAlleEmpfaenger()
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "SELECT * FROM Empfaenger ORDER BY Name;";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   //Die globale Variable "queryResult" wird dadurch mit einer Map belegt.
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname, queryResult);
   
   //hohle das query-result aus der globalen Variable queryResult
   //der Resultatvektor
   std::vector<Empfaenger> result;
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
      
      //erzeuge Objekte vom Typ Empfaenger aus der Zwischenspeichermap
      Empfaenger empfTemp(tempMap["Name"], tempMap["Emailadresse"], tempMap["Adresse"]);
      //füge Objekte zum Resultatvektor hinzu
      result.push_back(empfTemp);
   }
   queryResult.clear();   
   return result;
}

Empfaenger DB::getErstenEmpfaenger()
{
   //hier werden die Abfrageresultate in einer globalen Variable zwischengespeichert (Value ist Map: temp)
   std::map <int, std::map<std::string, std::string> > queryResult;

   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "SELECT * FROM Empfaenger ORDER BY Name;";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   //Die globale Variable "queryResult" wird dadurch mit einer Map belegt.
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname, queryResult);
   
   //hohle das query-result aus der globalen Variable queryResult
   //der Resultatvektor
   std::vector<Empfaenger> result;
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
      
      //erzeuge Objekte vom Typ Empfaenger aus der Zwischenspeichermap
      Empfaenger empfTemp(tempMap["Name"], tempMap["Emailadresse"], tempMap["Adresse"]);
      //füge Objekte zum Resultatvektor hinzu
      result.push_back(empfTemp);
   }
   queryResult.clear();   
   return result[0];
}

Absender DB::getErstenAbsender()
{
   //hier werden die Abfrageresultate in einer globalen Variable zwischengespeichert (Value ist Map: temp)
   std::map <int, std::map<std::string, std::string> > queryResult;

   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "SELECT * FROM Absender ORDER BY Name;";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   //Die globale Variable "queryResult" wird dadurch mit einer Map belegt.
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname, queryResult);
   
   //hohle das query-result aus der globalen Variable queryResult
   //der Resultatvektor
   std::vector<Absender> result;
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
      
      //erzeuge Objekte vom Typ Absender aus der Zwischenspeichermap
      Absender absTemp(tempMap["Name"], tempMap["Emailadresse"], tempMap["Adresse"]);
      //füge Objekte zum Resultatvektor hinzu
      result.push_back(absTemp);
   }
   queryResult.clear();   
   return result[0];
}

std::vector<Absender> DB::getAlleAbsender()
{
   //hier werden die Abfrageresultate in einer globalen Variable zwischengespeichert (Value ist Map: temp)
   std::map <int, std::map<std::string, std::string> > queryResult;

   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "SELECT * FROM Absender ORDER BY Name;";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   //Die globale Variable "queryResult" wird dadurch mit einer Map belegt.
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname, queryResult);
   
   //hohle das query-result aus der globalen Variable queryResult
   //der Resultatvektor
   std::vector<Absender> result;
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
      
      //erzeuge Objekte vom Typ Absender aus der Zwischenspeichermap
      Absender absTemp(tempMap["Name"], tempMap["Emailadresse"], tempMap["Adresse"]);
      //füge Objekte zum Resultatvektor hinzu
      result.push_back(absTemp);
   }
   queryResult.clear();
   return result;
}

std::vector<Ware> DB::getAlleWaren()
{
   //hier werden die Abfrageresultate in einer globalen Variable zwischengespeichert (Value ist Map: temp)
   std::map <int, std::map<std::string, std::string> > queryResult;

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
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname, queryResult);
   
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
      std::stof(tempMap["Preis_pro_kg"]), std::stof(tempMap["Preis_pro_St"]), std::stof(tempMap["Menge_in_kg"]), std::stof(tempMap["Menge_in_St"]), tempMap["Kommentar"]);
      //füge Objekte vom Typ Ware zum Resultatvektor hinzu
      result.push_back(wareTemp);
   }
   queryResult.clear();
   return result;
}

InfoBestellung DB::getErsteInfoBestellung()
{
   //hier werden die Abfrageresultate in einer globalen Variable zwischengespeichert (Value ist Map: temp)
   std::map <int, std::map<std::string, std::string> > queryResult;

   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "SELECT * FROM InfoBestellung;";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   //Die globale Variable "queryResult" wird dadurch mit einer Map belegt.
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname, queryResult);
   
   fprintf(stderr, "Haltepunkt1");
   
   //hohle das query-result aus der globalen Variable queryResult
   //der Resultatvektor
   std::vector<InfoBestellung> result;
   //eine Zwischenspeichermap
   std::map<std::string, std::string> tempMap;

   fprintf(stderr, "Haltepunkt2");

   fprintf(stderr, "Haltepunkt2 %s", queryResult.size());


   //durchlaufe queryResult
   for (auto const& dataset : queryResult)
   {
      fprintf(stderr, "Haltepunkt_Schleife_außen");
       
      //durchlaufe die Maps in queryResult
      for (auto const& valuesOfDataset : dataset.second)
      {
         //fülle die Zwischenspeichermap
         tempMap[valuesOfDataset.first] = valuesOfDataset.second;
      }
      
   fprintf(stderr, "Haltepunkt3");

      
      //erzeuge Objekte vom Typ Infobestellung aus der Zwischenspeichermap
      InfoBestellung Temp(tempMap["Zieldatum"], tempMap["Zielzeit"], tempMap["Kommentar"]);
      //füge Objekte zum Resultatvektor hinzu
      result.push_back(Temp);
   }
   queryResult.clear();   
   return result[0];
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

void DB::updateMengeInSt(std::string ware, std::string warengruppe, float mengeSt)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "UPDATE Ware SET Menge_in_St = " + std::to_string(mengeSt) + " \
             WHERE Name = '" + ware + "' AND Warengruppe = '" + warengruppe + "';";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname);
}

void DB::updateMengeInKg(std::string ware, std::string warengruppe, float mengeKg)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "UPDATE Ware SET Menge_in_kg = " + std::to_string(mengeKg) + " \
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

void DB::updateWerteInAbsenderEmpfaenger(std::string tabelle, std::string name, std::string feld, std::string wert)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "UPDATE " + tabelle + " SET " + feld + " = '" + wert + "' \
             WHERE Name = '" + name + "';";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname);
}

void DB::clearAllMengeFelder()
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "UPDATE Ware SET Menge_in_St = 0;" \
             "UPDATE Ware SET Menge_in_Kg = 0;";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname);
}

void DB::deleteWare(std::string ware, std::string warengruppe)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "DELETE FROM Ware WHERE Name = '" + ware + "' \
             AND Warengruppe = '" + warengruppe + "';";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname);
}

bool DB::warengruppeIsDeletable(std::string warengruppe)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "SELECT ID FROM Ware WHERE Warengruppe = '" + warengruppe + "';";

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
      
      //erzeuge Objekte vom Typ std::string aus der Zwischenspeichermap
      std::string IDTemp(tempMap["ID"]);
      //füge Objekte vom Typ std::string zum Resultatvektor hinzu
      result.push_back(IDTemp);
   }
   if (result.size() == 0)
   {
      //Die Warengruppe kann gelöscht werden, weil keine
      //Fremdschlüssel der Warengruppe mehr in der Tabelle "Ware" vorkommen.
      return true;
   }
   else
   {
      //Die Warengruppe kann nicht gelöscht werden, weil sie noch als
      //Fremdschlüssel in der Tabelle "Ware" auftaucht.
      return false;
   }
}

void DB::deleteWarengruppe(std::string warengruppe)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "DELETE FROM Warengruppe WHERE Name = '" + warengruppe + "';";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname);
}

void DB::deleteRecordInAbsenderEmpfaenger(std::string tabelle, std::string name)
{
   char *sql;
   
   //erstelle zunächst String-SQL-Anweisung
   std::string sqlPrae;
   //Pragma... Damit keine Fremdschlüssel eingetragen werden, die gar nicht existieren.
   sqlPrae = "PRAGMA foreign_keys = on;\n" \
             "DELETE FROM " + tabelle + " WHERE Name = '" + name + "';";

   //konvertiere sqlPrae in char*
   sql = (char*) sqlPrae.c_str();
   
   //erzeuge einen String mit dem Funktionsname, der executeSqlSelect übergeben wird
   std::string funktionsname(__func__);
   
   //führe Sql-Code aus
   executeSqlSelect(db, sql, zErrMsg, rc, data, funktionsname);
}