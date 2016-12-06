//--- Oberflache.cpp - start ---
#include "Oberflache.h"
#include "Ware.h"
#include "DB.h"
#include <iostream>
#include <QString>
#include <vector>
#include <string> 
#include <Warengruppe.h>
#include <QMessageBox>
#include "Helper.h"
//#include "Empfaenger.h"

#include <sstream>

Oberflache::Oberflache(QMainWindow *parent) : QMainWindow(parent){
//Constructor

//lädt UI
 	setupUi(this);
	
/**
*Daten aus Datenbank lesen	sortiert
*/

	DB db("db");

	//db.deleteWare("Blatt", "Reh");
	
	 // db.createTables(Helper::getSqlFromFile("db.sql"));

	 // db.insertRecordInWarengruppe("Reh", "Hat ein kleines Gehörn.");
	 // db.insertRecordInWarengruppe("Hirsch", "Hat ein großes Geweih.");
	 // db.insertRecordInWarengruppe("Wildschwein", "Kann Trüffel erschnüffeln");
 
	 // db.insertRecordInWare("Filet", "Reh");
	 // db.insertRecordInWare("Haxen", "Hirsch");
	 // db.insertRecordInWare("Blatt", "Reh");
	 // db.insertRecordInWare("Lende", "Hirsch");
	 // db.insertRecordInWare("Wurstfleisch", "Wildschwein");

	//std::cout << db.getAlleEmpfaenger()[0].getName() << std::endl;
	
	//Ware Schinken = Ware("Schinken","Fleisch",3.3,3.4,3.5,3.6,"kommentar Schinken");//debugging
	//Ware Banane = Ware("Banane","Obst",2.5,2.6,2.7,2.8,"kommentar Banane");//debugging
	//Ware Paprika = Ware("Paprika","Gemuese",2.4,2.5,2.6,2.7,"kommentar Paprika");//debugging
	//Ware Salami = Ware("Salami","Fleisch",2.2,2.3,2.4,2.5,"kommentar Salami");//debugging
	
	//warenVector.push_back(Salami);//debugging
	//warenVector.push_back(Schinken);//debugging
	//warenVector.push_back(Paprika);//debugging
	//warenVector.push_back(Banane);//debugging
	
	warenVector = db.getAlleWaren();
	
	//select die einen Vector<Warengruppe> zurück gibt
	//warenGruppeVector = db.getAlleWarengruppenNamen();
	
	NameAbsenderEdit->insert(QString::fromStdString(db.getAlleAbsender()[0].getName()));
		QTextDocument* ED;
		ED -> setPlainText(QString::fromStdString(db.getAlleAbsender()[0].getAdresse()));
	AdresseAbsenderEdit->setDocument(ED);
	EmailAbsenderEdit->insert(QString::fromStdString(db.getAlleAbsender()[0].getEmailadresse()));
	
	NameEmpfaengerEdit->insert(QString::fromStdString(db.getAlleEmpfaenger()[0].getName()));
		QTextDocument* AD;
		AD -> setPlainText(QString::fromStdString(db.getAlleEmpfaenger()[0].getAdresse()));
	AdresseEmpfaengerEdit->setDocument(AD);
	EmailEmpfaengerEdit->insert(QString::fromStdString(db.getAlleEmpfaenger()[0].getEmailadresse()));
//Daten werden auf Oberfläche geladen	
	for(unsigned i3 = 0;i3<warenVector.size();++i3){		
		warenNameVector.push_back(warenVector[i3].getWarenGruppeName() + " " + warenVector[i3].getWarenName());
	}
	
	for(unsigned i4 = 0; i4<db.getAlleWarengruppenNamen().size();++i4){
		warenGruppeVector.push_back(Warengruppe(db.getAlleWarengruppenNamen()[i4], ""));
	}

	WarenTW->sortItems(0);
	this -> aktualisiereOberflaeche();
	
	
	connect(WareHinzuPB, SIGNAL(clicked()), this, SLOT(generiereWare()));
	connect(schliesenButton, SIGNAL(clicked()), this, SLOT(beenden()));
	connect(versendenButton, SIGNAL(clicked()), this, SLOT(versendeEmail()));
	connect(WarenGruppeHinzuPB, SIGNAL(clicked()), this, SLOT(generiereWarenGruppe()));	
	connect(WarEntfernenPB, SIGNAL(clicked()), this, SLOT(entferneWare()));
	connect(WarenTW, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(zelleaktualisiert(QTableWidgetItem*)));
	connect(WarenGruppeEntfPB, SIGNAL(clicked()), this, SLOT(entferneWarenGruppe()));
	connect(EinstellungenPButton, SIGNAL(clicked()), this, SLOT(aktualisiereEinstellungen()));
	
}

Oberflache::~Oberflache() {
//Deconstructor	

}

