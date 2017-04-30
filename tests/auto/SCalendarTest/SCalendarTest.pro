QT = core testlib

TARGET = tst_sdatetime
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

include(../../testConfig.pri)

INCDIR = ../../../src
INCLUDEPATH += $$INCDIR
HEADERS += $$INCDIR/sdatetime.h $$INCDIR/scalendar.h
SOURCES += $$INCDIR/sdatetime.cpp $$INCDIR/scalendar.cpp

SOURCES += tst_scalendar.cpp
