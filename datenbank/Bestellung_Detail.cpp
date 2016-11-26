#include "Bestellung_Detail.hpp"

#include <iostream>

Bestellung_Detail::Bestellung_Detail(long id, std::string ware, std::string warengruppe, \
                     long id_bestellung, std::string name_bestellung, \
                     float menge_in_kg, float preis_pro_kg, \
                     float menge_in_stueck, float preis_pro_stueck, \
                     std::string kommentar)
{
   l_id = id;
   s_ware = ware;
   s_warengruppe = warengruppe;
   l_id_bestellung = id_bestellung;
   s_name_bestellung = name_bestellung;
   f_menge_in_kg = menge_in_kg;
   f_preis_pro_kg = preis_pro_kg;
   f_menge_in_stueck = menge_in_stueck;
   f_preis_pro_stueck = preis_pro_stueck;
   s_kommentar = kommentar;
   
   //Zählvariable
   int i = 0;
   
   //Berechnung des Bestellpreises
   //Werte in kg
   if ((menge_in_kg != 0) and (preis_pro_kg != 0))
   {
      f_bestellpreis = menge_in_kg * preis_pro_kg;
      i++;
   }
   //Werte in Stueck
   if ((menge_in_stueck != 0) and (preis_pro_stueck != 0))
   {
      f_bestellpreis = menge_in_stueck * preis_pro_stueck;
      i++;
   }
   //Werte in kg und Stueck
   if (((menge_in_stueck != 0) and (preis_pro_stueck != 0)) and ((menge_in_kg != 0) and (preis_pro_kg != 0)))
   {
      f_bestellpreis = (menge_in_kg * preis_pro_kg) + (menge_in_stueck * preis_pro_stueck);
      i++;
   }
   //Wenn gar keine Paare von Werten kg/Stueck gegeben sind... 
   if (i == 0)
   {
      f_bestellpreis = 0;
   }
}

Bestellung_Detail::~Bestellung_Detail()
{
}

