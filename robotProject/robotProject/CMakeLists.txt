# Set required CMake standard
cmake_minimum_required(VERSION 3.0)

# Set required C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set name, version and language of project
project(robotProject VERSION 1.0.0 LANGUAGES CXX)

# Define application source files
set(APP_SOURCES
    src/main.cpp
    src/robotics/joint.h
    src/robotics/joint.cpp
    src/robotics/robot.h
    src/robotics/robot.cpp
    src/robotics/cylinder3d.h
    src/robotics/cylinder3d.cpp
    src/robotics/coordinatesystem.h
    src/robotics/coordinatesystem.cpp
    src/robotics/trajectoryplanner.h
    src/robotics/trajectoryplanner.cpp
    src/gui/eulerinput.h
    src/gui/eulerinput.cpp
    src/gui/jointdisplay.h
    src/gui/jointdisplay.cpp
    src/gui/statusmessage.h
    src/gui/statusmessage.cpp
    )

# Define applicaiton include directories
set(APP_INCLUDE_DIRS
    src
    src/robotics
    src/gui
    )

# Display sources of each folder together
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${APP_SOURCES})

# Include directories
include_directories(${APP_INCLUDE_DIRS})

# Declare dependencies
find_package(Qt5 REQUIRED COMPONENTS Core 3DCore 3DRender 3DInput 3DExtras Widgets)
find_package(Threads REQUIRED)
find_library(NLOPT_LIB nlopt)

# Qt Flags
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Set build type to Debug/Release
set(CMAKE_BUILD_TYPE "Debug")

# Add target with sources
add_executable(${PROJECT_NAME} ${APP_SOURCES})

# link the libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::3DCore
    Qt5::3DExtras
    Qt5::3DRender
    Qt5::3DInput
    )
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE nlopt)


# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall>
    $<$<CXX_COMPILER_ID:MSVC>: /W3>
    )

