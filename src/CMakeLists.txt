cmake_minimum_required(VERSION 3.9...3.12)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(stimeline VERSION 0.0.1
        DESCRIPTION "stimeline - timeline app for writers"
        LANGUAGES CXX)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -fPIC")

# Find the QtWidgets library
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Qml CONFIG REQUIRED)
find_package(Qt5Quick CONFIG REQUIRED)
find_package(Qt5QuickControls2 CONFIG REQUIRED)

include_directories(3rdParty/quazip/quazip)
include_directories(3rdParty/qt-supermacros)
include_directories(customItems)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/quazip)

# Populate a CMake variable with the sources
set(stimeline_SRCS
    main.cpp
    stimeline.cpp
    scalendar.cpp
    sdatetime.cpp
    ssettings.cpp
    customItems/eventtimelineview.cpp
    sobject.cpp
    sobjectmodel.cpp
    sassistant.cpp
    sobjectsortproxymodel.cpp
    ssave.cpp
    stagsmodel.cpp
    splot.cpp
    splotsmodel.cpp
    serasmodel.cpp
    )

# Tell CMake to create the executable
add_executable(stimeline ${stimeline_SRCS} qml.qrc defaults.qrc)

target_compile_features(stimeline PUBLIC cxx_std_14)

# Use modules from Qt 5
target_link_libraries(stimeline Qt5::Core)
target_link_libraries(stimeline Qt5::Gui)
target_link_libraries(stimeline Qt5::Qml)
target_link_libraries(stimeline Qt5::Quick)
target_link_libraries(stimeline Qt5::QuickControls2)
target_link_libraries(stimeline quazip)
