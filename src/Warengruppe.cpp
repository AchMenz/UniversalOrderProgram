//start Waregurppe.cpp
#include "Warengruppe.h"
#include <string>

Warengruppe::Warengruppe(string wgn,  string k):
warenGruppeName(wgn), kommentar(k){
	
}

Warengruppe::~Warengruppe(){
	
}

string Warengruppe::getWarenGruppeName(){
	return warenGruppeName;
}

string Warengruppe::getKommentar(){
	return kommentar;
}
