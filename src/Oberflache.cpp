//--- Oberflache.cpp - start ---

//WarenNameEdit

#include "Oberflache.h"
#include "Ware.h"
#include <iostream>
#include <QString>
#include <vector>
#include <string> 

//using namespace std;

Oberflache::Oberflache(QMainWindow *parent) : QMainWindow(parent){
//Constructor

//lädt UI
 	setupUi(this);
	
//Daten aus Datenbank lesen	
	Ware Schinken = Ware(1,"Schinken","Fleisch",3.3);//debugging
	Ware Paprika = Ware(1,"Paprika","Gemuese",2.0);//debugging
	Ware Banane = Ware(1,"Banane","Obst",4.5);//debugging
	Ware Salami = Ware(1,"Salami","Fleisch",4.2);//debugging
	
	warenVector.push_back(Schinken);//debugging
	warenVector.push_back(Paprika);//debugging
	warenVector.push_back(Banane);//debugging
	warenVector.push_back(Salami);//debugging
	
//Daten werden auf Oberfläche geladen	
	for(unsigned i = 0;i<warenVector.size();++i){
	//string s = warenVector[i].getName(); 
	new QListWidgetItem(QString::fromStdString( warenVector[i].getWarenName() ), WarenList);
	}
	
	
	
	//warenVector[0][0] ="test";
	//vector<string> second = vector<string>(4,"100t"); 
	//vector< vector<string> > second(4, vector<string>(4,"100asd"));
	//std::cout << s << std::endl;//doku

	//Oberfläche reagiert auf aktion vom User
	connect(generierenButton, SIGNAL(clicked()), this, SLOT(generiereWare()));
	connect(hinzuButton, SIGNAL(clicked()), this, SLOT(WareZuBestellListe()));
	connect(schliesenButton, SIGNAL(clicked()), this, SLOT(beenden()));
	connect(versendenButton, SIGNAL(clicked()), this, SLOT(versendeEmail()));
	connect(WarenList, SIGNAL(itemSelectionChanged()), this, SLOT(anzeigenWareEigenschaft()));
	}
Oberflache::~Oberflache() {
//Deconstructor	

}

void Oberflache::generiereWare(){
//erstellt neue Ware mit Daten aus Oberfläche
	Ware w1 = Ware(
	1,
	(WarenNameEdit -> text()).toStdString(),
	(WarenGruppeEdit -> text()).toStdString(),
	(Preis2Edit -> text()).toDouble()
	);
	
	warenVector.push_back(w1);
	new QListWidgetItem(QString::fromStdString( w1.getWarenName() ), WarenList);
	
	std::cout << w1.getMenge() << std::endl;//debugging
	std::cout << w1.getWarenName() << std::endl;//debugging
	std::cout << w1.getWarenGruppeName() << std::endl;//debugging
	std::cout << w1.getPreis() << std::endl;//debugging
	
	
	std::cout << "" << std::endl;//debugging
	std::cout << "Laegne der Liste" << std::endl;//debugging
	std::cout << warenVector.size() << std::endl;//debugging
	}
	
	
	void Oberflache::WareZuBestellListe(){
		std::cout << "warezubestellen" << std::endl;//debugging
	}
	
	void Oberflache::beenden(){
		 qApp->quit();
	}
	
	void Oberflache::versendeEmail(){
		std::cout << "versendeEmail" << std::endl;//debugging
	//JÖRG!!!!
	//hier soll die email generiert werden und dann mit einem EmailProgramm(Thunderbird) verschickt werden
	}
	
	void Oberflache::anzeigenWareEigenschaft(){
	//zeigt preis und Menge auf Oberfläche an
		MengenEdit -> clear();
		PreisEdit -> clear();
	
		MengenEdit -> insert(QString::number(warenVector[WarenList->currentRow()].getMenge()));
		PreisEdit -> insert(QString::number(warenVector[WarenList->currentRow()].getPreis()));
	}