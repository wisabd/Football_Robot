# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /root/nfs_client/EE212_Rob

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/nfs_client/EE212_Rob/build

# Include any dependencies generated for this target.
include src/CMakeFiles/Test3_Perception.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/Test3_Perception.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/Test3_Perception.dir/flags.make

src/CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.o: src/CMakeFiles/Test3_Perception.dir/flags.make
src/CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.o: ../src/Test3_Perception.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/nfs_client/EE212_Rob/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.o"
	cd /root/nfs_client/EE212_Rob/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.o -c /root/nfs_client/EE212_Rob/src/Test3_Perception.cpp

src/CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.i"
	cd /root/nfs_client/EE212_Rob/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/nfs_client/EE212_Rob/src/Test3_Perception.cpp > CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.i

src/CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.s"
	cd /root/nfs_client/EE212_Rob/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/nfs_client/EE212_Rob/src/Test3_Perception.cpp -o CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.s

src/CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.o.requires:
.PHONY : src/CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.o.requires

src/CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.o.provides: src/CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/Test3_Perception.dir/build.make src/CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.o.provides.build
.PHONY : src/CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.o.provides

src/CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.o.provides.build: src/CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.o

# Object files for target Test3_Perception
Test3_Perception_OBJECTS = \
"CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.o"

# External object files for target Test3_Perception
Test3_Perception_EXTERNAL_OBJECTS =

bin/Test3_Perception: src/CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.o
bin/Test3_Perception: src/CMakeFiles/Test3_Perception.dir/build.make
bin/Test3_Perception: src/CMakeFiles/Test3_Perception.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/Test3_Perception"
	cd /root/nfs_client/EE212_Rob/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Test3_Perception.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/Test3_Perception.dir/build: bin/Test3_Perception
.PHONY : src/CMakeFiles/Test3_Perception.dir/build

src/CMakeFiles/Test3_Perception.dir/requires: src/CMakeFiles/Test3_Perception.dir/Test3_Perception.cpp.o.requires
.PHONY : src/CMakeFiles/Test3_Perception.dir/requires

src/CMakeFiles/Test3_Perception.dir/clean:
	cd /root/nfs_client/EE212_Rob/build/src && $(CMAKE_COMMAND) -P CMakeFiles/Test3_Perception.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/Test3_Perception.dir/clean

src/CMakeFiles/Test3_Perception.dir/depend:
	cd /root/nfs_client/EE212_Rob/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/nfs_client/EE212_Rob /root/nfs_client/EE212_Rob/src /root/nfs_client/EE212_Rob/build /root/nfs_client/EE212_Rob/build/src /root/nfs_client/EE212_Rob/build/src/CMakeFiles/Test3_Perception.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/Test3_Perception.dir/depend

