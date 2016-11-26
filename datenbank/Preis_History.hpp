#ifndef PREIS_HISTORY_HPP
#define PREIS_HISTORY_HPP

#include <string>

class Preis_History
{
public:
   Preis_History(long id, std::string ware, std::string warengruppe, std::string datum, bool aktuell, float preis_pro_kg, float preis_pro_stueck);
   ~Preis_History();
   
   long l_id;
   std::string s_ware;
   std::string s_warengruppe;
   std::string s_datum;
   bool b_aktuell;
   float f_preis_pro_kg;
   float f_preis_pro_stueck;
};

#endif // PREIS_HISTORY_HPP
