#include "Ware.hpp"

Ware::Ware(long id, std::string name, std::string warengruppe, float preis_pro_kg, \
   float preis_pro_stueck, std::string warennummer, std::string kommentar)
{
   l_id = id;
   s_name = name;
   s_warengruppe = warengruppe;
   f_preis_pro_kg = preis_pro_kg;
   f_preis_pro_stueck = preis_pro_stueck;
   s_warennummer = warennummer;
   s_kommentar = kommentar;
}

Ware::~Ware()
{
}

