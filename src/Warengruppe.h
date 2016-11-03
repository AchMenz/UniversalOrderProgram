//Start Waregruppe.h

#ifndef WARENGRUPPE_H
#define WARENGRUPPE_H

#include <string>

using namespace std;

class Warengruppe{
	public:
		Warengruppe(string wgn, string k);
		~Warengruppe();
		
		string getWarenGruppeName();
		string getKommentar();
		
		
	private:
	string warenGruppeName;
	string kommentar;
};
#endif