//--- Oberflache.cpp - start ---
#include "Oberflache.h"
#include "Ware.h"
#include "DB.h"
#include <iostream>
#include <QString>
#include <vector>
#include <string> 
#include <stdlib.h>
#include <algorithm>
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
	
	warenVector = db.getAlleWaren();

	Absender ersterAbsender = db.getErstenAbsender();
	Empfaenger ersterEmpfaenger = db.getErstenEmpfaenger();
	
	NameAbsenderEdit->insert(QString::fromStdString(ersterAbsender.getName()));
	AdresseAbsenderEdit->textCursor().insertText(QString::fromStdString(ersterAbsender.getAdresse()));
    EmailAbsenderEdit->insert(QString::fromStdString(ersterAbsender.getEmailadresse()));
	
    NameEmpfaengerEdit->insert(QString::fromStdString(ersterEmpfaenger.getName()));
	AdresseEmpfaengerEdit->textCursor().insertText(QString::fromStdString(ersterEmpfaenger.getAdresse()));
    EmailEmpfaengerEdit->insert(QString::fromStdString(ersterEmpfaenger.getEmailadresse()));
	
	InfoBestellung i = 	db.getErsteInfoBestellung();
	string zeitstring = i.getZielzeit();
	string datumstring = i.getZieldatum();
	
	string hs = zeitstring.substr(0,2);
	string mins = zeitstring.substr(3,2);
	
	string ts = datumstring.substr(0,2);
	string mons = datumstring.substr(3,2);
	string js = datumstring.substr(6,4);
	
	std::string::size_type sz;
	
	int h = std::stoi (hs,&sz);
	int min = std::stoi (mins,&sz);
	
	int t = std::stoi (ts,&sz);
	int mon = std::stoi (mons,&sz);
	int j = std::stoi (js,&sz);
	
	ZeitEdit -> setTime(QTime(h, min, 0, 0));
	DatumEdit -> setDate(QDate(j, mon, t));
	ZielzeitKommentarEdit -> textCursor().insertText(QString::fromStdString(i.getKommentar()));
	
	WareEntfCB -> addItem(QString::fromStdString("test"));
	
	this -> aktualisiereOberflaeche();
	
	connect(WareHinzuPB, SIGNAL(clicked()), this, SLOT(generiereWare()));
	connect(schliesenButton, SIGNAL(clicked()), this, SLOT(beenden()));
	connect(versendenButton, SIGNAL(clicked()), this, SLOT(versendeEmail()));
	connect(WarenGruppeHinzuPB, SIGNAL(clicked()), this, SLOT(generiereWarenGruppe()));	
	connect(WarEntfernenPB, SIGNAL(clicked()), this, SLOT(entferneWare()));
	connect(WarenTW, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(zelleaktualisiert(QTableWidgetItem*)));
	connect(WarenGruppeEntfPB, SIGNAL(clicked()), this, SLOT(entferneWarenGruppe()));
	connect(EinstellungenPButton, SIGNAL(clicked()), this, SLOT(aktualisiereEinstellungen()));
	connect(DatumEdit, SIGNAL(dateChanged(QDate)), this, SLOT(aktualisiereZielDatum(QDate)));
	connect(ZeitEdit, SIGNAL(timeChanged(QTime)), this, SLOT(aktualisiereZielZeit(QTime)));
	connect(ZielzeitKommentarEdit, SIGNAL(textChanged()), this, SLOT(aktualisiereZielKommentar()));
	
	db.closeDatabase();
}

Oberflache::~Oberflache() {
//Deconstructor	

}

void Oberflache::generiereWare(){
//erstellt neue Ware mit Daten aus Oberfläche

	DB db("db");
	
	db.insertRecordInWare(WarenNameHinzuEdit -> text().toStdString(), WarenGruppeCB -> currentText().toStdString());
	
		this -> aktualisiereOberflaeche();
		db.closeDatabase();
}
	
	
void Oberflache::beenden(){
	 qApp->quit();
}
	
