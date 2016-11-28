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

		
		
		void Ware::setWarenName(string s){
			warenName = s;
		}
		void Ware::setWarenGruppeName(string s){
			warenGruppeName = s;
		}
		void Ware::setPreisProGewicht(float f){
			preisProGewicht = f;
		}
		void Ware::setPreisProStueck(float f){
			preisProStueck = f;
		}
		void Ware::setMengeInGewicht(float f){
			mengeInGewicht = f;
		}
		void Ware::setMengeInStueck(float f){
			mengeInStueck = f;
		}
		void Ware::setKommentar(string s){
			kommentar = s;
		}
