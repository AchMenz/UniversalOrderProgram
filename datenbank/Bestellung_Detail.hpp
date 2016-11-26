#ifndef BESTELLUNG_DETAIL_HPP
#define BESTELLUNG_DETAIL_HPP

#include <string>

class Bestellung_Detail
{
public:
   Bestellung_Detail(long id, std::string ware, std::string warengruppe, \
                     long id_bestellung, std::string name_bestellung, \
                     float menge_in_kg, float preis_pro_kg, \
                     float menge_in_stueck, float preis_pro_stueck, \
                     std::string kommentar = "");
   ~Bestellung_Detail();
   
   long l_id;
   std::string s_ware;
   std::string s_warengruppe;
   long l_id_bestellung;
   std::string s_name_bestellung;
   float f_menge_in_kg;
   float f_preis_pro_kg;
   float f_menge_in_stueck;
   float f_preis_pro_stueck;
   float f_bestellpreis;
   std::string s_kommentar;

};

#endif // BESTELLUNG_DETAIL_HPP