void Oberflache::versendeEmail(){
//übergebe Thunderbird einen Emailtext aus den entsprechenden Tabellendaten
  DB db("db");
  Absender abs = db.getErstenAbsender();
  Empfaenger empf = db.getErstenEmpfaenger();
  InfoBestellung info = db.getErsteInfoBestellung();
  std::vector<Ware> waren = db.getAlleWaren();

  std::string warentextKg;
  std::string warentextSt;
  warentextKg = "";
  warentextSt = "";
  
  //baue zwei Strings auf; einen für Menge in Gewicht und einen für Menge in Stueck
  for (Ware i : waren)
  {
	 if (i.getMengeInStueck() == 0 and i.getMengeInGewicht() == 0) 
	 {
		continue;
	 }   
	 else if (i.getMengeInStueck() != 0 and i.getMengeInGewicht() == 0)
	 {
		 warentextSt += Helper::toString(i.getMengeInStueck()) + " Stueck " + i.getWarenGruppeName() + "-" + i.getWarenName() + ". " + i.getKommentar() + "\n";
	 }
	 else if (i.getMengeInStueck() == 0 and i.getMengeInGewicht() != 0)
	 {
		 warentextKg += Helper::toString(i.getMengeInGewicht()) + " kg " + i.getWarenGruppeName() + "-" + i.getWarenName() + ". " + i.getKommentar() + "\n";
	 }
	 else
	 {
		 warentextSt += Helper::toString(i.getMengeInStueck()) + " Stueck " + i.getWarenGruppeName() + "-" + i.getWarenName() + ". " + i.getKommentar() + "\n";
		 warentextKg += Helper::toString(i.getMengeInGewicht()) + " kg " + i.getWarenGruppeName() + "-" + i.getWarenName() + ". " + i.getKommentar() + "\n";
	 }
  };

  //bearbeite Datumsstring
  std::string datum = info.getZieldatum();
  std::replace(datum.begin(), datum.end(), ':', '.');
  //baue den emailText-String auf
  std::string emailText;
  emailText =
  "Absender: " + abs.getName() + "\n" + \
  abs.getAdresse() + "\n\n" + \
  "Empfaenger: " + empf.getName() + "\n" +
  empf.getAdresse() + "\n\n" + \
  "Bestellung fuer " + datum + " " + info.getZielzeit() + "\n\n" + \
  warentextKg + "\n" + \
  warentextSt + "\n" + \
  info.getKommentar() + "\n\n" + \
  "Mit freundlichen Grueszen" + "\n" + \
  abs.getName() + "\n";
  
  //ersetze Kommas in emailText, weil die Thunderbird-CLI da einen Bug hat
  std::replace(emailText.begin(), emailText.end(), ',', ';');

  //baue den Thunderbirdstring auf, der in der Kommandozeile ausgeführt wird. 
  std::string thunderbirdString = "thunderbird -compose to=" + empf.getEmailadresse() + ",subject='Bestellung: " + abs.getName() + "; Datum: " + datum + "',body='" + emailText + "'";
		system(thunderbirdString.c_str());
	
	db.closeDatabase();
}
	
	void Oberflache::generiereWarenGruppe(){
/**
*Warengruppe wird generiert
*/
		
		DB db("db");

		db.insertRecordInWarengruppe(WarenGruppeHinzuEdit -> text().toStdString(), WarenGruppeInfoEdit -> toPlainText().toStdString());
		this -> aktualisiereOberflaeche();
		db.closeDatabase();
	}
	
	void Oberflache::aktualisiereOberflaeche(){	
		disconnect(WarenTW, 0, 0, 0);
		
		DB db("db");

		WareEntfCB -> clear();
		WarenGruppeCB -> clear();
		WarenGruppeEntfCB -> clear();
		WarenTW -> setRowCount(0);
		
		warenGruppeVector.clear();
		warenNameVector.clear();
		warenVector.clear();
		
		warenVector = db.getAlleWaren();
		
		//Vektor aus Strings, WarenGruppe + WarenName
		for(unsigned i3 = 0;i3<warenVector.size();++i3){		
		warenNameVector.push_back(warenVector[i3].getWarenGruppeName() + " " + warenVector[i3].getWarenName());
		}
		
		//Vektor aus Objekten von WarenGruppe
		for(unsigned i4 = 0; i4<db.getAlleWarengruppenNamen().size();++i4){
		warenGruppeVector.push_back(Warengruppe(db.getAlleWarengruppenNamen()[i4], ""));
		}
		
		
		
		//befüllt combo box um waren zu löschen
		for(unsigned i1 = 0;i1<warenNameVector.size();++i1){
			WareEntfCB -> addItem(QString::fromStdString(warenNameVector[i1]));
			std::cout << "WarenNameVector " + warenNameVector[i1]<< std::endl;
		}
		//befüllt combo box um warengruppen zu löschen
			for(unsigned i2 = 0;i2<warenGruppeVector.size();++i2){
				WarenGruppeEntfCB -> addItem(QString::fromStdString(warenGruppeVector[i2].getWarenGruppeName()));
				WarenGruppeCB -> addItem(QString::fromStdString(warenGruppeVector[i2].getWarenGruppeName()));
			}
		//befüllt Haupttabelle
			for(unsigned i3 = 0;i3<warenVector.size();++i3){
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
				WarenTW->setItem(i3, 7, new QTableWidgetItem(QString::fromStdString(warenVector[i3].getKommentar())));
			
				Qt::ItemFlags flags;
			
				flags = WarenTW->item(i3, 0)->flags();
				flags |= Qt::ItemIsSelectable;
				flags &= ~Qt::ItemIsEditable; 
				WarenTW->item(i3, 0)->setFlags(flags);
				
				flags = WarenTW->item(i3, 1)->flags();
				flags |= Qt::ItemIsSelectable;
				flags &= ~Qt::ItemIsEditable; 
				WarenTW->item(i3, 1)->setFlags(flags);
				
				flags = WarenTW->item(i3, 6)->flags();
				flags |= Qt::ItemIsSelectable;
				flags &= ~Qt::ItemIsEditable; 
				WarenTW->item(i3, 6)->setFlags(flags);
				
				WarenTW->sortItems(0);
				
			}
		connect(WarenTW, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(zelleaktualisiert(QTableWidgetItem*)));	
		db.closeDatabase();
	}
	
	void Oberflache::entferneWare(){
		string s = 	WareEntfCB -> currentText().toStdString();
		DB db("db");
		
		for(unsigned i1 = 0;i1<warenVector.size();++i1){
			if( (warenVector[i1].getWarenGruppeName()+ " " + warenVector[i1].getWarenName() ).compare(WareEntfCB -> currentText().toStdString()) == 0){
				//std::cout << "Ware: " + warenVector[i1].getWarenName() << std::endl;
				//std::cout << "WarenGruppe: " + warenVector[i1].getWarenGruppeName() << std::endl;
				db.deleteWare(warenVector[i1].getWarenName(), warenVector[i1].getWarenGruppeName());
				//warenVector.erase(warenVector.begin()+ i1 );
				break;
			}
		}
		// for(unsigned i2 = 0;i2<warenNameVector.size();++i2){
			// //std::cout << warenNameVector[i2] << std::endl;
			// if(warenNameVector[i2].compare(s) == 0){
				// warenNameVector.erase(warenNameVector.begin() + i2 );
				// break;
			// }
		//}
		this -> aktualisiereOberflaeche();
		
		db.closeDatabase();
	}
	
	void Oberflache::zelleaktualisiert(QTableWidgetItem* x){
		disconnect(WarenTW, 0, 0, 0);
		DB db("db");
		
   // void updatePreisProKg(std::string ware, std::string warengruppe, float preis = 0);

   // //ändert einen Wert in einem Datensatz der Tabelle "Ware"
   // void updatePreisProSt(std::string ware, std::string warengruppe, float preis = 0);
   
   // //ändert einen Wert in einem Datensatz der Tabelle "Ware"
   // void updateMengeInSt(std::string ware, std::string warengruppe, float mengeSt = 0);

   // //ändert einen Wert in einem Datensatz der Tabelle "Ware"
   // void updateMengeInKg(std::string ware, std::string warengruppe, float mengeKg = 0);
		
		
		  switch ( x -> column() ) { 
			  
				case 0:  
					warenVector[x -> row()].setWarenGruppeName(x -> text().toStdString());
					break;
				case 1:
					warenVector[x -> row()].setWarenName(x -> text().toStdString());
					break;   
				case 2:
					warenVector[x -> row()].setPreisProGewicht(x -> text().toFloat());
					db.updatePreisProKg(warenVector[x -> row()].getWarenName(), warenVector[x -> row()].getWarenGruppeName(), warenVector[x -> row()].getPreisProGewicht());
                   // db.updatePreisProKg("Lende","Hirsch",7.5);
					break;
				case 3:
					warenVector[x -> row()].setPreisProStueck(x -> text().toFloat());
					db.updatePreisProSt(warenVector[x -> row()].getWarenName(), warenVector[x -> row()].getWarenGruppeName(), warenVector[x -> row()].getPreisProStueck());
					break;
				case 4:
					warenVector[x -> row()].setMengeInGewicht(x -> text().toFloat());
					db.updateMengeInKg(warenVector[x -> row()].getWarenName(), warenVector[x -> row()].getWarenGruppeName(), warenVector[x -> row()].getMengeInGewicht());
					break;
				case 5:
					warenVector[x -> row()].setMengeInStueck(x -> text().toFloat());
					db.updateMengeInSt(warenVector[x -> row()].getWarenName(), warenVector[x -> row()].getWarenGruppeName(), warenVector[x -> row()].getMengeInStueck());
					break;
				case 7:
					warenVector[x -> row()].setKommentar(x -> text().toStdString());
					db.updateKommentar(warenVector[x -> row()].getWarenName(), warenVector[x -> row()].getWarenGruppeName(), warenVector[x -> row()].getKommentar());
					break;
			}		
	
	  
		
		
		this -> aktualisiereOberflaeche();
		
		db.closeDatabase();
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
		db.closeDatabase();
	}
	
	void Oberflache::aktualisiereEinstellungen(){
		// std::cout << "test"<< std::endl;
		
		DB db("db");
		
		// WarenNameHinzuEdit -> text()).toStdString()
		
		// NameAbsenderEdit->insert(QString::fromStdString(ersterAbsender.getName()));
	// AdresseAbsenderEdit->textCursor().insertText(QString::fromStdString(ersterAbsender.getAdresse()));
    // EmailAbsenderEdit->insert(QString::fromStdString(ersterAbsender.getEmailadresse()));
	
    // NameEmpfaengerEdit->insert(QString::fromStdString(ersterEmpfaenger.getName()));
	// AdresseEmpfaengerEdit->textCursor().insertText(QString::fromStdString(ersterEmpfaenger.getAdresse()));
    // EmailEmpfaengerEdit->insert(QString::fromStdString(ersterEmpfaenger.getEmailadresse()));
		
		db.updateErstenWertInAbsenderEmpfaenger("Absender", "Name", NameAbsenderEdit->text().toStdString());
		db.updateErstenWertInAbsenderEmpfaenger("Absender", "Adresse", AdresseAbsenderEdit->toPlainText().toStdString());
		db.updateErstenWertInAbsenderEmpfaenger("Absender", "Emailadresse", EmailAbsenderEdit->text().toStdString());
		
		db.updateErstenWertInAbsenderEmpfaenger("Empfaenger", "Name", NameEmpfaengerEdit->text().toStdString());
		db.updateErstenWertInAbsenderEmpfaenger("Empfaenger", "Adresse", AdresseEmpfaengerEdit->toPlainText().toStdString());
		db.updateErstenWertInAbsenderEmpfaenger("Empfaenger", "Emailadresse", EmailEmpfaengerEdit->text().toStdString());
	}
	
	void Oberflache::aktualisiereZielDatum(QDate d){
		// std::cout << d.toString().toStdString()<< std::endl;
		DB db("db");
		
				std::stringstream tss;
				tss<<(d.day());
				std::string t = tss.str();
				
				std::stringstream mss;
				mss<<(d.month());
				std::string m = mss.str();
				
				std::stringstream jss;
				jss<<(d.year());
				std::string j = jss.str();
		
		db.updateWerteInInfoBestellung("Zieldatum", t + ":" + m + ":" + j);
		
		db.closeDatabase();
	}
	
	
		void Oberflache::aktualisiereZielZeit(QTime t){	
		// std::cout << t.toString().toStdString()<< std::endl;
		
		DB db("db");
		db.updateWerteInInfoBestellung("Zielzeit", t.toString().toStdString());
		
		db.closeDatabase();
		}
		
		void Oberflache::aktualisiereZielKommentar(){	
		// std::cout << "komm"<< std::endl;
		
		DB db("db");
		
		db.updateWerteInInfoBestellung("Kommentar", ZielzeitKommentarEdit->toPlainText().toStdString());
		
		db.closeDatabase();
		}
	
