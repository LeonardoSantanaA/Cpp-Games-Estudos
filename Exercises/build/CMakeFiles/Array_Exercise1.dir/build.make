# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lekaum/Desktop/Games-C++/Exercises

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lekaum/Desktop/Games-C++/Exercises/build

# Include any dependencies generated for this target.
include CMakeFiles/Array_Exercise1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Array_Exercise1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Array_Exercise1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Array_Exercise1.dir/flags.make

CMakeFiles/Array_Exercise1.dir/exerciseArray1.cpp.o: CMakeFiles/Array_Exercise1.dir/flags.make
CMakeFiles/Array_Exercise1.dir/exerciseArray1.cpp.o: /home/lekaum/Desktop/Games-C++/Exercises/exerciseArray1.cpp
CMakeFiles/Array_Exercise1.dir/exerciseArray1.cpp.o: CMakeFiles/Array_Exercise1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lekaum/Desktop/Games-C++/Exercises/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Array_Exercise1.dir/exerciseArray1.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Array_Exercise1.dir/exerciseArray1.cpp.o -MF CMakeFiles/Array_Exercise1.dir/exerciseArray1.cpp.o.d -o CMakeFiles/Array_Exercise1.dir/exerciseArray1.cpp.o -c /home/lekaum/Desktop/Games-C++/Exercises/exerciseArray1.cpp

CMakeFiles/Array_Exercise1.dir/exerciseArray1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Array_Exercise1.dir/exerciseArray1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lekaum/Desktop/Games-C++/Exercises/exerciseArray1.cpp > CMakeFiles/Array_Exercise1.dir/exerciseArray1.cpp.i

CMakeFiles/Array_Exercise1.dir/exerciseArray1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Array_Exercise1.dir/exerciseArray1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lekaum/Desktop/Games-C++/Exercises/exerciseArray1.cpp -o CMakeFiles/Array_Exercise1.dir/exerciseArray1.cpp.s

# Object files for target Array_Exercise1
Array_Exercise1_OBJECTS = \
"CMakeFiles/Array_Exercise1.dir/exerciseArray1.cpp.o"

# External object files for target Array_Exercise1
Array_Exercise1_EXTERNAL_OBJECTS =

Array_Exercise1: CMakeFiles/Array_Exercise1.dir/exerciseArray1.cpp.o
Array_Exercise1: CMakeFiles/Array_Exercise1.dir/build.make
Array_Exercise1: CMakeFiles/Array_Exercise1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lekaum/Desktop/Games-C++/Exercises/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Array_Exercise1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Array_Exercise1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Array_Exercise1.dir/build: Array_Exercise1
.PHONY : CMakeFiles/Array_Exercise1.dir/build

CMakeFiles/Array_Exercise1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Array_Exercise1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Array_Exercise1.dir/clean

CMakeFiles/Array_Exercise1.dir/depend:
	cd /home/lekaum/Desktop/Games-C++/Exercises/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lekaum/Desktop/Games-C++/Exercises /home/lekaum/Desktop/Games-C++/Exercises /home/lekaum/Desktop/Games-C++/Exercises/build /home/lekaum/Desktop/Games-C++/Exercises/build /home/lekaum/Desktop/Games-C++/Exercises/build/CMakeFiles/Array_Exercise1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Array_Exercise1.dir/depend

