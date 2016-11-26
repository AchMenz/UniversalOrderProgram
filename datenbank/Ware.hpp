#ifndef WARE_HPP
#define WARE_HPP

#include <string>

class Ware
{
public:
   Ware(long id, std::string name, std::string warengruppe, float preis_pro_kg, \
   float preis_pro_stueck, std::string warennummer = "", std::string kommentar = "");
   
   ~Ware();
   
   long l_id;
   std::string s_name;
   std::string s_warengruppe;
   float f_preis_pro_kg;
   float f_preis_pro_stueck;
   std::string s_warennummer;
   std::string s_kommentar;
};

#endif // WARE_HPP
