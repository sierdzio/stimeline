QT += core gui qml quick quickcontrols2

CONFIG += c++14

DEFINES *= QT_USE_QSTRINGBUILDER

HEADERS += \
    src/tags.h \
    src/stimeline.h \
    src/scalendar.h \
    src/sdatetime.h \
    src/ssettings.h \
    src/customItems/eventtimelineview.h \
    src/sobject.h \
    src/sobjectmodel.h \
    src/sassistant.h \
    src/sobjectsortproxymodel.h

SOURCES += src/main.cpp \
    src/stimeline.cpp \
    src/scalendar.cpp \
    src/sdatetime.cpp \
    src/ssettings.cpp \
    src/customItems/eventtimelineview.cpp \
    src/sobject.cpp \
    src/sobjectmodel.cpp \
    src/sassistant.cpp \
    src/sobjectsortproxymodel.cpp

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
