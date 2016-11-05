QT += core gui qml quick

CONFIG += c++11

DEFINES *= QT_USE_QSTRINGBUILDER

HEADERS += \
    src/sevent.h \
    src/seventptr.h \
    src/tags.h \
    src/stimeline.h \
    src/scalendar.h \
    src/seventdb.h

SOURCES += src/main.cpp \
    src/sevent.cpp \
    src/stimeline.cpp \
    src/scalendar.cpp \
    src/seventdb.cpp

RESOURCES += qml.qrc

DISTFILES += .gitignore \
    README.md \
    LICENSE.md \
    stimeline.doxyfile

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
