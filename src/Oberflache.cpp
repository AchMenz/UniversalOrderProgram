//--- Oberflache.cpp - start ---
#include "Oberflache.h"
#include "Ware.h"
#include <iostream>
#include <QString>
#include <vector>
#include <string> 

#include <sstream>

Oberflache::Oberflache(QMainWindow *parent) : QMainWindow(parent){
//Constructor

//lädt UI
 	setupUi(this);
	
//Daten aus Datenbank lesen	sortiert
	
	Ware Schinken = Ware("Schinken","Fleisch",3.3,3.3,3.0,3.0,"kommentar Schinken");//debugging
	Ware Banane = Ware("Banane","Obst",2.5,2.5,2.0,2.0,"kommentar Banane");//debugging
	Ware Paprika = Ware("Paprika","Gemuese",2.4,2.4,2.1,2.1,"kommentar Paprika");//debugging
	Ware Salami = Ware("Salami","Fleisch",2.2,2.2,1.9,1.9,"kommentar Salami");//debugging
	
	warenVector.push_back(Salami);//debugging
	warenVector.push_back(Schinken);//debugging
	warenVector.push_back(Paprika);//debugging
	warenVector.push_back(Banane);//debugging
	
	//ALT
	/*Ware Schinken = Ware(1,"Schinken","Fleisch",3.3);//debugging
	Ware Paprika = Ware(1,"Paprika","Gemuese",2.0);//debugging
	Ware Banane = Ware(1,"Banane","Obst",4.5);//debugging
	Ware Salami = Ware(1,"Salami","Fleisch",4.2);//debugging
	
	warenVector.push_back(Salami);//debugging
	warenVector.push_back(Schinken);//debugging
	warenVector.push_back(Paprika);//debugging
	warenVector.push_back(Banane);//debugging
	*/
	
//Daten werden auf Oberfläche geladen	
	for(unsigned i3 = 0;i3<warenVector.size();++i3){
	
	
	
	
	//ALT
	//string s = warenVector[i].getName(); 
	//new QListWidgetItem(QString::fromStdString( warenVector[i3].getWarenGruppeName() + " " + warenVector[i3].getWarenName() ), WarenList);
	}
	
	//WarenList -> QListWidget::sortItems();
		
	connect(WareHinzuPB, SIGNAL(clicked()), this, SLOT(generiereWare()));
	connect(schliesenButton, SIGNAL(clicked()), this, SLOT(beenden()));
	connect(versendenButton, SIGNAL(clicked()), this, SLOT(versendeEmail()));	
	
	//ALT
	//Oberfläche reagiert auf aktion vom User
	/*connect(generierenButton, SIGNAL(clicked()), this, SLOT(generiereWare()));
	connect(hinzuButton, SIGNAL(clicked()), this, SLOT(WareZuBestellListe()));
	connect(schliesenButton, SIGNAL(clicked()), this, SLOT(beenden()));
	connect(versendenButton, SIGNAL(clicked()), this, SLOT(versendeEmail()));
	connect(WarenList, SIGNAL(itemSelectionChanged()), this, SLOT(anzeigenWareEigenschaft()));)*/
	}
Oberflache::~Oberflache() {
//Deconstructor	

}

void Oberflache::generiereWare(){
//erstellt neue Ware mit Daten aus Oberfläche

	Ware w1 = Ware((WarenNameHinzuEdit -> text()).toStdString(),"WarenGruppe",0,0,0,0,"");
	
	//ALT
	//Ware w1 = Ware(1,(WarenNameHinzuEdit -> text()).toStdString(),"WarenGruppe",0);

	/*Ware w1 = Ware(
	1,
	(WarenNameHinzuEdit -> text()).toStdString(),
	(WarenGruppeEdit -> text()).toStdString(),
	(Preis2Edit -> text()).toDouble()
	);*/
	
	warenVector.push_back(w1);
	
	//ALT
	//new QListWidgetItem(QString::fromStdString( w1.getWarenName() ), WarenList);
	
	
	std::cout << w1.getWarenName() << std::endl;//debugging
	std::cout << w1.getWarenGruppeName() << std::endl;//debugging
	std::cout << w1.getPreisProGewicht() << std::endl;//debugging
	
	
	std::cout << "" << std::endl;//debugging
	std::cout << "Laegne der Liste" << std::endl;//debugging
	std::cout << warenVector.size() << std::endl;//debugging
	}
	
	
	/*void Oberflache::WareZuBestellListe(){
		bestelltWarenVector.push_back(warenVector[WarenList->currentRow()]);
		vector<string> vecStr;
		string str;
		
		
		
		
		for(unsigned i1 = 0;i1<bestelltWarenVector.size();++i1){
			//itoa(bestelltWarenVector[i1].getMenge(),menge,10); 
			//itoa(bestelltWarenVector[i1].getPreis(),preis,10); 
			
			
			std::stringstream mengess;
			mengess<<bestelltWarenVector[i1].getMenge();
			std::string menge = mengess.str();
			
			std::stringstream preisss;
			preisss<<bestelltWarenVector[i1].getPreis();
			std::string preis = preisss.str();
			
			if(str.find(bestelltWarenVector[i1].getWarenGruppeName() + " " + bestelltWarenVector[i1].getWarenName() + " Menge:" + menge + " Preis:" + preis) == string::npos){
				//vector zum sortieren
				vecStr.push_back(bestelltWarenVector[i1].getWarenGruppeName() + " " + bestelltWarenVector[i1].getWarenName() + " Menge:" + menge + " Preis:" + preis);	
			}
		}
		
		std::sort(vecStr.begin(), vecStr.end());
		
		//vector in string geschrieben
		EinkaufswagenListe -> clear();
		for(unsigned i2 = 0;i2<vecStr.size();++i2){
					
					new QListWidgetItem(QString::fromStdString( vecStr[i2] ), EinkaufswagenListe);
					
					
					str += vecStr[i2];
					str += "\n";
				}
		
		std::cout << str << std::endl;
	
	}*/
	
	void Oberflache::beenden(){
		 qApp->quit();
	}
	
	void Oberflache::versendeEmail(){
		std::cout << "versendeEmail" << std::endl;//debugging
	//JÖRG!!!!
	//hier soll die email generiert werden und dann mit einem EmailProgramm(Thunderbird) verschickt werden
	}
	
	//ALT
	/*void Oberflache::anzeigenWareEigenschaft(){
	//zeigt preis und Menge auf Oberfläche an
		MengenEdit -> clear();
		PreisEdit -> clear();
	
		MengenEdit -> insert(QString::number(warenVector[WarenList->currentRow()].getMenge()));
		PreisEdit -> insert(QString::number(warenVector[WarenList->currentRow()].getPreis()));
	}*/