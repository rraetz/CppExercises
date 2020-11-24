cmake_minimum_required(VERSION 3.5)

project(robotProject LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# Find package Eigen
include_directories(libs/eigen-3.3.8/Eigen)
#find_package (Eigen3 3.3 REQUIRED NO_MODULE)



add_executable(robotProject
    src/main.cpp
    src/widget.cpp
    src/widget.h
    src/widget.ui
    src/utils.h
    src/spaceTransformations.h
    )


target_link_libraries(robotProject PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries (robotProject PRIVATE Eigen3::Eigen)
