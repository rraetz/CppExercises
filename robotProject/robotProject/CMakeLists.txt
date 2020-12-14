cmake_minimum_required(VERSION 3.0)

# Set name, version and language of project
project(robotProject VERSION 1.0.0 LANGUAGES CXX)


# Declare dependencies
find_package(Qt5 REQUIRED COMPONENTS Core 3DCore 3DRender 3DInput 3DExtras Widgets)

# Find package Eigen
#include_directories(libs/eigen-3.3.8/Eigen)
# find_package (Eigen3 3.3 REQUIRED NO_MODULE)

find_library(NLOPT_LIB nlopt)



# Qt Flags
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
# Instruct CMake to get the resources
set(CMAKE_AUTORCC ON)

set(CMAKE_WARN_DEPRECATED FALSE)

# Add target with sources
add_executable(${PROJECT_NAME}
        main.cpp
        joint.h
        robot.h
        utils.h
        cylinder3d.h
        coordinatesystem.h
        trajectoryplanner.h
        eulerinput.h
        jointdisplay.h
        statusmessage.h
    )


# link the qt3d libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::3DCore
    Qt5::3DExtras
    Qt5::3DRender
    Qt5::3DInput
    )

target_link_libraries(${PROJECT_NAME} PRIVATE nlopt)

# Link libs
#if(UNIX)
#    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core PRIVATE Threads::Threads)
#else(UNIX)
#    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core)
#endif(UNIX)

#set(RunCMake_TEST_OPTIONS -Wdev -Wno-deprecated)



# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall>
    $<$<CXX_COMPILER_ID:MSVC>: /W3>
    )



