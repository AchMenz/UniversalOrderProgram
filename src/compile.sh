#!/bin/bash

#kompiliert das Programm und löscht überflüssige Dateien

qmake -project;
qmake;
make;

rm Makefile moc_* *.pro ui_* *.o

mv ${PWD##*/} executeMe.ec
