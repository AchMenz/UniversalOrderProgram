#ifndef WARENGRUPPE_HPP
#define WARENGRUPPE_HPP

#include <string>

class Warengruppe
{
public:
   Warengruppe(long id, std::string name, std::string kommentar = "");
   ~Warengruppe();
   
   long l_id;
   std::string s_name;
   std::string s_kommentar;
};

#endif // WARENGRUPPE_HPP
