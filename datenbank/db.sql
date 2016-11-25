--
-- File generated with SQLiteStudio v3.1.0 on Do. Okt. 27 11:25:01 2016
--
-- Text encoding used: UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: Warengruppe
DROP TABLE IF EXISTS Warengruppe;

CREATE TABLE Warengruppe (
    ID        INTEGER       PRIMARY KEY ASC AUTOINCREMENT,
    Name      VARCHAR (100) NOT NULL,
    Kommentar VARCHAR (300) 
);


-- Table: Ware
DROP TABLE IF EXISTS Ware;

CREATE TABLE Ware (
    ID             INTEGER       PRIMARY KEY ASC AUTOINCREMENT,
    Warennummer    VARCHAR (50),
    Name           VARCHAR (100),
    Kommentar      VARCHAR (300),
    ID_Warengruppe INTEGER       REFERENCES Warengruppe (ID) 
                                 NOT NULL
);


-- Table: Bestellung
DROP TABLE IF EXISTS Bestellung;

CREATE TABLE Bestellung (
    ID              INTEGER       PRIMARY KEY ASC AUTOINCREMENT,
    Zieldatum       DATE          NOT NULL,
    Zielzeit        TIME,
    Kommentar       VARCHAR (300)
);


-- Table: Bestellung_Detail
DROP TABLE IF EXISTS Bestellung_Detail;

CREATE TABLE Bestellung_Detail (
    ID              INTEGER       PRIMARY KEY ASC AUTOINCREMENT,
    Menge_in_kg     DECIMAL,
    Menge_in_Stueck DECIMAL,
    Bestellpreis    DECIMAL,
    Kommentar       VARCHAR (300),
    ID_Ware         INTEGER       REFERENCES Ware (ID),
    ID_Bestellung   INTEGER       REFERENCES Bestellung (ID)
);


-- Table: Preis_History
DROP TABLE IF EXISTS Preis_History;

CREATE TABLE Preis_History (
    ID               INTEGER PRIMARY KEY ASC AUTOINCREMENT,
    Preis_pro_kg     DECIMAL,
    Preis_pro_Stueck DECIMAL,
    Datum            DATE,
    Aktuell          BOOLEAN NOT NULL,
    ID_Ware          INTEGER REFERENCES Ware (ID) 
                             NOT NULL
);


COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
