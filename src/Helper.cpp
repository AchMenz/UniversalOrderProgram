#include <fstream>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <iomanip>

#include "Helper.h"

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

float Helper::toFloat(std::string stringFloat)
{
    float f;
    try {
        f = boost::lexical_cast<float>(stringFloat);
    } catch(boost::bad_lexical_cast const&) {
        f = 0;
        fprintf(stderr, "Not a float typed in.\n");
    }
    
    return f;
}

std::string Helper::toString(float floatString)
{
   std::stringstream stream;
   stream << std::fixed << std::setprecision(2) << floatString;
   std::string result = stream.str();
   return result;
}