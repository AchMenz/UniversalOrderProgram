#!/bin/bash

#kompiliert das Programm und löscht überflüssige Dateien

qmake -project;
qmake;
make;

rm *.o Makefile moc_* *.pro ui_*
