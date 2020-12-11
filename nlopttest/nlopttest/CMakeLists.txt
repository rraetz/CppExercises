# Set Name of project and language
project(try LANGUAGES CXX)

cmake_minimum_required(VERSION 3.0)


#add_library(libnlopt SHARED IMPORTED) # or STATIC instead of SHARED
#set_target_properties(nlopt PROPERTIES
#  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}nlopt-2.6.2/build/libnlopt.so"
#  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}nlopt-2.6.2/build/libnlopt"
#)


# Add target with sources
add_executable(${PROJECT_NAME} main.cpp )

#target_link_libraries(nlopt ${CMAKE_SOURCE_DIR}nlopt-2.6.2/build/libnlopt.so)

# set(CMAKE_FIND_LIBRARY_SUFFIXES .dll ${CMAKE_FIND_LIBRARY_SUFFIXES})

# add inlcude directories (path to nlopt.hpp)
target_include_directories(${PROJECT_NAME} PRIVATE
   $<INSTALL_INTERFACE:nlopt-2.6.2/build>
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/nlopt-2.6.2/build>)

#MESSAGE(${CMAKE_CURRENT_SOURCE_DIR}/nlopt-2.6.2/build)

# find library and save name in NLOPT_LIB
#find_library(NLOPT_LIB nlopt)
find_library(NLOPT_LIB nlopt HINTS ${CMAKE_CURRENT_LIST_DIR}/nlopt-2.6.2/build)
MESSAGE(STATUS " ---------> Found NLOPT Lib: " ${NLOPT_LIB})

# link found library to project
target_link_libraries(${PROJECT_NAME} PRIVATE nlopt)


# Define required c++ standard to C++11
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall -Wextra -pedantic>
$<$<CXX_COMPILER_ID:MSVC>: /W3 /WX>
)


# Copy file to binary directory
#file(COPY ${NLOPT_LIB}
#        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


#find_library(FOOlib libfoo.a PATHS /home/user)
#target_link_libraries(FOOexe /home/user/libfoo.a)
