QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

INCDIR = ../../../src
INCLUDEPATH += $$INCDIR
HEADERS += $$INCDIR/sobject.h $$INCDIR/sdatetime.h $$INCDIR/sassistant.h
SOURCES += $$INCDIR/sobject.cpp $$INCDIR/sdatetime.cpp $$INCDIR/sassistant.cpp

SOURCES += SObjectTest.cpp
