#!/bin/bash

#kompiliert das Programm und löscht überflüssige Dateien

qmake -project;

sed '$aQMAKE_CXXFLAGS += -std=c++11' src.pro >> src2.pro;
sed '$aLIBS += -lsqlite3' src2.pro >> src3.pro;
rm src.pro;
mv src3.pro src.pro;
rm src2.pro;

qmake;
make;

rm Makefile moc_* *.pro ui_* *.o

mv ${PWD##*/} executeMe.ec
