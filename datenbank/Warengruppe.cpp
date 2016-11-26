#include "Warengruppe.hpp"

Warengruppe::Warengruppe(long id, std::string name, std::string kommentar)
{
   l_id = id;
   s_name = name;
   s_kommentar = kommentar;
}

Warengruppe::~Warengruppe()
{
}

