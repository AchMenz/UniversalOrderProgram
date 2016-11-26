#ifndef BESTELLUNG_HPP
#define BESTELLUNG_HPP

#include <string>

class Bestellung
{
public:
   Bestellung(long id, std::string name, std::string zieldatum, std::string zielzeit = "", std::string kommentar = "");
   ~Bestellung();
   
   long l_id;
   std::string s_name;
   std::string s_zieldatum;
   std::string s_zielzeit;
   std::string s_kommentar;

};

#endif // BESTELLUNG_HPP
