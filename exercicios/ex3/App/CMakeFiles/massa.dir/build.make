# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/leoyt/github/EA872/exercicios/ex3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leoyt/github/EA872/exercicios/ex3/App

# Include any dependencies generated for this target.
include CMakeFiles/massa.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/massa.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/massa.dir/flags.make

CMakeFiles/massa.dir/Models/massa/massa.cpp.o: CMakeFiles/massa.dir/flags.make
CMakeFiles/massa.dir/Models/massa/massa.cpp.o: ../Models/massa/massa.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leoyt/github/EA872/exercicios/ex3/App/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/massa.dir/Models/massa/massa.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/massa.dir/Models/massa/massa.cpp.o -c /home/leoyt/github/EA872/exercicios/ex3/Models/massa/massa.cpp

CMakeFiles/massa.dir/Models/massa/massa.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/massa.dir/Models/massa/massa.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leoyt/github/EA872/exercicios/ex3/Models/massa/massa.cpp > CMakeFiles/massa.dir/Models/massa/massa.cpp.i

CMakeFiles/massa.dir/Models/massa/massa.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/massa.dir/Models/massa/massa.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leoyt/github/EA872/exercicios/ex3/Models/massa/massa.cpp -o CMakeFiles/massa.dir/Models/massa/massa.cpp.s

CMakeFiles/massa.dir/Models/massa/massa.cpp.o.requires:

.PHONY : CMakeFiles/massa.dir/Models/massa/massa.cpp.o.requires

CMakeFiles/massa.dir/Models/massa/massa.cpp.o.provides: CMakeFiles/massa.dir/Models/massa/massa.cpp.o.requires
	$(MAKE) -f CMakeFiles/massa.dir/build.make CMakeFiles/massa.dir/Models/massa/massa.cpp.o.provides.build
.PHONY : CMakeFiles/massa.dir/Models/massa/massa.cpp.o.provides

CMakeFiles/massa.dir/Models/massa/massa.cpp.o.provides.build: CMakeFiles/massa.dir/Models/massa/massa.cpp.o


# Object files for target massa
massa_OBJECTS = \
"CMakeFiles/massa.dir/Models/massa/massa.cpp.o"

# External object files for target massa
massa_EXTERNAL_OBJECTS =

libmassa.a: CMakeFiles/massa.dir/Models/massa/massa.cpp.o
libmassa.a: CMakeFiles/massa.dir/build.make
libmassa.a: CMakeFiles/massa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/leoyt/github/EA872/exercicios/ex3/App/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmassa.a"
	$(CMAKE_COMMAND) -P CMakeFiles/massa.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/massa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/massa.dir/build: libmassa.a

.PHONY : CMakeFiles/massa.dir/build

CMakeFiles/massa.dir/requires: CMakeFiles/massa.dir/Models/massa/massa.cpp.o.requires

.PHONY : CMakeFiles/massa.dir/requires

CMakeFiles/massa.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/massa.dir/cmake_clean.cmake
.PHONY : CMakeFiles/massa.dir/clean

CMakeFiles/massa.dir/depend:
	cd /home/leoyt/github/EA872/exercicios/ex3/App && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leoyt/github/EA872/exercicios/ex3 /home/leoyt/github/EA872/exercicios/ex3 /home/leoyt/github/EA872/exercicios/ex3/App /home/leoyt/github/EA872/exercicios/ex3/App /home/leoyt/github/EA872/exercicios/ex3/App/CMakeFiles/massa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/massa.dir/depend
