#include "Stelle.h"

Stelle::Stelle(std::string Name, std::string Emailadresse, std::string Adresse)
{
   StelleName = Name;
   StelleAdresse = Adresse;
   StelleEmailadresse = Emailadresse;
}

Stelle::~Stelle()
{
}

std::string Stelle::getName()
{
   return StelleName;
}

std::string Stelle::getAdresse()
{
   return StelleAdresse;
}

std::string Stelle::getEmailadresse()
{
   return StelleEmailadresse;
}