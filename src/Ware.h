//Start Ware.h

#ifndef WARE_H
#define WARE_H

#include <string>

using namespace std;

class Ware{
	public:
		Ware(float m, string n, string wn, float p);
		~Ware();
		float getMenge();
		string getName();
		string getWarenName();
		float getPreis();
		
	private:
	float menge;
	string name;
	string warenName;
	float preis;
};
#endif