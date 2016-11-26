#include "Preis_History.hpp"

Preis_History::Preis_History(long id, std::string ware, std::string warengruppe, std::string datum, bool aktuell, float preis_pro_kg, float preis_pro_stueck)
{
   l_id = id;
   s_ware = ware;
   s_warengruppe = warengruppe;
   s_datum = datum;
   b_aktuell = aktuell;
   f_preis_pro_kg = preis_pro_kg;
   f_preis_pro_stueck = preis_pro_stueck;
}

Preis_History::~Preis_History()
{
}

