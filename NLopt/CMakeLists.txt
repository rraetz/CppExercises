# Set Name of project and language
project(try LANGUAGES CXX)

cmake_minimum_required(VERSION 3.0)

# Add target with sources
add_executable(${PROJECT_NAME} main.cpp )

# set(CMAKE_FIND_LIBRARY_SUFFIXES .dll ${CMAKE_FIND_LIBRARY_SUFFIXES})

# add inlcude directories (path to nlopt.hpp)
target_include_directories(${PROJECT_NAME} PRIVATE
   $<INSTALL_INTERFACE:NLopt/include>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/NLopt/include>)

# find library and save name in NLOPT_LIB
find_library(NLOPT_LIB libnlopt HINTS ${CMAKE_CURRENT_LIST_DIR}/NLopt/bin)
MESSAGE(STATUS " ---------> Found NLOPT Lib: " ${NLOPT_LIB})

# link found library to project
target_link_libraries(${PROJECT_NAME} PRIVATE ${NLOPT_LIB})


# Define required c++ standard to C++11
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall -Wextra -pedantic>
$<$<CXX_COMPILER_ID:MSVC>: /W3 /WX>
)


# Copy file to binary directory
file(COPY ${CMAKE_CURRENT_LIST_DIR}/NLopt/bin/libnlopt.dll
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

