//start Ware.cpp
#include "Ware.h"
#include <string>

Ware::Ware(string wn, string wgn, float ppg, float pps, float mig, float mis, string i):
warenName(wn), warenGruppeName(wgn), preisProGewicht(ppg), preisProStueck(pps), mengeInGewicht(mig), mengeInStueck(mis){
	
}

Ware::~Ware(){
	
}

string Ware::getWarenName(){
		return warenName;
}

string Ware::getWarenGruppeName(){
		return warenGruppeName;
}

float Ware::getPreisProGewicht(){
	return preisProGewicht;
}

float Ware::getPreisProStueck(){
	return preisProStueck;
}

float Ware::getMengeInGewicht(){
	return mengeInGewicht;
}

float Ware::getMengeInStueck(){
	return mengeInStueck;
}

string Ware::getKommentar(){
	return kommentar;
}
