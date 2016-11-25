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

   //keine Ahnung was die Funktion macht
   static int callback(void *NotUsed, int argc, char **argv, char **azColName);

   //führt den SQL-Code aus
   static int executeSql(sqlite3 *db, char *sql, char *zErrMsg, int rc, std::string funktionsname);

   //erstellt Tabellen nach Maßgabe einer Sql-Datei
   void createTables(std::string sqlFromFile);

   //schließt die Datenbank
   void closeDatabase();
   
   //fügt einen Datensatz in Warengruppe ein
   void insertRecordWarengruppe(std::string name, std::string kommentar = "");
   
   //fügt einen Datensatz in Ware ein
   void insertRecordWare(std::string name, long id_warengruppe, std::string warennummer = "", std::string kommentar = "");
   
   //fügt einen Datensatz in Bestellung ein
   void insertRecordBestellung(std::string zieldatum, std::string zielzeit = "", std::string kommentar = "");
   
   //fügt einen Datensatz in Bestellung_Detail ein
   void insertRecordBestellungDetail(long id_ware, long id_bestellung, float menge_in_kg, float menge_in_stueck, float bestellpreis, std::string kommentar = "");
   
   //fügt einen Datensatz in Preis_History ein
   void insertRecordPreisHistory(long id_ware, std::string datum, float preis_pro_kg, float preis_pro_stueck, bool aktuell);
};

#endif // DB_HPP
