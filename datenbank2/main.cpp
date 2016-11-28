#include <stdio.h>
#include <iostream>

#include "DB.hpp"

int main(int argc, char **argv)
{
   DB db("db");
//   db.insertRecordWarengruppe("Reh", "Hat ein kleines Gehörn.");
//   db.insertRecordWarengruppe("Hirsch", "Hat ein großes Geweih.");
   
//   db.insertRecordWare("Filet", "Reh");
//   db.insertRecordWare("Haxen", "Hirsch");
//   db.insertRecordWare("Blatt", "Reh");
//   db.insertRecordWare("Lende", "Hirsch");
//   db.insertRecordWare("Wurstfleisch", "Reh");

//   db.updateKommentar("Haxen", "Hirsch", "Ein Tier mit einem großen Geweih.");

   //Hohle einen Vector mit Strings von "Warengruppen" aus er DB.
//   std::vector<std::string> testVect = db.getAlleWarengruppenFromDB();
//   for (std::string i : testVect)
//   {
//      std::cout << i << std::endl;
//   }

   //Hohle einen Vector mit "Waren" aus der DB.
   std::vector<Ware> testVectWare = db.getAlleWarenFromDB();
   for (Ware i : testVectWare)
   {
      std::cout << i.getWarenName() << ", " << i.getWarenGruppeName() << ", " << i.getPreisProGewicht() \
      << ", " << i.getPreisProStueck() << ", " << i.getKommentar() << std::endl;
   }

   db.closeDatabase();
}