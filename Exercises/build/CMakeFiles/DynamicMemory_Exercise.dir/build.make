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
include CMakeFiles/DynamicMemory_Exercise.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DynamicMemory_Exercise.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DynamicMemory_Exercise.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DynamicMemory_Exercise.dir/flags.make

CMakeFiles/DynamicMemory_Exercise.dir/exerciseDynamicMemory.cpp.o: CMakeFiles/DynamicMemory_Exercise.dir/flags.make
CMakeFiles/DynamicMemory_Exercise.dir/exerciseDynamicMemory.cpp.o: /home/lekaum/Desktop/Games-C++/Exercises/exerciseDynamicMemory.cpp
CMakeFiles/DynamicMemory_Exercise.dir/exerciseDynamicMemory.cpp.o: CMakeFiles/DynamicMemory_Exercise.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lekaum/Desktop/Games-C++/Exercises/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DynamicMemory_Exercise.dir/exerciseDynamicMemory.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DynamicMemory_Exercise.dir/exerciseDynamicMemory.cpp.o -MF CMakeFiles/DynamicMemory_Exercise.dir/exerciseDynamicMemory.cpp.o.d -o CMakeFiles/DynamicMemory_Exercise.dir/exerciseDynamicMemory.cpp.o -c /home/lekaum/Desktop/Games-C++/Exercises/exerciseDynamicMemory.cpp

CMakeFiles/DynamicMemory_Exercise.dir/exerciseDynamicMemory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DynamicMemory_Exercise.dir/exerciseDynamicMemory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lekaum/Desktop/Games-C++/Exercises/exerciseDynamicMemory.cpp > CMakeFiles/DynamicMemory_Exercise.dir/exerciseDynamicMemory.cpp.i

CMakeFiles/DynamicMemory_Exercise.dir/exerciseDynamicMemory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DynamicMemory_Exercise.dir/exerciseDynamicMemory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lekaum/Desktop/Games-C++/Exercises/exerciseDynamicMemory.cpp -o CMakeFiles/DynamicMemory_Exercise.dir/exerciseDynamicMemory.cpp.s

# Object files for target DynamicMemory_Exercise
DynamicMemory_Exercise_OBJECTS = \
"CMakeFiles/DynamicMemory_Exercise.dir/exerciseDynamicMemory.cpp.o"

# External object files for target DynamicMemory_Exercise
DynamicMemory_Exercise_EXTERNAL_OBJECTS =

DynamicMemory_Exercise: CMakeFiles/DynamicMemory_Exercise.dir/exerciseDynamicMemory.cpp.o
DynamicMemory_Exercise: CMakeFiles/DynamicMemory_Exercise.dir/build.make
DynamicMemory_Exercise: CMakeFiles/DynamicMemory_Exercise.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lekaum/Desktop/Games-C++/Exercises/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DynamicMemory_Exercise"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DynamicMemory_Exercise.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DynamicMemory_Exercise.dir/build: DynamicMemory_Exercise
.PHONY : CMakeFiles/DynamicMemory_Exercise.dir/build

CMakeFiles/DynamicMemory_Exercise.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DynamicMemory_Exercise.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DynamicMemory_Exercise.dir/clean

CMakeFiles/DynamicMemory_Exercise.dir/depend:
	cd /home/lekaum/Desktop/Games-C++/Exercises/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lekaum/Desktop/Games-C++/Exercises /home/lekaum/Desktop/Games-C++/Exercises /home/lekaum/Desktop/Games-C++/Exercises/build /home/lekaum/Desktop/Games-C++/Exercises/build /home/lekaum/Desktop/Games-C++/Exercises/build/CMakeFiles/DynamicMemory_Exercise.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DynamicMemory_Exercise.dir/depend

