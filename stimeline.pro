QT += core gui qml quick

CONFIG += c++11

DEFINES *= QT_USE_QSTRINGBUILDER

HEADERS += \
    src/sevent.h \
    src/seventptr.h \
    src/tags.h \
    src/stimeline.h \
    src/scalendar.h \
    src/seventdb.h \
    src/sdatetime.h \
    src/ssettings.h \
    src/qmlcontroller.h \
    src/seventmodel.h

SOURCES += src/main.cpp \
    src/sevent.cpp \
    src/stimeline.cpp \
    src/scalendar.cpp \
    src/seventdb.cpp \
    src/sdatetime.cpp \
    src/ssettings.cpp \
    src/qmlcontroller.cpp \
    src/seventmodel.cpp

RESOURCES += qml.qrc \
    defaults.qrc

DISTFILES += \
    README.md \
    LICENSE.md \
    defaults/calendar/dynyghtian.json \
    todo.md

OTHER_FILES += \
    .gitignore \
    stimeline.doxyfile \
    exampleData/example1.json

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
