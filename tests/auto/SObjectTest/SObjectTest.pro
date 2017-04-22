QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

include(../../data/testData.pri)
include(../../testConfig.pri)

INCDIR = ../../../src
INCLUDEPATH += $$INCDIR
HEADERS += $$INCDIR/sobject.h $$INCDIR/sdatetime.h $$INCDIR/sassistant.h \
           $$INCDIR/tags.h
SOURCES += $$INCDIR/sobject.cpp $$INCDIR/sdatetime.cpp $$INCDIR/sassistant.cpp

SOURCES += SObjectTest.cpp
