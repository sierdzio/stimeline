QT += core gui qml quick quickcontrols2

CONFIG += c++14
#CONFIG += sanitizer sanitize_address

DEFINES *= QT_USE_QSTRINGBUILDER
DEFINES += QTQMLTRICKS_NO_PREFIX_ON_GETTERS

LIBS += -lz
include(3rdParty/quazip/quazip.pri)
include(3rdParty/qt-supermacros/QtSuperMacros.pri)

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
    src/sobjectsortproxymodel.h \
    src/ssave.h

SOURCES += src/main.cpp \
    src/stimeline.cpp \
    src/scalendar.cpp \
    src/sdatetime.cpp \
    src/ssettings.cpp \
    src/customItems/eventtimelineview.cpp \
    src/sobject.cpp \
    src/sobjectmodel.cpp \
    src/sassistant.cpp \
    src/sobjectsortproxymodel.cpp \
    src/ssave.cpp

RESOURCES += qml.qrc \
    defaults.qrc

DISTFILES += \
    README.md \
    LICENSE.md \
    defaults/calendar/dynyghtian.json \
    todo.md \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

OTHER_FILES += \
    .gitignore \
    stimeline.doxyfile \
    exampleData/example1.json \
    3rdParty/quazip/version.txt \
    3rdParty/quazip/COPYING \
    3rdParty/qt-supermacros/LICENSE.md \
    3rdParty/qt-supermacros/README.md

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
