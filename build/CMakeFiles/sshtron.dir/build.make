# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/grig/Documents/1. Projects/SSHtron"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/grig/Documents/1. Projects/SSHtron/build"

# Include any dependencies generated for this target.
include CMakeFiles/sshtron.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sshtron.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sshtron.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sshtron.dir/flags.make

CMakeFiles/sshtron.dir/src/main.cpp.o: CMakeFiles/sshtron.dir/flags.make
CMakeFiles/sshtron.dir/src/main.cpp.o: /Users/grig/Documents/1.\ Projects/SSHtron/src/main.cpp
CMakeFiles/sshtron.dir/src/main.cpp.o: CMakeFiles/sshtron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/grig/Documents/1. Projects/SSHtron/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sshtron.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sshtron.dir/src/main.cpp.o -MF CMakeFiles/sshtron.dir/src/main.cpp.o.d -o CMakeFiles/sshtron.dir/src/main.cpp.o -c "/Users/grig/Documents/1. Projects/SSHtron/src/main.cpp"

CMakeFiles/sshtron.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sshtron.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/grig/Documents/1. Projects/SSHtron/src/main.cpp" > CMakeFiles/sshtron.dir/src/main.cpp.i

CMakeFiles/sshtron.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sshtron.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/grig/Documents/1. Projects/SSHtron/src/main.cpp" -o CMakeFiles/sshtron.dir/src/main.cpp.s

# Object files for target sshtron
sshtron_OBJECTS = \
"CMakeFiles/sshtron.dir/src/main.cpp.o"

# External object files for target sshtron
sshtron_EXTERNAL_OBJECTS =

sshtron: CMakeFiles/sshtron.dir/src/main.cpp.o
sshtron: CMakeFiles/sshtron.dir/build.make
sshtron: CMakeFiles/sshtron.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/grig/Documents/1. Projects/SSHtron/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sshtron"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sshtron.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sshtron.dir/build: sshtron
.PHONY : CMakeFiles/sshtron.dir/build

CMakeFiles/sshtron.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sshtron.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sshtron.dir/clean

CMakeFiles/sshtron.dir/depend:
	cd "/Users/grig/Documents/1. Projects/SSHtron/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/grig/Documents/1. Projects/SSHtron" "/Users/grig/Documents/1. Projects/SSHtron" "/Users/grig/Documents/1. Projects/SSHtron/build" "/Users/grig/Documents/1. Projects/SSHtron/build" "/Users/grig/Documents/1. Projects/SSHtron/build/CMakeFiles/sshtron.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/sshtron.dir/depend

