QT += core gui qml quick quickcontrols2

CONFIG += c++14

DEFINES *= QT_USE_QSTRINGBUILDER

HEADERS += \
    src/sevent.h \
    src/tags.h \
    src/stimeline.h \
    src/scalendar.h \
    src/sdatetime.h \
    src/ssettings.h \
    src/seventmodel.h \
    src/sutils.h

SOURCES += src/main.cpp \
    src/sevent.cpp \
    src/stimeline.cpp \
    src/scalendar.cpp \
    src/sdatetime.cpp \
    src/ssettings.cpp \
    src/seventmodel.cpp \
    src/sutils.cpp

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
