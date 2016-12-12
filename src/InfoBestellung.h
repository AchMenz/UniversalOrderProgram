#ifndef INFOBESTELLUNG_H
#define INFOBESTELLUNG_H

#include <string>

class InfoBestellung
{
public:
   InfoBestellung(std::string zieldatum, std::string zielzeit, std::string kommentar);
   ~InfoBestellung();

   std::string getZieldatum();
   std::string getZielzeit();
   std::string getKommentar();

private:

   std::string sZielDatum;
   std::string sZielZeit;
   std::string sKommentar;

};

#endif // INFOBESTELLUNG_H
