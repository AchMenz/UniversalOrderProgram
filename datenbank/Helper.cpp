#include <fstream>

#include "Helper.hpp"

std::string Helper::getSqlFromFile(char* file)
{   
   std::string s;
   std::string a;

   //erstelle Lesestream aus Datei file
   std::ifstream sql(file);
   
   //Wenn Lesestream existiert, dann ...
   if(sql.is_open())
   {
      //solange Lesestream eine Zeile hat, dann ...
      while(sql.good())
      {
         //lies Zeile ein aus Lesestream "lesen" und speichere in s
         std::getline(sql, a);
         //baue String aus Zeilen zusammen
         s+= a + "\n";
      }
      fprintf(stderr, "Sql-File read succesfully.\n");
   }
   else
   {
      fprintf(stderr, "Cannot read sql-file.\n");
   }
   
   return s;
}
