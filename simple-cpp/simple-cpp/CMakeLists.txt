cmake_minimum_required(VERSION 3.0)

# Set name, version and language of project
project(simple-cpp VERSION 1.0.0 LANGUAGES CXX)

# Declare dependencies
find_package(Qt5 REQUIRED COMPONENTS Core 3DCore 3DRender 3DInput 3DExtras Widgets)

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
        main.h
        controller.cpp
        controller.h
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



