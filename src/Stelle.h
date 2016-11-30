#ifndef STELLE_H
#define STELLE_H

#include <string>

class Stelle
{
public:
   Stelle(std::string Name, std::string Emailadresse, std::string Adresse);
   ~Stelle();

   std::string getName();
   std::string getAdresse();
   std::string getEmailadresse();
   
private:

   std::string StelleName;
   std::string StelleAdresse;
   std::string StelleEmailadresse;
};

#endif // STELLE_H
