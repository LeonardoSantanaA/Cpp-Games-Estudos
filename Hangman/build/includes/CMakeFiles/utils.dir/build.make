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
CMAKE_SOURCE_DIR = /home/lekaum/Desktop/Games-C++/Hangman

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lekaum/Desktop/Games-C++/Hangman/build

# Include any dependencies generated for this target.
include includes/CMakeFiles/utils.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include includes/CMakeFiles/utils.dir/compiler_depend.make

# Include the progress variables for this target.
include includes/CMakeFiles/utils.dir/progress.make

# Include the compile flags for this target's objects.
include includes/CMakeFiles/utils.dir/flags.make

includes/CMakeFiles/utils.dir/Utils.cpp.o: includes/CMakeFiles/utils.dir/flags.make
includes/CMakeFiles/utils.dir/Utils.cpp.o: /home/lekaum/Desktop/Games-C++/Hangman/includes/Utils.cpp
includes/CMakeFiles/utils.dir/Utils.cpp.o: includes/CMakeFiles/utils.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lekaum/Desktop/Games-C++/Hangman/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object includes/CMakeFiles/utils.dir/Utils.cpp.o"
	cd /home/lekaum/Desktop/Games-C++/Hangman/build/includes && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT includes/CMakeFiles/utils.dir/Utils.cpp.o -MF CMakeFiles/utils.dir/Utils.cpp.o.d -o CMakeFiles/utils.dir/Utils.cpp.o -c /home/lekaum/Desktop/Games-C++/Hangman/includes/Utils.cpp

includes/CMakeFiles/utils.dir/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utils.dir/Utils.cpp.i"
	cd /home/lekaum/Desktop/Games-C++/Hangman/build/includes && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lekaum/Desktop/Games-C++/Hangman/includes/Utils.cpp > CMakeFiles/utils.dir/Utils.cpp.i

includes/CMakeFiles/utils.dir/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utils.dir/Utils.cpp.s"
	cd /home/lekaum/Desktop/Games-C++/Hangman/build/includes && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lekaum/Desktop/Games-C++/Hangman/includes/Utils.cpp -o CMakeFiles/utils.dir/Utils.cpp.s

# Object files for target utils
utils_OBJECTS = \
"CMakeFiles/utils.dir/Utils.cpp.o"

# External object files for target utils
utils_EXTERNAL_OBJECTS =

includes/libutils.so: includes/CMakeFiles/utils.dir/Utils.cpp.o
includes/libutils.so: includes/CMakeFiles/utils.dir/build.make
includes/libutils.so: includes/CMakeFiles/utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lekaum/Desktop/Games-C++/Hangman/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libutils.so"
	cd /home/lekaum/Desktop/Games-C++/Hangman/build/includes && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
includes/CMakeFiles/utils.dir/build: includes/libutils.so
.PHONY : includes/CMakeFiles/utils.dir/build

includes/CMakeFiles/utils.dir/clean:
	cd /home/lekaum/Desktop/Games-C++/Hangman/build/includes && $(CMAKE_COMMAND) -P CMakeFiles/utils.dir/cmake_clean.cmake
.PHONY : includes/CMakeFiles/utils.dir/clean

includes/CMakeFiles/utils.dir/depend:
	cd /home/lekaum/Desktop/Games-C++/Hangman/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lekaum/Desktop/Games-C++/Hangman /home/lekaum/Desktop/Games-C++/Hangman/includes /home/lekaum/Desktop/Games-C++/Hangman/build /home/lekaum/Desktop/Games-C++/Hangman/build/includes /home/lekaum/Desktop/Games-C++/Hangman/build/includes/CMakeFiles/utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : includes/CMakeFiles/utils.dir/depend

