//Start Ware.h

#ifndef WARE_H
#define WARE_H

#include <string>

using namespace std;

class Ware{
	public:
		Ware(float m, string n, string wpn, float p);
		~Ware();
		float getMenge();
		string getWarenName();
		string getWarenGruppeName();
		float getPreis();
		
		
	private:
	float menge;
	string warenName;
	string warenGruppeName;
	float preis;
};
#endif