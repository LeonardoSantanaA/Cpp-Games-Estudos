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
CMAKE_SOURCE_DIR = /home/lekaum/Desktop/Games-C++/File_IO

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lekaum/Desktop/Games-C++/File_IO/build

# Include any dependencies generated for this target.
include CMakeFiles/FileIO.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/FileIO.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/FileIO.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FileIO.dir/flags.make

CMakeFiles/FileIO.dir/src/FileIO.cpp.o: CMakeFiles/FileIO.dir/flags.make
CMakeFiles/FileIO.dir/src/FileIO.cpp.o: /home/lekaum/Desktop/Games-C++/File_IO/src/FileIO.cpp
CMakeFiles/FileIO.dir/src/FileIO.cpp.o: CMakeFiles/FileIO.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lekaum/Desktop/Games-C++/File_IO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FileIO.dir/src/FileIO.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/FileIO.dir/src/FileIO.cpp.o -MF CMakeFiles/FileIO.dir/src/FileIO.cpp.o.d -o CMakeFiles/FileIO.dir/src/FileIO.cpp.o -c /home/lekaum/Desktop/Games-C++/File_IO/src/FileIO.cpp

CMakeFiles/FileIO.dir/src/FileIO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FileIO.dir/src/FileIO.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lekaum/Desktop/Games-C++/File_IO/src/FileIO.cpp > CMakeFiles/FileIO.dir/src/FileIO.cpp.i

CMakeFiles/FileIO.dir/src/FileIO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FileIO.dir/src/FileIO.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lekaum/Desktop/Games-C++/File_IO/src/FileIO.cpp -o CMakeFiles/FileIO.dir/src/FileIO.cpp.s

# Object files for target FileIO
FileIO_OBJECTS = \
"CMakeFiles/FileIO.dir/src/FileIO.cpp.o"

# External object files for target FileIO
FileIO_EXTERNAL_OBJECTS =

FileIO: CMakeFiles/FileIO.dir/src/FileIO.cpp.o
FileIO: CMakeFiles/FileIO.dir/build.make
FileIO: src/includes/libutils.so
FileIO: CMakeFiles/FileIO.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lekaum/Desktop/Games-C++/File_IO/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable FileIO"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FileIO.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FileIO.dir/build: FileIO
.PHONY : CMakeFiles/FileIO.dir/build

CMakeFiles/FileIO.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FileIO.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FileIO.dir/clean

CMakeFiles/FileIO.dir/depend:
	cd /home/lekaum/Desktop/Games-C++/File_IO/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lekaum/Desktop/Games-C++/File_IO /home/lekaum/Desktop/Games-C++/File_IO /home/lekaum/Desktop/Games-C++/File_IO/build /home/lekaum/Desktop/Games-C++/File_IO/build /home/lekaum/Desktop/Games-C++/File_IO/build/CMakeFiles/FileIO.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FileIO.dir/depend

