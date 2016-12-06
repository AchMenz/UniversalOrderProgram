#include "InfoBestellung.h"

InfoBestellung::InfoBestellung(std::string zieldatum, std::string zielzeit, std::string kommentar)
{
   sZielDatum = zieldatum;
   sZielZeit = zielzeit;
   sKommentar = kommentar;
}

InfoBestellung::~InfoBestellung()
{
}

std::string InfoBestellung::getZieldatum()
{
   return sZielDatum;
}

std::string InfoBestellung::getZielzeit()
{
   return sZielZeit;
}

std::string InfoBestellung::getKommentar()
{
   return sKommentar;
}