cmake_minimum_required(VERSION 3.5)

# Set Name of project and language
project(Ex03 LANGUAGES CXX)

# Define application source files
set(APP_SOURCES
    src/main.cpp
    src/ui/widget.cpp
    src/ui/widget.h
    src/ui/widget.ui
    src/ui/qcustomplot-source/qcustomplot.cpp
    src/ui/qcustomplot-source/qcustomplot.h
    src/ui/ekgwidget.cpp
    src/ui/ekgwidget.h
    src/ui/ekgwidget.ui
    )

# Define applicaiton include directories
set(APP_INCLUDE_DIRS
    src
    src/ui
    src/ui/qcustomplot-source
    )

# Check if variables are assigned correctly (only for debugging)
message("Application source files: " "${APP_SOURCES}")
message("Application include dirs: " "${APP_INCLUDE_DIRS}")

# Make it look like in the exercise PDF (headers and source files displayed together)
# --> However, personally I prefer the separation of header and source files
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${APP_SOURCES})

# Define how to handle Qt targets
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set build type to Debug/Release
set(CMAKE_BUILD_TYPE "Debug")

# Set required C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set required packages
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS PrintSupport REQUIRED)


# Include directories
include_directories(${APP_INCLUDE_DIRS})

# Create executable using the specified source files
add_executable(Ex03 ${APP_SOURCES})

# Link Qt libraries
target_link_libraries(Ex03 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Ex03 PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

# Map custom configuration to release Qt
# --> set up a mapping so that the Release configuration for the Qt imported target is
# used in the COVERAGE CMake configuration.Qt
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")

# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall>
$<$<CXX_COMPILER_ID:MSVC>: /W3>
)
