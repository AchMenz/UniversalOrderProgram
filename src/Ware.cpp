//start Ware.cpp
#include "Ware.h"
#include <string>

Ware::Ware(float m, string n, string wpn, float p):
menge(m), warenName(n), warenGruppeName(wpn), preis(p){
	
}

Ware::~Ware(){
	
}

float Ware::getMenge(){
	return menge;
}
string Ware::getWarenName(){
		return warenName;
}
string Ware::getWarenGruppeName(){
		return warenGruppeName;;
}
float Ware::getPreis(){
	return preis;
}