void Oberflache::generiereWare(){
/**
*erstellt neue Ware mit Daten aus Oberfläche
*/

	//WarenGruppeCB
	DB db("db");
	
	Ware w1 = Ware((WarenNameHinzuEdit -> text()).toStdString(),WarenGruppeCB -> currentText().toStdString(),0,0,0,0,"");
	string s =  w1.getWarenGruppeName()+ " " + w1.getWarenName();
	
	db.insertRecordInWare(WarenNameHinzuEdit -> text().toStdString(), WarenGruppeCB -> currentText().toStdString());
	
	warenVector.push_back(w1);
	warenNameVector.push_back(s);
	std::sort(warenNameVector.begin(), warenNameVector.end());
	
	
		this -> aktualisiereOberflaeche();
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
		//JÖRG!!!!
		//hier soll die email generiert werden und dann mit einem EmailProgramm(Thunderbird) verschickt werden
		
	}
	
	void Oberflache::generiereWarenGruppe(){
/**
*Warengruppe wird generiert
*/
		
		DB db("db");
		
		Warengruppe wp = Warengruppe(WarenGruppeHinzuEdit -> text().toStdString(),WarenGruppeInfoEdit -> toPlainText().toStdString());
		db.insertRecordInWarengruppe(WarenGruppeHinzuEdit -> text().toStdString(), WarenGruppeInfoEdit -> toPlainText().toStdString());
		
		warenGruppeVector.push_back(wp);
		
		//kann das weg?
		vector<string> v;
		
		for(unsigned i1 = 0;i1<warenGruppeVector.size();++i1){
		string s = warenGruppeVector[i1].getWarenGruppeName();
		v.push_back(s);
		}
		
		std::sort(v.begin(), v.end());
	
		//for(unsigned i2 = 0;i2<v.size();++i2){
		//	WarenGruppeCB -> addItem(QString::fromStdString( v[i2] ));
		//}
		this -> aktualisiereOberflaeche();
	}
	
	void Oberflache::aktualisiereOberflaeche(){	
		
		DB db("db");
		
		
		std::vector<std::string> testVect = db.getAlleWarengruppenNamen();
	//for (std::string i : testVect)
		// {
		// std::cout << i << std::endl;
		// }
		// std::cout << " " << std::endl;
		// std::cout << "test" << std::endl;
		
			WareEntfCB -> clear();
			WarenGruppeCB -> clear();
			WarenGruppeEntfCB -> clear();
			WarenTW -> setRowCount(0);
			
		//befüllt combo box um waren zu löschen
			for(unsigned i1 = 0;i1<warenNameVector.size();++i1){
				WareEntfCB -> addItem(QString::fromStdString(warenNameVector[i1]));
			}
		//befüllt combo box um warengruppen zu löschen
			for(unsigned i2 = 0;i2<warenGruppeVector.size();++i2){
				WarenGruppeEntfCB -> addItem(QString::fromStdString(warenGruppeVector[i2].getWarenGruppeName()));
				WarenGruppeCB -> addItem(QString::fromStdString(warenGruppeVector[i2].getWarenGruppeName()));
			}
		//befüllt Haupttabelle
			for(unsigned i3 = 0;i3<warenVector.size();++i3){
				disconnect(WarenTW, 0, 0, 0);
				WarenTW->insertRow( WarenTW->rowCount() );
					
				//std::cout << "Ware: " + warenVector[i3].getWarenName() << std::endl;
				//std::cout << "WarenGruppe: " + warenVector[i3].getWarenGruppeName() << std::endl;
					
				float gpreisd = 0;
				
				gpreisd = (warenVector[i3].getPreisProGewicht() * warenVector[i3].getMengeInGewicht()) + (warenVector[i3].getPreisProStueck() * warenVector[i3].getMengeInStueck());
				
				
				std::stringstream ppgss;
				ppgss<<(warenVector[i3].getPreisProGewicht());
				std::string ppg = ppgss.str();
				
				std::stringstream ppsss;
				ppsss<<(warenVector[i3].getPreisProStueck());
				std::string pps = ppsss.str();
				
				std::stringstream migss;
				migss<<(warenVector[i3].getMengeInGewicht());
				std::string mig = migss.str();
				
				std::stringstream misss;
				misss<<(warenVector[i3].getMengeInStueck());
				std::string mis = misss.str();
				
				std::stringstream gpreisss;
				gpreisss<<(gpreisd);
				std::string gpreiss = gpreisss.str();
				
				WarenTW->setItem(i3, 1, new QTableWidgetItem(QString::fromStdString(warenVector[i3].getWarenName())));
				WarenTW->setItem(i3, 0, new QTableWidgetItem(QString::fromStdString(warenVector[i3].getWarenGruppeName())));
				WarenTW->setItem(i3, 2, new QTableWidgetItem(QString::fromStdString(ppg)));
				WarenTW->setItem(i3, 3, new QTableWidgetItem(QString::fromStdString(pps)));
				WarenTW->setItem(i3, 4, new QTableWidgetItem(QString::fromStdString(mig)));
				WarenTW->setItem(i3, 5, new QTableWidgetItem(QString::fromStdString(mis)));
				WarenTW->setItem(i3, 6, new QTableWidgetItem(QString::fromStdString(gpreiss)));
			
				Qt::ItemFlags flags;
			
				flags = WarenTW->item(i3, 0)->flags();
				flags |= Qt::ItemIsSelectable;
				flags &= ~Qt::ItemIsEditable; 
				WarenTW->item(i3, 0)->setFlags(flags);
				
				flags = WarenTW->item(i3, 1)->flags();
				flags |= Qt::ItemIsSelectable;
				flags &= ~Qt::ItemIsEditable; 
				WarenTW->item(i3, 1)->setFlags(flags);
				
				WarenTW->sortItems(0);
				
			}
			connect(WarenTW, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(zelleaktualisiert(QTableWidgetItem*)));
	}
	
	void Oberflache::entferneWare(){
		string s = 	WareEntfCB -> currentText().toStdString();
		DB db("db");
		//int z = 0;
		for(unsigned i1 = 0;i1<warenVector.size();++i1){
				//std::cout << warenVector[i1].getWarenGruppeName() + " " + warenVector[i1].getWarenName() << std::endl;
				//z++;
			if( (warenVector[i1].getWarenGruppeName()+ " " + warenVector[i1].getWarenName() ).compare(s) == 0){
				std::cout << "Ware: " + warenVector[i1].getWarenName() << std::endl;
				std::cout << "WarenGruppe: " + warenVector[i1].getWarenGruppeName() << std::endl;
				db.deleteWare(warenVector[i1].getWarenName(), warenVector[i1].getWarenGruppeName());
				warenVector.erase(warenVector.begin()+ i1 );
				break;
			}
		}
		for(unsigned i2 = 0;i2<warenNameVector.size();++i2){
			//std::cout << warenNameVector[i2] << std::endl;
			if(warenNameVector[i2].compare(s) == 0){
				warenNameVector.erase(warenNameVector.begin() + i2 );
				break;
			}
		}
		this -> aktualisiereOberflaeche();
		
	}
	
	void Oberflache::zelleaktualisiert(QTableWidgetItem* x){
		disconnect(WarenTW, 0, 0, 0);
		
		  switch ( x -> column() ) { 
			  
				case 0:  
					warenVector[x -> row()].setWarenGruppeName(x -> text().toStdString());
					break;
				case 1:
					warenVector[x -> row()].setWarenName(x -> text().toStdString());
					break;   
				case 2:
					warenVector[x -> row()].setPreisProGewicht(x -> text().toFloat());
					break;
				case 3:
					warenVector[x -> row()].setPreisProStueck(x -> text().toFloat());
					break;
				case 4:
					warenVector[x -> row()].setMengeInGewicht(x -> text().toFloat());
					break;
				case 5:
					warenVector[x -> row()].setMengeInStueck(x -> text().toFloat());
					break;
				case 6:
					warenVector[x -> row()].setKommentar(x -> text().toStdString());
					break;
			}		
	
	  
		
		
		this -> aktualisiereOberflaeche();
		
		//connect(WarenTW, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(zelleaktualisiert(QTableWidgetItem*)));
	}
	
	void Oberflache::entferneWarenGruppe(){
		DB db("db");
		bool b = true;
		for(unsigned i1 = 0;i1<warenVector.size();++i1){
			if(warenVector[i1].getWarenGruppeName().compare(WarenGruppeEntfCB -> currentText().toStdString()) == 0){
				b= false;
				
			}
		}
		if(b == true){
			for(unsigned i3 = 0;i3<warenGruppeVector.size();++i3){
				if(warenGruppeVector[i3].getWarenGruppeName().compare(WarenGruppeEntfCB -> currentText().toStdString())== 0){
					warenGruppeVector.erase(warenGruppeVector.begin() + i3);
					db.deleteWarengruppe(warenGruppeVector[i3].getWarenGruppeName());
				}
			}
			this -> aktualisiereOberflaeche();
		}else{
			QMessageBox msgBox;
			msgBox.setText("Warengruppe konnte nicht entfernt werden, weil noch eine Ware mit dieser Warengruppe existiert.");
			msgBox.exec();
		}
	}
	
	void Oberflache::aktualisiereEinstellungen(){
		std::cout << "test"<< std::endl;
	}
	
	//ALT
	/*void Oberflache::anzeigenWareEigenschaft(){
	//zeigt preis und Menge auf Oberfläche an
		MengenEdit -> clear();
		PreisEdit -> clear();
	
		MengenEdit -> insert(QString::number(warenVector[WarenList->currentRow()].getMenge()));
		PreisEdit -> insert(QString::number(warenVector[WarenList->currentRow()].getPreis()));
	}*/
