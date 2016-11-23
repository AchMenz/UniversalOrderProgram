#include <stdio.h>
#include <iostream>

#include "DB.hpp"
#include "Helper.hpp"

int main(int argc, char* argv[])
{
   //erstelle eine Datenbank oder verbinde mit einer schon bestehenden
   DB db("test.db");
   
   //lies SQL aus einer Datei ein und erstelle in der Datenbank entsprechende Tabellen
   db.createTables(Helper::getSqlFromFile("db.sql"));
   
   //schließ die Datenbank wieder
   db.closeDatabase();
}
