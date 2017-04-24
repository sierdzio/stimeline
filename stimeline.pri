CONFIG += c++14

# Warning! QStringBuilder can crash your app! See last point here:
# https://www.kdab.com/uncovering-32-qt-best-practices-compile-time-clazy/
DEFINES *= QT_USE_QSTRINGBUILDER
DEFINES += QTQMLTRICKS_NO_PREFIX_ON_GETTERS
QMAKE_CXXFLAGS += -Werror
