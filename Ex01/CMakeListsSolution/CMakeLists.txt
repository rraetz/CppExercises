# Set Name of project and language
project(Ex01 LANGUAGES CXX)

# Set Path for the EXE file
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Set cmake version
cmake_minimum_required(VERSION 3.10)

# set build type to Debug/Release
set(CMAKE_BUILD_TYPE "Debug")

# Create executable using the specified source files
add_executable(${PROJECT_NAME}
    Ex01.cpp
    )

# Define required c++ standard to C++11
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall -Wextra -pedantic>
$<$<CXX_COMPILER_ID:MSVC>: /W3 /WX>
)

