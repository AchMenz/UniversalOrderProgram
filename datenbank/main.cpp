#include <stdio.h>
#include <iostream>

#include "DB.hpp"
#include "Helper.hpp"

int main(int argc, char* argv[])
{
   //erstelle eine Datenbank oder verbinde mit einer schon bestehenden
   DB db("test.db");
   
   //lies SQL aus einer Datei ein und erstelle in der Datenbank entsprechende Tabellen
   //db.createTables(Helper::getSqlFromFile("db.sql"));
   
   //fügt einen Datensatz in Warengruppe ein
   //db.insertRecordWarengruppe("Reh", "Ein Tier, dass ein kleines Geweih trägt.");
   
   //fügt einen Datensatz in Ware ein
   //db.insertRecordWare("Haxe2", 1);

   //fügt einen Datensatz in Bestellung ein
   //db.insertRecordBestellung("2016-11-30", "10:15", "Bla Bla");

   //fügt einen Datensatz in Bestellung_Detail ein
   //db.insertRecordBestellungDetail(1,1,3.5,4.4,32.50,"Nicht gefrostet.");

   //fügte einen Datensatz in Preis_History ein
   //db.insertRecordPreisHistory(1,"2015-10-16", 12.30, 10, true);

   //schließ die Datenbank wieder
   db.closeDatabase();
}
