QT = core testlib

TARGET = tst_sobject
TEMPLATE = app
CONFIG += qt warn_on depend_includepath testcase

include(../../data/testData.pri)
include(../../testConfig.pri)

INCDIR = ../../../src
INCLUDEPATH += $$INCDIR
HEADERS += $$INCDIR/sobject.h $$INCDIR/sdatetime.h $$INCDIR/sassistant.h \
           $$INCDIR/tags.h
SOURCES += $$INCDIR/sobject.cpp $$INCDIR/sdatetime.cpp $$INCDIR/sassistant.cpp

SOURCES += tst_sobject.cpp
