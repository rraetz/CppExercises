# Set Name of project and language
project(Ex04 LANGUAGES CXX)

# Set cmake version
cmake_minimum_required(VERSION 3.10)

# set build type to Debug/Release
set(CMAKE_BUILD_TYPE "Debug")

# Require threads package
find_package(Threads REQUIRED)

# Create executable using the specified source files
add_executable(${PROJECT_NAME}
    main.cpp
    )

# Define required c++ standard to C++11
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

# Link threading library
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall>
$<$<CXX_COMPILER_ID:MSVC>: /W3>
)
