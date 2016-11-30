# UniversalOrderProgram
This program should create lists of orders for little companies and send them via email.

Database: SQlite

Language: C++

Parameter zum Kompilieren (mit CodeLite):

Linker: "-l sqlite3

Compiler "-std=c++11"



# You need 
## .pro-File
In der .pro File von Qmake muss folgendes hinzugefügt werden (unter "# Input"):

LIBS += -lsqlite3

QMAKE_CXXFLAGS += -std=c++11

## packages
sudo apt-get install sqlite3 libsqlite3-dev
