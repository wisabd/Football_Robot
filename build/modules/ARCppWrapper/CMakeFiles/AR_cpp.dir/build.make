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
include modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/depend.make

# Include the progress variables for this target.
include modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/progress.make

# Include the compile flags for this target's objects.
include modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/flags.make

modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.o: modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/flags.make
modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.o: ../modules/ARCppWrapper/ARToolKitLib.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /root/nfs_client/EE212_Rob/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.o"
	cd /root/nfs_client/EE212_Rob/build/modules/ARCppWrapper && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.o -c /root/nfs_client/EE212_Rob/modules/ARCppWrapper/ARToolKitLib.cpp

modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.i"
	cd /root/nfs_client/EE212_Rob/build/modules/ARCppWrapper && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /root/nfs_client/EE212_Rob/modules/ARCppWrapper/ARToolKitLib.cpp > CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.i

modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.s"
	cd /root/nfs_client/EE212_Rob/build/modules/ARCppWrapper && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /root/nfs_client/EE212_Rob/modules/ARCppWrapper/ARToolKitLib.cpp -o CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.s

modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.o.requires:
.PHONY : modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.o.requires

modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.o.provides: modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.o.requires
	$(MAKE) -f modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/build.make modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.o.provides.build
.PHONY : modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.o.provides

modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.o.provides.build: modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.o

# Object files for target AR_cpp
AR_cpp_OBJECTS = \
"CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.o"

# External object files for target AR_cpp
AR_cpp_EXTERNAL_OBJECTS =

lib/libAR_cpp.a: modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.o
lib/libAR_cpp.a: modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/build.make
lib/libAR_cpp.a: modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../lib/libAR_cpp.a"
	cd /root/nfs_client/EE212_Rob/build/modules/ARCppWrapper && $(CMAKE_COMMAND) -P CMakeFiles/AR_cpp.dir/cmake_clean_target.cmake
	cd /root/nfs_client/EE212_Rob/build/modules/ARCppWrapper && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AR_cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/build: lib/libAR_cpp.a
.PHONY : modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/build

modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/requires: modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/ARToolKitLib.cpp.o.requires
.PHONY : modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/requires

modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/clean:
	cd /root/nfs_client/EE212_Rob/build/modules/ARCppWrapper && $(CMAKE_COMMAND) -P CMakeFiles/AR_cpp.dir/cmake_clean.cmake
.PHONY : modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/clean

modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/depend:
	cd /root/nfs_client/EE212_Rob/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/nfs_client/EE212_Rob /root/nfs_client/EE212_Rob/modules/ARCppWrapper /root/nfs_client/EE212_Rob/build /root/nfs_client/EE212_Rob/build/modules/ARCppWrapper /root/nfs_client/EE212_Rob/build/modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/ARCppWrapper/CMakeFiles/AR_cpp.dir/depend
