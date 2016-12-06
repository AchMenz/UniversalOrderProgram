--
-- File generated with SQLiteStudio v3.1.0 on Mo. Nov. 28 17:18:55 2016
--
-- Text encoding used: UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: Ware
DROP TABLE IF EXISTS Ware;

CREATE TABLE Ware (
    ID           INTEGER NOT NULL
                         PRIMARY KEY AUTOINCREMENT,
    Name         TEXT    NOT NULL,
    Preis_pro_kg DECIMAL,
    Preis_pro_St DECIMAL,
    Kommentar    TEXT,
    Warengruppe  TEXT    REFERENCES Warengruppe (Name) 
                         NOT NULL
);


-- Table: Warengruppe
DROP TABLE IF EXISTS Warengruppe;

CREATE TABLE Warengruppe (
    Name      TEXT NOT NULL
                   PRIMARY KEY
                   UNIQUE,
    Kommentar TEXT
);

-- Table: Empfaenger
DROP TABLE IF EXISTS Empfaenger;

CREATE TABLE Empfaenger (
    Name         TEXT NOT NULL
                      PRIMARY KEY
                      UNIQUE,
    Adresse      TEXT,
    Emailadresse TEXT    NOT NULL
);


-- Table: Absender
DROP TABLE IF EXISTS Absender;

CREATE TABLE Absender (
    Name         TEXT NOT NULL
                      PRIMARY KEY
                      UNIQUE,
    Adresse      TEXT,
    Emailadresse TEXT    NOT NULL
);

INSERT INTO Empfaenger (Name, Emailadresse, Adresse) VALUES ("unbekannt", "unbekannt", "unbekannt");
INSERT INTO Absender (Name, Emailadresse, Adresse) VALUES ("unbekannt", "unbekannt", "unbekannt");

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
