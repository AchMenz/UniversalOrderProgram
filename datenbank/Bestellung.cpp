#include "Bestellung.hpp"

Bestellung::Bestellung(long id, std::string name, std::string zieldatum, std::string zielzeit, std::string kommentar)
{
   l_id = id;
   s_name = name;
   s_zieldatum = zieldatum;
   s_zielzeit = zielzeit;
   s_kommentar = kommentar;
}

Bestellung::~Bestellung()
{
}

