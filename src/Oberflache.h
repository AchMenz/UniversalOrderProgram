//--- Oberfläche.h - start ---

#ifndef OBERFLACHE_H
#define OBEFLACHE_H

#include "ui_Oberflache.h"
#include <vector>
#include <string>
#include "Ware.h"

using namespace std;

class Oberflache : public QMainWindow, public Ui::MainWindow{
  	Q_OBJECT

 	public:
 		Oberflache (QMainWindow *parent = 0);
 		~Oberflache();
		
	private slots:
		void generiereWare();
		void beenden();
		void versendeEmail();
		
		
	private:
		vector<Ware> warenVector;
		vector<Ware> bestelltWarenVector;
		//vector<int> second = vector<int> (4,100); 
		//vector< vector<string> > second;
		
};
#endif