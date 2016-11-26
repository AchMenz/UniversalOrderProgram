#ifndef DB_HPP
#define DB_HPP

#include <sqlite3.h> 
#include <string>
#include <vector>
#include <map>

#include "Ware.hpp"
#include "Warengruppe.hpp"
#include "Preis_History.hpp"
#include "Bestellung.hpp"

class DB
{
public:

   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   const char* data = "Callback function called";

   DB(const char* DatabaseName);
   ~DB();

   //keine Ahnung, was die Funktion macht
   static int callback(void *NotUsed, int argc, char **argv, char **azColName);
   
   //keine Ahnung, was die Funktion macht
   static int callback_select(void *data, int argc, char **argv, char **azColName);

   //führt den SQL-Code aus (Insert)
   static void executeSqlInsert(sqlite3 *db, char *sql, char *zErrMsg, int rc, std::string funktionsname);
   
   //führt den SQL-Code aus (Select)
   static void executeSqlSelect(sqlite3 *db, char *sql, char *zErrMsg, int rc, const void* data, std::string funktionsname);

   //sucht zu einer ID die Ware, wenn die Warengruppe bekannt ist
   static std::string getWareNamePerID(long id, sqlite3 *db, char *zErrMsg, int rc, const void* data);


   //erstellt Tabellen nach Maßgabe einer Sql-Datei
   void createTables(std::string sqlFromFile);

   //schließt die Datenbank
   void closeDatabase();

   //Inserts
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
   
   

   //Selects
   //gibt einen Vector aus allen Datensätzen des Typs "Warengruppe" aus der Datenbank zurück
   std::vector<Warengruppe> getAlleWarengruppenFromDB();
   //void test();
   
   //gibt einen Vector aus allen Datensätzen des Typs "Ware" von einer Warengruppe aus der Datenbank zurück
   std::vector<Ware> getAlleWarenOfOneWarengruppeFromDB(std::string warengruppe);
   
   //gibt einen Vector aus allen Datensätzen des Typs "Preis_History" einer best. Warengruppe und optional einer einzelnen Ware zurück 
   std::vector<Preis_History> getAllePreiseOfOneWarengruppeAndOneWare(std::string warengruppe, std::string ware = "");
   
   //gibt einen Vector mit allen Bestellungen, oder nur eine bestimmten Datums zurück
   std::vector<Bestellung> getAlleBestellungenOrOne(std::string zieldatum = "");

   //gibt einen Vector mit allen Bestellungsdetails einer oder mehrerer Bestellung zurück
   //std::vector<Bestellung_Detail> getBestellungsdetailsOfOneBestellung(std::string zieldatum = "");

};

#endif // DB_HPP
