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
include src/CMakeFiles/Test2_Servo.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/Test2_Servo.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/Test2_Servo.dir/flags.make

src/CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.o: src/CMakeFiles/Test2_Servo.dir/flags.make
src/CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.o: ../src/Test2_Servo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/nfs_client/EE212_Rob/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.o"
	cd /root/nfs_client/EE212_Rob/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.o -c /root/nfs_client/EE212_Rob/src/Test2_Servo.cpp

src/CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.i"
	cd /root/nfs_client/EE212_Rob/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/nfs_client/EE212_Rob/src/Test2_Servo.cpp > CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.i

src/CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.s"
	cd /root/nfs_client/EE212_Rob/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/nfs_client/EE212_Rob/src/Test2_Servo.cpp -o CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.s

src/CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.o.requires:
.PHONY : src/CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.o.requires

src/CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.o.provides: src/CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/Test2_Servo.dir/build.make src/CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.o.provides.build
.PHONY : src/CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.o.provides

src/CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.o.provides.build: src/CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.o

# Object files for target Test2_Servo
Test2_Servo_OBJECTS = \
"CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.o"

# External object files for target Test2_Servo
Test2_Servo_EXTERNAL_OBJECTS =

bin/Test2_Servo: src/CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.o
bin/Test2_Servo: src/CMakeFiles/Test2_Servo.dir/build.make
bin/Test2_Servo: src/CMakeFiles/Test2_Servo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/Test2_Servo"
	cd /root/nfs_client/EE212_Rob/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Test2_Servo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/Test2_Servo.dir/build: bin/Test2_Servo
.PHONY : src/CMakeFiles/Test2_Servo.dir/build

src/CMakeFiles/Test2_Servo.dir/requires: src/CMakeFiles/Test2_Servo.dir/Test2_Servo.cpp.o.requires
.PHONY : src/CMakeFiles/Test2_Servo.dir/requires

src/CMakeFiles/Test2_Servo.dir/clean:
	cd /root/nfs_client/EE212_Rob/build/src && $(CMAKE_COMMAND) -P CMakeFiles/Test2_Servo.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/Test2_Servo.dir/clean

src/CMakeFiles/Test2_Servo.dir/depend:
	cd /root/nfs_client/EE212_Rob/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/nfs_client/EE212_Rob /root/nfs_client/EE212_Rob/src /root/nfs_client/EE212_Rob/build /root/nfs_client/EE212_Rob/build/src /root/nfs_client/EE212_Rob/build/src/CMakeFiles/Test2_Servo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/Test2_Servo.dir/depend

