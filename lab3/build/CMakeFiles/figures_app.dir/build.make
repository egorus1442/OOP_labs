# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/apple/Downloads/2134f/3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/apple/Downloads/2134f/3/build

# Include any dependencies generated for this target.
include CMakeFiles/figures_app.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/figures_app.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/figures_app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/figures_app.dir/flags.make

CMakeFiles/figures_app.dir/src/main.cpp.o: CMakeFiles/figures_app.dir/flags.make
CMakeFiles/figures_app.dir/src/main.cpp.o: /Users/apple/Downloads/2134f/3/src/main.cpp
CMakeFiles/figures_app.dir/src/main.cpp.o: CMakeFiles/figures_app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/apple/Downloads/2134f/3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/figures_app.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/figures_app.dir/src/main.cpp.o -MF CMakeFiles/figures_app.dir/src/main.cpp.o.d -o CMakeFiles/figures_app.dir/src/main.cpp.o -c /Users/apple/Downloads/2134f/3/src/main.cpp

CMakeFiles/figures_app.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/figures_app.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/apple/Downloads/2134f/3/src/main.cpp > CMakeFiles/figures_app.dir/src/main.cpp.i

CMakeFiles/figures_app.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/figures_app.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/apple/Downloads/2134f/3/src/main.cpp -o CMakeFiles/figures_app.dir/src/main.cpp.s

# Object files for target figures_app
figures_app_OBJECTS = \
"CMakeFiles/figures_app.dir/src/main.cpp.o"

# External object files for target figures_app
figures_app_EXTERNAL_OBJECTS =

figures_app: CMakeFiles/figures_app.dir/src/main.cpp.o
figures_app: CMakeFiles/figures_app.dir/build.make
figures_app: libfigures_lib.a
figures_app: CMakeFiles/figures_app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/apple/Downloads/2134f/3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable figures_app"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/figures_app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/figures_app.dir/build: figures_app
.PHONY : CMakeFiles/figures_app.dir/build

CMakeFiles/figures_app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/figures_app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/figures_app.dir/clean

CMakeFiles/figures_app.dir/depend:
	cd /Users/apple/Downloads/2134f/3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/apple/Downloads/2134f/3 /Users/apple/Downloads/2134f/3 /Users/apple/Downloads/2134f/3/build /Users/apple/Downloads/2134f/3/build /Users/apple/Downloads/2134f/3/build/CMakeFiles/figures_app.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/figures_app.dir/depend
