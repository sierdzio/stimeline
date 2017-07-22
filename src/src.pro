QT += core gui qml quick quickcontrols2

android {
    QT += androidextras
}

LIBS += -lz
include(../stimeline.pri)
include(3rdParty/quazip/quazip.pri)
include(3rdParty/qt-supermacros/QtSuperMacros.pri)
#DEFINES += QT_DEPRECATED_WARNINGS

TARGET = sTimeline

raspberry {
    target.path = /home/pi/Desktop
}

HEADERS += \
    stimeline.h \
    scalendar.h \
    sdatetime.h \
    ssettings.h \
    customItems/eventtimelineview.h \
    sobject.h \
    sobjectmodel.h \
    sassistant.h \
    sobjectsortproxymodel.h \
    ssave.h \
    tags.h \
    stagsmodel.h \
    splot.h \
    splotsmodel.h \
    serasmodel.h

SOURCES += \
    main.cpp \
    stimeline.cpp \
    scalendar.cpp \
    sdatetime.cpp \
    ssettings.cpp \
    customItems/eventtimelineview.cpp \
    sobject.cpp \
    sobjectmodel.cpp \
    sassistant.cpp \
    sobjectsortproxymodel.cpp \
    ssave.cpp \
    stagsmodel.cpp \
    splot.cpp \
    splotsmodel.cpp \
    serasmodel.cpp

RESOURCES += \
    qml.qrc \
    defaults.qrc

DISTFILES += \
    ../README.md \
    ../LICENSE.md \
    ../todo.md \
    defaults/calendar/dynyghtian.json \
    defaults/calendar/gregorian.json \
    android/AndroidManifest.xml \
    android/src/stimeline/SaveIntent.java

OTHER_FILES += \
    ../.gitignore \
    ../stimeline.doxyfile \
    ../.clang-format \
    exampleData/example1.json \
    3rdParty/quazip/version.txt \
    3rdParty/quazip/COPYING \
    3rdParty/qt-supermacros/LICENSE.md \
    3rdParty/qt-supermacros/README.md

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android:!raspberry: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

