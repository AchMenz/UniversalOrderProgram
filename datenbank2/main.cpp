#include <stdio.h>
#include <iostream>

#include "DB.h"
#include "Helper.h"
#include "Absender.h"
#include "Empfaenger.h"

int main(int argc, char **argv)
{
//DB erzeugen etc.
	//erzeugt datenbankobjekt mit name db
   DB db("db");

   //erzeugt Tabellen in der Datenbank db, auf Grundlage der Datei: "db.sql"
   //db.createTables(Helper::getSqlFromFile("db.sql"));
   





//Erzeuge Daten
//   db.insertRecordInWarengruppe("Reh", "Hat ein kleines Gehörn.");
//   db.insertRecordInWarengruppe("Hirsch", "Hat ein großes Geweih.");
// 
//   db.insertRecordInWare("Filet", "Reh");
//   db.insertRecordInWare("Haxen", "Hirsch");
//   db.insertRecordInWare("Blatt", "Reh");
//   db.insertRecordInWare("Lende", "Hirsch");
//   db.insertRecordInWare("Wurstfleisch", "Reh");
//
//   db.insertRecordInAbsenderEmpfaenger("Empfaenger", "Las Kalisz", "Las Kalisz\nStraße des Wildes 123\n04353 Tomnice", "laskalisz@web.pl");





//Ändere Daten
   //db.updateKommentar("Lende", "Hirsch", "Bitte eingefroren.");
   //db.updatePreisProKg("Haxen", "Hirsch", 4.5);
   //db.updatePreisProSt("Lende", "Hirsch", 35.45);
   
   //ändert einen Wert in der Tabelle "Absender" oder "Empfänger"
   //db.updateWerteInAbsenderEmpfaenger("Empfaenger", "Wursthandel Jankowski", "Emailadresse", "jankowskiInPolen@mail.pl");





//Lösche Daten
   //lösche eine Ware
   //db.deleteWare("Blatt", "Reh");
   
   //prüft, ob die Warengruppe noch in der Tabelle "Ware" als Fremdschlüssel vorkommt
   //std::cout << db.warengruppeIsDeletable("Reh") << std::endl;

   //lösche eine Warengruppe
   //db.deleteWarengruppe("Reh");

   //lösche einen Datensatz in der Tabelle "Empfaenger" oder "Absender"
   //db.deleteRecordInAbsenderEmpfaenger("Empfaenger", "Wildhandel Broy 2");





//Hohle Daten
   //Hohle einen Vector mit Strings von "Warengruppen" aus der DB.
//   std::vector<std::string> testVect = db.getAlleWarengruppenNamen();
//   for (std::string i : testVect)
//   {
//      std::cout << i << std::endl;
//   }

   //Hohle einen Vector mit "Waren" aus der DB.
//   std::vector<Ware> testVectWare = db.getAlleWaren();
//   for (Ware i : testVectWare)
//   {
//      std::cout << i.getWarenName() << ", " << i.getWarenGruppeName() << ", " << i.getPreisProGewicht() \
//      << ", " << i.getPreisProStueck() << ", " << i.getKommentar() << std::endl;
//   }

   //Hohle einen Vector mit Strings von "Empfaenger" aus der DB
//   std::vector<std::string> testVect = db.getAlleEmpfaengerNamen();
//   for (std::string i : testVect)
//   {
//      std::cout << i << std::endl;
//   }

   //Hohle einen Vector mit "Stellen" aus der DB
//   std::vector<Absender> testVect = db.getAlleAbsender();
//   for (Absender i : testVect)
//   {
//      std::cout << i.getName() << ", " << i.getAdresse() << ", " << i.getEmailadresse() << std::endl;
//   };

//schließe Datenbank
   //Die Datenbank unbedingt schließen, sonst bleibt sie wohl möglich im Speicher!
   db.closeDatabase();
}