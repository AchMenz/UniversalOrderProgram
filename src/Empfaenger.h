#ifndef EMPFAENGER_H
#define EMPFAENGER_H

#include "Stelle.h"

class Empfaenger : public Stelle
{
public:
   Empfaenger(std::string Name, std::string Emailadresse, std::string Adresse = "");
   ~Empfaenger();

};

#endif // EMPFAENGER_H
