#ifndef DB_HPP
#define DB_HPP

#include <sqlite3.h> 
#include <string>
#include <vector>
#include <map>

#include "Ware.h"

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


   //schließt die Datenbank
   void closeDatabase();


   //Inserts
   //fügt einen Datensatz in Warengruppe ein
   void insertRecordWarengruppe(std::string name, std::string kommentar = "");
   
   //fügt einen Datensatz in Ware ein
   void insertRecordWare(std::string name, std::string warengruppe);
   
   
   //Selects
   //gibt einen Vector aus allen Datensätzen des Typs "Warengruppe" aus der Datenbank zurück
   std::vector<std::string> getAlleWarengruppenFromDB();

   //gibt einen Vector aus allen Datensätzen des Typs "Ware" zurück
   std::vector<Ware> getAlleWarenFromDB();
   
   //ändert einen Wert in Ware
   void updatePreisProKg(std::string ware, std::string warengruppe, float preis = 0);

   //ändert einen Wert in Ware
   void updatePreisProSt(std::string ware, std::string warengruppe, float preis = 0);

   //ändert einen Wert in Ware
   void updateKommentar(std::string ware, std::string warengruppe, std::string kommentar);

};

#endif // DB_HPP
