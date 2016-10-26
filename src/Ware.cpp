//start Ware.cpp
#include "Ware.h"
#include <string>

Ware::Ware(float m, string n, string wn, float p):
menge(m), name(n), warenName(wn), preis(p){
	
}

Ware::~Ware(){
	
}

float Ware::getMenge(){
	return menge;
}
string Ware::getName(){
		return name;
}
string Ware::getWarenName(){
		return warenName;;
}
float Ware::getPreis(){
	return preis;
}