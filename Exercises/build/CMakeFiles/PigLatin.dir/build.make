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
include CMakeFiles/PigLatin.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PigLatin.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PigLatin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PigLatin.dir/flags.make

CMakeFiles/PigLatin.dir/PigLatin.cpp.o: CMakeFiles/PigLatin.dir/flags.make
CMakeFiles/PigLatin.dir/PigLatin.cpp.o: /home/lekaum/Desktop/Games-C++/Exercises/PigLatin.cpp
CMakeFiles/PigLatin.dir/PigLatin.cpp.o: CMakeFiles/PigLatin.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lekaum/Desktop/Games-C++/Exercises/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PigLatin.dir/PigLatin.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PigLatin.dir/PigLatin.cpp.o -MF CMakeFiles/PigLatin.dir/PigLatin.cpp.o.d -o CMakeFiles/PigLatin.dir/PigLatin.cpp.o -c /home/lekaum/Desktop/Games-C++/Exercises/PigLatin.cpp

CMakeFiles/PigLatin.dir/PigLatin.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PigLatin.dir/PigLatin.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lekaum/Desktop/Games-C++/Exercises/PigLatin.cpp > CMakeFiles/PigLatin.dir/PigLatin.cpp.i

CMakeFiles/PigLatin.dir/PigLatin.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PigLatin.dir/PigLatin.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lekaum/Desktop/Games-C++/Exercises/PigLatin.cpp -o CMakeFiles/PigLatin.dir/PigLatin.cpp.s

# Object files for target PigLatin
PigLatin_OBJECTS = \
"CMakeFiles/PigLatin.dir/PigLatin.cpp.o"

# External object files for target PigLatin
PigLatin_EXTERNAL_OBJECTS =

PigLatin: CMakeFiles/PigLatin.dir/PigLatin.cpp.o
PigLatin: CMakeFiles/PigLatin.dir/build.make
PigLatin: CMakeFiles/PigLatin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lekaum/Desktop/Games-C++/Exercises/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable PigLatin"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PigLatin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PigLatin.dir/build: PigLatin
.PHONY : CMakeFiles/PigLatin.dir/build

CMakeFiles/PigLatin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PigLatin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PigLatin.dir/clean

CMakeFiles/PigLatin.dir/depend:
	cd /home/lekaum/Desktop/Games-C++/Exercises/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lekaum/Desktop/Games-C++/Exercises /home/lekaum/Desktop/Games-C++/Exercises /home/lekaum/Desktop/Games-C++/Exercises/build /home/lekaum/Desktop/Games-C++/Exercises/build /home/lekaum/Desktop/Games-C++/Exercises/build/CMakeFiles/PigLatin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PigLatin.dir/depend

