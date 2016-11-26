#include <stdio.h>
#include <iostream>

#include "DB.hpp"
#include "Helper.hpp"

#include <string>
#include <vector>


#include "Bestellung_Detail.hpp"

int main(int argc, char* argv[])
{
   //erstelle eine Datenbank oder verbinde mit einer schon bestehenden
   DB db("test.db");
   
   //lies SQL aus einer Datei ein und erstelle in der Datenbank entsprechende Tabellen
   //db.createTables(Helper::getSqlFromFile("db.sql"));
   
   
   //Inserts
   
   //fügt einen Datensatz in Warengruppe ein
   //db.insertRecordWarengruppe("Reh");
   
   //fügt einen Datensatz in Ware ein
   //db.insertRecordWare("Haxe2", 1);

   //fügt einen Datensatz in Bestellung ein
   //db.insertRecordBestellung("2016-12-05", "10:15", "Bitte rote Kisten mitgeben.");

   //fügt einen Datensatz in Bestellung_Detail ein
   //db.insertRecordBestellungDetail(2,5,3.5,4.4,32.50,"Nicht gefrostet.");

   //fügte einen Datensatz in Preis_History ein
   //db.insertRecordPreisHistory(1, 2, "2015-10-16", 12.30, 10, true);

   
   //Selects
   
   //gibt alle Warengruppen zurück
//   std::vector<Warengruppe> testVectWarengruppe = db.getAlleWarengruppenFromDB();
//   for (Warengruppe i : testVectWarengruppe)
//   {
//      std::cout << i.l_id << ", " << i.s_name << ", " << i.s_kommentar << std::endl;
//   }

   //gibt alle Waren einer Warengruppe aus
//   std::vector<Ware> testVectWare = db.getAlleWarenOfOneWarengruppeFromDB("Reh");
//   for (Ware i : testVectWare)
//   {
//      std::cout << i.l_id << ", " << i.s_name << ", " << i.s_warengruppe << ", " << i.f_preis_pro_kg << \
//      ", " << i.f_preis_pro_stueck << ", " << i.s_warennummer << ", " << i.s_kommentar <<  std::endl;
//   }

   //gibt alle Preise einer Warengruppe und optional einer Ware an
//   std::vector<Preis_History> testVectPreis = db.getAllePreiseOfOneWarengruppeAndOnePreis("Hirsch");
//   for (Preis_History i : testVectPreis)
//   {
//      std::cout << i.l_id << ", " << i.s_ware << ", " << i.s_warengruppe << ", " << i.s_datum << \
//      ", " << i.b_aktuell << ", " << i.f_preis_pro_kg << ", " << i.f_preis_pro_stueck <<  std::endl;
//   }

   //gibt alle Bestellungen aus oder nur solche bestimmten Datums
//   std::vector<Bestellung> testVectBestellung = db.getAlleBestellungenOrOne("2016-11-30");
//   for (Bestellung i : testVectBestellung)
//   {
//      std::cout << i.l_id << ", " << i.s_zieldatum << ", " << i.s_zielzeit << ", " << i.s_kommentar << std::endl;
//   }

   Bestellung_Detail test(5, "ware", "warengruppe", 2, "Woche 1", 0, 0, 0, 6);
   std::cout << test.f_bestellpreis << std::endl;

   //schließ die Datenbank wieder
   db.closeDatabase();
}
