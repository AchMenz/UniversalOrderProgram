//Start Ware.h

#ifndef WARE_H
#define WARE_H

#include <string>

using namespace std;

class Ware{
	public:
		Ware(string wn, string wgn, float ppg, float pps, float mig, float mis, string k);
		~Ware();
		
		void setWarenName(string s);
		void setWarenGruppeName(string s);
		void setPreisProGewicht(float f);
		void setPreisProStueck(float f);
		void setMengeInGewicht(float f);
		void setMengeInStueck(float f);
		void setKommentar(string s);
		
		string getWarenName();
		string getWarenGruppeName();
		float getPreisProGewicht();
		float getPreisProStueck();
		float getMengeInGewicht();
		float getMengeInStueck();
		string getKommentar();
		
		
	private:
	
	string warenName;
	string warenGruppeName;
	string info;
	float preisProGewicht;
	float preisProStueck;
	float mengeInGewicht;
	float mengeInStueck;
	string kommentar;
};
#endif