# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/cmake/715/bin/cmake

# The command to remove a file.
RM = /snap/cmake/715/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/raphael/Documents/CppExercises/robotProject/robotProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/raphael/Documents/CppExercises/robotProject/build-robotProject-Desktop_Qt_5_12_10_GCC_64bit-Debug

# Include any dependencies generated for this target.
include CMakeFiles/robotProject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/robotProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/robotProject.dir/flags.make

CMakeFiles/robotProject.dir/robotProject_autogen/mocs_compilation.cpp.o: CMakeFiles/robotProject.dir/flags.make
CMakeFiles/robotProject.dir/robotProject_autogen/mocs_compilation.cpp.o: robotProject_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/raphael/Documents/CppExercises/robotProject/build-robotProject-Desktop_Qt_5_12_10_GCC_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/robotProject.dir/robotProject_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/robotProject.dir/robotProject_autogen/mocs_compilation.cpp.o -c /home/raphael/Documents/CppExercises/robotProject/build-robotProject-Desktop_Qt_5_12_10_GCC_64bit-Debug/robotProject_autogen/mocs_compilation.cpp

CMakeFiles/robotProject.dir/robotProject_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robotProject.dir/robotProject_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/raphael/Documents/CppExercises/robotProject/build-robotProject-Desktop_Qt_5_12_10_GCC_64bit-Debug/robotProject_autogen/mocs_compilation.cpp > CMakeFiles/robotProject.dir/robotProject_autogen/mocs_compilation.cpp.i

CMakeFiles/robotProject.dir/robotProject_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robotProject.dir/robotProject_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/raphael/Documents/CppExercises/robotProject/build-robotProject-Desktop_Qt_5_12_10_GCC_64bit-Debug/robotProject_autogen/mocs_compilation.cpp -o CMakeFiles/robotProject.dir/robotProject_autogen/mocs_compilation.cpp.s

CMakeFiles/robotProject.dir/main.cpp.o: CMakeFiles/robotProject.dir/flags.make
CMakeFiles/robotProject.dir/main.cpp.o: /home/raphael/Documents/CppExercises/robotProject/robotProject/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/raphael/Documents/CppExercises/robotProject/build-robotProject-Desktop_Qt_5_12_10_GCC_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/robotProject.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/robotProject.dir/main.cpp.o -c /home/raphael/Documents/CppExercises/robotProject/robotProject/main.cpp

CMakeFiles/robotProject.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robotProject.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/raphael/Documents/CppExercises/robotProject/robotProject/main.cpp > CMakeFiles/robotProject.dir/main.cpp.i

CMakeFiles/robotProject.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robotProject.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/raphael/Documents/CppExercises/robotProject/robotProject/main.cpp -o CMakeFiles/robotProject.dir/main.cpp.s

CMakeFiles/robotProject.dir/controller.cpp.o: CMakeFiles/robotProject.dir/flags.make
CMakeFiles/robotProject.dir/controller.cpp.o: /home/raphael/Documents/CppExercises/robotProject/robotProject/controller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/raphael/Documents/CppExercises/robotProject/build-robotProject-Desktop_Qt_5_12_10_GCC_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/robotProject.dir/controller.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/robotProject.dir/controller.cpp.o -c /home/raphael/Documents/CppExercises/robotProject/robotProject/controller.cpp

CMakeFiles/robotProject.dir/controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robotProject.dir/controller.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/raphael/Documents/CppExercises/robotProject/robotProject/controller.cpp > CMakeFiles/robotProject.dir/controller.cpp.i

CMakeFiles/robotProject.dir/controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robotProject.dir/controller.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/raphael/Documents/CppExercises/robotProject/robotProject/controller.cpp -o CMakeFiles/robotProject.dir/controller.cpp.s

# Object files for target robotProject
robotProject_OBJECTS = \
"CMakeFiles/robotProject.dir/robotProject_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/robotProject.dir/main.cpp.o" \
"CMakeFiles/robotProject.dir/controller.cpp.o"

# External object files for target robotProject
robotProject_EXTERNAL_OBJECTS =

robotProject: CMakeFiles/robotProject.dir/robotProject_autogen/mocs_compilation.cpp.o
robotProject: CMakeFiles/robotProject.dir/main.cpp.o
robotProject: CMakeFiles/robotProject.dir/controller.cpp.o
robotProject: CMakeFiles/robotProject.dir/build.make
robotProject: /home/raphael/Qt5.12.10/5.12.10/gcc_64/lib/libQt5Widgets.so.5.12.10
robotProject: /home/raphael/Qt5.12.10/5.12.10/gcc_64/lib/libQt53DExtras.so.5.12.10
robotProject: /home/raphael/Qt5.12.10/5.12.10/gcc_64/lib/libQt53DRender.so.5.12.10
robotProject: /home/raphael/Qt5.12.10/5.12.10/gcc_64/lib/libQt53DInput.so.5.12.10
robotProject: /home/raphael/Qt5.12.10/5.12.10/gcc_64/lib/libQt5Gamepad.so.5.12.10
robotProject: /home/raphael/Qt5.12.10/5.12.10/gcc_64/lib/libQt53DLogic.so.5.12.10
robotProject: /home/raphael/Qt5.12.10/5.12.10/gcc_64/lib/libQt53DCore.so.5.12.10
robotProject: /home/raphael/Qt5.12.10/5.12.10/gcc_64/lib/libQt5Network.so.5.12.10
robotProject: /home/raphael/Qt5.12.10/5.12.10/gcc_64/lib/libQt5Gui.so.5.12.10
robotProject: /home/raphael/Qt5.12.10/5.12.10/gcc_64/lib/libQt5Core.so.5.12.10
robotProject: CMakeFiles/robotProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/raphael/Documents/CppExercises/robotProject/build-robotProject-Desktop_Qt_5_12_10_GCC_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable robotProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/robotProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/robotProject.dir/build: robotProject

.PHONY : CMakeFiles/robotProject.dir/build

CMakeFiles/robotProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/robotProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/robotProject.dir/clean

CMakeFiles/robotProject.dir/depend:
	cd /home/raphael/Documents/CppExercises/robotProject/build-robotProject-Desktop_Qt_5_12_10_GCC_64bit-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/raphael/Documents/CppExercises/robotProject/robotProject /home/raphael/Documents/CppExercises/robotProject/robotProject /home/raphael/Documents/CppExercises/robotProject/build-robotProject-Desktop_Qt_5_12_10_GCC_64bit-Debug /home/raphael/Documents/CppExercises/robotProject/build-robotProject-Desktop_Qt_5_12_10_GCC_64bit-Debug /home/raphael/Documents/CppExercises/robotProject/build-robotProject-Desktop_Qt_5_12_10_GCC_64bit-Debug/CMakeFiles/robotProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/robotProject.dir/depend
