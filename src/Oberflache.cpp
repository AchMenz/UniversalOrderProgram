//--- Oberflache.cpp - start ---

//WarenNameEdit

#include "Oberflache.h"
#include "Ware.h"
#include <iostream>
#include <QString>
#include <vector>
#include <string>

using namespace std;

Oberflache::Oberflache(QMainWindow *parent) : QMainWindow(parent){
 	setupUi(this);
	
	Ware Schinken = Ware(1,"Schinken","Fleisch",3);//todo
	Ware Paprika = Ware(1,"Paprika","Gemuese",2);//todo
	Ware Banane = Ware(1,"Banane","Obst",4);//todo
	Ware Salami = Ware(1,"Salami","Fleisch",4);//todo
	
	warenListe.push_back(Schinken);
	warenListe.push_back(Paprika);
	warenListe.push_back(Banane);
	warenListe.push_back(Salami);
	
	
	for(unsigned i = 0;i<warenListe.size();++i){
	//string s = warenListe[i].getName(); 
	new QListWidgetItem(QString::fromStdString( warenListe[i].getName() ), WarenList);
	}
	
	
	
	//warenListe[0][0] ="test";
	//vector<string> second = vector<string>(4,"100t"); 
	//vector< vector<string> > second(4, vector<string>(4,"100asd"));
	//std::cout << s << std::endl;//doku
	
	connect(generierenButton, SIGNAL(clicked()), this, SLOT(generiereWare()));
	//connect(generierenButton, &QPushButton::click, this, &Oberflache::generiereWare);
}
Oberflache::~Oberflache() {
	
}

void Oberflache::generiereWare(){	
	Ware w1 = Ware(
	1,
	(WarenNameEdit -> text()).toStdString(),
	(WarenGruppeEdit -> text()).toStdString(),
	(Preis2Edit -> text()).toDouble()
	);
	
	warenListe.push_back(w1);
	new QListWidgetItem(QString::fromStdString( w1.getName() ), WarenList);
	std::cout << w1.getMenge() << std::endl;//doku
	std::cout << w1.getName() << std::endl;//doku
	std::cout << w1.getWarenName() << std::endl;//doku
	std::cout << w1.getPreis() << std::endl;//doku
	
	
	std::cout << "" << std::endl;
	std::cout << "Laegne der Liste" << std::endl;
	std::cout << warenListe.size() << std::endl;
	}