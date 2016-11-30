#ifndef ABSENDER_H
#define ABSENDER_H

#include "Stelle.h"

class Absender : public Stelle
{
public:
   Absender(std::string Name, std::string Emailadresse, std::string Adresse);
   ~Absender();

};

#endif // ABSENDER_H
